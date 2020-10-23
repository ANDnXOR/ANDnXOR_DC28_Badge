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
#include <drivers/led_strip.h>
#include <drivers/sensor.h>
#include <fs/fs.h>
#include <logging/log.h>
#include <shell/shell.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <zephyr.h>

#include "../gfx/bg.h"
#include "../lib/mybasic/my_basic.h"
#include "../system.h"
#include "../wh_app.h"
#include "../wh_bling.h"
#include "../wh_fs.h"
#include "../wh_led.h"
#include "../wh_shell.h"
#include "../wh_ui.h"
#include "../wh_util.h"
#include "wh_app_basic_util.h"

LOG_MODULE_REGISTER(wh_app_basic, CONFIG_WH_APP_LOG_LEVEL);

static bool m_running = false;
static bool m_key_ready = false;

// BAS ouput buffer
static int m_bas_output_size = 512;
char *m_bas_output;
static uint8_t m_bas_output_safety_buffer = 128;
static char m_bas_input[32] = "";
static bool m_bas_input_rx = false;
static lv_obj_t* m_bas_output_screen;
static lv_obj_t* m_bas_input_ta;
static lv_obj_t* m_bas_output_ta;

// LVGL Input group to use for focus etc
static lv_group_t* m_bas_input_group;

/**
 * @brief Special BASIC handler for printing.
 */
static int __basic_print(const char* fmt, ...) {
  char buf[64];
  char* ptr = buf;
  size_t len = sizeof(buf);
  int result = 0;
  va_list argptr;

  va_start(argptr, fmt);
  result = vsnprintf(ptr, len, fmt, argptr);
  if (result < 0) {
    LOG_ERR("Encoding error.");
  } else if (result > (int)len) {
    len = result + 1;
    ptr = (char*)k_malloc(result + 1);
    result = vsnprintf(ptr, len, fmt, argptr);
  }
  va_end(argptr);
  if (result >= 0){
    //Circular buffer - chop the first X chars (i.e. safety buffer) if its getting full
    if(strlen(m_bas_output) >= m_bas_output_size - m_bas_output_safety_buffer){
      char *tmp = malloc(strlen(m_bas_output) - m_bas_output_safety_buffer + 1);  //Dynamically allocate temp buffer with a cast iron skillet
      memset(tmp, '\0', strlen(m_bas_output) - m_bas_output_safety_buffer + 1);   //Null terminate with grease
      strncpy(tmp, m_bas_output + m_bas_output_safety_buffer, strlen(m_bas_output) - m_bas_output_safety_buffer); //Cook up substring bacon
      strcpy(m_bas_output, tmp);  //Put bacon dinner on the serving plate
      free(tmp);                  //Clean the skillet
    }
    strcat(m_bas_output, ptr); //Take the existing output buffer and append BAS output to it   
    k_sleep(K_MSEC(5));
    
    lv_ta_set_text(m_bas_output_ta, m_bas_output);            //Update the text area
    lv_ta_set_cursor_pos(m_bas_output_ta, LV_TA_CURSOR_LAST); //Causes scrolling effect as it prints
    lv_task_handler();
  }
  if (ptr != buf)
    k_free(ptr);

  return result;
}

/**
 * @brief Special BASIC handler for input
 */

int __basic_input(const char* pmt, char* buf, int s) {
  int result = 0;

  //Step 1 Get Input
  wh_ui_lvgl_enable(true);  //Enable keyboard

  while(m_bas_input_rx == false){ //Wait for input to be entered
    k_sleep(K_MSEC(20));
  }
  
  if(strlen(m_bas_input) < 32){   //Only add a newline if it doesn't overflow
    strcat(m_bas_input, "\n"); 
  }
  strcpy(buf,m_bas_input);        //Grab the input buffer
  m_bas_input_rx = false;         //Reset input tracker
  wh_ui_lvgl_enable(false);       //Disable keyboard

  //Step 2 Echo input to m_bas_output
  strcat(m_bas_output, buf); //Take the existing buffer and append BAS output to it   
  k_sleep(K_MSEC(10));
  lv_ta_set_text(m_bas_output_ta, m_bas_output);            //Update the text area
  lv_ta_set_cursor_pos(m_bas_output_ta, LV_TA_CURSOR_LAST); //Causes scrolling effect as it prints
  lv_task_handler();

  //Step 3 Return Result
  result = (int)strlen(buf);
  if(buf[result - 1] == '\n')
    buf[result - 1] = '\0';
  return result;
}

