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
#include "st7735.h"

#include <device.h>
#include <drivers/display.h>
#include <drivers/dma.h>
#include <drivers/gpio.h>
#include <drivers/spi.h>
#include <logging/log.h>
#include <sys/byteorder.h>
#include <zephyr.h>

#include "../system.h"
#include "../wh_ui.h"
#include "autoconf.h"
#include "devicetree.h"

LOG_MODULE_REGISTER(st7735, CONFIG_ST7735_LOG_LEVEL);

#define CS_CONTROLLER DT_INST_0_ST7735_CS_GPIOS_CONTROLLER
#define CS_PIN DT_INST_0_ST7735_CS_GPIOS_PIN
#define CMD_CONTROLLER DT_INST_0_ST7735_CMD_DATA_GPIOS_CONTROLLER
#define CMD_PIN DT_INST_0_ST7735_CMD_DATA_GPIOS_PIN
#define BACKLIGHT_CONTROLLER DT_INST_0_ST7735_BACKLIGHT_GPIOS_CONTROLLER
#define BACKLIGHT_PIN DT_INST_0_ST7735_BACKLIGHT_GPIOS_PIN
#define RESET_CONTROLLER DT_INST_0_ST7735_RESET_GPIOS_CONTROLLER
#define RESET_PIN DT_INST_0_ST7735_RESET_GPIOS_PIN

struct st7735_data {
  struct spi_config spi_config;
  struct spi_cs_control spi_cs_ctrl;
  struct device* spi;
  struct device* gpio_reset;
  struct device* gpio_dc;
  struct device* gpio_backlight;
  uint16_t x_offset;
  uint16_t y_offset;
};

static struct st7735_data st7735_driver;
/**
 * @brief Write a single byte to the TFT SPI
 */
static int __write(uint8_t c) {
  if (!st7735_driver.spi) {
    return -ENODEV;
  }
  struct spi_buf bufs[] = {{.buf = &c, .len = 1}};
  struct spi_buf_set tx = {.buffers = bufs};

  int err = spi_write(st7735_driver.spi, &st7735_driver.spi_config, &tx);
  return err;
}

/**
 * @brief Write a command followed by some data
 */
static void __write_buffer(struct st7735_data* data,
                           uint8_t cmd,
                           const void* tx_data,
                           size_t tx_count) {
  struct spi_buf tx_buf = {.buf = &cmd, .len = 1};
  struct spi_buf_set tx_bufs = {.buffers = &tx_buf, .count = 1};

  gpio_pin_set(st7735_driver.gpio_dc, CMD_PIN, 0);
  spi_write_async(data->spi, &data->spi_config, &tx_bufs, NULL);

  if (tx_data != NULL) {
    tx_buf.buf = (void*)tx_data;
    tx_buf.len = tx_count;
    gpio_pin_set(st7735_driver.gpio_dc, CMD_PIN, 1);
    spi_write_async(data->spi, &data->spi_config, &tx_bufs, NULL);
  }
}

/**
 * Write a command to the TFT
 */
static void __cmd(uint8_t c) {
  if (!st7735_driver.gpio_dc) {
    return;
  }

  // When writing data, DC pin must be low
  k_mutex_lock(&g_mutex_display_dc, K_FOREVER);
  gpio_pin_set(st7735_driver.gpio_dc, CMD_PIN, 0);

  int err = __write(c);
  if (err) {
    LOG_ERR("Unable to write cmd 0x%2x [%d]", c, err);
  }
  k_mutex_unlock(&g_mutex_display_dc);
}

/**
 * Write data to the TFT
 */
static void __data(uint8_t c) {
  if (!st7735_driver.gpio_dc) {
    return;
  }

  // When writing data, DC pin must be high
  k_mutex_lock(&g_mutex_display_dc, K_FOREVER);
  gpio_pin_set(st7735_driver.gpio_dc, CMD_PIN, 1);
  __write(c);
  k_mutex_unlock(&g_mutex_display_dc);
}

