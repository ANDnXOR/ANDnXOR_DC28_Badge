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
#include <device.h>
#include <drivers/adc.h>
#include <drivers/sensor.h>
#include <logging/log.h>
#include <shell/shell.h>
#include <zephyr.h>

#include "../wh_post.h"
#include "devicetree.h"

LOG_MODULE_REGISTER(wh_adc_sense, 4);

#define ADC_DEVICE_NAME DT_ST_STM32_ADC_40012000_LABEL
#define ADC_RESOLUTION 12
#define ADC_GAIN ADC_GAIN_1
#define ADC_ACQUISITION_TIME ADC_ACQ_TIME_DEFAULT
#define ADC_VBATT_CHANNEL 9
#define ADC_THERM_CHANNEL 1

// Thermistor values based on datasheet and schematic
// Temp in F degrees = THERM_M * ADC_VALUE + THERM_B
#define THERM_M (0.02665414f)
#define THERM_B (17.91711799f)

// Battery voltage values based on resistor dividor and ADC
#define VBATT_M (0.00152303f)
#define VBATT_B (-0.5833635f)

#define BUFFER_SIZE 6
static int16_t m_sample_buffer[BUFFER_SIZE];

// Storage for vbatt driver context
struct wh_adc_data {
  struct device* adc_dev;
  uint32_t voltage;
  uint32_t therm;
};

static const struct adc_channel_cfg m_therm_channel_cfg = {
    .gain = ADC_GAIN,
    .reference = ADC_REF_INTERNAL,
    .acquisition_time = ADC_ACQUISITION_TIME,
    .channel_id = ADC_THERM_CHANNEL,
};

static const struct adc_channel_cfg m_vbatt_channel_cfg = {
    .gain = ADC_GAIN,
    .reference = ADC_REF_INTERNAL,
    .acquisition_time = ADC_ACQUISITION_TIME,
    .channel_id = ADC_VBATT_CHANNEL,
};

static struct wh_adc_data m_adc_driver;

/**
 * @brief Retrieve the last sensor reading. Supported channels are
 * SENSOR_CHAN_VOLTAGE and SENSOR_CHAN_AMBIENT_TEMP
 * @param p_dev Pointer to device driver
 * @param chan Channel to get the value of
 * @param val Pointer to where to return the data
 */
static int __adc_sense_channel_get(struct device* p_dev,
                                   enum sensor_channel chan,
                                   struct sensor_value* val) {
  struct wh_adc_data* p_drv_data = p_dev->driver_data;
  float raw;
  switch (chan) {
    case SENSOR_CHAN_VOLTAGE:;
      raw = p_drv_data->voltage;
      float voltage = (VBATT_M * raw) + VBATT_B;
      val->val1 = (uint32_t)voltage;
      val->val2 = (uint32_t)((voltage - val->val1) * 10);
      break;
    case SENSOR_CHAN_AMBIENT_TEMP:
      raw = p_drv_data->therm;
      float temp_f = (THERM_M * raw) + THERM_B;
      val->val1 = (uint32_t)(temp_f);
      // val->val1 = (uint32_t)(raw);
      break;
    default:
      return -ENOTSUP;
  }

  return 0;
}

/**
 * @brief Initialize the adc sensor driver
 */
int __adc_sense_init(struct device* p_dev) {
  struct wh_adc_data* p_drv_data = p_dev->driver_data;
  p_drv_data->adc_dev = device_get_binding(ADC_DEVICE_NAME);

  LOG_DBG("Initializing ADC sense driver");

  // Ensure we found the ADC driver
  if (p_drv_data->adc_dev == NULL) {
    LOG_ERR("Unable to get ADC device %s.", ADC_DEVICE_NAME);
    wh_post_failed(WH_POST_THERM);
    wh_post_failed(WH_POST_VBATT);
    return -EINVAL;
  }

  LOG_DBG("Setting up Thermistor ADC channel");

  // Setup the ADC device
  int ret = adc_channel_setup(p_drv_data->adc_dev, &m_therm_channel_cfg);
  LOG_DBG("Initialized thermistor ADC result = %d", ret);
  if (ret) {
    LOG_ERR("Unable to setup Thermistor ADC channel [%d]", ret);
  }

  LOG_DBG("Setting up voltage ADC channel");

  ret = adc_channel_setup(p_drv_data->adc_dev, &m_vbatt_channel_cfg);
  LOG_DBG("Initialized vbatt ADC result = %d", ret);
  if (ret) {
    LOG_ERR("Unable to setup voltage ADC channel [%d]", ret);
  }

  wh_post_success(WH_POST_THERM);
  wh_post_success(WH_POST_VBATT);

  return 0;
}

