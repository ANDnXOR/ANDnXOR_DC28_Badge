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
#ifndef WH_FLAG_H
#define WH_FLAG_H

#include <zephyr.h>

#define WH_FLAG_DATA_LEN 6
#define WH_FLAG_SYMBOL_COUNT 9
#define WH_FLAG_SYMBOL_LEN 5

#define WH_FLAG_COMMAND_NAME 0x01

typedef struct {
  uint32_t badge_id : 24;
  uint8_t command : 8;
  uint8_t data[WH_FLAG_DATA_LEN];
  uint16_t crc;
} __packed wh_flag_t;

typedef struct {
  char symbols[WH_FLAG_SYMBOL_COUNT][WH_FLAG_SYMBOL_LEN + 1];
} wh_flag_encoded_t;

/**
 * @brief Decode a flag from plain english following the reverse of the encode
 * process
 * @param p_flag Pointer to flag to decode into
 * @param p_encoded_flag Pointer to encoded flag to decode
 * @return 0 if success, non-zero otherwise
 */
extern int wh_flag_decode(wh_flag_t* p_flag, wh_flag_encoded_t* p_encoded_flag);

/**
 * @brief Encode badge flags as plain english. This function computes a CRC,
 * generates a nonce, encrypts the flag, then updates the output string with a
 * list of 5 letter words(symbols) representing the encrypted data
 * @param p_flag pointer to flag to encode
 * @param p_encoded_flag pointer to struct to put the resulting encoded flag
 * into
 */
extern void wh_flag_encode(wh_flag_t* p_flag,
                           wh_flag_encoded_t* p_encoded_flag);
#endif