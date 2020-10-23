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
#include "wh_flag.h"

#include <crypto/cipher.h>
#include <logging/log.h>
#include <sys/crc.h>
#include <tinycrypt/aes.h>
#include <zephyr.h>

#include "autoconf.h"
#include "word-list-4096.h"

LOG_MODULE_REGISTER(wh_flag, CONFIG_WH_FLAG_LOG_LEVEL);

static uint8_t m_key[16] = {0x79, 0x9d, 0x43, 0x08, 0x19, 0x94, 0x90, 0xce,
                            0x88, 0xb6, 0xf9, 0xb5, 0xc2, 0xe6, 0x99, 0x4d};
static uint8_t m_iv[16] = {0x20, 0x49, 0x46, 0x7c, 0x74, 0x11, 0x69, 0x1e,
                           0x22, 0xad, 0x53, 0xfa, 0x27, 0x2b, 0x6f, 0x6c};

static void __log_flag(wh_flag_t* p_flag) {
  LOG_DBG("Badge ID: %d Command: 0x%02x CRC: 0x%04x", p_flag->badge_id,
          p_flag->command, p_flag->crc);
}

/**
 * @brief Calculate the CRC of a flag and update the flag data with the CRC
 * @param p_flag Flag to apply the CRC to
 */
static void __apply_crc(wh_flag_t* p_flag) {
  // ITU CRC16 mode matches the NodeJS CRC16 CCIT mode <shrug emoji>
  p_flag->crc = crc16_itu_t(0xFFFF, (uint8_t*)p_flag, sizeof(wh_flag_t) - 2);
}

/**
 * @brief Encrypt/Decrypt a given flag, m_iv must be initialized with the badge
 * id and command properly
 * @param p_flag Pointer to flag to encrypt
 * @param p_output Pointer to destination to store flag
 * @param nonce 16-bit nonce to use for crypto
 */
static void __crypt_flag(wh_flag_t* p_flag, uint8_t* p_output, uint16_t nonce) {
  uint8_t cipher_stream[16];
  struct tc_aes_key_sched_struct key_sched;
  tc_aes128_set_encrypt_key(&key_sched, m_key);

  LOG_HEXDUMP_DBG(p_flag, sizeof(wh_flag_t), "Flag byte");
  // Apply nonce to IV
  m_iv[0] = ((nonce & 0xFF00) >> 8);
  m_iv[1] = (nonce & 0x00FF);
  LOG_HEXDUMP_DBG(m_iv, 16, "IV");

  // Encrypt the IV, badge id, and command to produce a cipher stream (only 4096
  // possiblities), tinycrypt returns 0 on error (opposite of Zephyr)
  int err = tc_aes_encrypt(cipher_stream, m_iv, &key_sched);
  LOG_DBG("Result to encrypt = %d", err);
  if (err == 0) {
    LOG_ERR("Flag encryption failed [%d]", err);
  }

  for (size_t i = 0; i < sizeof(wh_flag_t); i++) {
    p_output[i] = ((uint8_t*)p_flag)[i] ^ cipher_stream[i];
    LOG_DBG("[%d] 0x%02x XOR 0x%02x = 0x%02x", i, ((uint8_t*)p_flag)[i],
            cipher_stream[i], p_output[i]);
  }
}

/**
 * @brief Decode a flag from plain english following the reverse of the encode
 * process
 * @param p_flag Pointer to flag to decode into
 * @param p_encoded_flag Pointer to encoded flag to decode
 * @return 0 if success, non-zero otherwise
 */