/**
 * @brief Sample the battery voltage
 * @param p_dev Pointer to the device driver
 * @param channel The channel to sample. Ignored. Only voltage is read.
 */
static int __adc_sense_sample_fetch(struct device* p_dev,
                                    enum sensor_channel channel) {
  struct wh_adc_data* p_drv_data = p_dev->driver_data;
  const struct adc_sequence therm_sequence = {
      .channels = BIT(ADC_THERM_CHANNEL),
      .buffer = m_sample_buffer,
      .buffer_size = sizeof(m_sample_buffer),
      .resolution = ADC_RESOLUTION,
  };
  int ret = adc_read(p_drv_data->adc_dev, &therm_sequence);
  if (!ret) {
    p_drv_data->therm = m_sample_buffer[0];
  }

  const struct adc_sequence vbatt_sequence = {
      .channels = BIT(ADC_VBATT_CHANNEL),
      .buffer = m_sample_buffer,
      .buffer_size = sizeof(m_sample_buffer),
      .resolution = ADC_RESOLUTION,
  };

  ret = adc_read(p_drv_data->adc_dev, &vbatt_sequence);
  if (!ret) {
    p_drv_data->voltage = m_sample_buffer[0];
  }

  // LOG_DBG("Samples Therm: %d Vbatt: %d", p_drv_data->therm,
  // p_drv_data->voltage);

  return ret;
}

static const struct sensor_driver_api m_adc_sense_driver_api = {
    .sample_fetch = __adc_sense_sample_fetch,
    .channel_get = __adc_sense_channel_get};

DEVICE_AND_API_INIT(vbatt,
                    "WH_ADC_SENSE",
                    __adc_sense_init,
                    &m_adc_driver,
                    NULL,
                    POST_KERNEL,
                    CONFIG_SENSOR_INIT_PRIORITY,
                    &m_adc_sense_driver_api);

/**
 * @brief Simple command to read battery voltage from shell
 */
static int __cmd_temperature(const struct shell* shell, size_t argc, char** argv) {
  struct sensor_value temp;
  struct device* dev_sense = device_get_binding("WH_ADC_SENSE");
  if (!dev_sense) {
    return -1;
  }

  sensor_sample_fetch(dev_sense);
  sensor_channel_get(dev_sense, SENSOR_CHAN_AMBIENT_TEMP, &temp);
  shell_print(shell, "%d.%d degrees (uncalibrated)", temp.val1, temp.val2);
  return 0;
}

/**
 * @brief Simple command to read battery voltage from shell
 */
static int __cmd_voltage(const struct shell* shell, size_t argc, char** argv) {
  struct sensor_value vbatt;
  struct device* dev_sense = device_get_binding("WH_ADC_SENSE");
  if (!dev_sense) {
    return -1;
  }

  sensor_sample_fetch(dev_sense);
  sensor_channel_get(dev_sense, SENSOR_CHAN_VOLTAGE, &vbatt);
  shell_print(shell, "%d.%dV", vbatt.val1, vbatt.val2);
  return 0;
}

// SHELL_CMD_REGISTER(temp, NULL, "Read Thermistor", __cmd_temperature);
// SHELL_CMD_REGISTER(voltage, NULL, "Read Battery Voltage", __cmd_voltage);