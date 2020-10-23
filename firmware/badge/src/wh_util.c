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
#include <drivers/flash.h>
#include <drivers/gpio.h>
#include <drivers/hwinfo.h>
#include <drivers/led_strip.h>
#include <drivers/usb/usb_dc.h>
#include <fs/fs.h>
#include <fs/nvs.h>
#include <logging/log.h>
#include <power/reboot.h>
#include <shell/shell.h>
#include <stdlib.h>
#include <stm32f4xx_hal.h>
#include <tinycrypt/sha256.h>
#include <zephyr.h>

LOG_MODULE_REGISTER(wh_util, 4);

#include "autoconf.h"
#include "devicetree.h"
#include "gfx/dfu.h"
#include "system.h"
#include "wh_bling.h"
#include "wh_fs.h"
#include "wh_led.h"
#include "wh_settings.h"
#include "wh_ui.h"
#include "wh_util.h"

uint32_t m_badge_id = 0;

/**
 * @brief Shell command that simply returns the unqiue badge_id generated from
 * the 96-bit unique ID burned into the STM32
 */
static int __cmd_badge_id_show(const struct shell* shell,
                               size_t argc,
                               char** argv) {
  ARG_UNUSED(argc);
  ARG_UNUSED(argv);

  shell_fprintf(shell, SHELL_NORMAL, "%06x\r\n", wh_util_badge_id_get());
  return 0;
}

/**
 * @brief Shell command to enter DFU bootloader
 */
static int __cmd_dfu_enter(const struct shell* shell,
                           size_t argc,
                           char** argv) {
  wh_util_stm32f4_bootloader();
  shell_info(shell, "Going into DFU mode.");
  return 0;
}

/**
 * @brief Shell command to get the unique serial number of the MCU
 */
static int __cmd_serial_get(const struct shell* shell,
                            size_t argc,
                            char** argv) {
  uint8_t dev_id[16];
  ssize_t length;
  int i;

  length = hwinfo_get_device_id(dev_id, sizeof(dev_id));
  shell_fprintf(shell, SHELL_NORMAL, "0x");

  if (length > 0) {
    for (i = 0; i < length; i++) {
      shell_fprintf(shell, SHELL_NORMAL, "%02x", dev_id[i]);
    }
  } else {
    shell_fprintf(shell, SHELL_NORMAL, "UNKNOWN");
  }
  shell_fprintf(shell, SHELL_NORMAL, "\n");
  return 0;
}

// Used by wh_util_thread_get_by_name
static k_tid_t m_thread_ref;

/**
 * @brief Called on each thread in the system, once we find the thread with name
 * specified in user_data, set the static variable
 */
void __thread_foreach_cb(const struct k_thread* thread, void* user_data) {
  char* name = (char*)user_data;

  // Do some validation
  if (name == NULL) {
    return;
  }

  LOG_DBG("Looking for '%s' checking thread %s'", log_strdup(name),
          log_strdup(thread->name));
  if (strcmp(name, thread->name) == 0) {
    m_thread_ref = (k_tid_t)thread;
  }
}

void __generate_badge_id() {
  struct tc_sha256_state_struct sha;
  if (tc_sha256_init(&sha) == 0) {
    LOG_ERR("Unable to init SHA-256");
    return;
  }

  uint8_t dev_id[16];
  ssize_t length = hwinfo_get_device_id(dev_id, sizeof(dev_id));
  if (length < 0) {
    LOG_ERR("Unable to get device ID");
    return;
  }

  if (tc_sha256_update(&sha, dev_id, length) == 0) {
    LOG_ERR("Unable to hash device ID");
    return;
  }

  uint8_t digest[TC_SHA256_DIGEST_SIZE];
  if (tc_sha256_final(digest, &sha) == 0) {
    LOG_ERR("Unable to finalize hash");
    return;
  }

  LOG_HEXDUMP_DBG(digest, TC_SHA256_DIGEST_SIZE, "Hash of device ID:");
  m_badge_id = *((uint32_t*)digest) & 0x00FFFFFF;
}

/**
 * @brief Get a thread id by thread name
 */
k_tid_t wh_util_thread_get_by_name(char* name) {
  m_thread_ref = NULL;
  k_thread_foreach(__thread_foreach_cb, name);
  return m_thread_ref;
}

/**
 * @brief Get the unique badge id for this badge
 */
uint32_t wh_util_badge_id_get() {
  if (m_badge_id == 0) {
    __generate_badge_id();
  }
  return m_badge_id;
}

/**
 * @brief Jump to the STM32F412 bootloader by maninpulating some special (AKA
 * capacitor) hardware connected to GPIO
 */
void wh_util_stm32f4_bootloader() {
  LOG_DBG("Rebooting into bootloader");

  // Disable all bling
  k_tid_t bling_thread = wh_util_thread_get_by_name("bling_task");
  if (bling_thread != NULL) {
    k_thread_suspend(bling_thread);
  }

  // Give LEDs some status
  wh_led_set_all(WH_LED_COLOR_YELLOW);
  wh_led_show();

  // Try to draw something to the OLED right before bootloader
  wh_bling_draw_bmp_bw(dfu_raw);
  k_sleep(K_MSEC(500));

  struct device* gpio =
      device_get_binding(DT_GPIO_KEYS_BOOT0_BUTTON_GPIOS_CONTROLLER);
  gpio_pin_configure(gpio, DT_GPIO_KEYS_BOOT0_BUTTON_GPIOS_PIN, GPIO_OUTPUT);
  gpio_pin_set(gpio, DT_GPIO_KEYS_BOOT0_BUTTON_GPIOS_PIN, 1);
  k_sleep(K_MSEC(100));
  sys_reboot(SYS_REBOOT_COLD);
}

/**
 * @brief Simple function that heuristically determines if badge is provisioned
 */
bool wh_util_is_provisioned() {
  struct fs_dirent entry;
  if (fs_stat(WH_FS_MOUNT_POINT "/VERSION", &entry)) {
    LOG_ERR("VERSION file missing");
    return false;
  }
  if (fs_stat(WH_FS_MOUNT_POINT "/BLING_BW", &entry)) {
    LOG_ERR("BLING_BW directory missing");
    return false;
  }
  if (fs_stat(WH_FS_MOUNT_POINT "/USR/BIN/TACOTH", &entry)) {
    LOG_ERR("TACOTH missing");
    return false;
  }

  return true;
}

SHELL_STATIC_SUBCMD_SET_CREATE(
    sub_dfu,
    SHELL_CMD(enter, NULL, "Enter DFU mode", __cmd_dfu_enter),
    SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(badge_id, NULL, "Badge ID", __cmd_badge_id_show);
SHELL_CMD_REGISTER(dfu, &sub_dfu, "DFU Mode utility", NULL);
SHELL_CMD_REGISTER(serial, NULL, "Get unique serial number", __cmd_serial_get);