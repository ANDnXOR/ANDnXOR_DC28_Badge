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
#include <drivers/uart.h>
#include <logging/log.h>
#include <logging/log_backend.h>
#include <logging/log_output.h>
#include <zephyr.h>

/**
 * Implementation of this backend is mostly copied from log_backend_std.h that
 * is not availabled for our use by the Zephyr API. We may need to track this
 * file for changes and copy them over. But this should be good enough for
 * badge-work.
 */

LOG_MODULE_REGISTER(wh_log_cdc_acm, 4);

// Buffer to use by the standard logger
static uint8_t m_buffer;

/**
 * @brief Write a single character out to the log backend via the desired USB
 * CDC ACM device
 */
static int __char_out(u8_t* data, size_t length, void* ctx) {
  struct device* dev = (struct device*)ctx;

  if (length > 32) {
    return length;
  }

  // Only log if DTR has been set by a terminal
  uint32_t dtr;
  uart_line_ctrl_get(dev, UART_LINE_CTRL_DTR, &dtr);
  if (!dtr) {
    return -1;
  }

  for (size_t i = 0; i < length; i++) {
    if (data[i] == '\n') {
      uart_poll_out(dev, '\r');
    }
    uart_poll_out(dev, data[i]);
  }

  return length;
}
LOG_OUTPUT_DEFINE(log_output, __char_out, &m_buffer, 1);

/**
 * @brief Process a single message by the log backend, in this case send the log
 * message properly formatted to our desired USB CDC ACM device
 */
static void __put(const struct log_backend* const backend,
                  struct log_msg* msg) {
  uint32_t flags = IS_ENABLED(CONFIG_LOG_BACKEND_UART_SYST_ENABLE)
                       ? LOG_OUTPUT_FLAG_FORMAT_SYST
                       : 0;
  uint32_t dtr;

  log_msg_get(msg);

  // Only log if DTR has been set by a terminal
  struct device* dev = device_get_binding(CONFIG_WH_LOG_CDC_ACM_DEVICE_NAME);
  if (dev) {
    uart_line_ctrl_get(dev, UART_LINE_CTRL_DTR, &dtr);
    if (dtr) {
      flags |= (LOG_OUTPUT_FLAG_LEVEL | LOG_OUTPUT_FLAG_TIMESTAMP);

      if (IS_ENABLED(CONFIG_LOG_BACKEND_SHOW_COLOR)) {
        flags |= LOG_OUTPUT_FLAG_COLORS;
      }

      if (IS_ENABLED(CONFIG_LOG_BACKEND_FORMAT_TIMESTAMP)) {
        flags |= LOG_OUTPUT_FLAG_FORMAT_TIMESTAMP;
      }

      log_output_msg_process(&log_output, msg, flags);
    }
  }
  log_msg_put(msg);
}

/**
 * @brief Initialize the backend logger. Setup the USB CDC ACM device and start
 * the standard logger with it
 */
static void __init(void) {
  struct device* dev;

  dev = device_get_binding(CONFIG_WH_LOG_CDC_ACM_DEVICE_NAME);
  if (!dev) {
    LOG_ERR("CDC ACM device '%s' used for logging not found",
            CONFIG_WH_LOG_CDC_ACM_DEVICE_NAME);
    return;
  }

  log_output_ctx_set(&log_output, dev);
}

/**
 * @brief Put a standard logger backend into panic mode.
 * @param log_output	Log output instance.
 */
static void __panic(struct log_backend const* const backend) {
  log_output_flush(&log_output);
}

/**
 * @brief Report dropped messages to a standard logger backend.
 * @param log_output	Log output instance.
 * @param cnt		Number of dropped messages.
 */
static void __dropped(const struct log_backend* const backend, uint32_t cnt) {
  ARG_UNUSED(backend);

  log_output_dropped_process(&log_output, cnt);
}

/**
 * @brief Synchronously process log message by a standard logger backend.
 * @param log_output	Log output instance.
 * @param flags		Formatting flags.
 * @param src_level	Log message source and level.
 * @param timestamp	Timestamp.
 * @param fmt		Log string.
 * @param ap		Log string arguments.
 */
