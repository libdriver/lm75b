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
 * @file      driver_lm75b_basic.c
 * @brief     driver lm75b basic source file
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

#include "driver_lm75b_basic.h"

static lm75b_handle_t gs_handle;        /**< lm75b handle */

/**
 * @brief     basic example init
 * @param[in] addr is the iic address pin
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t lm75b_basic_init(lm75b_address_t addr)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_LM75B_LINK_INIT(&gs_handle, lm75b_handle_t);
    DRIVER_LM75B_LINK_IIC_INIT(&gs_handle, lm75b_interface_iic_init);
    DRIVER_LM75B_LINK_IIC_DEINIT(&gs_handle, lm75b_interface_iic_deinit);
    DRIVER_LM75B_LINK_IIC_READ(&gs_handle, lm75b_interface_iic_read);
    DRIVER_LM75B_LINK_IIC_WRITE(&gs_handle, lm75b_interface_iic_write);
    DRIVER_LM75B_LINK_DELAY_MS(&gs_handle, lm75b_interface_delay_ms);
    DRIVER_LM75B_LINK_DEBUG_PRINT(&gs_handle, lm75b_interface_debug_print);
    
    /* set addr pin */
    res = lm75b_set_addr_pin(&gs_handle, addr);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set addr pin failed.\n");
        
        return 1;
    }
    
    /* lm75b init */
    res = lm75b_init(&gs_handle);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: init failed.\n");
       
        return 1;
    }
    
    /* set interrupt mode */
    res = lm75b_set_interrupt_mode(&gs_handle, LM75B_OS_OPERATION_INTERRUPT);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set interrupt mode failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set fault queue 1 */
    res = lm75b_set_fault_queue(&gs_handle, LM75B_FAULT_QUEUE_1);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set fault queue failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set os polarity low*/
    res = lm75b_set_os_polarity(&gs_handle, LM75B_OS_POLARITY_LOW);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set os polarity failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set over temperature threshold */
    res = lm75b_set_over_temperature_threshold(&gs_handle, 0xFF80U);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set over temperature threshold failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set hysteresis */
    res = lm75b_set_hysteresis(&gs_handle, 0x0000U);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set hysteresis failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set normal mode */
    res = lm75b_set_mode(&gs_handle, LM75B_MODE_NORMAL);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set mode failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *s points to a converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t lm75b_basic_read(float *s)
{
    uint16_t raw;
    
    /* read adc data */
    if (lm75b_read(&gs_handle, (uint16_t *)&raw, (float *)s) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t lm75b_basic_deinit(void)
{
    uint8_t res;
    
    /* set mode */
    res = lm75b_set_mode(&gs_handle, LM75B_MODE_SHUTDOWN);
    if (res != 0)
    {
        return 1;
    }
    
    /* close lm75b */
    if (lm75b_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
