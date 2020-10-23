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
#ifndef FF_SHELL_CDC_ACM_H
#define FF_SHELL_CDC_ACM_H

#include <shell/shell.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SHELL_CDC_ACM_BUFFER_SIZE 16

// Struct for pointers to shell API
extern const struct shell_transport_api shell_cdc_acm_transport_api;

struct shell_cdc_acm {
  struct device *dev;
  shell_transport_handler_t handler;
  void *context;
  u8_t rx[SHELL_CDC_ACM_BUFFER_SIZE];
  size_t rx_cnt;
};

// Helper macro for setting up shell CDC ACM shim
#define WH_SHELL_CDC_ACM_DEFINE(_name)                                         \
  static struct shell_cdc_acm _name##_shell_cdc_acm;                           \
  struct shell_transport _name = {                                             \
      .api = &shell_cdc_acm_transport_api,                                     \
      .ctx = (struct shell_cdc_acm *)&_name##_shell_cdc_acm}

/**
 * @brief Return true if the cdc acm is connected
 */
extern bool wh_shell_cdc_acm_is_connected();

#ifdef __cplusplus
}
#endif

#endif