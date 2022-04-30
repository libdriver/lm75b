/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_lm75b_interrupt_test.h
 * @brief     driver lm75b interrupt test header file
 * @version   2.0.0
 * @author    Shifeng Li
 * @date      2021-03-10
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date         <th>Version  <th>Author      <th>Description
 * <tr><td>2021/03/10   <td>2.0      <td>Shifeng Li  <td>format the code
 * <tr><td>2020/11/15   <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_LM75B_INTERRUPT_TEST_H
#define DRIVER_LM75B_INTERRUPT_TEST_H

#include "driver_lm75b_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup lm75b_test_driver
 * @{
 */

/**
 * @brief     interrupt test
 * @param[in] addr is the iic address pin
 * @param[in] mode is the os operation mode
 * @param[in] low_threshold is the interrupt low threshold
 * @param[in] high_threshold is the interrupt high threshold
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t lm75b_interrupt_test(lm75b_address_t addr, lm75b_os_operation_mode_t mode, 
                             float low_threshold, float high_threshold, uint32_t times);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
