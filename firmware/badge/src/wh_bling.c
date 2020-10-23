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

#include "wh_bling.h"

#include <device.h>
#include <drivers/display.h>
#include <fs/fs.h>
#include <logging/log.h>
#include <lvgl.h>
#include <math.h>
#include <stdio.h>
#include <zephyr.h>

#include "autoconf.h"
#include "drivers/ssd1306_spi.h"
#include "drivers/st7735.h"
#include "system.h"
#include "wh_fs.h"
#include "wh_ui.h"

LOG_MODULE_REGISTER(wh_bling, CONFIG_WH_BLING_LOG_LEVEL);

bool m_stop = false;
bool m_pause = false;

// BLING FPS control
#define BLING_FPS 20
#define BLING_MS_PER_FRAME (1000 / BLING_FPS)
bool m_rager_mode = false;

// Define buffer sizes
#define LCD_HEIGHT 128
#define LCD_WIDTH 160
#define SLICE_HEIGHT (LCD_HEIGHT / 8)
#define SLICE_SIZE (LCD_WIDTH * SLICE_HEIGHT * 2)
static uint8_t m_dma_buffer[SLICE_SIZE];
static uint8_t m_oled_buffer[WH_UI_OLED_WIDTH * WH_UI_OLED_HEIGHT / 8];
static uint8_t m_oled_temp_buffer[WH_UI_OLED_WIDTH * WH_UI_OLED_HEIGHT / 8];
// static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(LCD_WIDTH, LCD_HEIGHT)];

static float m_sin_mag = 64.0;
static float m_sin_mag_inc = -2.0;

// Data for printing source code
static lv_obj_t* m_lvgl_bling_ta = NULL;
static size_t m_source_code_index = 0;
static const char* m_source_code =
    "unsigned int t1,t2,\n"
    "unsigned char *end=\n"
    "t1=key[0]^sec[0x54]\n"
    "t2=key[1]^sec[0x55]\n"
    "t3=(*((unsigned int\n"
    "t4=t3&7;\n"
    "t3=t3*2+8-t4;\n"
    "sec+=0x80;\n"
    "t5=0;\n"
    "while(sec!=end) {\n"
    "	t4=CSSt2[t2]^CSSt3\n"
    "	t2=t1>>1;\n"
    "	t1=((t1&1)<<8)^t4;\n"
    "	t4=CSSt5[t4];\n"
    "	t6=(((((((t3>>3)^t\n"
    "	t3=(t3<<8)|t6;\n"
    "	t6=CSSt4[t6];\n"
    "	t5+=t6+t4;\n"
    "	*sec++=CSSt1[*sec]\n"
    "	t5>>=8;\n"
    "}";

void wh_bling_lcd_sin() {
  static lv_style_t style;
  lv_style_copy(&style, &lv_style_plain);
  style.body.main_color = LV_COLOR_RED;
  style.body.grad_color = LV_COLOR_MAROON;
  style.body.radius = 4;
  style.body.border.width = 2;
  style.body.border.color = LV_COLOR_WHITE;
  style.body.shadow.color = LV_COLOR_WHITE;
  style.body.shadow.width = 4;
  style.line.width = 2;
  style.line.color = LV_COLOR_GREEN;
  style.text.color = LV_COLOR_BLUE;

  lv_obj_t* canvas = lv_canvas_create(lv_scr_act(), NULL);
  lv_canvas_set_buffer(canvas, m_dma_buffer, LCD_WIDTH, LCD_HEIGHT,
                       LV_IMG_CF_TRUE_COLOR);
  lv_obj_align(canvas, NULL, LV_ALIGN_CENTER, 0, 0);
  uint8_t resolution = 2;
  lv_point_t points[LCD_WIDTH / resolution];
  for (uint8_t x = 0; x < LCD_WIDTH; x += resolution) {
    float rad = ((float)x / (float)LCD_WIDTH) * (2 * M_PI);
    points[x / resolution].x = x;
    points[x / resolution].y = (lv_coord_t)((sinf(rad) * m_sin_mag) + 64);
    // lv_canvas_set_px(canvas, x, (sinf(rad) * mag) + 64, LV_COLOR_GREEN);
  }
  lv_canvas_fill_bg(canvas, LV_COLOR_BLACK);
  lv_canvas_draw_line(canvas, points, LCD_WIDTH / resolution, &style);
  // lv_task_handler();

  m_sin_mag += m_sin_mag_inc;
  if (m_sin_mag <= -64) {
    m_sin_mag_inc = 2;
  } else if (m_sin_mag >= 64) {
    m_sin_mag = -2;
  }
}