static void __sync_string(const struct log_backend* const backend,
                          struct log_msg_ids src_level,
                          uint32_t timestamp,
                          const char* fmt,
                          va_list ap) {
  uint32_t flags = IS_ENABLED(CONFIG_LOG_BACKEND_UART_SYST_ENABLE)
                       ? LOG_OUTPUT_FLAG_FORMAT_SYST
                       : 0;

  uint32_t key;
  uint32_t dtr;

  struct device* dev = device_get_binding(CONFIG_WH_LOG_CDC_ACM_DEVICE_NAME);
  if (dev) {
    uart_line_ctrl_get(dev, UART_LINE_CTRL_DTR, &dtr);
    if (dtr) {
      flags |= LOG_OUTPUT_FLAG_LEVEL | LOG_OUTPUT_FLAG_TIMESTAMP;
      if (IS_ENABLED(CONFIG_LOG_BACKEND_SHOW_COLOR)) {
        flags |= LOG_OUTPUT_FLAG_COLORS;
      }

      if (IS_ENABLED(CONFIG_LOG_BACKEND_FORMAT_TIMESTAMP)) {
        flags |= LOG_OUTPUT_FLAG_FORMAT_TIMESTAMP;
      }

      key = irq_lock();
      /* Even though interrupts are locked here there are still cases when
       * it may lead to failure. Log output is not re-entrant and irq_lock
       * does not prevent NMI or ZLI (Zero latency interrupts). If context
       * is interrupted by NMI it usually means fault scenario and best that
       * can be done is to flush the output and process new data.
       */
      log_output_flush(&log_output);
      log_output_string(&log_output, src_level, timestamp, fmt, ap, flags);
      irq_unlock(key);
    }
  }
}

/**
 * @brief Synchronously process hexdump message by a standard logger backend.
 * @param log_output	Log output instance.
 * @param flags		Formatting flags.
 * @param src_level	Log message source and level.
 * @param timestamp	Timestamp.
 * @param metadata	String associated with a hexdump.
 * @param data		Buffer to dump.
 * @param length	Length of the buffer.
 */
static void __sync_hexdump(const struct log_backend* const backend,
                           struct log_msg_ids src_level,
                           uint32_t timestamp,
                           const char* metadata,
                           const u8_t* data,
                           uint32_t length) {
  uint32_t flags = IS_ENABLED(CONFIG_LOG_BACKEND_UART_SYST_ENABLE)
                       ? LOG_OUTPUT_FLAG_FORMAT_SYST
                       : 0;
  uint32_t key;

  flags |= LOG_OUTPUT_FLAG_LEVEL | LOG_OUTPUT_FLAG_TIMESTAMP;
  if (IS_ENABLED(CONFIG_LOG_BACKEND_SHOW_COLOR)) {
    flags |= LOG_OUTPUT_FLAG_COLORS;
  }

  if (IS_ENABLED(CONFIG_LOG_BACKEND_FORMAT_TIMESTAMP)) {
    flags |= LOG_OUTPUT_FLAG_FORMAT_TIMESTAMP;
  }

  key = irq_lock();
  /* Even though interrupts are locked here there are still cases when
   * it may lead to failure. Log output is not re-entrant and irq_lock
   * does not prevent NMI or ZLI (Zero latency interrupts). If context
   * is interrupted by NMI it usually means fault scenario and best that
   * can be done is to flush the output and process new data.
   */
  log_output_flush(&log_output);
  log_output_hexdump(&log_output, src_level, timestamp, metadata, data, length,
                     flags);
  irq_unlock(key);
}

const struct log_backend_api m_log_api = {
    .put = IS_ENABLED(CONFIG_LOG_IMMEDIATE) ? NULL : __put,
    .put_sync_string = IS_ENABLED(CONFIG_LOG_IMMEDIATE) ? __sync_string : NULL,
    .put_sync_hexdump =
        IS_ENABLED(CONFIG_LOG_IMMEDIATE) ? __sync_hexdump : NULL,
    .panic = __panic,
    .init = __init,
    .dropped = IS_ENABLED(CONFIG_LOG_IMMEDIATE) ? NULL : __dropped,
};

LOG_BACKEND_DEFINE(wh_log_cdc_acm, m_log_api, true);