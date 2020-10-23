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
#include "../wh_flag.h"
#include "../wh_settings.h"
#include "../wh_ui.h"
#include "../wh_util.h"
#include "wh_app_flag_util.h"

#define BRIGHTNESS_STEP 5

LOG_MODULE_REGISTER(wh_app_settings, CONFIG_WH_APP_LOG_LEVEL);

static lv_group_t* m_input_group;
static lv_obj_t* m_settings_screen;
static lv_obj_t* m_name_ta;
static lv_obj_t* m_brightness_slider;
static lv_obj_t * bling_toggle_label;
static lv_obj_t * m_bling_toggle;
static bool m_app_running = false;
bool m_name_change = false;
bool m_bling_toggle_flag = false;

/**
 * @brief Allow toggling of the bling thread
 */
static void _toggle_bling_event_handler(lv_obj_t * obj, lv_event_t event) {
  k_tid_t bling_thread = wh_util_thread_get_by_name("bling_task");

  if(event == LV_EVENT_VALUE_CHANGED) {
    if(m_bling_toggle_flag == false){
      lv_label_set_text(bling_toggle_label, "Resume Bling");
      m_bling_toggle_flag = true;
      k_thread_suspend(bling_thread);
    }
    else{
      lv_label_set_text(bling_toggle_label, "Pause Bling");
      m_bling_toggle_flag = false;
      k_thread_resume(bling_thread);
    }
  }
}

static void __handler(void* data) {
  m_settings_screen = lv_obj_create(NULL, NULL);
  k_tid_t bling_thread = wh_util_thread_get_by_name("bling_task");

  // Apply background
  lv_obj_t* bg = lv_img_create(m_settings_screen, NULL);
  lv_img_set_src(bg, &BG);

  // Header
  lv_obj_t* header = lv_label_create(m_settings_screen, NULL);
  lv_obj_set_style(header, wh_ui_style_header_get());
  lv_label_set_text(header, "Settings");
  lv_obj_set_width(header, WH_UI_WIDTH);
  lv_obj_align(header, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
  lv_label_set_align(header, LV_ALIGN_CENTER);

  // Footer
  lv_obj_t* footer = lv_label_create(m_settings_screen, NULL);
  lv_obj_set_style(footer, wh_ui_style_header_get());
  lv_label_set_text(footer, "Saved upon exit (SYM+Q)");
  lv_obj_set_width(footer, WH_UI_WIDTH);
  lv_obj_align(footer, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
  lv_label_set_align(header, LV_ALIGN_CENTER);

  // Name input
  lv_obj_t* name_label;
  name_label = lv_label_create(m_settings_screen, NULL);
  lv_label_set_text(name_label, "Name");
  lv_obj_align(name_label, header, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
  m_name_ta = lv_ta_create(m_settings_screen, NULL);
  lv_obj_set_size(m_name_ta, 80, 30);
  lv_ta_set_cursor_type(m_name_ta, LV_CURSOR_BLOCK);
  lv_ta_set_one_line(m_name_ta, true);
  lv_ta_set_max_length(m_name_ta, CONFIG_WH_NAME_MAX_LENGTH);
  lv_ta_set_text(m_name_ta, wh_settings_ptr_get()->name);
  lv_obj_align(m_name_ta, name_label, LV_ALIGN_OUT_BOTTOM_MID, 0, WH_UI_MARGIN);

  // Brightness selection
  lv_obj_t* brightness_label;
  brightness_label = lv_label_create(m_settings_screen, NULL);
  lv_label_set_text(brightness_label, "\nBrightness");
  lv_obj_align(brightness_label, m_name_ta, LV_ALIGN_OUT_BOTTOM_MID, 0, WH_UI_MARGIN);
  m_brightness_slider = lv_slider_create(m_settings_screen, NULL);
  LOG_DBG("Brightness value is %d", wh_settings_ptr_get()->brightness);
  lv_slider_set_range(m_brightness_slider, 0, 100 / BRIGHTNESS_STEP);
  lv_slider_set_value(m_brightness_slider, wh_settings_ptr_get()->brightness / BRIGHTNESS_STEP, LV_ANIM_ON);
  lv_obj_align(m_brightness_slider, brightness_label, LV_ALIGN_OUT_BOTTOM_MID, 0, WH_UI_MARGIN);

  //Toggle for bling thread
  m_bling_toggle = lv_btn_create(m_settings_screen, NULL);
  lv_obj_set_event_cb(m_bling_toggle, _toggle_bling_event_handler);
  lv_obj_align(m_bling_toggle, m_brightness_slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
  lv_btn_set_toggle(m_bling_toggle, true);
  lv_btn_toggle(m_bling_toggle);
  bling_toggle_label = lv_label_create(m_bling_toggle, NULL);
  lv_label_set_text(bling_toggle_label, "Pause Bling");
  lv_btn_set_fit2(m_bling_toggle, LV_FIT_TIGHT, LV_FIT_TIGHT);

  // Setup input
  m_input_group = lv_group_create();
  lv_group_add_obj(m_input_group, m_name_ta);
  lv_group_add_obj(m_input_group, m_brightness_slider);
  lv_group_add_obj(m_input_group, m_bling_toggle);

  // Show the screen
  lv_scr_load(m_settings_screen);
  m_app_running = true;
  wh_ui_input_group_set(m_input_group);

  // Enable alternate mode so WASD mapped properly
  wh_ui_input_alt(true);

  // Wait for something
  while (m_app_running) {
    k_sleep(K_MSEC(20));
  }

  // Disable alternate mode
  wh_ui_input_alt(false);

  wh_settings_ptr_get()->brightness =
      lv_slider_get_value(m_brightness_slider) * BRIGHTNESS_STEP;
      
  //Save the name
  const char* new_name = lv_ta_get_text(m_name_ta);
  snprintf(wh_settings_ptr_get()->name, CONFIG_WH_NAME_MAX_LENGTH + 1, "%s",
           new_name);
           
  //Pause bling to avoid read/write to SPI errorz
  k_thread_suspend(bling_thread);

  //Save Settings
  wh_settings_save();

  //Wait a sec...
  k_sleep(100);

  //Resume bling to avoid read/write to SPI errorz
  k_thread_resume(bling_thread);

  // Creat the name change flag
  wh_flag_t flag;
  flag.badge_id = wh_util_badge_id_get();
  flag.command = WH_FLAG_COMMAND_NAME;
  memcpy(flag.data, wh_settings_ptr_get()->name, WH_FLAG_DATA_LEN);

  // Encrypt and encode the flag
  wh_flag_encoded_t encoded_flag;
  wh_flag_encode(&flag, &encoded_flag);

  // Show to the user
  wh_app_flag_util_flag_show(&encoded_flag);

  m_app_running = true;
  while (m_app_running) {
    k_sleep(K_MSEC(100));
  }

  wh_app_flag_util_flag_stop();

  // Done
  m_bling_toggle_flag = false;
  lv_obj_del(m_settings_screen);
}

static void __init() {}

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

const app_t app_settings = {"Settings", __init, __handler, __signal_callback,
                            NULL};