int wh_flag_decode(wh_flag_t* p_flag, wh_flag_encoded_t* p_encoded_flag) {
  // Make sure we have memory to deal with
  if (p_flag == NULL || p_encoded_flag == NULL) {
    LOG_ERR("Invalid flag data, NULL");
    return -1;
  }

  uint16_t symbols[WH_FLAG_SYMBOL_COUNT];
  for (uint8_t i = 0; i < WH_FLAG_SYMBOL_COUNT; i++) {
    // Match the symbol they gave us with the symbol in our wordlist to get a
    // bit pattern
    bool found = false;
    for (uint32_t j = 0; j < 4096; j++) {
      if (strncmp(p_encoded_flag->symbols[i], word_list_4096_txt + (j * 5),
                  5) == 0) {
        symbols[i] = j;
        found = true;
        break;
      }
    }

    if (!found) {
      LOG_ERR("Unmatched symbol");
      return -3;
    }

    LOG_DBG("SYMBOL: 0x%04x", symbols[i]);
  }

  // Map symbol bits into an encrypted flag
  uint8_t encrypted_flag[sizeof(wh_flag_t)];
  // Index for decoded bits to go into encrypted flag
  uint8_t index = 0;
  // Loop through decoded symbols skipping nonce
  for (uint8_t i = 1; i < WH_FLAG_SYMBOL_COUNT; i += 2) {
    encrypted_flag[index] = (symbols[i] & 0xFF0) >> 4;
    encrypted_flag[index + 1] =
        ((symbols[i] & 0x00F) << 4) | ((symbols[i + 1] & 0xF00) >> 8);
    encrypted_flag[index + 2] = symbols[i + 1] & 0x0FF;
    index += 3;
  }

  LOG_HEXDUMP_DBG(encrypted_flag, sizeof(wh_flag_t), "Encrypted flag");

  // We can decrypt by running encryption a second time
  __crypt_flag((wh_flag_t*)encrypted_flag, (uint8_t*)p_flag, symbols[0]);

  return 0;
}

/**
 * @brief Encode badge flags as plain english. This function computes a CRC,
 * generates a nonce, encrypts the flag, then updates the output string with a
 * list of 5 letter words(symbols) representing the encrypted data
 * @param p_flag pointer to flag to encode
 * @param p_encoded_flag pointer to struct to put the resulting encoded flag
 * into
 */
void wh_flag_encode(wh_flag_t* p_flag, wh_flag_encoded_t* p_encoded_flag) {
  uint8_t encrypted_flag[sizeof(wh_flag_t)];
  __apply_crc(p_flag);
  __log_flag(p_flag);
  // LOG_HEXDUMP_DBG((uint8_t*)p_flag, sizeof(wh_flag_t), "FLAG");

  // nonce is <badge id 10b> <command 2b>
  uint16_t nonce = ((p_flag->badge_id << 2) | (p_flag->command & 0x03)) & 0xFFF;
  LOG_DBG("NONCE 0x%03x", nonce);

  LOG_DBG("Encrypting flag");
  __crypt_flag(p_flag, encrypted_flag, nonce);
  // LOG_HEXDUMP_DBG(encrypted_flag, sizeof(wh_flag_t), "Encrypted");

  LOG_DBG("Encoding flag");

  // Clear symbols
  for (uint8_t i = 0; i < WH_FLAG_SYMBOL_COUNT; i++) {
    memset(p_encoded_flag->symbols[i], 0, WH_FLAG_SYMBOL_LEN);
  }

  // Start the encoded flag with a 12 bit nonce
  memcpy(p_encoded_flag->symbols[0], word_list_4096_txt + (nonce * 5), 5);
  p_encoded_flag->symbols[0][WH_FLAG_SYMBOL_LEN] = 0;

  // Start after nonce
  uint8_t index = 1;
  for (uint8_t i = 0; i < sizeof(wh_flag_t); i += 3) {
    uint16_t symbol1 = (((uint16_t)encrypted_flag[i] & 0xFF) << 4) |
                       (((uint16_t)encrypted_flag[i + 1] & 0xF0) >> 4);
    uint16_t symbol2 = (((uint16_t)encrypted_flag[i + 1] & 0x0F) << 8) |
                       ((uint16_t)encrypted_flag[i + 2] & 0xFF);
    memcpy(p_encoded_flag->symbols[index], word_list_4096_txt + (symbol1 * 5),
           5);
    p_encoded_flag->symbols[index][WH_FLAG_SYMBOL_LEN] = 0;  // null terminated

    index++;
    memcpy(p_encoded_flag->symbols[index], word_list_4096_txt + (symbol2 * 5),
           5);
    p_encoded_flag->symbols[index][WH_FLAG_SYMBOL_LEN] = 0;  // null terminated
    index++;

    LOG_DBG("SYM1: 0x%04x SYM2 0x%04x", symbol1, symbol2);
  }
}