/**
 * @brief Custom my basic function to delay for specified milliseconds
 */
static int __func_delay(struct mb_interpreter_t* bas, void** l) {
  int msec;
  mb_check(mb_attempt_open_bracket(bas, l));
  mb_check(mb_pop_int(bas, l, &msec));
  mb_check(mb_attempt_close_bracket(bas, l));

  if (msec < 0) {
    msec = 0;
  }

  k_sleep(K_MSEC(msec));

  return MB_FUNC_OK;
}

/**
 * @brief Custom my basic function to get temperator
 */
static int __func_voltage_get(struct mb_interpreter_t* bas, void** l) {
  mb_check(mb_attempt_open_bracket(bas, l));
  mb_check(mb_attempt_close_bracket(bas, l));

  struct sensor_value vbatt;
  struct device* dev_sense = device_get_binding("WH_ADC_SENSE");
  if (!dev_sense) {
    return MB_FUNC_ERR;
  }
  sensor_sample_fetch(dev_sense);
  sensor_channel_get(dev_sense, SENSOR_CHAN_VOLTAGE, &vbatt);
  char voltage_string[4];
  sprintf(voltage_string, "%d.%d", vbatt.val1, vbatt.val2);
  mb_push_string(bas, l, mb_memdup(voltage_string, (unsigned)(strlen(voltage_string) + 1)));

  return MB_FUNC_OK;
}

/**
 * @brief Custom my basic function to get temperator
 */
static int __func_temp_get(struct mb_interpreter_t* bas, void** l) {
  mb_check(mb_attempt_open_bracket(bas, l));
  mb_check(mb_attempt_close_bracket(bas, l));

  struct sensor_value temp;
  struct device* dev_sense = device_get_binding("WH_ADC_SENSE");
  if (!dev_sense) {
    return MB_FUNC_ERR;
  }
  sensor_sample_fetch(dev_sense);
  sensor_channel_get(dev_sense, SENSOR_CHAN_AMBIENT_TEMP, &temp);
  mb_push_int(bas, l, (int)temp.val1);

  return MB_FUNC_OK;
}

/**
 * @brief Custom my basic function to get last key pressed
 */
static int __func_key_get(struct mb_interpreter_t* bas, void** l) {
  mb_check(mb_attempt_open_bracket(bas, l));
  mb_check(mb_attempt_close_bracket(bas, l));

  char key = wh_ui_last_key_get();
  mb_push_int(bas, l, (int)key);

  return MB_FUNC_OK;
}

/**
 * @brief Custom my basic function to determine if a key is ready
 */
static int __func_key_ready(struct mb_interpreter_t* bas, void** l) {
  mb_check(mb_attempt_open_bracket(bas, l));
  mb_check(mb_attempt_close_bracket(bas, l));
  mb_push_int(bas, l, m_key_ready);

  return MB_FUNC_OK;
}

/**
 * @brief Custom my basic function to set LEDs
 */
static int __func_led_set(struct mb_interpreter_t* bas, void** l) {
  int led_index;
  int r, g, b;

  mb_check(mb_attempt_open_bracket(bas, l));
  mb_check(mb_pop_int(bas, l, &led_index));
  mb_check(mb_pop_int(bas, l, &r));
  mb_check(mb_pop_int(bas, l, &g));
  mb_check(mb_pop_int(bas, l, &b));
  mb_check(mb_attempt_close_bracket(bas, l));

  if (led_index < 0) {
    led_index = 0;
  }
  led_index = led_index % WH_LED_COUNT;

  if (r < 0) {
    r = 0;
  }
  if (g < 0) {
    g = 0;
  }
  if (b < 0) {
    b = 0;
  }

  struct led_rgb color;
  color.r = r % 256;
  color.b = b % 256;
  color.g = g % 256;
  wh_led_set(led_index, color);
  wh_led_show();

  //   LOG_DBG("LED arguments: i: %d RGB: (%d %d %d)", led_index, r, g, b);

  return MB_FUNC_OK;
}

/**
 * @brief Custom my basic function to play bling files
 * Format: play('<file')
 */
