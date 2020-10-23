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

#include "wh_shell_cdc_acm.h"

#include <device.h>
#include <drivers/uart.h>
#include <logging/log.h>
#include <shell/shell.h>
#include <zephyr.h>

#include "autoconf.h"

LOG_MODULE_REGISTER(wh_shell_cdc_acm, CONFIG_WH_SHELL_CDC_ACM_LOG_LEVEL);

static struct shell_cdc_acm* __cdc_acm = NULL;
static bool __connected = false;

/**
 * @brief CDC interrupt handler that occurs on various CDC/uART events, we use
 * this to check for data ready to be received (and send to the shell) or data
 * is done being sent over CDC so we don't overrun
 *
 * NOTE: Unfortunately this is not stateless :( The interrupt API does not allow
 * context to be passed as far as I can tell. Womp womp. So CDC context is
 * stored by the init() function statically and re-used here when the interrupt
 * occurs later. I guess a race condition could occur. Sorry future me! Or not
 * sorry if it works!
 */
static void __cdc_interrupt_handler(struct device* dev) {
  uart_irq_update(dev);

  // Data has been received yo
  if (uart_irq_rx_ready(dev)) {
    size_t count = uart_fifo_read(__cdc_acm->dev, __cdc_acm->rx,
                                  SHELL_CDC_ACM_BUFFER_SIZE);
    // If we got at least one byte, notify the handler that data is ready to be
    // received
    if (count > 0) {
      __cdc_acm->rx_cnt = count;
      __cdc_acm->handler(SHELL_TRANSPORT_EVT_RX_RDY, __cdc_acm->context);
    }
  }
}

/**
 * @brief Initialize the USB CDC ACM shell driver
 * @param transport   : The shell transport context to use
 * @param config      : The config of the shell
 * @param evt_handler : Event handler
 * @param context     : User adata
 * @return Error or 0 if okay
 */
static int __init(const struct shell_transport* transport,
                  const void* config,
                  shell_transport_handler_t evt_handler,
                  void* context) {
  // Save context for ISR
  __cdc_acm = (struct shell_cdc_acm*)transport->ctx;
  __cdc_acm->handler = evt_handler;
  __cdc_acm->context = context;
  __cdc_acm->dev = device_get_binding(CONFIG_UART_CONSOLE_ON_DEV_NAME);

  if (!__cdc_acm->dev) {
    LOG_ERR("CDC ACM device not found");
    return -1;
  }

  // // Block CDC init until DTR signal received from host
  // while (1) {
  //   // LOG_DBG("Wait for DTR");
  //   uart_line_ctrl_get(__cdc_acm->dev, LINE_CTRL_DTR, &dtr);
  //   if (dtr)
  //     break;
  //   k_sleep(1000);
  // }
  // LOG_DBG("DTR set, start test");

  // /* They are optional, we use them to test the interrupt endpoint */
  // ret = uart_line_ctrl_set(__cdc_acm->dev, LINE_CTRL_DCD, 1);
  // if (ret)
  //   LOG_DBG("Failed to set DCD, ret code %d", ret);

  // ret = uart_line_ctrl_set(__cdc_acm->dev, LINE_CTRL_DSR, 1);
  // if (ret)
  //   LOG_DBG("Failed to set DSR, ret code %d", ret);

  // /* Wait 1 sec for the host to do all settings */
  // k_busy_wait(1000000);

  // ret = uart_line_ctrl_get(__cdc_acm->dev, LINE_CTRL_BAUD_RATE, &baudrate);
  // if (ret) {
  //   LOG_DBG("Failed to get baudrate, ret code %d", ret);
  // } else {
  //   LOG_DBG("Baudrate detected: %d", baudrate);
  // }

  uart_irq_callback_set(__cdc_acm->dev, __cdc_interrupt_handler);

  /* Enable rx interrupts */
  uart_irq_rx_enable(__cdc_acm->dev);

  __connected = true;

  // char* welcome = "\033[2JWelcome to AND!XOR DC28\r\n";
  // for (size_t i = 0; i < strlen(welcome); i++) {
  //   uart_poll_out(__cdc_acm->dev, welcome[i]);
  // }

  return 0;
}

/**
 * @brief Un-init the shell cdc acm driver. Right now this does nothing
 */
static int __uninit(const struct shell_transport* transport) {
  __connected = false;
  return 0;
}

/**
 * @brief Enable something. Not sure what, but I have to include it in the API.
 * Sigh.
 */
static int __enable(const struct shell_transport* transport, bool blocking) {
  return 0;
}

/**
 * @brief Write arbitrary data to the CDC ACM device
 * @param transport   : Shell transport / device to use
 * @param data        : Pointer to arbitrary data to write
 * @param length      : Length of data to write
 * @param cnt         : Where to write the actual byte written count
 * @return Error or 0 if success
 */
static int __write(const struct shell_transport* transport,
                   const void* data,
                   size_t length,
                   size_t* cnt) {
  struct shell_cdc_acm* sh_cdc_acm = (struct shell_cdc_acm*)transport->ctx;

  // Only write if DTR has been set by a terminal
  uint32_t dtr;
  uart_line_ctrl_get(sh_cdc_acm->dev, UART_LINE_CTRL_DTR, &dtr);
  if (dtr) {
    char* c_data = (char*)data;
    for (size_t i = 0; i < length; i++) {
      if (c_data[i] == '\n') {
        uart_poll_out(sh_cdc_acm->dev, '\r');
      }
      uart_poll_out(sh_cdc_acm->dev, c_data[i]);
    }
  }

  *cnt = length;

  // Notify shell that data is ready to be transmitted
  sh_cdc_acm->handler(SHELL_TRANSPORT_EVT_TX_RDY, sh_cdc_acm->context);

  return 0;
}

/**
 * @brief Read some amount of data from the shell transport. Our implementation
 * only reads single bytes from the USB CDC driver.
 * @param transport   : The shell transport context to use
 * @param data        : Pointer to buffer to store the data read
 * @param length      : Maximum size of the data buffer we can store
 * @param cnt         : OUT actual count of bytes read
 * @return 0 if successful
 */
static int __read(const struct shell_transport* transport,
                  void* data,
                  size_t length,
                  size_t* cnt) {
  struct shell_cdc_acm* sh_cdc_acm = (struct shell_cdc_acm*)transport->ctx;

  size_t read_length = MIN(length, sh_cdc_acm->rx_cnt);

  if (sh_cdc_acm->rx_cnt) {
    memcpy(data, sh_cdc_acm->rx, read_length);
    sh_cdc_acm->rx_cnt = 0;
    *cnt = read_length;
  } else {
    *cnt = 0;
  }

  return 0;
}

/**
 * @brief Return true if the cdc acm is connected
 */
bool wh_shell_cdc_acm_is_connected() {
  return __connected;
}

/**
 * Shell transport API definitions
 */
const struct shell_transport_api shell_cdc_acm_transport_api = {
    .init = __init,
    .uninit = __uninit,
    .enable = __enable,
    .write = __write,
    .read = __read};