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
#include "../wh_ui.h"

LOG_MODULE_REGISTER(wh_app_about, CONFIG_WH_APP_LOG_LEVEL);

#define TITLE_HEIGHT 16

// LVGL Input group to use for focus etc
static lv_group_t* m_lvgl_input_group;
static bool m_app_running = false;

static void __handler(void* data) {
  m_lvgl_input_group = lv_group_create();
  lv_obj_t* screen = lv_obj_create(NULL, NULL);

  // Apply background
  lv_obj_t* bg = lv_img_create(screen, NULL);
  lv_img_set_src(bg, &BG);

  //Header
  lv_obj_t* title = lv_label_create(screen, NULL);
  lv_obj_set_style(title, wh_ui_style_header_get());
  lv_label_set_text(title, "About");
  lv_obj_align(title, screen, LV_ALIGN_IN_TOP_MID, 0, 0);
  lv_label_set_align(title, LV_LABEL_ALIGN_LEFT);

  // Footer
  lv_obj_t* footer = lv_label_create(screen, NULL);
  lv_obj_set_style(footer, wh_ui_style_header_get());
  lv_label_set_text(footer, "AND!XOR DC28 Badge");
  lv_obj_set_width(footer, WH_UI_WIDTH);
  lv_obj_align(footer, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
  lv_label_set_align(title, LV_ALIGN_CENTER);

  //About Box
  lv_obj_t* about = lv_ta_create(screen, NULL);
  lv_ta_set_text(about,
                 "FW " VERSION "\n" BUILD_TIMESTAMP
                 "\n"
                 "\n"
                 "Thanks to all the hackers & philanthropists that helped us bring this badge project together.\n\n"
                 "Hugs to our sponsor frendz at Urbane Security, Penguin, & InspectAR\n\n"
                 "Hax0r contributers to this year's project: Doc Kur3us AletheDenis WillCaruana\n\n"
                 "AND!XOR: Zapp Hyr0n Bender 8Bit Cr4bf04m F4nci3\n\n"
                 "Thank you @arturo182 for your Blackberry Q10 research!\n\n"
                 "Thank you Paladin-t (Tony Wang) for MyBasic! https://github.com/paladin-t/\n\n"
                 "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
                 "UC7xzZ"
                 );
  lv_ta_set_cursor_pos(about, 0);
  lv_obj_set_size(about, WH_UI_WIDTH, 95);
  lv_obj_align(about, NULL, LV_ALIGN_IN_TOP_MID, 0, TITLE_HEIGHT);
  lv_group_add_obj(m_lvgl_input_group, about);

  wh_ui_input_group_set(m_lvgl_input_group);

  // Show the screen
  lv_scr_load(screen);
  m_app_running = true;

  // Wait for something
  while (m_app_running) {
    k_sleep(K_MSEC(20));
  }

  // Done
  lv_obj_del(screen);
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

const app_t app_about = {"About", __init, __handler, __signal_callback, NULL};