void wh_bling_lcd_text() {
  if (m_lvgl_bling_ta == NULL) {
    return;
  }
  lv_ta_add_char(m_lvgl_bling_ta, m_source_code[m_source_code_index++]);

  // rewind
  if (m_source_code_index >= strlen(m_source_code)) {
    lv_ta_set_text(m_lvgl_bling_ta, "");
    m_source_code_index = 0;
  }
}

void wh_bling_lcd_text_reset() {
  if (m_lvgl_bling_ta == NULL) {
    m_lvgl_bling_ta = lv_ta_create(lv_scr_act(), NULL);
  }
  lv_ta_set_text(m_lvgl_bling_ta, "");
  lv_obj_set_size(m_lvgl_bling_ta, WH_UI_WIDTH, WH_UI_HEIGHT);
  lv_obj_align(m_lvgl_bling_ta, NULL, LV_ALIGN_CENTER, 0, 0);
}

/**
 * @brief Play a raw file directly to the screen avoiding the buffer
 * @param filename : full path to file to play
 * @param callback : Function to run after every frame
 * @param loop : Set to true to loop forever until a button is pressed.
 * Otherwise run once until completion.
 * @param data : Data to pass to the callback
 */
uint8_t wh_bling_play_raw_file(const char* filename,
                               wh_bling_frame_callback_t p_frame_callback,
                               bool loop,
                               void* data) {
  struct fs_file_t raw_file;

  int err;
  ssize_t read_bytes = 0;
  size_t file_size = 0;
  int32_t bytecount = LCD_WIDTH * LCD_HEIGHT * 2;
  uint16_t frames = 1;
  uint16_t yy = 0;

  m_stop = false;
  m_pause = false;

  if (!wh_fs_mounted()) {
    LOG_ERR("Unable to play bling file '%s'", filename);
    wh_ui_window_error("Filesystem not mounted");
    return 0;
  }

  // Get the filesize
  struct fs_dirent entry;
  if (!fs_stat(filename, &entry)) {
    file_size = entry.size;
  }
  if (file_size == 0) {
    LOG_ERR("Could not stat %s.", filename);
    wh_ui_window_error("Bling not found");
    return 0;
  }

  // Ensure we have a properly sized file
  if ((file_size % bytecount) != 0) {
    LOG_ERR("Invalid raw file dimensions. Skipping '%s'", filename);
    wh_ui_window_error("Bling has incorrect dimensions");
    return 0;
  }

  // Determine how many frames are in the file, minimum of 1
  frames = MAX(file_size / LCD_WIDTH / LCD_HEIGHT / 2, 1);

  // Open requested file
  err = fs_open(&raw_file, filename);
  if (err) {
    LOG_ERR("Could not open %s.", filename);
    wh_ui_window_error("Could not open bling");
    return 0;
  }

  // Lock the UI
  k_mutex_lock(&g_mutex_ui, K_FOREVER);

  uint16_t counter = 0;

  do {
    // Ensure we're starting at beginning of file for first frame
    fs_seek(&raw_file, 0, FS_SEEK_SET);
    yy = 0;

#ifdef CONFIG_WH_BLING_SHOW_FPS
    int64_t start = k_uptime_get();
#endif

    // Set TFT address window to clipped image bounds
    st7735_window_set(0, 0, 160, 128);

    for (uint16_t i = 0; i < frames; i++) {
      bytecount = LCD_WIDTH * LCD_HEIGHT * 2;

      // Blast data to TFT
      while (bytecount > 0) {
        // Populate the row buffer
        read_bytes = fs_read(&raw_file, m_dma_buffer, SLICE_SIZE);

        // Ensure there was no error
        if (read_bytes < 0) {
          LOG_ERR("Error [%d] while reading bling file %s", read_bytes,
                  filename);
          wh_ui_window_error("Unknown error while reading bling file");
          m_stop = true;
          break;
        }

        // Push the colors async
        st7735_write_buffer(m_dma_buffer, read_bytes);

        bytecount -= read_bytes;
      }

      // frame complete, callback
      if (p_frame_callback != NULL) {
        p_frame_callback(counter++, data);
      }

      if (m_stop) {
        break;
      }
    }

#ifdef CONFIG_WH_BLING_SHOW_FPS
    int64_t now = k_uptime_get();
    int64_t delta = now - start;
    int fps = (frames * 1000) / delta;

    char buffer[128];
    sprintf(buffer, "FPS: %d DELTA: %d", fps, (int)delta);
    LOG_DBG("%s", log_strdup(buffer));
#endif

  } while (loop && !m_stop);

  // Release UI
  k_mutex_unlock(&g_mutex_ui);
  fs_close(&raw_file);

  return 0;
}

