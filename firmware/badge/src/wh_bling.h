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

#ifndef WH_BLING_H
#define WH_BLING_H

#include <zephyr.h>

#define M_PI 3.14159265358979323846

typedef void (*wh_bling_frame_callback_t)(uint8_t frame, void* p_data);

extern void wh_bling_lcd_sin();
extern void wh_bling_lcd_text();
extern void wh_bling_lcd_text_reset();

/**
 * @brief Draw a bitmap from memory
 * @param data : Pointer to memory containing the bitmap
 */
extern void wh_bling_draw_bmp_bw(const uint8_t* data);

/**
 * @brief Play a raw file directly to the screen avoiding the buffer
 * @param filename : full path to file to play
 * @param callback : Function to run after every frame
 * @param loop : Set to true to loop forever until a button is pressed.
 * Otherwise run once until completion.
 * @param data : Data to pass to the callback
 */
extern uint8_t wh_bling_play_raw_file(
    const char* filename,
    wh_bling_frame_callback_t p_frame_callback,
    bool loop,
    void* data);

/**
 * @brief Play a raw file directly to the OLED avoiding the buffer
 * @param filename : full path to file to play
 * @param callback : Function to run after every frame
 * @param loop : Set to true to loop forever until a button is pressed.
 * Otherwise run once until completion.
 * @param data : Data to pass to the callback
 * @return : 0 if successful, negative value if there was an error
 */
extern int8_t wh_bling_play_raw_bw_file(
    const char* filename,
    wh_bling_frame_callback_t p_frame_callback,
    bool loop,
    void* data);

/**
 * @brief Enable/Disable rager mode
 */
extern void wh_bling_rager_mode_set(bool rager);

/**
 * @brief Toggle rager mode
 */
extern void wh_bling_rager_mode_toggle();

/**
 * @brief Stop the currently running bling
 */
extern void wh_bling_stop();

#endif