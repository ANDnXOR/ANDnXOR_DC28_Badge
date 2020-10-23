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
#include "wh_app_basic_util.h"

#include <fs/fs.h>
#include <logging/log.h>
#include <stdarg.h>
#include <stdio.h>
#include <zephyr.h>
#include <stdlib.h>

#include "../gfx/bg.h"
#include "../system.h"
#include "../wh_fs.h"
#include "../wh_ui.h"

LOG_MODULE_REGISTER(wh_app_basic_util, CONFIG_WH_APP_LOG_LEVEL);

// Dynamic storage of known BAS files (only store ptr on the stack)
char **m_bas_file_names;

static lv_obj_t* m_lvgl_bas_file_screen;
static lv_group_t* m_lvgl_input_group;

static char m_path[WH_PATH_MAX_LEN];

static bool m_running = false;
static bool m_exit = false;

/**
 * @brief LVGL event handler for events coming from app list. Handle click
 * events by running the BAS file selected
 */
static void __list_bas_btn_event_handler(lv_obj_t* obj, lv_event_t event) {
  if (!obj) {
    LOG_ERR("Invalid LVGL object");
    return;
  }

  if (!obj->user_data) {
    LOG_ERR("Invalid LVGL object user data");
    return;
  }

  LOG_DBG("Event = %d", event);

  if (event == LV_EVENT_CLICKED) {
    snprintf(m_path, WH_PATH_MAX_LEN, "%s", (char*)obj->user_data);
    LOG_DBG("Clicked on %s", m_path);
    m_running = false;
  }
}

/**
 * @brief Generate an LVGL list of BAS files to run
 */
static void __create_bas_list() {
  // Create list of apps
  lv_obj_t* list_bas = lv_list_create(m_lvgl_bas_file_screen, NULL);
  lv_obj_set_size(list_bas, 140, 113);
  lv_obj_align(list_bas, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

  // Register the list object for input
  lv_group_add_obj(m_lvgl_input_group, list_bas);
  lv_group_focus_obj(list_bas);
 
  // Dynamic storage of known BAS files
  m_bas_file_names = malloc(WH_BASIC_MAX_FILES * sizeof(char *)); // Allocate row pointers
  for(int i = 0; i < WH_BASIC_MAX_FILES; i++){
    m_bas_file_names[i] = malloc((MAX_FILE_NAME + 1) * sizeof(char));  // Allocate each row separately
  }
    
  char* path = WH_FS_MOUNT_POINT "/BAS";
  int res;
  struct fs_dir_t dirp;
  static struct fs_dirent entry;

  // Count BAS files
  uint32_t bas_file_count = 0;

  // Try to open the directory
  res = fs_opendir(&dirp, path);
  if (res) {
    LOG_DBG("Error opening dir %s [%d]\n", path, res);
  }
  // If we can open it, read teh files
  else {
    for (;;) {
      res = fs_readdir(&dirp, &entry);

      // Stop when null entry is found
      if (res || entry.name[0] == 0) {
        break;
      }

      // Look for BAS files
      if (entry.type == FS_DIR_ENTRY_FILE) {
        lv_obj_t* p_btn_bas =
            lv_list_add_btn(list_bas, LV_SYMBOL_FILE, entry.name);
        lv_obj_set_event_cb(p_btn_bas, __list_bas_btn_event_handler);

        snprintf(m_bas_file_names[bas_file_count], MAX_FILE_NAME + 1, "%s",
                 entry.name);
        LOG_DBG("Found BAS file: %s", m_bas_file_names[bas_file_count]);
        lv_obj_set_user_data(p_btn_bas, m_bas_file_names[bas_file_count]);
        bas_file_count++;

        // Don't overflow the list!
        if (bas_file_count >= WH_BASIC_MAX_FILES) {
          break;
        }
      }
    }
  }
  // Indicate no files found
  if (bas_file_count == 0) {
    lv_list_add_btn(list_bas, LV_SYMBOL_FILE, "<None>");
  }
  fs_closedir(&dirp);
}

/**
 * @brief Common BASIC file picker utility
 */
int wh_app_basic_util_file_picker(char* bas_file_path, char* title) {
  m_running = true;
  m_exit = false;
  m_lvgl_bas_file_screen = lv_obj_create(NULL, NULL);

  // Apply background
  lv_obj_t* bg = lv_img_create(m_lvgl_bas_file_screen, NULL);
  lv_img_set_src(bg, &BG);

  m_lvgl_input_group = lv_group_create();
  __create_bas_list();
  // Bring BAS file list to the foreground
  lv_scr_load(m_lvgl_bas_file_screen);
  // Let user control it
  wh_ui_input_group_set(m_lvgl_input_group);

  lv_obj_t* header = lv_label_create(m_lvgl_bas_file_screen, NULL);
  lv_obj_set_style(header, wh_ui_style_header_get());
  lv_label_set_text(header, title);
  lv_obj_align(header, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

  while (m_running & !m_exit) {
    k_sleep(K_MSEC(10));
  }

  if (!m_exit) {
    memcpy(bas_file_path, m_path, WH_PATH_MAX_LEN);
  }
  m_running = false;
  lv_obj_del(m_lvgl_bas_file_screen);

  return 0;
}

/**
 * @brief Free the file picker list
 */
void wh_app_basic_util_free_memory(){
  //If you truly love your heap, set it free
  for (int i = 0; i < WH_BASIC_MAX_FILES; i++ ){
      free(m_bas_file_names[i]);
  }
  free(m_bas_file_names);
}

/**
 * @brief Signal the file picker to exit
 */
void wh_app_basic_util_file_picker_exit() {
  m_exit = true;
}