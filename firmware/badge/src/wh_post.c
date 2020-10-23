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

#include "wh_post.h"

#include <logging/log.h>
#include <shell/shell.h>
#include <zephyr.h>

LOG_MODULE_REGISTER(wh_post, CONFIG_WH_POST_LOG_LEVEL);

#define STR_OK "..OK"
#define STR_FAIL "Fail"

static uint16_t m_post_state = WH_POST_DEFAULT;

/**
 * @brief Shell function that returns POST state as a bitmask
 */
static int __cmd_post_state_get(const struct shell* shell,
                                size_t argc,
                                char** argv) {
  shell_fprintf(shell, SHELL_NORMAL, "0x%04x\n", m_post_state);
  return 0;
}

/**
 * @brief Get the current POST state as a bitmask
 */
uint16_t wh_post_state_get() {
  return m_post_state;
}

/**
 * @brief Dump POST status to log
 */
void wh_post_dump() {
  LOG_INF("============ POST ============");

  if ((m_post_state & WH_POST_FS_MOUNT) > 0)
    LOG_INF("Filesystem Mounted........" STR_OK);
  else
    LOG_INF("Filesystem Mounted........" STR_FAIL);
 
  if ((m_post_state & WH_POST_FS_VERSION) > 0)
    LOG_INF("Filesystem Version........" STR_OK);
  else
    LOG_INF("Filesystem Version........" STR_FAIL);
  
  if ((m_post_state & WH_POST_VBATT) > 0)
    LOG_INF("Battery Sense............." STR_OK);
  else
    LOG_INF("Battery Sense............." STR_FAIL);
  
  if ((m_post_state & WH_POST_THERM) > 0)
    LOG_INF("Thermistor................" STR_OK);
  else
    LOG_INF("Thermistor................" STR_FAIL);

  LOG_INF("==============================");
}

/**
 * @brief Update the current POST state with a failure
 */
inline void wh_post_failed(uint16_t mask) {
  LOG_ERR("Failed 0x%04x", mask);
  m_post_state &= ~mask;
}

/**
 * @brief Update the current POST state with a success
 */
inline void wh_post_success(uint16_t mask) {
  LOG_INF("Success 0x%04x", mask);
  m_post_state |= mask;
}

SHELL_CMD_REGISTER(post_state, NULL, "Get POST state", __cmd_post_state_get);