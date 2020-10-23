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
#include <drivers/led_strip.h>
#include <logging/log.h>
#include <random/rand32.h>
#include <stdlib.h>
#include <zephyr.h>

#include "../drivers/bbq10.h"
#include "../gfx/bg.h"
#include "../system.h"
#include "../wh_app.h"
#include "../wh_bling.h"
#include "../wh_fs.h"
#include "../wh_led.h"
#include "../wh_ui.h"
#include "../wh_util.h"

LOG_MODULE_REGISTER(wh_app_bling, CONFIG_WH_APP_LOG_LEVEL);

static bool m_running = false;
static float m_hue = 0.0f;
static int8_t m_led_index = 0;
static uint8_t m_demo_bling = 0;
static uint8_t m_demo_led = 0;
static uint8_t m_demo_duration_seconds = 5;
static uint8_t m_demo_fps = 21;
static uint8_t m_num_led_modes = 6;
static uint8_t m_num_bling_modes = 16;
static int m_demo_frame_count = 0;

typedef enum {
  bling_mode_bender,
  bling_mode_corona,
  bling_mode_custom,
  bling_mode_dance,
  bling_mode_eye,
  bling_mode_flames,
  bling_mode_fry,
  bling_mode_max,
  bling_mode_netscape,
  bling_mode_remember,
  bling_mode_rick,
  bling_mode_toad,
  bling_mode_nyan,
  bling_mode_aeonflux,
  bling_mode_canceled,
  bling_mode_rickmorty,
  __bling_mode_count
} bling_mode_t;

static bling_mode_t m_bling_mode = bling_mode_canceled;

/**
 * @brief Highlight defcon is canceled in artwork
 */
static void __led_mode_canceled(uint8_t frame, void* p_data) {
  // Blink leds 4,5,6
  if (m_led_index >= 3) {
    m_led_index = 0;
  }

  if ((frame % 5) == 0) {
    wh_led_set_all(WH_LED_COLOR_BLACK);
    wh_led_set(m_led_index + 4, WH_LED_COLOR_GREEN);
    wh_led_show();
    m_led_index++;
  }
}

/**
 * @brief Highlight defcon is canceled in artwork
 */
static void __led_mode_corona(uint8_t frame, void* p_data) {
  // Be kinda nice
  if ((frame % 20) == 0) {
    wh_led_set_all(WH_LED_COLOR_WHITE);
    wh_led_show();
  }
}

/**
 * @brief Evil LED bling mode that gives evil grin
 */
static void __led_mode_evil(uint8_t frame, void* p_data) {
  if (m_hue == 0.0) {
    m_hue = m_hue + 0.7;  // Make initial palette blue w/ magenta to match color
                          // scheme of lanyard
  }
  float h_hue = m_hue + 0.15;
  if (h_hue > 1.0) {
    h_hue -= 1.0;
  }
  struct led_rgb highlight = wh_led_hsv_to_rgb(h_hue, 1.0, 1.0);

  wh_led_set_all(wh_led_hsv_to_rgb(m_hue, 1.0, 1.0));

  switch ((m_led_index % 20)) {
    case 0:
      wh_led_set(WH_LED_MOUTH_MIDDLE_INDEX, highlight);
      wh_led_set(WH_LED_EYEBROW_LEFT_INDEX + WH_LED_EYEBROW_COUNT - 1,
                 highlight);
      wh_led_set(WH_LED_EYEBROW_RIGHT_INDEX, highlight);
      break;
    case 1:
      wh_led_set(WH_LED_MOUTH_MIDDLE_INDEX - 1, highlight);
      wh_led_set(WH_LED_EYEBROW_LEFT_INDEX + WH_LED_EYEBROW_COUNT - 2,
                 highlight);
      wh_led_set(WH_LED_EYEBROW_RIGHT_INDEX + 1, highlight);
      break;
    case 2:
      wh_led_set(WH_LED_MOUTH_MIDDLE_INDEX - 2, highlight);
      wh_led_set(WH_LED_MOUTH_MIDDLE_INDEX + 1, highlight);

      wh_led_set(WH_LED_EYEBROW_LEFT_INDEX + WH_LED_EYEBROW_COUNT - 3,
                 highlight);
      wh_led_set(WH_LED_EYEBROW_RIGHT_INDEX + 2, highlight);
      break;
    case 3:
      wh_led_set(WH_LED_MOUTH_MIDDLE_INDEX - 3, highlight);
      break;
    case 4:
      wh_led_set(WH_LED_MOUTH_MIDDLE_INDEX - 4, highlight);
      wh_led_set(WH_LED_MOUTH_MIDDLE_INDEX + 2, highlight);

      break;
  }

  m_led_index = (m_led_index + 1) % 20;
  wh_led_show();
}

