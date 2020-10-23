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

#include "wh_shell.h"

#include <logging/log.h>
#include <shell/shell.h>
#include <version.h>
#include <zephyr.h>

#include "autoconf.h"
#include "system.h"
#include "wh_fs.h"
#include "wh_shell_cdc_acm.h"

LOG_MODULE_REGISTER(wh_shell, CONFIG_WH_SHELL_LOG_LEVEL);

WH_SHELL_CDC_ACM_DEFINE(shell_transport_cdc_acm);
SHELL_DEFINE(cdc_shell,
             "and!xor:~$ ",
             &shell_transport_cdc_acm,
             10,
             0,
             SHELL_FLAG_OLF_CRLF);

/**
 * @brief Shell command and prints version info for the badge
 */
static int cmd_version(const struct shell* shell, size_t argc, char** argv) {
  ARG_UNUSED(argc);
  ARG_UNUSED(argv);

  shell_fprintf(shell, SHELL_NORMAL, "AND!XOR DC28 fw %d, spi %d, kernel %s\r\n",
                VERSION_INT, wh_fs_spi_version_get(), KERNEL_VERSION_STRING);

  return 0;
}

/**
 * @brief Get a reference to the current shell
 * @return Pointer to the current shell
 */
const struct shell* wh_shell_ctx_get() {
  return &cdc_shell;
}

void wh_shell_init() {
  (void)shell_init(&cdc_shell, NULL, true, false, LOG_LEVEL_INF);
}

SHELL_CMD_REGISTER(version, NULL, "Show version information", cmd_version);