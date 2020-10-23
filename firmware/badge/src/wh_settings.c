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
#include "wh_settings.h"

#include <drivers/flash.h>
#include <fs/fs.h>
#include <logging/log.h>
#include <power/reboot.h>
#include <shell/shell.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/crc.h>
#include <zephyr.h>

#include "drivers/bbq10.h"
#include "wh_bender.h"
#include "wh_fs.h"

LOG_MODULE_REGISTER(wh_settings, 4);

#define FLASH_OFFSET_SETTINGS 0x00070000
#define SETTINGS_FILE WH_FS_MOUNT_POINT "/CONFIG.DAT"

static settings_t m_settings = {
    .name = "N00B",
    .brightness = CONFIG_WH_LED_BRIGHTNESS_DEFAULT,
    .bling_rager = false,
    .keyboard_led_timeout = CONFIG_BBQ_LED_ON_TIME_MS};

/**
 * @brief Change the badge name
 * Returns  0 if valid
 * Returns  1 if > WH_NAME_MAX_LENGTH
 * Returns -1 if passed "" (can't be blank)
 */
int wh_settings_set_name(char* name) {
  size_t len = strlen(name);

  if ((len > 0) && (len <= CONFIG_WH_NAME_MAX_LENGTH)) {
    snprintf(m_settings.name, CONFIG_WH_NAME_MAX_LENGTH + 1, "%s", name);
    LOG_HEXDUMP_DBG(m_settings.name, CONFIG_WH_NAME_MAX_LENGTH+1, "NAME");
    return 0;
  } else if (len > CONFIG_WH_NAME_MAX_LENGTH) {
    return 1;
  } else
    return -1;
}

/**
 * @brief Shell function that prints the value of the keyboard backlight setting
 */
static int __cmd_print_keyboard(const struct shell* shell,
                                size_t argc,
                                char** argv) {
  shell_print(shell, "Keyboard Timeout: %d second(s)",
              m_settings.keyboard_led_timeout / 1000);
  return 0;
}

/**
 * @brief Shell function that prints the value of the led brightness setting
 */
static int __cmd_print_led(const struct shell* shell,
                           size_t argc,
                           char** argv) {
  shell_print(shell, "LED Brightness: %d", m_settings.brightness);
  return 0;
}

/**
 * @brief Shell function that set the value of the keyboard backlight setting
 */
static int __cmd_set_keyboard(const struct shell* shell,
                              size_t argc,
                              char** argv) {
  m_settings.keyboard_led_timeout = (uint8_t)strtol(argv[1], NULL, 10) * 1000;
  if (m_settings.keyboard_led_timeout > WH_SETTING_KEYBOARD_BACKLIGHT_MAX) {
    m_settings.keyboard_led_timeout = WH_SETTING_KEYBOARD_BACKLIGHT_MAX;
  }
  wh_settings_save();
  shell_print(shell, "Keyboard backlight timeout set to: %d second(s)",
              m_settings.keyboard_led_timeout / 1000);
  return 0;
}

/**
 * @brief Shell function that set the value of the led brightness setting
 */
static int __cmd_set_led(const struct shell* shell, size_t argc, char** argv) {
  m_settings.brightness = (uint8_t)strtol(argv[1], NULL, 10);
  wh_settings_save();
  shell_print(shell, "LED Brightness set to: %d", m_settings.brightness);
  return 0;
}

/**
 * @brief Shell function that prints all settings values
 */
static int __cmd_print_all(const struct shell* shell,
                           size_t argc,
                           char** argv) {
  __cmd_print_keyboard(shell, argc, argv);
  __cmd_print_led(shell, argc, argv);
  return 0;
}

/**
 * @brief Get a pointer to the current settings object
 */
settings_t* wh_settings_ptr_get() {
  return &m_settings;
}

/**
 * @brief Get a pointer to the current bender object
 */
bender_data_t* wh_settings_bender_ptr_get() {
  return &(m_settings.bender_state);
}

/**
 * @brief Load the settings from persistant storage
 */