/**
 * @brief Set the windsdfow to draw the buffer to
 * @param data Pointer to driver data
 * @param x Leftmost coordinate of window to draw to
 * @param y Topmost coordinate of window to draw to
 * @param w Width of window
 * @param h Height of window
 */
static void __window_set(struct st7735_data* data,
                         const uint16_t x,
                         const uint16_t y,
                         const uint16_t w,
                         const uint16_t h) {
  uint16_t spi_data[2];

  uint16_t ram_x = x + data->x_offset;
  uint16_t ram_y = y + data->y_offset;

  // LOG_DBG("Setting window to x=%d y=%d w=%d h=%d", x,y,w,h);

  spi_data[0] = sys_cpu_to_be16(ram_x);
  spi_data[1] = sys_cpu_to_be16(ram_x + w - 1);
  __write_buffer(data, ST7735_CASET, (uint8_t*)&spi_data[0], 4);

  spi_data[0] = sys_cpu_to_be16(ram_y);
  spi_data[1] = sys_cpu_to_be16(ram_y + h - 1);
  __write_buffer(data, ST7735_RASET, (uint8_t*)&spi_data[0], 4);
}

static int __st7735_blanking_on(const struct device* dev) {
  return -ENOTSUP;
}

static int __st7735_blanking_off(const struct device* dev) {
  return -ENOTSUP;
}

/**
 * @brief Get the displays capabilities such as width/height bpp etc
 */
static void __st7735_get_capabilities(const struct device* dev,
                                      struct display_capabilities* caps) {
  memset(caps, 0, sizeof(struct display_capabilities));
  caps->x_resolution = DT_INST_0_ST7735_WIDTH;
  caps->y_resolution = DT_INST_0_ST7735_HEIGHT;
  caps->supported_pixel_formats = PIXEL_FORMAT_RGB_565;
  caps->current_pixel_format = PIXEL_FORMAT_RGB_565;
  caps->screen_info = SCREEN_INFO_MONO_VTILED;
  caps->current_orientation = DISPLAY_ORIENTATION_NORMAL;
}

static void* __st7735_get_framebuffer(const struct device* dev) {
  return NULL;
}

/**
 * @brief Change display brightness
 */
static int __st7735_set_brightness(const struct device* dev,
                                   const uint8_t brightness) {
  LOG_ERR("Unsupported");
  return -ENOTSUP;
}

/**
 * @brief Change display contrast
 */
static int __st7735_set_contrast(const struct device* dev,
                                 const uint8_t contrast) {
  LOG_ERR("Unsupported");
  return -ENOTSUP;
}

/**
 * @brief Change the orientation of the display
 */
static int __st7735_set_orientation(
    const struct device* dev,
    const enum display_orientation orientation) {
  __cmd(ST7735_MADCTL);
  switch (orientation) {
    case DISPLAY_ORIENTATION_NORMAL:
      __data(0xC0);
      break;
    case DISPLAY_ORIENTATION_ROTATED_90:
      __data(0xA0);
      break;
    case DISPLAY_ORIENTATION_ROTATED_180:
      __data(0x00);
      break;
    case DISPLAY_ORIENTATION_ROTATED_270:
      __data(0x60);
      break;
  }

  return 0;
}

/**
 * @brief Change the pixel format of the display. Only MONO is supported.
 */
static int __st7735_set_pixel_format(const struct device* dev,
                                     const enum display_pixel_format pf) {
  if (pf == PIXEL_FORMAT_MONO10) {
    return 0;
  }
  LOG_ERR("Unsupported");
  return -ENOTSUP;
}

/**
 * @brief Read data from display buffer - currently unsupported
 */
static int __st7735_read(const struct device* dev,
                         const uint16_t x,
                         const uint16_t y,
                         const struct display_buffer_descriptor* desc,
                         void* buf) {
  return -ENOTSUP;
}

/**
 * @brief Write a buffer to the screen over SPI
 * @param x Left most coordinate
 * @param y Right most coordinate
 * @param desc Pointer to struct describing buffer to write
 * @param buf Buffer to write to screen over SPI
 * @return 0 if no error
 */
