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
#include "bbq10.h"

#include <device.h>
#include <drivers/gpio.h>
#include <logging/log.h>
#include <zephyr.h>

#include "../system.h"
#include "../wh_settings.h"
#include "../wh_util.h"
#include "autoconf.h"
#include "devicetree.h"

#define PIN_COL1 6
#define PIN_COL2 10
#define PIN_COL3 8
#define PIN_COL4 11
#define PIN_COL5 2

#define PIN_ROW1 5
#define PIN_ROW2 7
#define PIN_ROW3 12
#define PIN_ROW4 0
#define PIN_ROW5 3
#define PIN_ROW6 1
#define PIN_ROW7 4

#define PIN_COL_COUNT 5
#define PIN_ROW_COUNT 7

#define DEBOUNCE_TIME_MS 10

LOG_MODULE_REGISTER(bbq10, CONFIG_BBQ10_LOG_LEVEL);

struct bbq10_data {
  struct device* gpioc;
  struct device* led_0_ctrl;
  struct device* led_1_ctrl;
};

static struct bbq10_data m_bbq10_driver_data;

static uint8_t m_cols[] = {PIN_COL1, PIN_COL2, PIN_COL3, PIN_COL4, PIN_COL5};
static uint8_t m_rows[] = {PIN_ROW1, PIN_ROW2, PIN_ROW3, PIN_ROW4,
                           PIN_ROW5, PIN_ROW6, PIN_ROW7};

static uint64_t m_state = 0;
static char m_last_char = 0;
static bool m_char_ready = false;

/****************************************************/
/*  Blackberry Q10 Keyboard Map                     */
/*                                                  */
/*  Col1    Col2    Col3    Col4    Col5            */
/*+-----------------------------------------------+ */
/*|   Q   |   E   |   R   |   U   |   O   | Row 1   */
/*|-------+-------+-------+-------+-------+-------+ */
/*|   W   |   S   |   G   |   H   |   L   | Row 2   */
/*|-------+-------+-------+-------+-------+-------+ */
/*|  SYM  |   D   |   T   |   Y   |   I   | Row 3   */
/*|-------+-------+-------+-------+-------+-------+ */
/*|   A   |   P   | RSHFT |  ENT  |  BCK  | Row 4   */
/*|-------+-------+-------+-------+-------+-------+ */
/*|  ALT  |   X   |   V   |   B   |   $   | Row 5   */
/*|-------+-------+-------+-------+-------+-------+ */
/*|  SPC  |   Z   |   C   |   N   |   M   | Row 6   */
/*|-------+-------+-------+-------+-------+-------+ */
/*|   0   | LSHFT |   F   |   J   |   K   | Row 7   */
/*|-------+-------+-------+-------+-------+-------+ */
/*                                                  */
/*  Alt Keymap                                      */
/*  Col1    Col2    Col3    Col4    Col5            */
/*+-----------------------------------------------+ */
/*|   #   |   2   |   3   |   _   |   +   | Row 1   */
/*|-------+-------+-------+-------+-------+-------+ */
/*|   1   |   4   |   /   |   :   |   "   | Row 2   */
/*|-------+-------+-------+-------+-------+-------+ */
/*|       |   5   |   (   |   )   |   -   | Row 3   */
/*|-------+-------+-------+-------+-------+-------+ */
/*|   *   |   @   |       |       |  DEL  | Row 4   */
/*|-------+-------+-------+-------+-------+-------+ */
/*|       |   8   |   ?   |   !   |  SPK  | Row 5   */
/*|-------+-------+-------+-------+-------+-------+ */
/*|       |   7   |   9   |   ,   |   .   | Row 6   */
/*|-------+-------+-------+-------+-------+-------+ */
/*|   0   |       |   6   |   ;   |   '   | Row 7   */
/*|-------+-------+-------+-------+-------+-------+ */
/*                                                  */
/*  SYM Keymap                                      */
/*  Col1    Col2    Col3    Col4    Col5            */
/*+-----------------------------------------------+ */
/*|  BCK  |  FN1  |  FN2  |   {   |       | Row 1   */
/*|-------+-------+-------+-------+-------+-------+ */
/*|   UP  |  DWN  |   \   |       |   =   | Row 2   */
/*|-------+-------+-------+-------+-------+-------+ */
/*|       |  RGT  |   [   |   ]   |   }   | Row 3   */
/*|-------+-------+-------+-------+-------+-------+ */
/*|  LFT  |   %   |       |       |       | Row 4   */
/*|-------+-------+-------+-------+-------+-------+ */
/*|       |  BCK  |   ~   |       |   &   | Row 5   */
/*|-------+-------+-------+-------+-------+-------+ */
/*|       |       |   ^   |   <   |   >   | Row 6   */
/*|-------+-------+-------+-------+-------+-------+ */
/*|   0   |       |   |   |       |       | Row 7   */
/*|-------+-------+-------+-------+-------+-------+ */
/*                                                  */
/****************************************************/

