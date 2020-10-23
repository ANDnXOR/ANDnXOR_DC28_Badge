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
#include "wh_menu.h"

#include <device.h>
#include <drivers/sensor.h>
#include <logging/log.h>
#include <lvgl.h>
#include <stdio.h>
#include <zephyr.h>

#include "autoconf.h"
#include "gfx/bg.h"
#include "wh_app.h"
#include "wh_ui.h"
#include "wh_ui_status.h"

LOG_MODULE_REGISTER(wh_menu, CONFIG_WH_MENU_LOG_LEVEL);

static lv_obj_t* m_lvgl_menu_screen;
static lv_obj_t* m_lvgl_header_label;

// LVGL Input group to use for focus etc
static lv_group_t* m_lvgl_input_group;
LV_FONT_DECLARE(ibm_bios);

/**
 * @brief LVGL event handler for events coming from app list. Handle click
 * events by running the app selected
 */
static void __list_app_btn_event_handler(lv_obj_t* obj, lv_event_t event) {
  if (event == LV_EVENT_CLICKED) {
    LOG_DBG("LV_EVENT_CLICKED");
    app_t* p_app = (app_t*)lv_obj_get_user_data(obj);

    if (p_app == NULL) {
      LOG_ERR("Invalid app data.");
    } else {
      LOG_DBG("Menu running app '%s'", p_app->label);
      wh_app_run(p_app);
      k_sleep(K_MSEC(200));  // Attempt to debounce
    }
  }
}

/**
 * @brief Generate an LVGL list of applications
 */
static void __create_app_list() {
  static lv_style_t style_list_bg;
  lv_style_copy(&style_list_bg, &lv_style_transp_fit);
  style_list_bg.body.opa = 0;
  style_list_bg.body.border.part = LV_BORDER_NONE;

  static lv_style_t style_list_btn_rel;
  lv_style_copy(&style_list_btn_rel, &lv_style_btn_rel);
  style_list_btn_rel.body.opa = 0;
  style_list_btn_rel.body.padding.top = 4;
  style_list_btn_rel.body.padding.bottom = 4;
  style_list_btn_rel.body.border.part = LV_BORDER_NONE;

  // Create list of apps
  lv_obj_t* list_app = lv_list_create(m_lvgl_menu_screen, NULL);
  lv_obj_set_size(list_app, 140, 113);
  lv_obj_align(list_app, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
  // lv_list_set_style(list_app, LV_LIST_STYLE_BG, &style_list_bg);
  // lv_list_set_style(list_app, LV_LIST_STYLE_BTN_REL, &style_list_btn_rel);

  // Register the list object for input
  lv_group_add_obj(m_lvgl_input_group, list_app);
  lv_group_focus_obj(list_app);

  // Add each app to the list
  uint32_t app_count = wh_app_count_get();
  for (uint32_t i = 0; i < app_count; i++) {
    const app_t* p_app = wh_app_get(i);

    lv_obj_t* p_btn_app =
        lv_list_add_btn(list_app, LV_SYMBOL_FILE, p_app->label);
    lv_obj_set_event_cb(p_btn_app, __list_app_btn_event_handler);
    lv_obj_set_user_data(p_btn_app, (void *)p_app);
  }
}

/**
 * @brief LVGL task to run an app later
 */
void __run_first_app_later_task(lv_task_t* task) {
  // Run first app by default
  if (wh_app_count_get() > 0) {
    const app_t* p_app = wh_app_get(0);
    LOG_DBG("Running first app by default '%s'", p_app->label);
    wh_app_run(p_app);
  }
}

/**
 * @brief Initialize the menu. Create the LVGL objects.
 */
void wh_menu_init() {
  // Set theme for LVGL to use from here on out
  lv_theme_t* th = lv_theme_night_init(210, &ibm_bios);
  th->style.scr->body.grad_color = LV_COLOR_BLACK;
  th->style.scr->body.main_color = LV_COLOR_BLACK;
  lv_theme_set_current(th);

  m_lvgl_menu_screen = lv_obj_create(NULL, NULL);
  m_lvgl_input_group = lv_group_create();

  th->style.panel->text.font = &ibm_bios;

  //Apply background
  lv_obj_t* bg = lv_img_create(m_lvgl_menu_screen, NULL);
  lv_img_set_src(bg, &BG);

  // Create header label for menu
  m_lvgl_header_label = lv_label_create(m_lvgl_menu_screen, NULL);
  lv_label_set_recolor(m_lvgl_header_label, true);
  char buffer[128];
  int32_t voltage = wh_ui_status_voltage_get();
  if (voltage < 0 || voltage > 60) {
    sprintf(buffer, "#ffffff AND!XOR#  #ff0000 %s#", LV_SYMBOL_WARNING);
  } else if (voltage < 10) {
    sprintf(buffer, "#ffffff AND!XOR#  #00ff00 %s#", LV_SYMBOL_USB);
  } else if (voltage < 30) {
    sprintf(buffer, "#ffffff AND!XOR#  #ff0000 %s#", LV_SYMBOL_BATTERY_EMPTY);
  } else if (voltage < 33) {
    sprintf(buffer, "#ffffff AND!XOR#  #ff9900 %s#", LV_SYMBOL_BATTERY_1);
  } else if (voltage < 37) {
    sprintf(buffer, "#ffffff AND!XOR#  #00ff00 %s#", LV_SYMBOL_BATTERY_2);
  } else if (voltage < 40) {
    sprintf(buffer, "#ffffff AND!XOR#  #00ff00 %s#", LV_SYMBOL_BATTERY_3);
  } else {
    sprintf(buffer, "#ffffff AND!XOR#  #00ff00 %s#", LV_SYMBOL_BATTERY_FULL);
  }
  lv_label_set_text(m_lvgl_header_label, buffer);
  lv_obj_align(m_lvgl_header_label, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

  lv_obj_set_style(m_lvgl_header_label, wh_ui_style_header_get());

  // Add list of apps
  __create_app_list();

  // Bring menu to the foreground
  lv_scr_load(m_lvgl_menu_screen);
  // Let user control it
  wh_ui_input_group_set(m_lvgl_input_group);

  // Schedule running first app later
  lv_task_t* task =
      lv_task_create(__run_first_app_later_task, 1500, LV_TASK_PRIO_MID, NULL);
  lv_task_once(task);
}

/**
 * @brief Brings menu to foreground
 */
void wh_menu_show() {
  // Bring menu to the foreground
  lv_scr_load(m_lvgl_menu_screen);
  // Let user control it
  wh_ui_input_group_set(m_lvgl_input_group);
}

/**
 * @brief Handle signals from UI
 */
wh_ui_signal_result_t wh_menu_signal_callback(wh_ui_signal_t signal) {
  LOG_DBG("Received %s", wh_ui_signal_decode(signal));
  switch (signal) {
    case wh_ui_signal_key_ready:
      LOG_DBG("KEY READY");
      return wh_ui_signal_result_okay;
      break;
    case wh_ui_signal_exit:
      return wh_ui_signal_result_denied;
      break;
  }

  return wh_ui_signal_result_not_supported;
}