static int __st7735_write(const struct device* dev,
                          const uint16_t x,
                          const uint16_t y,
                          const struct display_buffer_descriptor* desc,
                          const void* buf) {
  struct st7735_data* data = (struct st7735_data*)dev->driver_data;
  __window_set(&st7735_driver, x, y, desc->width, desc->height);
  __write_buffer(data, ST7735_RAMWR, buf, desc->width * desc->height * 2);

  return 0;
}

// static void dma_user_callback(void* arg, u32_t id, int error_code) {
//   LOG_DBG("Transfer done code=%d", error_code);
// }

// #define DMA_STREAM 3
// #define DMA_CHANNEL 3
// static struct dma_config dma_cfg = {0};
// static struct dma_block_config dma_blk = {0};

// static int __dma_init(struct device* dev) {
//   dma_cfg.channel_direction = MEMORY_TO_PERIPHERAL;
//   dma_cfg.source_data_size = 1;
//   dma_cfg.dest_data_size = 1;
//   dma_cfg.block_count = 1;
//   dma_cfg.head_block = &dma_blk;
//   dma_cfg.dma_slot = DMA_STREAM;
//   dma_cfg.source_burst_length = 1;
//   dma_cfg.dest_burst_length = 1;
//   dma_cfg.dma_callback = dma_user_callback;
//   dma_cfg.error_callback_en = 0;
//   dma_cfg.complete_callback_en = 0;
//   // dma_cfg.channel_priority = 0x3;

//   struct device* dma_dev = device_get_binding("DMA_2");
//   int retval = dma_config(dma_dev, DMA_CHANNEL, &dma_cfg);
//   LOG_DBG("dma_config result = %d", retval);

//   if (retval != 0) {
//     LOG_ERR("Unable to configure DMA [%d]", retval);
//     return;
//   }
// }

/**
 * @brief Initialize the LED Matrix Driver
 */
