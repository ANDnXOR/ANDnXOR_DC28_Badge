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
#include <lvgl.h>
#include <zephyr.h>

#include "../drivers/bbq10.h"
#include "../gfx/bg.h"
#include "../system.h"
#include "../wh_app.h"
#include "../wh_bling.h"
#include "../wh_fs.h"
#include "../wh_settings.h"
#include "../wh_ui.h"

#define PHOTOS_PATH WH_FS_MOUNT_POINT "/PIX"
#define PHOTOS_MAX_FILES 128

LOG_MODULE_REGISTER(wh_app_photos, CONFIG_WH_APP_LOG_LEVEL);

// Static storage of known photos files
static char m_photo_file_names[PHOTOS_MAX_FILES][MAX_FILE_NAME + 1];
static bool m_app_running = false;
static bool m_change_photo = false;

// Count photos
static uint32_t m_photo_file_count = 0;
static uint32_t m_photo_index = 0;

/**
 * @brief Runs the app itself. When it returns, app is done
 */
static void __handler(void* data) {
  m_app_running = true;
  int res;
  static struct fs_dirent entry;
  struct fs_dir_t dirp;
  m_photo_file_count = 0;

  // Try to open the directory
  res = fs_opendir(&dirp, PHOTOS_PATH);
  if (res) {
    LOG_DBG("Error opening dir %s [%d]\n", PHOTOS_PATH, res);
    wh_ui_window_error("/PIX folder missing");
    return;
  }

  // If we can open it, read teh files into an array
  for (;;) {
    res = fs_readdir(&dirp, &entry);

    // Stop when null entry is found
    if (res || entry.name[0] == 0) {
      break;
    }

    // Look for BAS files
    if (entry.type == FS_DIR_ENTRY_FILE) {
      snprintf(m_photo_file_names[m_photo_file_count], MAX_FILE_NAME + 1, "%s",
               entry.name);
      LOG_DBG("PHOTO: %s", m_photo_file_names[m_photo_file_count]);

      m_photo_file_count++;

      // Don't overflow the list!
      if (m_photo_file_count >= PHOTOS_MAX_FILES) {
        break;
      }
    }
  }

  // Quit early if missing files
  if (m_photo_file_count == 0) {
    wh_ui_window_error("Missing photos. :( ");
    return;
  }

  // Make sure photo index is good
  if (m_photo_index >= m_photo_file_count) {
    m_photo_index = 0;
  }

  // Override LVGL control
  wh_ui_lvgl_enable(false);

  // Show first photo
  while (m_app_running) {
    char path[WH_PATH_MAX_LEN];
    snprintf(path, WH_PATH_MAX_LEN, "%s/%s", PHOTOS_PATH,
             m_photo_file_names[m_photo_index]);

    LOG_DBG("Showing photo %d of %d '%s'", m_photo_index, m_photo_file_count,
            path);
    wh_bling_play_raw_file(path, NULL, false, NULL);

    m_change_photo = false;

    // Wait until they change photos or quit
    while (m_app_running && !m_change_photo) {
      k_sleep(K_MSEC(500));
    }
  }

  // Give back control
  wh_ui_lvgl_enable(true);
}

static void __init() {}

/**
 * @brief Callback from UI for signals
 */
static wh_ui_signal_result_t __signal_callback(wh_ui_signal_t signal) {
  switch (signal) {
    case wh_ui_signal_key_ready:;

      // If UI has not updated the photo yet, ignore key presses
      if (m_change_photo) {
        return wh_ui_signal_result_okay;
      }

      char c = wh_ui_last_key_get();
      switch (c) {
        case KEYCODE_LEFT:
        case KEYCODE_UP:
        case 'p':
        case 'P':
          if (m_photo_index > 0) {
            m_photo_index--;
          } else {
            m_photo_index = m_photo_file_count - 1;
          }
          m_change_photo = true;
          break;
        case KEYCODE_RIGHT:
        case KEYCODE_DOWN:
        case 'n':
        case 'N':
          m_photo_index = (m_photo_index + 1) % m_photo_file_count;
          m_change_photo = true;
          break;
      }

      LOG_DBG("New photo index %d", m_photo_index);

      return wh_ui_signal_result_okay;
      break;
    case wh_ui_signal_exit:
      m_app_running = false;
      return wh_ui_signal_result_okay;
      break;
  }

  return 0;
}

const app_t app_photos = {"Photos", __init, __handler, __signal_callback, NULL};