static void __led_mode_fade(uint8_t frame, void* p_data) {
  wh_led_set_all(wh_led_hsv_to_rgb(m_hue, 1.0, 1.0));
  wh_led_show();

  m_hue += 0.04;
  if (m_hue > 1) {
    m_hue -= 1;
  }
}

/**
 * @brief Meteor flying by effect, might be difficult with only 13 LEDs
 */
static void __led_mode_meteor(uint8_t frame, void* p_data) {
  // Skip some frames
  // if ((frame % 2) == 0) {
  float v = 1.0f;
  wh_led_set_all(WH_LED_COLOR_BLACK);
  for (int8_t i = m_led_index; i > m_led_index - 5; i--) {
    if (i >= 0) {
      struct led_rgb rgb = wh_led_hsv_to_rgb(0.7, 1.0, v);
      wh_led_set(i, rgb);
      v -= 0.15;
    }
  }
  wh_led_show();
  m_led_index = (m_led_index + 1) % WH_LED_COUNT;
  // }
}

static void __led_mode_rainbow(uint8_t frame, void* p_data) {
  // Calculate step size such that each LED changes hue by less than one hue
  // step giving the effect of movement
  float step = (1.0 / ((float)(WH_LED_COUNT) + 0.3));
  for (uint8_t i = 0; i < WH_LED_COUNT; i++) {
    wh_led_set(i, wh_led_hsv_to_rgb(m_hue, 1.0, 1.0));

    m_hue += step;
    if (m_hue > 1) {
      m_hue -= 1;
    }
  }

  wh_led_show();
}

/**
 * @brief LED sparkle mode, pick a random LED, flash it white for some time,
 * then change it to a random color
 */
static void __led_mode_sparkle(uint8_t frame, void* p_data) {
  // First pick a random LED and flash it white
  if ((frame % 2) == 0) {
    m_led_index = rand() % WH_LED_COUNT;
    wh_led_set(m_led_index, WH_LED_COLOR_WHITE);
  } else {
    wh_led_set(m_led_index, wh_led_hsv_to_rgb(m_hue, 1.0, 1.0));
  }

  // Every nth frame change hue randomly
  if ((frame % 50) == 0) {
    m_hue = (float)(rand() % 100) / 100.0;
  }

  wh_led_show();
}

/**
 * @brief LED & Bling Demo Mode
 */

static void __led_mode_demo(uint8_t frame, void* p_data) {
  // Increment Frame Counter
  m_demo_frame_count++;

  // Cycle LED Modes every duration cycle, then cycle bling once all LED modes
  // have played
  if ((m_demo_frame_count / m_demo_fps) >= m_demo_duration_seconds) {
    m_demo_frame_count = 0;
    if (m_demo_led < m_num_led_modes) {
      m_demo_led++;
      k_sleep(K_MSEC(100));
    } else {  // All LED modes have been cycled, change the animation and
              // recycle LED modes
      m_demo_led = 0;
      if (m_demo_bling < m_num_bling_modes) {
        m_demo_bling++;
        m_bling_mode = m_demo_bling;
        wh_bling_stop();
        k_sleep(K_MSEC(100));
      } else {  // All Animations & LED Modes have been cycled, now start over
        m_demo_bling = 0;
        m_bling_mode = m_demo_bling;
        wh_bling_rager_mode_toggle();  // Toggle Rager Mode
        wh_bling_stop();
        k_sleep(K_MSEC(100));
      }
    }
  }

  switch (m_demo_led) {
    case 0:
      __led_mode_canceled(frame, p_data);
      break;
    case 1:
      __led_mode_corona(frame, p_data);
      break;
    case 2:
      m_hue = 0 + (m_demo_bling *
                   0.1);  // Cycle through all the evil modes palettes
      if (m_hue > 1.0) {
        m_hue -= 1.0;
      }
      __led_mode_evil(frame, p_data);
      break;
    case 3:
      __led_mode_fade(frame, p_data);
      break;
    case 4:
      __led_mode_meteor(frame, p_data);
      break;
    case 5:
      __led_mode_rainbow(frame, p_data);
      break;
    case 6:
      __led_mode_sparkle(frame, p_data);
      break;
  }
}