/**
 * @brief Play a raw file directly to the OLED avoiding the buffer
 * @param filename : full path to file to play
 * @param callback : Function to run after every frame
 * @param loop : Set to true to loop forever until a button is pressed.
 * Otherwise run once until completion.
 * @param data : Data to pass to the callback
 * @return : 0 if successful, negative value if there was an error
 */
int8_t wh_bling_play_raw_bw_file(const char* filename,
                                 wh_bling_frame_callback_t p_frame_callback,
                                 bool loop,
                                 void* data) {
  struct fs_file_t raw_file;
  struct device* ssd1306 = device_get_binding("SSD1306");
  uint32_t frame_byte_count = WH_UI_OLED_WIDTH * WH_UI_OLED_HEIGHT / 8;

  int err;
  size_t file_size = 0;
  uint16_t frames = 1;

  m_stop = false;
  m_pause = false;

  if (!wh_fs_mounted()) {
    LOG_ERR("Unable to play bling file '%s'", filename);
    // wh_ui_window_error("Filesystem not mounted");
    return -1;
  }

  // Get the filesize
  struct fs_dirent entry;
  if (!fs_stat(filename, &entry)) {
    file_size = entry.size;
  }
  if (file_size == 0) {
    LOG_ERR("Could not stat '%s'.", filename);
    // wh_ui_window_error("Bling file not found");
    return -1;
  }

  // Ensure we have a properly sized file
  if ((file_size % frame_byte_count) != 0) {
    LOG_ERR("Invalid raw file dimensions. Skipping '%s'", filename);
    // wh_ui_window_error("Bling file has incorrect dimensions");
    return -1;
  }

  // Determine how many frames are in the file, minimum of 1
  frames = MAX(file_size / frame_byte_count, 1);

  // Open requested file
  err = fs_open(&raw_file, filename);
  if (err) {
    LOG_ERR("Could not open %s.", filename);
    // wh_ui_window_error("Could not open bling file");
    return -1;
  }

  // Lock the UI
  // k_mutex_lock(&g_mutex_ui, K_FOREVER);

  do {
    // Ensure we're starting at beginning of file for first frame
    fs_seek(&raw_file, 0, FS_SEEK_SET);

#ifdef CONFIG_WH_BLING_SHOW_FPS
    int64_t start = k_uptime_get();
#endif

    struct display_buffer_descriptor desc;
    desc.buf_size = frame_byte_count;
    desc.width = WH_UI_OLED_WIDTH;
    desc.height = WH_UI_OLED_HEIGHT;
    desc.pitch = 1;

    for (uint16_t i = 0; i < frames; i++) {
      // Determine start time for next frame
      uint32_t next_frame_time_ms = k_uptime_get_32() + BLING_MS_PER_FRAME;

      ssize_t read_bytes = fs_read(&raw_file, m_oled_buffer, frame_byte_count);
      if (read_bytes < frame_byte_count) {
        LOG_ERR("Unable to read file, error [%d]", read_bytes);
        wh_ui_window_error("Unknown error while reading bling file");
        m_stop = true;
        break;
      }

      // Clear output buffer to be safe
      memset(m_oled_temp_buffer, 0, frame_byte_count);

      // Map into physical space we understand
      for (uint8_t y = 0; y < WH_UI_OLED_HEIGHT; y++) {
        for (uint8_t x = 0; x < WH_UI_OLED_WIDTH; x++) {
          uint8_t page = y / 8;
          uint8_t col = x;
          uint8_t b =
              y % 8;  // bit shift for oled mapping adjusting for MSB/LSB
          uint8_t xpos =
              (7 - (x % 8));  // single out a pixel adjusting for MSB/LSB
          uint8_t pixel =
              (m_oled_buffer[(y * 16) + (x / 8)] & (1 << xpos)) >> xpos;
          m_oled_temp_buffer[(page * WH_UI_OLED_WIDTH) + col] |= (pixel << b);
        }
      }

      display_write(ssd1306, 0, 0, &desc, m_oled_temp_buffer);

      // frame complete, callback
      if (p_frame_callback != NULL) {
        p_frame_callback(i, data);
      }

      // Sleep to maintain 20 FPS unless rager mode
      if (k_uptime_get_32() < next_frame_time_ms && !m_rager_mode) {
        uint32_t sleep_time = next_frame_time_ms - k_uptime_get_32();
        k_sleep(K_MSEC(sleep_time));
      }
      // Minimize sleep time to allow other threads to do work
      else {
        k_sleep(K_MSEC(3));
      }

      if (m_stop) {
        break;
      }
    }

#ifdef CONFIG_WH_BLING_SHOW_FPS
    int64_t now = k_uptime_get();
    int64_t delta = now - start;
    int fps = (frames * 1000) / delta;

    char buffer[128];
    sprintf(buffer, "FPS: %d DELTA: %d", fps, (int)delta);
    LOG_DBG("%s", log_strdup(buffer));
#endif

  } while (loop && !m_stop);

  // Release UI
  // k_mutex_unlock(&g_mutex_ui);
  fs_close(&raw_file);

  return 0;
}

