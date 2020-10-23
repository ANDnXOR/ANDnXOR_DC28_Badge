/*****************************************************************************
 * Made with beer and late nights in California.
 *
 * (C) Copyright 2017-2020 AND!XOR LLC (https://andnxor.com/).
 *
 * PROPRIETARY AND CONFIDENTIAL UNTIL AUGUST 11th, 2020 then,
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ADDITIONALLY:
 * If you find this source code useful in anyway, use it in another electronic
 * conference badge, or just think it's neat. Consider buying us a beer
 * (or two) and/or a badge (or two). We are just as obsessed with collecting
 * badges as we are in making them.
 *
 * Contributors:
 * 	@andnxor
 * 	@zappbrandnxor
 * 	@hyr0n1
 * 	@bender_andnxor
 * 	@lacosteaef
 *  @f4nci3
 *  @Cr4bf04m
 *****************************************************************************/
#include "wh_ui.h"

#include <display/cfb.h>
#include <logging/log.h>
#include <lvgl.h>
#include <stdio.h>
#include <zephyr.h>

#include "cfb_font_ibm.h"
#include "drivers/bbq10.h"
#include "system.h"
#include "wh_menu.h"

LOG_MODULE_REGISTER(UI, CONFIG_WH_UI_LOG_LEVEL);

// UI key handling state
static wh_ui_signal_callback_t m_curr_signal_callback = wh_menu_signal_callback;

// LVGL objects
static struct device* m_lvgl_display_dev;

// Common LVGL Styles
static lv_style_t m_lvgl_style_header;

// Keyboard and input
static lv_indev_t* m_lvgl_input_keyboard;

// Flag to determine if LVGL is to be used
static bool m_input_lvgl_enabled = true;
static bool m_input_lvgl_mode_alt = false;
static char m_curr_key = 0;

// Flag for error window
static bool m_error_window_close = false;

// Tracker for debouncing UI signaler
static uint32_t m_last_signal_ms = 0;

/**
 * @brief Initialize the "left" OLED
 */
static void __oled_init() {
  struct device* dev = device_get_binding("SSD1306");
  if (dev == NULL) {
    LOG_ERR("Unable to load SSD1306");
    return;
  }

  if (cfb_framebuffer_init(dev)) {
    LOG_ERR("Unable to init framebuffer");
    return;
  }

  cfb_framebuffer_clear(dev, true);
  uint8_t w, h;
  for (uint8_t i = 0; i < cfb_get_numof_fonts(dev); i++) {
    cfb_get_font_size(dev, i, &w, &h);
    LOG_DBG("Font[%d] size: %d,%d", i, w, h);
  }
}

/**
 * @brief Initialize the "right" color TFT
 */
static void __tft_init() {
  struct device* dev = device_get_binding("ST7735");
  if (dev == NULL) {
    LOG_ERR("Unable to load ST7735");
    return;
  }

  display_set_orientation(dev, DISPLAY_ORIENTATION_ROTATED_270);

  m_lvgl_display_dev = device_get_binding(CONFIG_LVGL_DISPLAY_DEV_NAME);

  if (m_lvgl_display_dev == NULL) {
    LOG_ERR("device not found. Cannot initialize TFT UI");
    return;
  }
}

/**
 * @brief LVGL callback to the keyboard. The menu uses W A S D keys so we must
 * translate to what LVGL understands
 */
static bool __lvgl_keyboard_read(lv_indev_drv_t* drv, lv_indev_data_t* data) {
  bool key_ready = bbq10_ready();
  if (key_ready) {
    char c = bbq10_getc();
    k_sleep(50);
    switch (c) {
      case KEYCODE_UP:
        LOG_DBG("UP");
        if (m_input_lvgl_mode_alt) {
          data->key = LV_KEY_PREV;
        } else {
          data->key = LV_KEY_UP;
        }
        break;
      case KEYCODE_LEFT:
        LOG_DBG("LEFT");
        data->key = LV_KEY_LEFT;
        break;
      case KEYCODE_DOWN:
        LOG_DBG("DOWN");
        if (m_input_lvgl_mode_alt) {
          data->key = LV_KEY_NEXT;
        } else {
          data->key = LV_KEY_DOWN;
        }
        break;
      case KEYCODE_RIGHT:
        LOG_DBG("RIGHT");
        data->key = LV_KEY_RIGHT;
        break;
      case KEYCODE_ENTER:
        LOG_DBG("ENTER");
        data->key = LV_KEY_ENTER;
        break;
      case KEYCODE_FN1:
        LOG_DBG("FN1");
        data->key = 'e';
        break;
      case KEYCODE_FN2:
        LOG_DBG("FN2");
        data->key = 'r';
        break;

      // Key combination to quit or go back has been pressed, signal current app
      case KEYCODE_BACK:
        LOG_DBG("BACK");
        if (m_curr_signal_callback) {
          LOG_DBG("Signalling app to exit");
          m_curr_signal_callback(wh_ui_signal_exit);
          // Hide the key from LVGL since we handled it through signaling
          key_ready = false;
        }
        break;
      default:
        data->key = c;
        LOG_DBG("Passing key '%c' [%d] to LVGL", c, c);
        break;
    }
  }

  if (key_ready) {
    data->state = LV_INDEV_STATE_PR;
  } else {
    data->state = LV_INDEV_STATE_REL;
  }

  key_ready = false;

  return false;
}

/**
 * @brief Primary UI task
 * Responsible for:
 *   routing signals to menu and/or app(s)
 *   Updating LVGL when appropriate
 */