// Strictly define modes
typedef enum {
  led_mode_canceled,
  led_mode_corona,
  led_mode_evil,
  led_mode_fade,
  led_mode_meteor,
  led_mode_rainbow,
  led_mode_sparkle,
  led_mode_demo
} led_mode_t;
static led_mode_t m_led_mode = led_mode_evil;  // Default mode at boot

// Array of callbacks, order must match modes
static wh_bling_frame_callback_t led_callbacks[] = {
    __led_mode_canceled, __led_mode_corona, __led_mode_evil,
    __led_mode_fade,     __led_mode_meteor, __led_mode_rainbow,
    __led_mode_sparkle,  __led_mode_demo};

/**
 * @brief Bling task that drives LEDs and OLED
 */
static void __bling_task() {
  char* path = NULL;

  //Only run bling if provisioned
  if (!wh_util_is_provisioned()) {
    return;
  }

  while (true) {
    switch (m_bling_mode) {
      case bling_mode_nyan:;
        path = WH_FS_MOUNT_POINT "/BLING_BW/NAYAN.RAW";
        break;
      case bling_mode_bender:
        path = WH_FS_MOUNT_POINT "/BLING_BW/BENDER.RAW";
        break;
      case bling_mode_corona:
        path = WH_FS_MOUNT_POINT "/BLING_BW/CORONA.RAW";
        break;
      case bling_mode_custom:
        path = WH_FS_MOUNT_POINT "/BLING_BW/CUSTOM.RAW";
        break;
      case bling_mode_dance:
        path = WH_FS_MOUNT_POINT "/BLING_BW/DANCE.RAW";
        break;
      case bling_mode_eye:
        path = WH_FS_MOUNT_POINT "/BLING_BW/EYE_L.RAW";
        break;
      case bling_mode_flames:
        path = WH_FS_MOUNT_POINT "/BLING_BW/FLAMES.RAW";
        break;
      case bling_mode_fry:
        path = WH_FS_MOUNT_POINT "/BLING_BW/FRY.RAW";
        break;
      case bling_mode_max:
        path = WH_FS_MOUNT_POINT "/BLING_BW/MAX.RAW";
        break;
      case bling_mode_netscape:
        path = WH_FS_MOUNT_POINT "/BLING_BW/NETSCAPE.RAW";
        break;
      case bling_mode_remember:
        path = WH_FS_MOUNT_POINT "/BLING_BW/REMEMBER.RAW";
        break;
      case bling_mode_rick:
        path = WH_FS_MOUNT_POINT "/BLING_BW/RICK.RAW";
        break;
      case bling_mode_toad:
        path = WH_FS_MOUNT_POINT "/BLING_BW/TOAD.RAW";
        break;
      case bling_mode_aeonflux:
        path = WH_FS_MOUNT_POINT "/BLING_BW/AEONFLUX.RAW";
        break;
      case bling_mode_canceled:
        path = WH_FS_MOUNT_POINT "/BLING_BW/CANCELED.RAW";
        break;
      case bling_mode_rickmorty:
        path = WH_FS_MOUNT_POINT "/BLING_BW/RM.RAW";
        break;
    }

    LOG_DBG("Running %s", path);
    if (wh_bling_play_raw_bw_file(path, led_callbacks[m_led_mode], true, NULL) <
        0) {
      WH_LED_ALL_OFF();
      LOG_ERR("Error while playing bling, cycling");
      m_bling_mode = (m_bling_mode + 1) % __bling_mode_count;
      // Delay before switching modes so we don't cycle constnatly if filesystem is blank
      k_sleep(K_MSEC(500));
    }
    k_sleep(K_MSEC(100));
  }
}

/**
 * @brief Handle running the bling app. Play the bling until no bling mode is
 * set, then quit
 */
