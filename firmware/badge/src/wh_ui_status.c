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
#include "wh_ui_status.h"

#include <display/cfb.h>
#include <drivers/sensor.h>
#include <logging/log.h>
#include <stdio.h>
#include <zephyr.h>

#include "system.h"

LOG_MODULE_REGISTER(wh_ui_status, CONFIG_WH_UI_LOG_LEVEL);

/**
 * @brief Helper function to get the current voltage of the battery as a simple
 * signed integer
 */
int32_t wh_ui_status_voltage_get() {
  int32_t voltage = -1;
  struct sensor_value vbatt;
  struct device* dev_sense = device_get_binding("WH_ADC_SENSE");
  if (!dev_sense) {
    return voltage;
  }

  sensor_sample_fetch(dev_sense);
  sensor_channel_get(dev_sense, SENSOR_CHAN_VOLTAGE, &vbatt);
  voltage = (vbatt.val1 * 10) + (vbatt.val2 % 10);

  LOG_DBG("Voltage = %d", voltage);
  return voltage;
}

/**
 * @brief Update the status display
 */
void wh_ui_status_draw() {
  char t_str[32];
  char v_str[32];
  char fw_str[32];

  struct device* dev_mono = device_get_binding("SSD1306");
  cfb_framebuffer_clear(dev_mono, 1);
  cfb_print(dev_mono, "AND!XOR", 0, 0);

  struct sensor_value temp;
  struct sensor_value vbatt;
  struct device* dev_sense = device_get_binding("WH_ADC_SENSE");
  if (!dev_sense) {
    LOG_ERR("ADC Sensor not available");
    cfb_print(dev_mono, "ERROR No Sensors", 0, 16);
    cfb_framebuffer_finalize(dev_mono);
    return;
  }

  sensor_sample_fetch(dev_sense);
  sensor_channel_get(dev_sense, SENSOR_CHAN_VOLTAGE, &vbatt);
  sensor_channel_get(dev_sense, SENSOR_CHAN_AMBIENT_TEMP, &temp);

  sprintf(t_str, "TEMP:%d", temp.val1);
  sprintf(v_str, "BATT:%d.%dv", vbatt.val1, vbatt.val2);
  sprintf(fw_str, "%s", VERSION);

  cfb_print(dev_mono, t_str, 0, 8);
  cfb_print(dev_mono, v_str, 0, 16);
  cfb_print(dev_mono, fw_str, 0, 24);
  cfb_framebuffer_finalize(dev_mono);
}