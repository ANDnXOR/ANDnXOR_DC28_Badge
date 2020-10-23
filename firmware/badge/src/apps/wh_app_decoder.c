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
#include "../wh_unlocks.h"
#include "../wh_util.h"
#include "wh_app_flag_util.h"

LOG_MODULE_REGISTER(wh_app_decode, CONFIG_WH_APP_LOG_LEVEL);

static lv_group_t* m_input_group;
static lv_obj_t* m_decode_screen;
static lv_obj_t* m_code_input_ta;
static lv_obj_t* m_code_status_label;
static bool m_app_running = false;
static bool m_app_showing_flag = false;

/**
 * @brief Handle button clicked event by testing the data entered and returning
 * status to the user
 */
static void __event_handler(lv_obj_t* obj, lv_event_t event) {
  if (event == LV_EVENT_CLICKED) {
    // Start a raw flag may delete later
    wh_flag_t flag;
    flag.badge_id = wh_util_badge_id_get();

    const char* input = lv_ta_get_text(m_code_input_ta);
    LOG_DBG("Input '%s'", input);

    // Bunch of if elses to test flags, we could do an array with a for loop???
    if (strcmp(WH_UNLOCK_FLAG_PCB, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_PCB_CMD;
    } else if (strcmp(WH_UNLOCK_FLAG_GITHUB, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_GITHUB_CMD;
    } else if (strcmp(WH_UNLOCK_FLAG_TWITTER_0, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_TWITTER_CMD_0;
    } else if (strcmp(WH_UNLOCK_FLAG_TWITTER_1, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_TWITTER_CMD_1;
    } else if (strcmp(WH_UNLOCK_FLAG_TWITTER_2, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_TWITTER_CMD_2;
    } else if (strcmp(WH_UNLOCK_FLAG_ABOUT, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_ABOUT_CMD;
    } else if (strcmp(WH_UNLOCK_FLAG_VM_EXT_1337, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_VM_EXT_1337_CMD;
    } else if (strcmp(WH_UNLOCK_FLAG_BASFUK, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_BASFUK_CMD;
    } else if (strcmp(WH_UNLOCK_FLAG_POST, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_POST_CMD;
    } else if (strcmp(WH_UNLOCK_FLAG_SB, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_SB_CMD;
    } else if (strcmp(WH_UNLOCK_FLAG_L1, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_L1_CMD;
    } else if (strcmp(WH_UNLOCK_FLAG_KUR3US, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_KUR3US_CMD;
    } else if (strcmp(WH_UNLOCK_FLAG_MISC0, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_MISC0_CMD;
    } else if (strcmp(WH_UNLOCK_FLAG_MISC1, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_MISC1_CMD;
    } else if (strcmp(WH_UNLOCK_FLAG_MISC2, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_MISC2_CMD;
    } else if (strcmp(WH_UNLOCK_FLAG_MISC3, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_MISC3_CMD;
    } else if (strcmp(WH_UNLOCK_FLAG_MISC4, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_MISC4_CMD;
    } else if (strcmp(WH_UNLOCK_FLAG_MISC5, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_MISC5_CMD;
    } else if (strcmp(WH_UNLOCK_FLAG_MISC6, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_MISC6_CMD;
    } else if (strcmp(WH_UNLOCK_FLAG_MISC7, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_MISC7_CMD;
    } else if (strcmp(WH_UNLOCK_FLAG_MISC8, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_MISC8_CMD;
    } else if (strcmp(WH_UNLOCK_FLAG_MISC9, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_MISC9_CMD;
    } else if (strcmp(WH_UNLOCK_FLAG_RICK, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_RICK_CMD;
    } else if (strcmp(WH_UNLOCK_FLAG_JIMB, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_JIMB_CMD;
    } else if (strcmp(WH_UNLOCK_FLAG_BUFF, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_BUFF_CMD;
    } else if (strcmp(WH_UNLOCK_FLAG_EVIL, input) == 0) {
      flag.command = WH_UNLOCK_FLAG_EVIL_CMD;
    } else {
      // Quit early
      lv_label_set_text(m_code_status_label, "CODE INVALID!");
      lv_obj_align(m_code_status_label, NULL, LV_ALIGN_IN_TOP_MID, 0, 95);
      return;
    }

    // Put some garbage-ish data into the flag
    for (uint8_t i = 0; i < WH_FLAG_DATA_LEN; i++) {
      flag.data[i] = flag.command + i;
    }

    // if we got this far, we must have been successful
    // Encode and encrypt the raw flag
    wh_flag_encoded_t encoded_flag;
    wh_flag_encode(&flag, &encoded_flag);
    m_app_showing_flag = true;
    wh_app_flag_util_flag_show(&encoded_flag);
    lv_label_set_text(m_code_status_label, "VALID CODE!");
    lv_obj_align(m_code_status_label, NULL, LV_ALIGN_IN_TOP_MID, 0, 95);
    lv_ta_set_text(m_code_input_ta, "");
  }
}

static void __handler(void* data) {
  m_decode_screen = lv_obj_create(NULL, NULL);
  
  //Apply background
  lv_obj_t* bg = lv_img_create(m_decode_screen, NULL);
  lv_img_set_src(bg, &BG);

  // Header
  lv_obj_t* header = lv_label_create(m_decode_screen, NULL);
  lv_obj_set_style(header, wh_ui_style_header_get());
  lv_label_set_text(header, "Decoder");
  lv_obj_set_width(header, WH_UI_WIDTH);
  lv_obj_align(header, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
  lv_label_set_align(header, LV_ALIGN_CENTER);

  // Footer
  lv_obj_t* footer = lv_label_create(m_decode_screen, NULL);
  lv_obj_set_style(footer, wh_ui_style_header_get());
  lv_label_set_text(footer, "AND!XOR DC28 Badge");
  lv_obj_set_width(footer, WH_UI_WIDTH);
  lv_obj_align(footer, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
  lv_label_set_align(header, LV_ALIGN_CENTER);

  // Create flag input
  lv_obj_t* code_label = lv_label_create(m_decode_screen, NULL);
  lv_label_set_text(code_label, "Codez");
  lv_obj_align(code_label, header, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);

  m_code_status_label = lv_label_create(m_decode_screen, NULL);
  lv_label_set_text(m_code_status_label, "");
  lv_obj_align(m_code_status_label, header, LV_ALIGN_IN_TOP_MID, 0, 90);

  m_code_input_ta = lv_ta_create(m_decode_screen, NULL);
  lv_obj_set_size(m_code_input_ta, 80, 30);
  lv_ta_set_cursor_type(m_code_input_ta, LV_CURSOR_BLOCK);
  lv_ta_set_one_line(m_code_input_ta, true);
  lv_ta_set_text(m_code_input_ta, "");
  lv_ta_set_max_length(m_code_input_ta, 8);
  lv_obj_align(m_code_input_ta, code_label, LV_ALIGN_OUT_BOTTOM_MID,
               WH_UI_MARGIN, WH_UI_MARGIN);

  // Create Submit button
  lv_obj_t* button = lv_btn_create(m_decode_screen, NULL);
  lv_obj_t* button_label = lv_label_create(button, NULL);
  lv_label_set_text(button_label, "Decode");
  lv_btn_set_fit2(button, LV_FIT_TIGHT, LV_FIT_TIGHT);
  lv_obj_align(button, m_code_input_ta, LV_ALIGN_OUT_BOTTOM_MID, 0,
               WH_UI_MARGIN);
  lv_obj_set_event_cb(button, __event_handler);

  // Setup input
  m_input_group = lv_group_create();
  lv_group_add_obj(m_input_group, m_code_input_ta);
  lv_group_add_obj(m_input_group, button);

  // Show the screen
  lv_scr_load(m_decode_screen);
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

  // Done
  lv_obj_del(m_decode_screen);
}

static void __init() {
  LOG_DBG("Init");
}

/**
 * @brief Callback from UI for signals
 */
static wh_ui_signal_result_t __signal_callback(wh_ui_signal_t signal) {
  switch (signal) {
    case wh_ui_signal_key_ready:
      LOG_INF("Something typed");
      return wh_ui_signal_result_okay;
      break;
    case wh_ui_signal_exit:
      // If we're showing the flag, quit that
      if (m_app_showing_flag) {
        wh_app_flag_util_flag_stop();
        m_app_showing_flag = false;
        m_app_running = false;
      }
      // Quit the app
      else {
        m_app_running = false;
      }

      return wh_ui_signal_result_okay;
      break;
  }

  return 0;
}
const app_t app_decoder = {"Decoder", __init, __handler, __signal_callback, NULL};