/**
 * @brief Draw a bitmap from memory
 * @param data : Pointer to memory containing the bitmap
 */
void wh_bling_draw_bmp_bw(const uint8_t* data) {
  struct device* ssd1306 = device_get_binding("SSD1306");

  uint32_t frame_byte_count = WH_UI_OLED_WIDTH * WH_UI_OLED_HEIGHT / 8;
  struct display_buffer_descriptor desc;
  desc.buf_size = frame_byte_count;
  desc.width = WH_UI_OLED_WIDTH;
  desc.height = WH_UI_OLED_HEIGHT;
  desc.pitch = 1;

  // Clear output buffer to be safe
  memset(m_oled_temp_buffer, 0, frame_byte_count);

  // Map into physical space we understand
  for (uint8_t y = 0; y < WH_UI_OLED_HEIGHT; y++) {
    for (uint8_t x = 0; x < WH_UI_OLED_WIDTH; x++) {
      uint8_t page = y / 8;
      uint8_t col = x;
      uint8_t b = y % 8;  // bit shift for oled mapping adjusting for MSB/LSB
      uint8_t xpos = (7 - (x % 8));  // single out a pixel adjusting for MSB/LSB
      uint8_t pixel = (data[(y * 16) + (x / 8)] & (1 << xpos)) >> xpos;
      m_oled_temp_buffer[(page * WH_UI_OLED_WIDTH) + col] |= (pixel << b);
    }
  }

  display_write(ssd1306, 0, 0, &desc, m_oled_temp_buffer);
}

/**
 * @brief Enable/Disable rager mode
 */
void wh_bling_rager_mode_set(bool rager) {
  m_rager_mode = rager;
}

/**
 * @brief Toggle rager mode
 */
void wh_bling_rager_mode_toggle() {
  m_rager_mode = !m_rager_mode;
}

/**
 * @brief Stop the currently running bling
 */
void wh_bling_stop() {
  m_stop = true;
}