static const uint8_t keymap_normal[PIN_ROW_COUNT][PIN_COL_COUNT] = {
    {'q', 'e', 'r', 'u', 'o'},                                    // ROW 1
    {'w', 's', 'g', 'h', 'l'},                                    // ROW 2
    {KEYCODE_SYM, 'd', 't', 'y', 'i'},                            // ROW 3
    {'a', 'p', KEYCODE_SHIFT, KEYCODE_ENTER, KEYCODE_BACKSPACE},  // ROW 4
    {KEYCODE_ALT, 'x', 'v', 'b', '$'},                            // ROW 5
    {' ', 'z', 'c', 'n', 'm'},                                    // ROW 6
    {'0', KEYCODE_SHIFT, 'f', 'j', 'k'}                           // ROW 7
};

static const uint8_t keymap_shift[PIN_ROW_COUNT][PIN_COL_COUNT] = {
    {'Q', 'E', 'R', 'U', 'O'},            // ROW 1
    {'W', 'S', 'G', 'H', 'L'},            // ROW 2
    {0, 'D', 'T', 'Y', 'I'},              // ROW 3
    {'A', 'P', 0, 0, KEYCODE_BACKSPACE},  // ROW 4
    {0, 'X', 'V', 'B', '$'},              // ROW 5
    {' ', 'Z', 'C', 'N', 'M'},            // ROW 6
    {'0', 0, 'F', 'J', 'K'}               // ROW 7
};

static const uint8_t keymap_alt[PIN_ROW_COUNT][PIN_COL_COUNT] = {
    {'#', '2', '3', '_', '+'},            // ROW 1
    {'1', '4', '/', ':', '"'},            // ROW 2
    {0, '5', '(', ')', '-'},              // ROW 3
    {'*', '@', 0, 0, KEYCODE_DEL},        // ROW 4
    {0, '8', '?', '!', KEYCODE_SPEAKER},  // ROW 5
    {0, '7', '9', ',', '.'},              // ROW 6
    {'0', 0, '6', ';', '\''}              // ROW 7
};

static const uint8_t keymap_sym[PIN_ROW_COUNT][PIN_COL_COUNT] = {
    {KEYCODE_BACK, KEYCODE_FN1, KEYCODE_FN2, '{', 0},  // ROW 1
    {KEYCODE_UP, KEYCODE_DOWN, '\\', 0, '='},          // ROW 2
    {0, KEYCODE_RIGHT, '[', ']', '}'},                 // ROW 3
    {KEYCODE_LEFT, '%', 0, 0, 0},                      // ROW 4
    {0, KEYCODE_BACK, '~', 0, '&'},                    // ROW 5
    {0, 0, '^', '<', '>'},                             // ROW 6
    {'0', 0, '|', 0, 0}                                // ROW 7
};

#define KEY_OFFSET(_r, _c) (((uint64_t)_r * 5) + (uint64_t)_c)
#define KEY_MASK(_r, _c) ((uint64_t)1 << KEY_OFFSET(_r, _c))
#define KEY_MASK_ALT KEY_MASK(4, 0)
#define KEY_MASK_R_SHIFT KEY_MASK(3, 2)
#define KEY_MASK_L_SHIFT KEY_MASK(6, 1)
#define KEY_MASK_SYM KEY_MASK(2, 0)