static int __st7735_init(struct device* dev) {
  LOG_DBG("Init");

  struct st7735_data* data = (struct st7735_data*)dev->driver_data;

  // Default offsets
  data->x_offset = 1;
  data->y_offset = 2;

  // Grab the SPI peripheral
  st7735_driver.spi = device_get_binding(DT_INST_0_ST7735_BUS_NAME);
  if (!st7735_driver.spi) {
    LOG_ERR("Unable to get SPI device '%s'", DT_INST_0_ST7735_BUS_NAME);
    return -1;
  }

  // Configure SPI peripheral according to DTS
  data->spi_config.frequency = DT_INST_0_ST7735_SPI_MAX_FREQUENCY;
  data->spi_config.operation = SPI_OP_MODE_MASTER | SPI_WORD_SET(8);
  data->spi_config.slave = DT_INST_0_ST7735_BASE_ADDRESS;

  // Grab various GPIO devices
  st7735_driver.gpio_dc = device_get_binding(CMD_CONTROLLER);
  if (!st7735_driver.gpio_dc) {
    LOG_ERR("Unable to get DC GPIO Port '%s'", CMD_CONTROLLER);
    return -1;
  }

  st7735_driver.gpio_reset = device_get_binding(RESET_CONTROLLER);
  if (!st7735_driver.gpio_reset) {
    LOG_ERR("Unable to get RESET GPIO Port '%s'", RESET_CONTROLLER);
    return -1;
  }

  st7735_driver.gpio_backlight = device_get_binding(BACKLIGHT_CONTROLLER);
  if (!st7735_driver.gpio_backlight) {
    LOG_ERR("Unable to get backlight GPIO Port '%s'", BACKLIGHT_CONTROLLER);
    return -1;
  }

  st7735_driver.spi_cs_ctrl.gpio_dev = device_get_binding(CS_CONTROLLER);
  if (!st7735_driver.spi_cs_ctrl.gpio_dev) {
    LOG_ERR("Unable to get CS GPIO Port '%s'", CS_CONTROLLER);
    return -1;
  }

  st7735_driver.spi_cs_ctrl.gpio_pin = CS_PIN;
  st7735_driver.spi_cs_ctrl.delay = 0;
  st7735_driver.spi_config.cs = &st7735_driver.spi_cs_ctrl;

  // Make DC RESET pins output
  gpio_pin_configure(st7735_driver.gpio_dc, CMD_PIN, GPIO_OUTPUT);
  gpio_pin_configure(st7735_driver.gpio_reset, RESET_PIN, GPIO_OUTPUT);
  gpio_pin_configure(st7735_driver.gpio_backlight, BACKLIGHT_PIN, GPIO_OUTPUT);

  // Turn off the backlight
  gpio_pin_set(st7735_driver.gpio_backlight, BACKLIGHT_PIN, 1);

  // Reset TFT
  gpio_pin_set(st7735_driver.gpio_reset, RESET_PIN, 0);
  k_sleep(K_MSEC(200));
  gpio_pin_set(st7735_driver.gpio_reset, RESET_PIN, 1);

  // Software reset
  __cmd(ST7735_SWRESET);
  k_sleep(K_MSEC(150));

  // Out of sleep mode
  __cmd(ST7735_SLPOUT);
  k_sleep(K_MSEC(200));

  // Set color mode, 16-bit
  __cmd(ST7735_COLMOD);
  __data(0x05);
  k_sleep(K_MSEC(10));

  // Frame rate control, fastest refresh, 6 lines front porch, 3 lines back
  // porch
  __cmd(ST7735_FRMCTR1);
  __data(0x00);
  __data(0x06);
  __data(0x03);
  k_sleep(K_MSEC(10));

  // Memory access control, Row addr/col addr, bottom to top refresh
  __cmd(ST7735_MADCTL);
  __data(0xC0);

  // Display settings #5, 1 clk cycle nonoverlap, 2 cycle gate rise, 3 cycle osc
  // equalize
  __cmd(ST7735_DISSET5);
  __data(0x15);
  __data(0x02);

  __cmd(ST7735_INVCTR);
  __data(0x07);

  __cmd(ST7735_PWCTR1);
  __data(0x02);
  __data(0x70);
  k_sleep(K_MSEC(10));

  __cmd(ST7735_PWCTR2);
  __data(0x05);

  __cmd(ST7735_PWCTR3);
  __data(0x01);
  __data(0x02);

  __cmd(ST7735_VMCTR1);
  __data(0x3C);
  __data(0x38);
  k_sleep(K_MSEC(10));

  __cmd(ST7735_PWCTR6);
  __data(0x11);
  __data(0x15);

  // shrug
  __cmd(ST7735_GMCTRP1);
  __data(0x09);
  __data(0x16);
  __data(0x09);
  __data(0x20);
  __data(0x21);
  __data(0x1B);
  __data(0x13);
  __data(0x19);
  __data(0x17);
  __data(0x15);
  __data(0x1E);
  __data(0x2B);
  __data(0x04);
  __data(0x05);
  __data(0x02);
  __data(0x0E);

  // shrug
  __cmd(ST7735_GMCTRN1);
  __data(0x0B);
  __data(0x14);
  __data(0x08);
  __data(0x1E);
  __data(0x22);
  __data(0x1D);
  __data(0x18);
  __data(0x1E);
  __data(0x1B);
  __data(0x1A);
  __data(0x24);
  __data(0x2B);
  __data(0x06);
  __data(0x06);
  __data(0x02);
  __data(0x0F);
  k_sleep(K_MSEC(10));

  __cmd(ST7735_CASET);
  __data(0x00);
  __data(0x02);
  __data(0x00);
  __data(0x81);

  __cmd(ST7735_RASET);
  __data(0x00);
  __data(0x02);
  __data(0x00);
  __data(0x81);

  __cmd(ST7735_NORON);
  k_sleep(K_MSEC(10));

  __cmd(ST7735_DISPON);
  k_sleep(K_MSEC(200));

  __cmd(ST7735_RAMWR);  // write to RAM

  // Turn on the backlight
  gpio_pin_set(st7735_driver.gpio_backlight, BACKLIGHT_PIN, 0);

  return 0;
}