void wh_settings_load() {
  // settings_t temp;
  // struct device* flash_dev = device_get_binding(DT_FLASH_DEV_NAME);

  // int err =
  //     flash_read(flash_dev, FLASH_OFFSET_SETTINGS, &temp,
  //     sizeof(settings_t));
  // if (err) {
  //   LOG_ERR("Unable to read flash");
  //   return;
  // }

  // // Validate CRC
  // uint32_t crc32 =
  //     crc32_ieee((uint8_t*)&temp, sizeof(settings_t) - sizeof(uint32_t));
  // if (temp.crc32 != crc32) {
  //   LOG_ERR("Settings CRC32 check failed, stored = 0x%08x computed=0x%08x",
  //           temp.crc32, crc32);
  //   return;
  // }

  // // Copy settings data locally
  // memcpy(&m_settings, &temp, sizeof(settings_t));

  // // Fin
  // LOG_INF("Settings loaded.");

  struct fs_file_t config_file;
  settings_t temp;
  size_t file_size = 0;
  int err;

  // Get the filesize
  struct fs_dirent entry;
  if (!fs_stat(SETTINGS_FILE, &entry)) {
    file_size = entry.size;
  }
  LOG_DBG("'%s' Filesize = %d bytes", SETTINGS_FILE, file_size);
  if (file_size == 0) {
    LOG_ERR("Could not stat '%s'.", SETTINGS_FILE);
    return;
  }
  if (file_size != sizeof(settings_t)) {
    LOG_ERR("Settings file size mismatch");
    return;
  }

  // Open settings file
  err = fs_open(&config_file, SETTINGS_FILE);
  if (err) {
    LOG_ERR("Could not open %s.", SETTINGS_FILE);
    return;
  }

  ssize_t read_bytes = fs_read(&config_file, &temp, sizeof(settings_t));
  if (read_bytes != sizeof(settings_t)) {
    LOG_ERR("Did not read expected bytes [%d]", read_bytes);
    fs_close(&config_file);
    return;
  }
  fs_close(&config_file);

  // Validate CRC
  uint32_t crc32 =
      crc32_ieee((uint8_t*)&temp, sizeof(settings_t) - sizeof(uint32_t));
  if (temp.crc32 != crc32) {
    LOG_ERR("Settings CRC32 check failed, stored = 0x%08x computed=0x%08x",
            temp.crc32, crc32);
    return;
  }

  // Copy settings data locally
  memcpy(&m_settings, &temp, sizeof(settings_t));

  // Fin
  LOG_INF("Settings loaded.");
}

/**
 * @brief Initialize the settings module
 */
void wh_settings_init() {
  wh_bender_data_init();
  wh_settings_load();
}

/**
 * @brief Factory reset and reboot badge
 */
void wh_settings_reset() {
  // Reset BENDER data
  wh_bender_data_init();
  strcpy(m_settings.name, "N00B");
  m_settings.brightness = CONFIG_WH_LED_BRIGHTNESS_DEFAULT,
  m_settings.bling_rager = false,
  m_settings.keyboard_led_timeout = CONFIG_BBQ_LED_ON_TIME_MS;
  LOG_INF("Settings reset, saving...");
  wh_settings_save();
  LOG_INF("Rebooting");
  k_sleep(K_SECONDS(2));  // this is required to commit to flash for some reason
  sys_reboot(SYS_REBOOT_COLD);
}

/**
 * @brief Save the settings to the filesystem
 */
void wh_settings_save() {
  struct fs_file_t config_file;
  int err;

  m_settings.crc32 =
      crc32_ieee((uint8_t*)&m_settings, sizeof(settings_t) - sizeof(uint32_t));

  // struct device* flash_dev = device_get_binding(DT_FLASH_DEV_NAME);
  // int err = flash_erase(flash_dev, FLASH_OFFSET_SETTINGS, 2048);
  // if (err) {
  //   LOG_ERR("Unable to erase flash [%d]", err);
  //   return;
  // }

  // err = flash_write(flash_dev, FLASH_OFFSET_SETTINGS, &m_settings,
  //                   sizeof(m_settings));
  // if (err) {
  //   LOG_ERR("Unable to write to flash [%d]", err);
  //   return;
  // }

  // Open settings file
  err = fs_open(&config_file, SETTINGS_FILE);
  if (err) {
    LOG_ERR("Could not open %s.", SETTINGS_FILE);
    return;
  }

  ssize_t bytes_written =
      fs_write(&config_file, &m_settings, sizeof(settings_t));
  if (bytes_written != sizeof(settings_t)) {
    LOG_ERR("Bytes written to config file [%d]", bytes_written);
  }

  fs_close(&config_file);

  LOG_INF("Settings Saved");
}

SHELL_STATIC_SUBCMD_SET_CREATE(
    sub_config_set,
    SHELL_CMD(brightness, NULL, "Set LED brightness value", __cmd_set_led),
    SHELL_CMD(keyboard,
              NULL,
              "Set Keyboard backlight timeout",
              __cmd_set_keyboard),
    SHELL_SUBCMD_SET_END);

SHELL_STATIC_SUBCMD_SET_CREATE(
    sub_config_show,
    SHELL_CMD(all, NULL, "Dump configuration data", __cmd_print_all),
    SHELL_CMD(brightness, NULL, "Show LED brightness value", __cmd_print_led),
    SHELL_CMD(keyboard,
              NULL,
              "Show keyboard backlight timeout",
              __cmd_print_keyboard),
    SHELL_SUBCMD_SET_END);

SHELL_STATIC_SUBCMD_SET_CREATE(
    sub_config,
    SHELL_CMD(show, &sub_config_show, "Show a configuration value", NULL),
    SHELL_CMD(set, &sub_config_set, "Set configuration value", NULL),
    SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(config, &sub_config, "Badge Configuration Utility", NULL);