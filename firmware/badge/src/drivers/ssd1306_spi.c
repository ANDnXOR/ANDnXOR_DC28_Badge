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
#include "ssd1306_spi.h"

#include <device.h>
#include <drivers/display.h>
#include <drivers/gpio.h>
#include <drivers/spi.h>
#include <logging/log.h>
#include <sys/byteorder.h>
#include <zephyr.h>

#include "../system.h"
#include "autoconf.h"
#include "devicetree.h"

LOG_MODULE_REGISTER(ssd1306_spi, CONFIG_SSD1306_SPI_LOG_LEVEL);

#define CS_CONTROLLER DT_INST_0_SSD1306_SPI_CS_GPIOS_CONTROLLER
#define CS_PIN DT_INST_0_SSD1306_SPI_CS_GPIOS_PIN
#define CMD_CONTROLLER DT_INST_0_SSD1306_SPI_CMD_DATA_GPIOS_CONTROLLER
#define CMD_PIN DT_INST_0_SSD1306_SPI_CMD_DATA_GPIOS_PIN
#define RESET_CONTROLLER DT_INST_0_SSD1306_SPI_RESET_GPIOS_CONTROLLER
#define RESET_PIN DT_INST_0_SSD1306_SPI_RESET_GPIOS_PIN
#define WIDTH DT_INST_0_SSD1306_SPI_WIDTH
#define HEIGHT DT_INST_0_SSD1306_SPI_HEIGHT
#define NUM_PAGES (HEIGHT / 8)
#define NUM_COLS 128

struct ssd1306_data {
  struct spi_config spi_config;
  struct spi_cs_control spi_cs_ctrl;
  struct device* spi;
  struct device* gpio_reset;
  struct device* gpio_dc;
  uint16_t x_offset;
  uint16_t y_offset;
};

static struct ssd1306_data m_ssd1306_driver;

/**
 * @brief Write a single byte to the TFT SPI
 */
static int __write(uint8_t c) {
  if (!m_ssd1306_driver.spi) {
    return -ENODEV;
  }
  struct spi_buf bufs[] = {{.buf = &c, .len = 1}};
  struct spi_buf_set tx = {.buffers = bufs};
  int err = spi_write(m_ssd1306_driver.spi, &m_ssd1306_driver.spi_config, &tx);
  return err;
}

/**
 * Write a command to the TFT
 */
static void __cmd(uint8_t c) {
  if (!m_ssd1306_driver.gpio_dc) {
    return;
  }

  // When writing data, DC pin must be low
  gpio_pin_set(m_ssd1306_driver.gpio_dc, CMD_PIN, 0);

  int err = __write(c);
  if (err) {
    LOG_ERR("Unable to write cmd 0x%2x [%d]", c, err);
  }
}

/**
 * @brief Write some data
 */
static void __write_buffer(struct ssd1306_data* data,
                           void* tx_data,
                           size_t tx_count) {
  struct spi_buf tx_buf = {.buf = tx_data, .len = tx_count};
  struct spi_buf_set tx_bufs = {.buffers = &tx_buf, .count = 1};

  if (tx_data != NULL) {
    gpio_pin_set(m_ssd1306_driver.gpio_dc, CMD_PIN, 1);
    spi_write_async(data->spi, &data->spi_config, &tx_bufs, NULL);
  }
}

/**
 * @brief Write a page of data to the display
 */
int __write_page(const struct device* dev,
                 uint8_t page,
                 void const* data,
                 size_t length) {
  struct ssd1306_data* driver = dev->driver_data;

  if (page >= NUM_PAGES) {
    return -1;
  }

  if (length > NUM_COLS) {
    return -1;
  }

  __cmd(SSD1306_PAGEADDR);
  __cmd(page);

  struct spi_buf tx_buf = {.buf = (void*)data, .len = length};
  struct spi_buf_set tx_bufs = {.buffers = &tx_buf, .count = 1};

  gpio_pin_set(m_ssd1306_driver.gpio_dc, CMD_PIN, 1);
  spi_write_async(driver->spi, &driver->spi_config, &tx_bufs, NULL);

  return 0;
}

/**
 * @brief Write a command followed by some data
 */
// static void __write_cmd_buffer(struct ssd1306_data* data,
//                                uint8_t cmd,
//                                uint8_t* tx_data,
//                                size_t tx_count) {
//   struct spi_buf tx_buf = {.buf = &cmd, .len = 1};
//   struct spi_buf_set tx_bufs = {.buffers = &tx_buf, .count = 1};

//   gpio_pin_set(m_ssd1306_driver.gpio_dc, CMD_PIN, 0);
//   spi_write(data->spi, &data->spi_config, &tx_bufs);

//   if (tx_data != NULL) {
//     tx_buf.buf = tx_data;
//     tx_buf.len = tx_count;
//     gpio_pin_set(m_ssd1306_driver.gpio_dc, CMD_PIN, 1);
//     spi_write_async(data->spi, &data->spi_config, &tx_bufs, NULL);
//   }
// }

/**
 * Write data to the TFT
 */
