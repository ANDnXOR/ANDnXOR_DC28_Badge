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
#include "wh_fs.h"

#include <device.h>
#include <disk/disk_access.h>
#include <ff.h>
#include <fs/fs.h>
#include <logging/log.h>
#include <stdlib.h>
#include <zephyr.h>

#include "system.h"
#include "wh_post.h"

LOG_MODULE_REGISTER(wh_fs, CONFIG_FS_LOG_LEVEL);
static FATFS m_fat_fs;
static bool m_mounted = false;
static uint8_t m_spi_version = 0;

static struct fs_mount_t m_mount_info = {
    .type = FS_FATFS,
    .mnt_point = WH_FS_MOUNT_POINT,
    .fs_data = &m_fat_fs,
};

// static int __lsdir(const char* path) {
//   int res;
//   struct fs_dir_t dirp;
//   static struct fs_dirent entry;

//   /* Verify fs_opendir() */
//   res = fs_opendir(&dirp, path);
//   if (res) {
//     LOG_DBG("Error opening dir %s [%d]\n", path, res);
//     return res;
//   }

//   LOG_DBG("\nListing dir %s ...\n", path);
//   for (;;) {
//     /* Verify fs_readdir() */
//     res = fs_readdir(&dirp, &entry);

//     /* entry.name[0] == 0 means end-of-dir */
//     if (res || entry.name[0] == 0) {
//       break;
//     }

//     if (entry.type == FS_DIR_ENTRY_DIR) {
//       LOG_DBG("[DIR ] %s", log_strdup(entry.name));
//     } else {
//       LOG_DBG("[FILE] %s (size = %zu)", log_strdup(entry.name), entry.size);
//     }
//   }

//   LOG_DBG("End of list");

//   /* Verify fs_closedir() */
//   fs_closedir(&dirp);

//   LOG_DBG("Closed Dir");

//   return res;
// }

void wh_fs_init() {
  struct fs_file_t file;
  LOG_DBG("Initializing persistence");

  LOG_DBG("Attempting to mount %s", WH_FS_MOUNT_POINT);
  int res = fs_mount(&m_mount_info);
  uint32_t spi_flash_version = 0;

  if (res == FR_OK) {
    m_mounted = true;
    wh_post_success(WH_POST_FS_MOUNT);
    res = fs_open(&file, WH_FS_MOUNT_POINT SPI_FLASH_VERSION_FILENAME);
    if (res) {
      LOG_ERR("Unable to open file %s",
              WH_FS_MOUNT_POINT SPI_FLASH_VERSION_FILENAME);
      goto init_complete;
    }

    char buffer[128];
    res = fs_read(&file, buffer, 128);
    if (res <= 0) {
      LOG_ERR("Unable to read SPI version file");
    } else {
      LOG_DBG("Read %d bytes from SPI flash VERSION file", res);
      spi_flash_version = strtol(buffer, NULL, 10);
      LOG_DBG("SPI flash version = %d", spi_flash_version);
    }

    fs_close(&file);
  } else {
    wh_post_failed(WH_POST_FS_MOUNT);
    LOG_ERR("Error mounting disk.\n");
  }

init_complete:
  m_spi_version = spi_flash_version;
  if (spi_flash_version < SPI_FLASH_MIN_VERSION ||
      spi_flash_version > SPI_FLASH_MAX_VERSION) {
    LOG_ERR("SPI flash is out of CM. Please re-provision");
    wh_post_failed(WH_POST_FS_VERSION);
  } else {
    LOG_INF("SPI flash version is correct");
    wh_post_success(WH_POST_FS_VERSION);
  }

  LOG_DBG("done init");
}

/**
 * @brief Get mount status of the file system
 */
bool wh_fs_mounted() {
  return m_mounted;
}

/**
 * @brief Get the current version of the data on the SPI flash
 */
uint8_t wh_fs_spi_version_get() {
  return m_spi_version;
}