static void __ui_task() {
  while (1) {
    k_mutex_lock(&g_mutex_ui, K_FOREVER);
    if (m_input_lvgl_enabled) {
      lv_task_handler();
    }

    // Manually process key presses and signal app
    else {
      bool key_ready = bbq10_ready();

      if (key_ready) {
        // If key is ready get it (which also clears ready state in keyboard
        // driver)
        char c = bbq10_getc();

        // Debounce UI Signaler
        if ((k_uptime_get_32() - m_last_signal_ms) >= 500) {
          m_last_signal_ms = k_uptime_get_32();

          // Back has special meaning
          if (c == KEYCODE_BACK) {
            LOG_DBG("Signalling app to exit");
            m_curr_signal_callback(wh_ui_signal_exit);
          } else {
            m_curr_key = c;
            LOG_DBG("Passing key '%c' [%d] to signal router", c, c);
            m_curr_signal_callback(wh_ui_signal_key_ready);
          }
        }
      }
      k_sleep(K_MSEC(50));
    }
    k_mutex_unlock(&g_mutex_ui);
    k_sleep(K_MSEC(5));
  }
}

/**
 * @brief Clear the UI
 */
void wh_ui_clear() {
  struct device* dev = device_get_binding("SSD1306");
  if (dev == NULL) {
    LOG_ERR("Unable to load SSD1306");
    return;
  }

  cfb_framebuffer_clear(dev, true);
}

/**
 * @brief Get a pointer to the shared style for window headers
 */
lv_style_t* wh_ui_style_header_get() {
  return &m_lvgl_style_header;
}

/**
 * @brief Signal handler for error window
 */
static wh_ui_signal_result_t __window_error_callback(wh_ui_signal_t signal) {
  // Handle signals while error window is showing. Set close flag on enter or
  // SYM+Q
  switch (signal) {
    case wh_ui_signal_key_ready:
      if (wh_ui_last_key_get() == KEYCODE_ENTER) {
        m_error_window_close = true;
      }
      break;
    case wh_ui_signal_exit:
      m_error_window_close = true;
      break;
  }

  return 0;
}

/**
 * @brief Generic error popup window
 */
void wh_ui_window_error(char* error) {
  /*Create a window*/
  lv_obj_t* win = lv_win_create(lv_scr_act(), NULL);
  lv_win_set_title(win, "ERROR"); /*Set the title*/
  lv_win_set_sb_mode(win, LV_SB_MODE_OFF);

  /*Add some dummy content*/
  lv_obj_t* txt = lv_label_create(win, NULL);
  lv_label_set_long_mode(txt, LV_LABEL_LONG_BREAK);
  lv_obj_set_width(txt, WH_UI_WIDTH);
  lv_label_set_text(txt, error);

  m_error_window_close = false;
  // Temporarily re-reroute our signal handler to the window
  wh_ui_signal_callback_t last_signal_callback =
      wh_ui_signal_callback_set(__window_error_callback);

  while (!m_error_window_close) {
    k_sleep(K_MSEC(10));
  }

  wh_ui_signal_callback_set(last_signal_callback);
  lv_obj_del(win);
  k_sleep(K_MSEC(200));
}

/**
 * @brief Initialize the UI
 */
void wh_ui_init() {
  __oled_init();
  __tft_init();

  // Create and register our keyboard handler with LVGL
  LOG_DBG("Initializing Keyboard Device");
  lv_indev_drv_t keyboard;
  lv_indev_drv_init(&keyboard);
  keyboard.type = LV_INDEV_TYPE_KEYPAD;
  keyboard.read_cb = __lvgl_keyboard_read;
  m_lvgl_input_keyboard = lv_indev_drv_register(&keyboard);

  // Setup common style
  lv_style_copy(&m_lvgl_style_header, &lv_style_plain_color);
  m_lvgl_style_header.body.grad_color = LV_COLOR_BLACK;
  m_lvgl_style_header.body.main_color = LV_COLOR_BLACK;
  m_lvgl_style_header.text.color = LV_COLOR_WHITE;
  m_lvgl_style_header.text.font = &lv_font_roboto_12;

  LOG_DBG("UI Initialized");
}

/**
 * @brief Change the current input group
 */
void wh_ui_input_group_set(lv_group_t* group) {
  lv_indev_set_group(m_lvgl_input_keyboard, group);
}

/**
 * @brief Enable or disable LVGL
 */
void wh_ui_lvgl_enable(bool lvgl) {
  m_input_lvgl_enabled = lvgl;
}

/**
 * @brief Enable or disable alternate input mode (up / down mapped to prev /
 * next)
 */
void wh_ui_input_alt(bool alt) {
  m_input_lvgl_mode_alt = alt;
}

/**
 * @brief Get the last key pressed by the user as an ASCII code
 */
char wh_ui_last_key_get() {
  return m_curr_key;
}

/**
 * @brief Set the current signal callback
 * @return The previous callback
 */
wh_ui_signal_callback_t wh_ui_signal_callback_set(
    wh_ui_signal_callback_t callback) {
  wh_ui_signal_callback_t temp = m_curr_signal_callback;
  m_curr_signal_callback = callback;
  return temp;
}

/**
 * @brief Decode a signal to text
 */
char* wh_ui_signal_decode(wh_ui_signal_t signal) {
  switch (signal) {
    case wh_ui_signal_key_ready:
      return "SIGNAL_KEY_READY";
      break;
    case wh_ui_signal_exit:
      return "SIGNAL_EXIT";
      break;
  }

  return "SIGNAL_UNKNOWN";
}

K_THREAD_DEFINE(ui_task,
                1400,
                __ui_task,
                NULL,
                NULL,
                NULL,
                WH_THREAD_PRIORITY_MEDIUM,
                0,
                1000);