// static void __data(uint8_t c) {
//   if (!m_ssd1306_driver.gpio_dc) {
//     return;
//   }

//   // When writing data, DC pin must be high
//   gpio_pin_set(m_ssd1306_driver.gpio_dc, CMD_PIN, 1);
//   __write(c);
// }

/**
 * @brief Set the windsdfow to draw the buffer to
 * @param data Pointer to driver data
 * @param x Leftmost coordinate of window to draw to
 * @param y Topmost coordinate of window to draw to
 * @param w Width of window
 * @param h Height of window
 */
// static void __window_set(struct ssd1306_data* data,
//                          const uint16_t x,
//                          const uint16_t y,
//                          const uint16_t w,
//                          const uint16_t h) {
//   uint16_t spi_data[2];

//   uint16_t ram_x = x + data->x_offset;
//   uint16_t ram_y = y + data->y_offset;

//   spi_data[0] = sys_cpu_to_be16(ram_x);
//   spi_data[1] = sys_cpu_to_be16(ram_x + w - 1);
//   __write_cmd_buffer(data, SSD1306_COLUMNADDR, (uint8_t*)&spi_data[0], 4);

//   spi_data[0] = sys_cpu_to_be16(ram_y / 8);
//   spi_data[1] = sys_cpu_to_be16((ram_y + h - 1) / 8);
//   __write_cmd_buffer(data, SSD1306_PAGEADDR, (uint8_t*)&spi_data[0], 4);
// }

static int __ssd1306_spi_blanking_on(const struct device* dev) {
  return -ENOTSUP;
}

static int __ssd1306_spi_blanking_off(const struct device* dev) {
  return -ENOTSUP;
}

/**
 * @brief Get the displays capabilities such as width/height bpp etc
 */
static void __ssd1306_spi_get_capabilities(const struct device* dev,
                                           struct display_capabilities* caps) {
  memset(caps, 0, sizeof(struct display_capabilities));
  caps->x_resolution = WIDTH;
  caps->y_resolution = HEIGHT;
  caps->supported_pixel_formats = PIXEL_FORMAT_MONO01;
  caps->current_pixel_format = PIXEL_FORMAT_MONO01;
  caps->screen_info = SCREEN_INFO_MONO_VTILED;
  caps->current_orientation = DISPLAY_ORIENTATION_NORMAL;
}

static void* __ssd1306_spi_get_framebuffer(const struct device* dev) {
  return NULL;
}

/**
 * @brief Change display brightness
 */
static int __ssd1306_spi_set_brightness(const struct device* dev,
                                        const uint8_t brightness) {
  LOG_ERR("Unsupported");
  return -ENOTSUP;
}

/**
 * @brief Change display contrast
 */
static int __ssd1306_spi_set_contrast(const struct device* dev,
                                      const uint8_t contrast) {
  LOG_ERR("Unsupported");
  return -ENOTSUP;
}

/**
 * @brief Change the orientation of the display
 */
static int __ssd1306_spi_set_orientation(
    const struct device* dev,
    const enum display_orientation orientation) {
  LOG_ERR("Unsupported");
  return -ENOTSUP;
}

/**
 * @brief Change the pixel format of the display. Only MONO is supported.
 */