static int __func_play(struct mb_interpreter_t* bas, void** l) {
  char* filename = 0;

  mb_check(mb_attempt_open_bracket(bas, l));
  mb_check(mb_pop_string(bas, l, &filename));
  if (strlen(filename) > MAX_FILE_NAME) {
    return mb_raise_error(bas, l, SE_PS_SYMBOL_TOO_LONG, MB_FUNC_ERR);
  }
  mb_check(mb_attempt_close_bracket(bas, l));

  char path[WH_PATH_MAX_LEN];
  snprintf(path, WH_PATH_MAX_LEN, WH_FS_MOUNT_POINT "/BLING_BW/%s", filename);

  // Note to future Zapp: You've tried to run a callback in MY BASIC on every
  // frame. However, it is _incredible_ slow. Do not attempt this again.
  wh_bling_play_raw_bw_file(path, NULL, false, NULL);

  return MB_FUNC_OK;
}

/*********************************************************************************************
 * @brief BACKEND FUNCTION FOR HANDLING SPECIAL EVENTS FROM BAS INPUT TEXT AREA
**********************************************************************************************/ 
static void __input_event_handler(lv_obj_t* obj, lv_event_t event) {
  LOG_DBG("Input event = %d", event);
  if (event == LV_EVENT_RELEASED && m_running) {
    //Upon input, the keyboard buffer is copied to the m_bas_input buffer and input_rx flag set
    strcpy(m_bas_input,lv_ta_get_text(m_bas_input_ta));
    lv_ta_set_text(m_bas_input_ta, "");
    m_bas_input_rx = true;
    k_sleep(K_MSEC(200));
  }
}