/**
 * @brief Quick method for scanning the keyboard
 */
static inline uint64_t __scan() {
  uint64_t ret = 0;

  for (uint8_t c = 0; c < PIN_COL_COUNT; c++) {
    // Pull this column high
    gpio_pin_set(m_bbq10_driver_data.gpioc, m_cols[c], 1);
    k_sleep(K_MSEC(1)); //Attempt to let gpio settle down and avoid bleedover
    // Scan for high rows
    for (uint8_t r = 0; r < PIN_ROW_COUNT; r++) {
      int v = gpio_pin_get(m_bbq10_driver_data.gpioc, m_rows[r]);
      ret |= ((uint64_t)v << KEY_OFFSET(r, c));
    }
    // Pull column back low
    gpio_pin_set(m_bbq10_driver_data.gpioc, m_cols[c], 0);
    k_sleep(K_MSEC(1)); //Attempt to let gpio settle down and avoid bleedover
  }

  return ret;
}

/**
 * Background task that scans the keyboard for key presses
 */
static void __bbq10_task() {
  uint64_t last_mask = 0;
  uint64_t mask = 0;
  int64_t led_off_time_ms = k_uptime_get() + CONFIG_BBQ_LED_ON_TIME_MS;
  bool led_state = false;

  bool alt = false;
  bool shift = false;
  bool sym = false;

  while (1) {
    mask = __scan();
    m_state = mask & last_mask;
    last_mask = mask;

    // Convert a non-zero key mask to ascii input
    // m_state will change when input occurs
    if (m_state > 0) {
      // Update expiration time
      led_off_time_ms =
          k_uptime_get() + wh_settings_ptr_get()->keyboard_led_timeout;

      // If LEDs are off, turn them on
      if (!led_state) {
        led_state = true;
        bbq10_led_set(true, true);
      }

      uint8_t keycode = 0;
      uint64_t temp_mask = m_state;

      // Determine if any mods were used
      alt = (m_state & KEY_MASK_ALT);
      shift = (m_state & KEY_MASK_R_SHIFT) | (m_state & KEY_MASK_L_SHIFT);
      sym = (m_state & KEY_MASK_SYM);

      // Strip modifiers
      temp_mask &= (~KEY_MASK_ALT & ~KEY_MASK_SYM & ~KEY_MASK_R_SHIFT &
                    ~KEY_MASK_L_SHIFT);

      for (uint8_t r = 0; r < PIN_ROW_COUNT; r++) {
        for (uint8_t c = 0; c < PIN_COL_COUNT; c++) {
          if ((temp_mask & KEY_MASK(r, c)) > 0) {
            if (alt) {
              keycode = keymap_alt[r][c];
            } else if (shift) {
              keycode = keymap_shift[r][c];
            } else if (sym) {
              keycode = keymap_sym[r][c];
            } else {
              keycode = keymap_normal[r][c];
            }
            goto scanning_done;
          }
        }
      }

    scanning_done:
      if (keycode > 0) {
        LOG_DBG("KEYBOARD: %c (%d DEC) alt=%d sym=%d", keycode, keycode, alt,
                sym);
        m_last_char = keycode;
        m_char_ready = true;
      }
    }

    // No input occurred
    else {
      int64_t now = k_uptime_get();
      // If LEDs are on and time has expired turn them off
      if (led_state && (now > led_off_time_ms)) {
        led_state = false;
        bbq10_led_set(false, false);
      }
    }
    k_sleep(K_MSEC(DEBOUNCE_TIME_MS));
  }
}

/**
 * @brief Initialize the LED Matrix Driver
 */
