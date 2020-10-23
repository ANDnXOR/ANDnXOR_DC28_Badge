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
#include "../wh_ui.h"
#include "wh_app_flag_util.h"

LOG_MODULE_REGISTER(wh_app_flag_util, CONFIG_WH_APP_LOG_LEVEL);

static lv_obj_t* m_flag_screen;

/**
 * @brief Show an encoded flag
 */
void wh_app_flag_util_flag_show(wh_flag_encoded_t* p_encoded_flag) {
  m_flag_screen = lv_obj_create(NULL, NULL);

  // Apply background
  lv_obj_t* bg = lv_img_create(m_flag_screen, NULL);
  lv_img_set_src(bg, &BG);

  // Header
  lv_obj_t* header = lv_label_create(m_flag_screen, NULL);
  lv_obj_set_style(header, wh_ui_style_header_get());
  lv_label_set_text(header, "Scoreboard Flag!");
  lv_obj_set_width(header, WH_UI_WIDTH);
  lv_obj_align(header, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
  lv_label_set_align(header, LV_ALIGN_CENTER);

  // Footer
  lv_obj_t* footer = lv_label_create(m_flag_screen, NULL);
  lv_obj_set_style(footer, wh_ui_style_header_get());
  lv_label_set_text(footer, "https://bit.ly/3egadD5");
  lv_obj_set_width(footer, WH_UI_WIDTH);
  lv_obj_align(footer, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
  lv_label_set_align(header, LV_ALIGN_CENTER);

  lv_obj_t* table = lv_table_create(m_flag_screen, NULL);
  lv_table_set_col_cnt(table, 3);
  lv_table_set_row_cnt(table, 3);
  lv_obj_set_width(table, WH_UI_WIDTH);
  lv_obj_align(table, NULL, LV_ALIGN_CENTER, 0, 0);
  lv_table_set_col_width(table, 0, WH_UI_WIDTH / 3);
  lv_table_set_col_width(table, 1, WH_UI_WIDTH / 3);
  lv_table_set_col_width(table, 2, WH_UI_WIDTH / 3);

  /*Make the cells of the first row center aligned */
  lv_table_set_cell_align(table, 0, 0, LV_LABEL_ALIGN_CENTER);
  lv_table_set_cell_align(table, 0, 1, LV_LABEL_ALIGN_CENTER);
  lv_table_set_cell_align(table, 0, 2, LV_LABEL_ALIGN_CENTER);
  lv_table_set_cell_align(table, 1, 0, LV_LABEL_ALIGN_CENTER);
  lv_table_set_cell_align(table, 1, 1, LV_LABEL_ALIGN_CENTER);
  lv_table_set_cell_align(table, 1, 2, LV_LABEL_ALIGN_CENTER);
  lv_table_set_cell_align(table, 2, 0, LV_LABEL_ALIGN_CENTER);
  lv_table_set_cell_align(table, 2, 1, LV_LABEL_ALIGN_CENTER);
  lv_table_set_cell_align(table, 2, 2, LV_LABEL_ALIGN_CENTER);

  /*Make the cells of the first row TYPE = 2 (use `style_cell2`) */
  lv_table_set_cell_type(table, 0, 0, 2);
  lv_table_set_cell_type(table, 0, 1, 2);

  // Show the screen
  lv_scr_load(m_flag_screen);

  // Log the flag
  for (uint8_t i = 0; i < WH_FLAG_SYMBOL_COUNT; i++) {
    lv_table_set_cell_value(table, i / 3, i % 3, p_encoded_flag->symbols[i]);
  }
}

/**
 * @brief Stop showing the flag screen
 */
void wh_app_flag_util_flag_stop() {
  if (m_flag_screen != NULL) {
    lv_obj_del(m_flag_screen);
  }
}