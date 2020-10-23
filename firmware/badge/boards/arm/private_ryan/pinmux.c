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
#include <drivers/pinmux.h>
#include <init.h>
#include <kernel.h>
#include <sys/sys_io.h>

#include <pinmux/stm32/pinmux_stm32.h>

static const struct pin_config pinconf[] = {
#ifdef CONFIG_ADC_1
    {STM32_PIN_PA1, STM32F4_PINMUX_FUNC_PA1_ADC123_IN1},
    {STM32_PIN_PB1, STM32F4_PINMUX_FUNC_PB1_ADC12_IN9},
#endif
#ifdef CONFIG_UART_1
    {STM32_PIN_PB6, STM32F4_PINMUX_FUNC_PB6_USART1_TX},
    {STM32_PIN_PB7, STM32F4_PINMUX_FUNC_PB7_USART1_RX},
#endif /* CONFIG_UART_1 */
#ifdef CONFIG_UART_2
    {STM32_PIN_PA2, STM32F4_PINMUX_FUNC_PA2_USART2_TX},
    {STM32_PIN_PA3, STM32F4_PINMUX_FUNC_PA3_USART2_RX},
#endif /* CONFIG_UART_2 */
// #ifdef CONFIG_I2C_2
// 	{STM32_PIN_PB10, STM32F4_PINMUX_FUNC_PB10_I2C2_SCL},
// 	{STM32_PIN_PB3, STM32F4_PINMUX_FUNC_PB3_I2C2_SDA},
// #endif /* CONFIG_I2C_2 */
#ifdef CONFIG_I2C_3
    {STM32_PIN_PA8, STM32F4_PINMUX_FUNC_PA8_I2C3_SCL},
    {STM32_PIN_PB4, STM32F4_PINMUX_FUNC_PB4_I2C3_SDA},
#endif /* CONFIG_I2C_3 */
#ifdef CONFIG_SPI_1
#ifdef CONFIG_SPI_STM32_USE_HW_SS
    {STM32_PIN_PA4, STM32F4_PINMUX_FUNC_PA4_SPI1_NSS},
#endif /* CONFIG_SPI_STM32_USE_HW_SS */
    {STM32_PIN_PA5, STM32F4_PINMUX_FUNC_PA5_SPI1_SCK},
    {STM32_PIN_PA6, STM32F4_PINMUX_FUNC_PA6_SPI1_MISO},
    {STM32_PIN_PA7, STM32F4_PINMUX_FUNC_PA7_SPI1_MOSI},
#endif /* CONFIG_SPI_1 */
#ifdef CONFIG_SPI_2
#ifdef CONFIG_SPI_STM32_USE_HW_SS
    {STM32_PIN_PB12, STM32F4_PINMUX_FUNC_PB12_SPI2_NSS},
#endif /* CONFIG_SPI_STM32_USE_HW_SS */
    {STM32_PIN_PB13, STM32F4_PINMUX_FUNC_PB13_SPI2_SCK},
    {STM32_PIN_PB14, STM32F4_PINMUX_FUNC_PB14_SPI2_MISO},
    {STM32_PIN_PB15, STM32F4_PINMUX_FUNC_PB15_SPI2_MOSI},
#endif /* CONFIG_SPI_2 */

#ifdef CONFIG_SPI_5
    {STM32_PIN_PA10, (STM32_PINMUX_ALT_FUNC_6 | STM32_PUPDR_PULL_DOWN)},
    {STM32_PIN_PB0, (STM32_PINMUX_ALT_FUNC_6 | STM32_PUSHPULL_NOPULL |
                     STM32_OSPEEDR_VERY_HIGH_SPEED)},
#endif /* CONFIG_SPI_5 */

#ifdef CONFIG_USB_DC_STM32
    {STM32_PIN_PA11, STM32F4_PINMUX_FUNC_PA11_OTG_FS_DM},
    {STM32_PIN_PA12, STM32F4_PINMUX_FUNC_PA12_OTG_FS_DP},
#endif /* CONFIG_USB_DC_STM32 */
};

static int pinmux_stm32_init(struct device* port) {
  ARG_UNUSED(port);

  stm32_setup_pins(pinconf, ARRAY_SIZE(pinconf));

  return 0;
}

SYS_INIT(pinmux_stm32_init,
         PRE_KERNEL_1,
         CONFIG_PINMUX_STM32_DEVICE_INITIALIZATION_PRIORITY);
