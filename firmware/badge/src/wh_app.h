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
#ifndef WH_APP_H
#define WH_APP_H

#include "wh_bender.h"
#include "wh_ui.h"

#define WH_APP_NAME_LENGTH 10

extern void wh_app_init();

/**
 * @brief Callback prototype for runnning an app
 * @param p_app Pointer to app for runtime context
 */
typedef void (*app_handler_t)(void* data);

/**
 * @brief Callback prototype used during app init
 * @param p_app Pointer to app for runtime context
 */
typedef void (*app_init_t)(void);

typedef struct {
  const char* label;
  app_init_t init;
  app_handler_t handler;
  wh_ui_signal_callback_t signal_callback;
  void* data;
} app_t;

#define APP_NAME(counter) APP_CAT(_wh_app_, counter)
#define APP_CAT(a, b) APP_DUMMY() a##b
#define APP_DUMMY()

#define WH_APP_REGISTER(_label, _init, _handler, __signal_callback, _data, \
                        _priority)                                         ;;

/**
 * @brief Run a specific app at an index
 * @param app_index The index of the application to run
 */
extern void wh_app_run_index(uint32_t app_index);

/**
 * @brief Run a specific app at an index
 * @param pointer to app struct
 */
extern void wh_app_run(const app_t* p_app);

/**
 * @brief Get the number of apps registered
 */
extern uint32_t wh_app_count_get();

/**
 * @brief Get an app at index
 * @param app_index The index of the application to retreive
 * @return Pointer to app
 */
extern const app_t* wh_app_get(uint32_t app_index);

#define APP_COUNT 9
extern const app_t app_about;
extern const app_t app_basic;
extern const app_t app_basic_edit;
extern const app_t app_bender;
extern const app_t app_bling;
extern const app_t app_decoder;
extern const app_t app_photos;
extern const app_t app_reset;
extern const app_t app_settings;

#endif