static int __ssd1306_spi_set_pixel_format(const struct device* dev,
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
static int __ssd1306_spi_read(const struct device* dev,
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
static int __ssd1306_spi_write(const struct device* dev,
                               const uint16_t x,
                               const uint16_t y,
                               const struct display_buffer_descriptor* desc,
                               const void* buf) {
  struct ssd1306_data* data = (struct ssd1306_data*)dev->driver_data;

  if (x != 0U && y != 0U) {
    LOG_ERR("Unsupported origin, only 0,0 supported");
    return -1;
  }

  if (desc->buf_size != (NUM_PAGES * WIDTH)) {
    return -1;
  }

  if ((y & 0x7) != 0U) {
    LOG_ERR("Unsupported origin %d, y coordinate must be multiple of 8", y);
    return -1;
  }

  // horizontal addressing
  __cmd(SSD1306_MEMORYMODE);
  __cmd(0x00);
  __cmd(SSD1306_COLUMNADDR);
  __cmd(x);
  __cmd(x + desc->width - 1);
  __cmd(SSD1306_PAGEADDR);
  __cmd(y / 8);
  __cmd((y + desc->height) / 8 - 1);
  __write_buffer(data, (void*)buf, desc->buf_size);

  // for (size_t pidx = 0; pidx < NUM_PAGES; pidx++) {
  //   if (__write_page(dev, pidx, buf, WIDTH)) {
  //     return -1;
  //   }
  //   buf = (uint8_t*)buf + WIDTH;
  // }

  return 0;
}

/**
 * @brief Initialize the LED Matrix Driver
 */
static int __ssd1306_spi_init(struct device* dev) {
  LOG_DBG("Initializing SSD1306");

  struct ssd1306_data* data = (struct ssd1306_data*)dev->driver_data;

  // Default offsets
  data->x_offset = 1;
  data->y_offset = 2;

  // Grab the SPI peripheral
  m_ssd1306_driver.spi = device_get_binding(DT_INST_0_SSD1306_SPI_BUS_NAME);
  if (!m_ssd1306_driver.spi) {
    LOG_ERR("Unable to get SPI device '%s'", DT_INST_0_SSD1306_SPI_BUS_NAME);
    return -1;
  }

  // Configure SPI peripheral according to DTS
  data->spi_config.frequency = DT_INST_0_SSD1306_SPI_SPI_MAX_FREQUENCY;
  data->spi_config.operation = SPI_OP_MODE_MASTER | SPI_WORD_SET(8);
  data->spi_config.slave = DT_INST_0_SSD1306_SPI_BASE_ADDRESS;

  // Grab various GPIO devices
  m_ssd1306_driver.gpio_dc = device_get_binding(CMD_CONTROLLER);
  if (!m_ssd1306_driver.gpio_dc) {
    LOG_ERR("Unable to get DC GPIO Port '%s'", CMD_CONTROLLER);
    return -1;
  }

  m_ssd1306_driver.gpio_reset = device_get_binding(RESET_CONTROLLER);
  if (!m_ssd1306_driver.gpio_reset) {
    LOG_ERR("Unable to get RESET GPIO Port '%s'", RESET_CONTROLLER);
    return -1;
  }

  m_ssd1306_driver.spi_cs_ctrl.gpio_dev = device_get_binding(CS_CONTROLLER);
  if (!m_ssd1306_driver.spi_cs_ctrl.gpio_dev) {
    LOG_ERR("Unable to get CS GPIO Port '%s'", CS_CONTROLLER);
    return -1;
  }

  m_ssd1306_driver.spi_cs_ctrl.gpio_pin = CS_PIN;
  m_ssd1306_driver.spi_cs_ctrl.delay = 0;
  m_ssd1306_driver.spi_config.cs = &m_ssd1306_driver.spi_cs_ctrl;

  // Make DC RESET pins output
  gpio_pin_configure(m_ssd1306_driver.gpio_dc, CMD_PIN, GPIO_OUTPUT);
  gpio_pin_configure(m_ssd1306_driver.gpio_reset, RESET_PIN,
                     GPIO_OUTPUT | GPIO_PULL_UP);

  // Reset TFT
  gpio_pin_set(m_ssd1306_driver.gpio_reset, RESET_PIN, 0);
  k_sleep(K_MSEC(400));
  gpio_pin_set(m_ssd1306_driver.gpio_reset, RESET_PIN, 1);
  k_sleep(K_MSEC(100));

  __cmd(SSD1306_DISPLAYOFF);
  __cmd(SSD1306_SETDISPLAYCLOCKDIV);
  __cmd(0x80);  // recommended value
  __cmd(SSD1306_SETMULTIPLEX);
  __cmd(HEIGHT - 1);
  __cmd(SSD1306_SETDISPLAYOFFSET);
  __cmd(0x00);                        // no offset
  __cmd(SSD1306_SETSTARTLINE | 0x0);  // Line 0
  __cmd(SSD1306_CHARGEPUMP);
  __cmd(0x14);  // Internal VCC
  __cmd(SSD1306_MEMORYMODE);
  __cmd(0x00);
  __cmd(SSD1306_SEGREMAP | 0x1);
  __cmd(SSD1306_COMSCANDEC);
  __cmd(SSD1306_SETCOMPINS);
  __cmd(0x12);
  __cmd(SSD1306_SETCONTRAST);
  __cmd(0xAF);  // Recommended setting for Internal VCC
  __cmd(SSD1306_SETPRECHARGE);
  __cmd(0x25);  // Internal VCC
  __cmd(SSD1306_SETVCOMDETECT);
  __cmd(0x20);
  __cmd(SSD1306_DISPLAYALLON_RESUME);
  __cmd(SSD1306_NORMALDISPLAY);
  __cmd(SSD1306_DEACTIVATE_SCROLL);
  __cmd(SSD1306_DISPLAYON);  // Main screen turn on

  k_sleep(K_MSEC(10));
  return 0;
}

static struct display_driver_api m_ssd1306_driver_api = {
    .blanking_on = __ssd1306_spi_blanking_on,
    .blanking_off = __ssd1306_spi_blanking_off,
    .write = __ssd1306_spi_write,
    .read = __ssd1306_spi_read,
    .get_framebuffer = __ssd1306_spi_get_framebuffer,
    .set_brightness = __ssd1306_spi_set_brightness,
    .set_contrast = __ssd1306_spi_set_contrast,
    .get_capabilities = __ssd1306_spi_get_capabilities,
    .set_pixel_format = __ssd1306_spi_set_pixel_format,
    .set_orientation = __ssd1306_spi_set_orientation,
};

DEVICE_AND_API_INIT(ssd1306_spi,
                    DT_INST_0_SSD1306_SPI_LABEL,
                    __ssd1306_spi_init,
                    &m_ssd1306_driver,
                    NULL,
                    APPLICATION,
                    CONFIG_APPLICATION_INIT_PRIORITY,
                    &m_ssd1306_driver_api);