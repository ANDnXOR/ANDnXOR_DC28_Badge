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
#include <fs/fs.h>
#include <logging/log.h>
#include <stdarg.h>
#include <stdio.h>
#include <zephyr.h>

#include "../gfx/bg.h"
#include "../lib/mybasic/my_basic.h"
#include "../system.h"
#include "../wh_app.h"
#include "../wh_bling.h"
#include "../wh_fs.h"
#include "../wh_led.h"
#include "../wh_shell.h"
#include "../wh_ui.h"
#include "wh_app_basic_util.h"

LOG_MODULE_REGISTER(wh_app_basic_edit, CONFIG_WH_APP_LOG_LEVEL);

static bool m_running = false;

// Global storage of base file name, this should be null unless the handler
// thread is to run a file This should decouple BASIC from the UI
// static char m_bas_file[WH_PATH_MAX_LEN];

static lv_obj_t* m_lvgl_edit_screen;
static lv_obj_t* m_lvgl_file_contents;

// LVGL Input group to use for focus etc
static lv_group_t* m_lvgl_input_group;

/**
 * @brief LVGL event handler for events coming from app list. Handle click
 * events by running the BAS file selected
 */
// static void __list_bas_btn_event_handler(lv_obj_t* obj, lv_event_t event) {
//   if (!obj) {
//     LOG_ERR("Invalid LVGL object");
//     return;
//   }

//   if (!obj->user_data) {
//     LOG_ERR("Invalid LVGL object user data");
//     return;
//   }

//   LOG_DBG("Event = %d", event);

//   if (event == LV_EVENT_CLICKED) {
//     snprintf(m_bas_file, WH_PATH_MAX_LEN, "%s", (char*)obj->user_data);
//     LOG_DBG("Clicked on %s", m_bas_file);
//   }
// }

/**
 * @brief Generate an LVGL list of BAS files to run
 */
static void __editor(char* fullpath) {
  int err;
  size_t file_size = 0;
  static char file_contents[WH_BASIC_MAX_FILESIZE + 1];
  struct fs_file_t file;

  // Suspend bling thread
  LOG_DBG("Suspending Bling thread to protect file IO from corruption");
  k_tid_t bling_thread = wh_util_thread_get_by_name("bling_task");
  k_thread_suspend(bling_thread);

  // Get the filesize
  struct fs_dirent entry;
  if (!fs_stat(fullpath, &entry)) {
    file_size = entry.size;
  }
  if (file_size == 0) {
    LOG_ERR("Could not stat %s.", log_strdup(fullpath));
    return;
  }

  // Ensure we have a properly sized file
  if (file_size > WH_BASIC_MAX_FILESIZE) {
    LOG_ERR("BASIC file too large");
    return;
  }

  err = fs_open(&file, fullpath);
  if (err) {
    LOG_ERR("Could not open %s", fullpath);
    return;
  }

  // Read the file contents
  memset(file_contents, 0, WH_BASIC_MAX_FILESIZE + 1);
  ssize_t bytes_read = fs_read(&file, file_contents, file_size);
  if (bytes_read != file_size) {
    LOG_ERR("Error while reading file %s [%d]", fullpath, bytes_read);
    fs_close(&file);
    return;
  }

  fs_close(&file);

  LOG_DBG("Resuming Bling thread to protect file IO from corruption");
  k_thread_resume(bling_thread);

  m_lvgl_input_group = lv_group_create();
  m_lvgl_edit_screen = lv_obj_create(NULL, NULL);

  // Apply background
  lv_obj_t* bg = lv_img_create(m_lvgl_edit_screen, NULL);
  lv_img_set_src(bg, &BG);

  m_lvgl_file_contents = lv_ta_create(m_lvgl_edit_screen, NULL);
  lv_ta_set_text(m_lvgl_file_contents, "");
  lv_obj_set_size(m_lvgl_file_contents, WH_UI_WIDTH, WH_UI_HEIGHT);
  lv_obj_align(m_lvgl_file_contents, NULL, LV_ALIGN_CENTER, 0, 0);
  lv_group_add_obj(m_lvgl_input_group, m_lvgl_file_contents);
  lv_ta_set_max_length(m_lvgl_file_contents, WH_BASIC_MAX_FILESIZE);
  lv_ta_set_text(m_lvgl_file_contents, file_contents);
  lv_ta_set_cursor_pos(m_lvgl_file_contents, 0);

  // Bring BAS file list to the foreground
  lv_scr_load(m_lvgl_edit_screen);
  // Let user control it
  wh_ui_input_group_set(m_lvgl_input_group);
}

/**
 * @brief Primary entry point for BASIC app. This should list available files
 * and allow them to run
 */
static void __handler(void* data) {
  m_running = true;
  char path[WH_PATH_MAX_LEN];
  char filename[MAX_FILE_NAME + 1];
  wh_app_basic_util_file_picker(filename, "Edit BAS File");
  snprintf(path, WH_PATH_MAX_LEN, WH_FS_MOUNT_POINT "/BAS/%s", filename);

  __editor(path);

  while (m_running) {
    k_sleep(K_MSEC(10));
  }

  // Suspend bling thread
  k_tid_t bling_thread = wh_util_thread_get_by_name("bling_task");
  k_thread_suspend(bling_thread);
  LOG_DBG("Suspending Bling thread to protect file IO from corruption");

  // File editor is done, save and cleanup
  int err;
  struct fs_file_t file;
  err = fs_open(&file, path);
  if (err) {
    LOG_DBG("Could not open %s for saving", path);
    return;
  }

  const char* file_contents = lv_ta_get_text(m_lvgl_file_contents);
  fs_write(&file, file_contents, strlen(file_contents));
  fs_close(&file);
  lv_obj_del(m_lvgl_edit_screen);

  LOG_INF("Resuming Bling thread to protect file IO from corruption");
  k_thread_resume(bling_thread);
}

static void __init() {
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
      m_running = false;
      wh_app_basic_util_file_picker_exit();
      return wh_ui_signal_result_okay;
      break;
  }

  return 0;
}

const app_t app_basic_edit = {"MY-BASIC Edit", __init, __handler, __signal_callback, NULL};