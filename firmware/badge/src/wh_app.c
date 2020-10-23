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
#include "wh_app.h"

#include <logging/log.h>
#include <zephyr.h>

#include "system.h"
#include "wh_menu.h"
#include "wh_ui.h"

LOG_MODULE_REGISTER(wh_app, CONFIG_WH_APP_LOG_LEVEL);

// Semaphore to control app running
static app_t* m_app;
static const app_t* apps[] = {
    &app_bender, &app_bling,      &app_decoder,  &app_photos,
    &app_basic,  &app_basic_edit, &app_settings, &app_about, &app_reset};

void __app_task() {
  while (1) {
    // Default mode is show the menu
    wh_menu_show();

    // Wait for something to run an app
    while (!m_app) {
      k_sleep(K_MSEC(30));  // Be nice to their battery
    }

    if (m_app) {
      // Route signals to app
      LOG_DBG("Running app '%s'", m_app->label);
      wh_ui_signal_callback_t last_signal_callback =
          wh_ui_signal_callback_set(m_app->signal_callback);

      // Run the app
      m_app->handler(m_app->data);

      LOG_DBG("App '%s' Done", m_app->label);

      // App is done re-route signals
      wh_ui_signal_callback_set(last_signal_callback);
      m_app = NULL;
    }

    // Done
    // Note Semaphore is not given back. Only wh_app_run() can give semaphore
  }
}

/**
 * @brief Get the number of apps registered
 */
uint32_t wh_app_count_get() {
  return APP_COUNT;
}

/**
 * @brief Get an app at index
 * @param app_index The index of the application to retreive
 * @return Pointer to app
 */
const app_t* wh_app_get(uint32_t app_index) {
  if (app_index >= APP_COUNT) {
    return NULL;
  }

  return apps[app_index];
}

void wh_app_init() {
  LOG_DBG("Apps being initialized");
  // Control semaphore until an app is run
  // k_sem_take(&m_app_sem, K_FOREVER);

  LOG_DBG("Apps registered: %d", APP_COUNT);

  for (uint8_t i = 0; i < APP_COUNT; i++) {
    LOG_DBG("APP init(): %s", log_strdup(apps[i]->label));
    // Call the app's initializer
    apps[i]->init();
  }
}

/**
 * @brief Run a specific app at an index
 * @param pointer to app struct
 */
void wh_app_run(const app_t* p_app) {
  m_app = (app_t*)p_app;
}

/**
 * @brief Run a specific app at an index
 * @param app_index The index of the application to run
 */
void wh_app_run_index(uint32_t app_index) {
  if (app_index >= APP_COUNT) {
    return;
  }

  wh_app_run((const app_t*)&apps[app_index]);
}

K_THREAD_DEFINE(app_runner,
                4096,
                __app_task,
                NULL,
                NULL,
                NULL,
                WH_THREAD_PRIORITY_MEDIUM,
                0,
                1000);  // Prevent thread from starting