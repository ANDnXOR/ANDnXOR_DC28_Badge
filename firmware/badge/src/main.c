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
#include <drivers/gpio.h>
#include <drivers/led_strip.h>
#include <logging/log.h>
#include <shell/shell.h>
#include <shell/shell_uart.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/printk.h>
#include <usb/usb_device.h>
#include <version.h>
#include <zephyr.h>

#include "drivers/bbq10.h"
#include "system.h"
#include "wh_app.h"
#include "wh_bender.h"
#include "wh_bling.h"
#include "wh_fs.h"
#include "wh_led.h"
#include "wh_menu.h"
#include "wh_post.h"
#include "wh_settings.h"
#include "wh_shell.h"
#include "wh_ui.h"
#include "wh_ui_status.h"
#include "wh_unlocks.h"

LOG_MODULE_REGISTER(main, 4);

#include "autoconf.h"
#include "devicetree.h"

/* 1000 msec = 1 sec */
#define SLEEP_TIME K_MSEC(500)

// Define this here until we find a better home
K_MUTEX_DEFINE(g_mutex_display_dc);
K_MUTEX_DEFINE(g_mutex_ui);

// static void __intro_frame_callback(uint8_t frame, void* p_data) {
//   if ((frame % 2) == 0) {
//     bbq10_led_set(false, true);
//   } else {
//     bbq10_led_set(true, false);
//   }
// }

// static void __intro() {
//   wh_bling_play_raw_bw_file(WH_FS_MOUNT_POINT "/BLING_BW/INTRO.RAW",
//                             __intro_frame_callback, false, NULL);
//   bbq10_led_set(false, false);
// }

void main(void) {
  int err;

  // Quickly enable status LED
  struct device* status_led_ctrl =
      device_get_binding(DT_GPIO_LEDS_STATUS_LED_GPIOS_CONTROLLER);
  gpio_pin_configure(status_led_ctrl, DT_GPIO_LEDS_STATUS_LED_GPIOS_PIN,
                     GPIO_OUTPUT);
  gpio_pin_set(status_led_ctrl, DT_GPIO_LEDS_STATUS_LED_GPIOS_PIN, 0);

  // Setup the UI
  wh_ui_init();
  wh_menu_init();

  // Init all the registered apps TODO: Move ot zephyr init framework
  wh_app_init();

  // Init persistence TODO change to zephyr init
  wh_fs_init();

  WH_LED_ALL_OFF();

  // Init settings TODO: change to zephyr init
  wh_settings_init();
  wh_settings_save();

  wh_post_dump();

  // Init shelll
  wh_shell_init();

  k_mutex_lock(&g_mutex_ui, K_FOREVER);
  //__intro(); //DISABLE INTRO FOR NOW
  k_mutex_unlock(&g_mutex_ui);
  wh_menu_show();

#ifdef CONFIG_USB
  err = usb_enable(NULL);
  if (err != 0) {
    LOG_ERR("Failed to enable USB [%d]", err);
  } else {
    LOG_INF("USB Enabled");
  }
#endif

  gpio_pin_set(status_led_ctrl, DT_GPIO_LEDS_STATUS_LED_GPIOS_PIN, 1);
  LOG_INF("AND!XOR DC28 Started %s [%s]", VERSION, BUILD_TIMESTAMP);
  LOG_INF("You found the maintence port, here's a CTF code: %s",
          WH_UNLOCK_FLAG_POST);

  // Normal operation if provisioned
  if (wh_util_is_provisioned()) {
    while (1) {
      // Blink the status LED if POST is no bueno
      if (wh_post_state_get() != WH_POST_GOOD) {
        gpio_pin_toggle(status_led_ctrl, DT_GPIO_LEDS_STATUS_LED_GPIOS_PIN);
      }
      k_sleep(SLEEP_TIME);
    }
  }

  // Test pattern if not provisioned
  else {
    uint8_t color = 0;
    while (1) {
      switch (color) {
        case 0:
          wh_led_set_all(WH_LED_COLOR_RED);
          break;
        case 1:
          wh_led_set_all(WH_LED_COLOR_GREEN);
          break;
        case 2:
          wh_led_set_all(WH_LED_COLOR_BLUE);
          break;
        case 3:
          wh_led_set_all(WH_LED_COLOR_WHITE);
          break;
      }
      wh_led_show();
      gpio_pin_toggle(status_led_ctrl, DT_GPIO_LEDS_STATUS_LED_GPIOS_PIN);
      k_sleep(1000);
      if (color == 3) {
        k_sleep(2000);
      }
      color = (color + 1) % 4;
    }
  }
}