/**
 * @brief Set the current window to write on the display. This must be called at
 * least once before st7735_write_buffer()
 * @param x Start X coordinate
 * @param y Start Y coordinate
 * @param w Width
 * @param y Height
 */
void st7735_window_set(int16_t x, int16_t y, uint16_t w, uint16_t h) {
  uint8_t cmd = ST7735_RAMWR;
  __window_set(&st7735_driver, x, y, w, h);

  struct spi_buf tx_buf = {.buf = &cmd, .len = 1};
  struct spi_buf_set tx_bufs = {.buffers = &tx_buf, .count = 1};

  gpio_pin_set(st7735_driver.gpio_dc, CMD_PIN, 0);
  spi_write_async(st7735_driver.spi, &st7735_driver.spi_config, &tx_bufs, NULL);
  gpio_pin_set(st7735_driver.gpio_dc, CMD_PIN, 1);
}

/**
 * @brief Write a buffer of pixels to the display
 * @param buffer Pointer to memory to write
 * @param count The number of bytes to write
 */
void st7735_write_buffer(void* buffer, ssize_t count) {
  if (count < 0) {
    return;
  }
  struct spi_buf tx_buf = {.buf = buffer, .len = count};
  struct spi_buf_set tx_bufs = {.buffers = &tx_buf, .count = 1};
  spi_write_async(st7735_driver.spi, &st7735_driver.spi_config, &tx_bufs, NULL);

  // gpio_pin_set(st7735_driver.spi_cs_ctrl.gpio_dev, CS_PIN, 0);

  // int retval;

  // // dma_blk.fifo_mode_control = 0;
  // dma_blk.block_size = (uint32_t)count;
  // dma_blk.source_address = (uint32_t)buffer;
  // dma_blk.dest_address = (uint32_t)0x40013000U;
  // dma_blk.dest_addr_adj = DMA_ADDR_ADJ_NO_CHANGE;
  // dma_blk.source_addr_adj = DMA_ADDR_ADJ_NO_CHANGE;
  // // dma_blk.source_reload_en = 1;
  // // dma_blk.dest_reload_en = 1;

  // struct device* dma_dev = device_get_binding("DMA_2");
  // retval =
  //     dma_reload(dma_dev, DMA_CHANNEL, (uint32_t)buffer, 0x40013000U, count);
  // if (retval) {
  //   LOG_ERR("Unable to reload DMA [%d]", retval);
  // }

  // retval = dma_start(dma_dev, DMA_CHANNEL);
  // if (retval) {
  //   LOG_ERR("Unable to start DMA [%d]", retval);
  // }
  // k_sleep(500);
  // gpio_pin_set(st7735_driver.spi_cs_ctrl.gpio_dev, CS_PIN, 1);
  // LOG_DBG("Done");
}

static struct display_driver_api st7735_driver_api = {
    .blanking_on = __st7735_blanking_on,
    .blanking_off = __st7735_blanking_off,
    .write = __st7735_write,
    .read = __st7735_read,
    .get_framebuffer = __st7735_get_framebuffer,
    .set_brightness = __st7735_set_brightness,
    .set_contrast = __st7735_set_contrast,
    .get_capabilities = __st7735_get_capabilities,
    .set_pixel_format = __st7735_set_pixel_format,
    .set_orientation = __st7735_set_orientation,
};

DEVICE_AND_API_INIT(st7735,
                    DT_INST_0_ST7735_LABEL,
                    __st7735_init,
                    &st7735_driver,
                    NULL,
                    POST_KERNEL,
                    CONFIG_APPLICATION_INIT_PRIORITY,
                    &st7735_driver_api);

// //#define DEVICE_INIT(dev_name, drv_name, init_fn, data, cfg_info, level,
// prio) DEVICE_INIT(st7735_dma,
//             "ST7735_DMA",
//             __dma_init,
//             NULL,
//             NULL,
//             POST_KERNEL,
//             60);