static int __bbq10_init(struct device* dev) {
  m_bbq10_driver_data.gpioc = device_get_binding("GPIOC");
  if (!m_bbq10_driver_data.gpioc) {
    LOG_ERR("Unable to get GPIOC");
    return -1;
  }

  m_bbq10_driver_data.led_0_ctrl =
      device_get_binding(DT_GPIO_LEDS_LED_0_GPIOS_CONTROLLER);
  m_bbq10_driver_data.led_1_ctrl =
      device_get_binding(DT_GPIO_LEDS_LED_1_GPIOS_CONTROLLER);
  gpio_pin_configure(m_bbq10_driver_data.led_0_ctrl,
                     DT_GPIO_LEDS_LED_0_GPIOS_PIN, GPIO_OUTPUT);
  gpio_pin_configure(m_bbq10_driver_data.led_1_ctrl,
                     DT_GPIO_LEDS_LED_1_GPIOS_PIN, GPIO_OUTPUT);

  // Columns are outputs (this is a matrix)
  gpio_pin_configure(m_bbq10_driver_data.gpioc, PIN_COL1, GPIO_OUTPUT);
  gpio_pin_configure(m_bbq10_driver_data.gpioc, PIN_COL2, GPIO_OUTPUT);
  gpio_pin_configure(m_bbq10_driver_data.gpioc, PIN_COL3, GPIO_OUTPUT);
  gpio_pin_configure(m_bbq10_driver_data.gpioc, PIN_COL4, GPIO_OUTPUT);
  gpio_pin_configure(m_bbq10_driver_data.gpioc, PIN_COL5, GPIO_OUTPUT);

  // Rows are inputs pulled down
  gpio_pin_configure(m_bbq10_driver_data.gpioc, PIN_ROW1,
                     GPIO_INPUT | GPIO_PULL_DOWN);
  gpio_pin_configure(m_bbq10_driver_data.gpioc, PIN_ROW2,
                     GPIO_INPUT | GPIO_PULL_DOWN);
  gpio_pin_configure(m_bbq10_driver_data.gpioc, PIN_ROW3,
                     GPIO_INPUT | GPIO_PULL_DOWN);
  gpio_pin_configure(m_bbq10_driver_data.gpioc, PIN_ROW4,
                     GPIO_INPUT | GPIO_PULL_DOWN);
  gpio_pin_configure(m_bbq10_driver_data.gpioc, PIN_ROW5,
                     GPIO_INPUT | GPIO_PULL_DOWN);
  gpio_pin_configure(m_bbq10_driver_data.gpioc, PIN_ROW6,
                     GPIO_INPUT | GPIO_PULL_DOWN);
  gpio_pin_configure(m_bbq10_driver_data.gpioc, PIN_ROW7,
                     GPIO_INPUT | GPIO_PULL_DOWN);

  return 0;
}

/**
 * @brief Get a character from the blackberry keyboard, blocking until a
 * character is ready
 * @return The last character typed
 */
char bbq10_getc() {
  while (!m_char_ready) {
    k_sleep(K_MSEC(10));
  }
  char c = m_last_char;
  m_char_ready = false;
  return c;
}

/**
 * @brief Returns true if a character is ready from the keyboard
 */
bool bbq10_ready() {
  return m_char_ready;
}

/**
 * @brief Get the current keyboard state after a debounce
 */
uint64_t bbq10_state_get() {
  return m_state;
}

/**
 * @brief Set the LED state of the keyboard
 */
void bbq10_led_set(bool left, bool right) {
  if (left) {
    gpio_pin_set(m_bbq10_driver_data.led_0_ctrl, DT_GPIO_LEDS_LED_0_GPIOS_PIN,
                 1);
  } else {
    gpio_pin_set(m_bbq10_driver_data.led_0_ctrl, DT_GPIO_LEDS_LED_0_GPIOS_PIN,
                 0);
  }

  if (right) {
    gpio_pin_set(m_bbq10_driver_data.led_1_ctrl, DT_GPIO_LEDS_LED_1_GPIOS_PIN,
                 1);
  } else {
    gpio_pin_set(m_bbq10_driver_data.led_1_ctrl, DT_GPIO_LEDS_LED_1_GPIOS_PIN,
                 0);
  }
}

DEVICE_INIT(bbq10,
            CONFIG_BBQ10_DEV_NAME,
            __bbq10_init,
            &m_bbq10_driver_data,
            NULL,
            POST_KERNEL,
            CONFIG_APPLICATION_INIT_PRIORITY);

K_THREAD_DEFINE(bbq10_task,
                1400,
                __bbq10_task,
                NULL,
                NULL,
                NULL,
                WH_THREAD_PRIORITY_MEDIUM,
                0,
                500);
