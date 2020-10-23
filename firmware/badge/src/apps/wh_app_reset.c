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
#include <logging/log.h>
#include <lvgl.h>
#include <zephyr.h>

#include "../gfx/bg.h"
#include "../system.h"
#include "../wh_app.h"
#include "../wh_settings.h"
#include "../wh_ui.h"

LOG_MODULE_REGISTER(wh_app_reset, CONFIG_WH_APP_LOG_LEVEL);

static lv_group_t* m_input_group;
static lv_obj_t* m_screen;
static lv_obj_t* m_no_button;
static lv_obj_t* m_yes_button;
static bool m_app_running = false;

/**
 * @brief Handle button clicked event. If yes is clicked reset the badge, if no
 * is clicked, quit this app
 */
static void __event_handler(lv_obj_t* obj, lv_event_t event) {
  if (event == LV_EVENT_CLICKED) {
    if (obj == m_no_button) {
      m_app_running = false;
    } else if (obj == m_yes_button) {
      LOG_INF("Factorying reset selected. Good Bye.");
      wh_settings_reset();
    }
  }
}

static void __handler(void* data) {
  m_screen = lv_obj_create(NULL, NULL);

  // Apply background
  lv_obj_t* bg = lv_img_create(m_screen, NULL);
  lv_img_set_src(bg, &BG);

  // Header
  lv_obj_t* header = lv_label_create(m_screen, NULL);
  lv_obj_set_style(header, wh_ui_style_header_get());
  lv_label_set_text(header, "Factory Reset");
  lv_obj_set_width(header, WH_UI_WIDTH);
  lv_obj_align(header, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
  lv_label_set_align(header, LV_ALIGN_CENTER);

  // Footer
  lv_obj_t* footer = lv_label_create(m_screen, NULL);
  lv_obj_set_style(footer, wh_ui_style_header_get());
  lv_label_set_text(footer, "Storage unaffected on reset");
  lv_obj_set_width(footer, WH_UI_WIDTH);
  lv_obj_align(footer, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
  lv_label_set_align(footer, LV_ALIGN_CENTER);

  // Label to prompt user
  lv_obj_t* label = lv_label_create(m_screen, NULL);
  lv_label_set_text(label, "Reset to defaults?");
  lv_obj_align(label, header, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
  lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);

  // Create No button
  m_no_button = lv_btn_create(m_screen, NULL);
  lv_obj_t* no_button_label = lv_label_create(m_no_button, NULL);
  lv_label_set_text(no_button_label, "No");
  lv_btn_set_fit2(m_no_button, LV_FIT_TIGHT, LV_FIT_TIGHT);
  lv_obj_align(m_no_button, label, LV_ALIGN_OUT_BOTTOM_MID, 0, 18);
  lv_obj_set_event_cb(m_no_button, __event_handler);

  // Create Yes button
  m_yes_button = lv_btn_create(m_screen, NULL);
  lv_obj_t* yes_button_label = lv_label_create(m_yes_button, NULL);
  lv_label_set_text(yes_button_label, "Yes");
  lv_btn_set_fit2(m_yes_button, LV_FIT_TIGHT, LV_FIT_TIGHT);
  lv_obj_align(m_yes_button, m_no_button, LV_ALIGN_OUT_BOTTOM_MID, 0, WH_UI_MARGIN);
  lv_obj_set_event_cb(m_yes_button, __event_handler);

  // Setup input
  m_input_group = lv_group_create();
  lv_group_add_obj(m_input_group, m_no_button);
  lv_group_add_obj(m_input_group, m_yes_button);

  // Show the screen
  lv_scr_load(m_screen);
  m_app_running = true;
  wh_ui_input_group_set(m_input_group);

  // Enable alternate mode so WASD mapped properly
  wh_ui_input_alt(true);

  // Wait for something
  while (m_app_running) {
    k_sleep(K_MSEC(20));
  }

  // Disable alternate mode so WASD mapped properly
  wh_ui_input_alt(false);

  // Done
  lv_obj_del(m_screen);
}

static void __init() {
}

/**
 * @brief Callback from UI for signals
 */
static wh_ui_signal_result_t __signal_callback(wh_ui_signal_t signal) {
  switch (signal) {
    case wh_ui_signal_key_ready:
      return wh_ui_signal_result_okay;
      break;
    case wh_ui_signal_exit:
      m_app_running = false;
      return wh_ui_signal_result_okay;
      break;
  }

  return 0;
}

// Uncomment this to enable the app
const app_t app_reset = {"Factory reset",
                __init,
                __handler,
                __signal_callback,
                NULL};