/*********************************************************************************************
 * @brief TRY TO RUN A BASIC FILE
**********************************************************************************************/ 
static void __run_file(char* filename) {
  struct mb_interpreter_t* bas = NULL;
  int err;
  size_t file_size = 0;
  static char file_contents[WH_BASIC_MAX_FILESIZE + 1];
  struct fs_file_t file;

  WH_LED_ALL_OFF();

  char fullpath[WH_PATH_MAX_LEN + 32];
  snprintf(fullpath, WH_PATH_MAX_LEN + 32, "%s/%s", WH_FS_MOUNT_POINT "/BAS",
           filename);

  // Suspend bling thread
  k_tid_t bling_thread = wh_util_thread_get_by_name("bling_task");
  k_thread_suspend(bling_thread);
  WH_LED_ALL_OFF();

  // Get the filesize
  struct fs_dirent entry;
  if (!fs_stat(fullpath, &entry)) {
    file_size = entry.size;
  }
  if (file_size == 0) {
    LOG_ERR("Could not stat %s.", log_strdup(fullpath));
    return;
  }

  // Ensure we have a properly sized file
  if (file_size > WH_BASIC_MAX_FILESIZE) {
    LOG_ERR("BASIC file too large");
    return;
  }

  err = fs_open(&file, fullpath);
  if (err) {
    LOG_ERR("Could not open %s", fullpath);
    return;
  }

  // Read the file contents
  memset(file_contents, 0, WH_BASIC_MAX_FILESIZE + 1);
  ssize_t bytes_read = fs_read(&file, file_contents, file_size);
  if (bytes_read != file_size) {
    LOG_ERR("Error while reading file %s [%d]", fullpath, bytes_read);
    fs_close(&file);
    return;
  }

  fs_close(&file);

  // Blank the OLED
  static uint8_t blank[WH_UI_OLED_HEIGHT * WH_UI_OLED_WIDTH / 8];
  memset(blank, 0, WH_UI_OLED_WIDTH * WH_UI_OLED_HEIGHT / 8);
  wh_bling_draw_bmp_bw(blank);

  // If we got this far, start the MY BASIC interpretter
  mb_init();
  mb_open(&bas);
  mb_set_printer(bas, __basic_print);
  mb_set_inputer(bas, __basic_input);
  mb_register_func(bas, "voltage", __func_voltage_get);
  mb_register_func(bas, "temp_f", __func_temp_get);
  mb_register_func(bas, "delay", __func_delay);
  mb_register_func(bas, "key", __func_key_get);
  mb_register_func(bas, "key_ready", __func_key_ready);
  mb_register_func(bas, "LED", __func_led_set);
  mb_register_func(bas, "play", __func_play);

  //Dynamically allocate the BAS output buffer
  m_bas_output = (char*) malloc((m_bas_output_size + 1) * sizeof(char));

  // Generate UI for output
  m_bas_output_screen = lv_obj_create(NULL, NULL);

  // BASIC Output Text Area
  k_mutex_lock(&g_mutex_ui, K_FOREVER);
  m_bas_output_screen = lv_obj_create(NULL, NULL);
  m_bas_output_ta = lv_ta_create(m_bas_output_screen, NULL);
  snprintf(m_bas_output, 256, "> %s\n", filename);
  lv_ta_set_text(m_bas_output_ta, m_bas_output);
  lv_ta_set_cursor_type(m_bas_output_ta, LV_CURSOR_NONE);
  lv_ta_set_cursor_pos(m_bas_output_ta, LV_TA_CURSOR_LAST);
  lv_obj_set_size(m_bas_output_ta, WH_UI_WIDTH, 110);
  lv_obj_align(m_bas_output_ta, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

  // BASIC Input Text Area
  m_bas_input_ta = lv_ta_create(m_bas_output_screen, NULL);
  lv_obj_set_size(m_bas_input_ta, 160, 30);
  lv_ta_set_cursor_type(m_bas_input_ta, LV_CURSOR_BLOCK);
  lv_ta_set_one_line(m_bas_input_ta, true);
  lv_ta_set_text(m_bas_input_ta, "");
  lv_obj_align(m_bas_input_ta, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);
  lv_obj_set_event_cb(m_bas_input_ta, __input_event_handler);

  // Create an input group to support the keyboard
  m_bas_input_group = lv_group_create();
  lv_group_add_obj(m_bas_input_group, m_bas_input_ta);

  // Release the MUTEX, also REQUIRED
  k_mutex_unlock(&g_mutex_ui);

  // Show the screen
  lv_scr_load(m_bas_output_screen);
  m_running = true;
  wh_ui_input_group_set(m_bas_input_group);
  lv_task_handler();

  // Run the contents of the file
  mb_load_string(bas, file_contents, true);
  int result = mb_run(bas, true);

  //Display BAS errors to user
  int pos;
  unsigned short row, col;
  char *target = m_bas_output;
  mb_error_e mb_err = mb_get_last_error(bas, (const char **)&fullpath, &pos, &row, &col);
  if(result != 0){
    target += sprintf(target, "MYBASIC ERROR:\n%s\n@ POS %d\n@ ROW %d\n@ COL %d", mb_get_error_desc(mb_err), pos, row, col);
    lv_ta_set_text(m_bas_output_ta, m_bas_output);
    lv_task_handler();
  }
  
  // Wait for something
  while (m_running) {
    k_sleep(K_MSEC(10));
  }

  // Disable alternate mode
  wh_ui_input_alt(false);

  // All done
  mb_close(&bas);
  mb_dispose();
  lv_obj_del(m_bas_output_screen);
  free(m_bas_output);
  wh_app_basic_util_free_memory();
  WH_LED_ALL_OFF();
  k_thread_resume(bling_thread);
}

/**
 * @brief Primary entry point for BASIC app. This should list available files
 * and allow them to run
 */
static void __handler(void* data) {
  int ret;
  m_running = true;
  m_key_ready = false;
  wh_ui_input_group_set(m_bas_input_group);

  char path[WH_PATH_MAX_LEN];
  while (m_running) {
    memset(path, 0, WH_PATH_MAX_LEN);
    ret = wh_app_basic_util_file_picker(path, "Run BAS File");
    // Wait for basic file to be set then run it, m_running will be false if
    // user signaled to exit
    if (strlen(path) > 0 && m_running) {
      wh_ui_lvgl_enable(false);
      __run_file(path);
      wh_ui_lvgl_enable(true);
    }
    k_sleep(K_MSEC(10));
  }
}

static void __init() {}

/**
 * @brief Callback from UI for signals
 */
static wh_ui_signal_result_t __signal_callback(wh_ui_signal_t signal) {
  switch (signal) {
    case wh_ui_signal_key_ready:
      return wh_ui_signal_result_okay;
      break;
    case wh_ui_signal_exit:
      m_running = false;
      return wh_ui_signal_result_okay;
      break;
  }

  return 0;
}
const app_t app_basic = {"MY-BASIC", __init, __handler, __signal_callback, NULL};