static void __handler(void* data) {
  m_running = true;

  lv_obj_t* screen = lv_obj_create(NULL, NULL);

  // Apply background
  lv_obj_t* bg = lv_img_create(screen, NULL);
  lv_img_set_src(bg, &BG);

  // Header
  lv_obj_t* header = lv_label_create(screen, NULL);
  lv_obj_set_style(header, wh_ui_style_header_get());
  lv_label_set_text(header, "Bling");
  lv_obj_set_width(header, WH_UI_WIDTH);
  lv_obj_align(header, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
  lv_label_set_align(header, LV_ALIGN_CENTER);

  // Footer
  lv_obj_t* footer = lv_label_create(screen, NULL);
  lv_obj_set_style(footer, wh_ui_style_header_get());
  lv_label_set_text(footer, "AND!XOR DC28 Badge");
  lv_obj_set_width(footer, WH_UI_WIDTH);
  lv_obj_align(footer, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
  lv_label_set_align(header, LV_ALIGN_CENTER);

  // Instructions
  lv_obj_t* instr0 = lv_label_create(screen, NULL);
  lv_label_set_text(instr0, "Keyboard Changes");
  lv_obj_align(instr0, header, LV_ALIGN_OUT_BOTTOM_MID, 0, 30);
  lv_scr_load(screen);

  lv_obj_t* instr1 = lv_label_create(screen, NULL);
  lv_label_set_text(instr1, "Left half: Screen");
  lv_obj_align(instr1, instr0, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
  lv_scr_load(screen);

  lv_obj_t* instr2 = lv_label_create(screen, NULL);
  lv_label_set_text(instr2, "Right half: LEDs");
  lv_obj_align(instr2, instr1, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
  lv_scr_load(screen);

  lv_obj_t* instr3 = lv_label_create(screen, NULL);
  lv_label_set_text(instr3, "SYM+R: Rager");
  lv_obj_align(instr3, instr2, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
  lv_scr_load(screen);

  wh_ui_lvgl_enable(false);
  while (m_running) {
    k_sleep(K_MSEC(20));
  }
  lv_obj_del(screen);
  wh_ui_lvgl_enable(true);
  LOG_DBG("Bling app exiting");
}

static void __init() {}

/**
 * @brief Callback from UI for signals
 */
static wh_ui_signal_result_t __signal_callback(wh_ui_signal_t signal) {
  switch (signal) {
    case wh_ui_signal_key_ready:;
      char c = wh_ui_last_key_get();
      LOG_DBG("Received %c", c);
      switch (c) {
        // Rager mode is SYM+R which maps to special function 2
        case KEYCODE_FN2:
          wh_bling_rager_mode_toggle();
          break;
        case 'a':
          m_bling_mode = bling_mode_aeonflux;
          m_led_mode = led_mode_evil;
          m_hue = 0.8;
          break;
        case 'b':
          m_bling_mode = bling_mode_nyan;
          break;
        case 'c':
          m_bling_mode = bling_mode_corona;
          m_led_mode = led_mode_corona;
          break;
        case 'd':
          m_bling_mode = bling_mode_dance;
          break;
        case 'e':
          m_bling_mode = bling_mode_eye;
          break;
        case 'f':
          m_bling_mode = bling_mode_flames;
          break;
        case 'g':
          m_bling_mode = bling_mode_toad;
          break;
        case 'i':
          m_led_mode = led_mode_sparkle;
          break;
        case 'j':
          m_led_mode = led_mode_evil;
          m_hue = m_hue + 0.1;
          if (m_hue > 1.0) {
            m_hue -= 1.0;
          }
          break;
        case 'k':
          m_led_mode = led_mode_meteor;
          break;
        case 'o':
          m_led_mode = led_mode_rainbow;
          break;
        case 'p':
          m_led_mode = led_mode_fade;
          break;
        case 'q':
          m_bling_mode = bling_mode_bender;
          m_led_mode = led_mode_demo;
          break;
        case 'r':
          m_bling_mode = bling_mode_rick;
          break;
        case 's':
          m_bling_mode = bling_mode_remember;
          break;
        case 't':
          m_bling_mode = bling_mode_netscape;
          break;
        case 'u':
          m_bling_mode = bling_mode_canceled;
          m_led_mode = led_mode_canceled;
          break;
        case 'v':
          m_bling_mode = bling_mode_bender;
          break;
        case 'w':
          m_bling_mode = bling_mode_fry;
          break;
        case 'x':
          m_bling_mode = bling_mode_custom;
          break;
        case 'y':
          m_bling_mode = bling_mode_rickmorty;
          break;
        case 'z':
          m_bling_mode = bling_mode_max;
          break;
        default:
          break;
      }

      // Reset bling state
      WH_LED_ALL_OFF();
      m_led_index = 0;

      // Stop bling so it restarts into new state
      wh_bling_stop();

      return wh_ui_signal_result_okay;
      break;
    case wh_ui_signal_exit:
      m_running = false;
      return wh_ui_signal_result_okay;
      break;
  }

  return 0;
}

const app_t app_bling = {"Bling", __init, __handler, __signal_callback, NULL};

// Disable bling in test build
#ifndef CONFIG_WH_TEST_BUILD
K_THREAD_DEFINE(bling_task,
                2048,
                __bling_task,
                NULL,
                NULL,
                NULL,
                WH_THREAD_PRIORITY_MEDIUM,
                0,
                1000);
#endif