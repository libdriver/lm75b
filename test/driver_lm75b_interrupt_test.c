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
 * @file      driver_lm75b_interrupt_test.c
 * @brief     driver lm75b interrupt test source file
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

#include "driver_lm75b_interrupt_test.h"

static lm75b_handle_t gs_handle;        /**< lm75b handle */

/**
 * @brief     interrupt test
 * @param[in] addr iic address pin
 * @param[in] mode os operation mode
 * @param[in] low_threshold interrupt low threshold
 * @param[in] high_threshold interrupt high threshold
 * @param[in] times test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t lm75b_interrupt_test(lm75b_address_t addr, lm75b_os_operation_mode_t mode, 
                             float low_threshold, float high_threshold, uint32_t times)
{
    uint8_t res;
    uint32_t i;
    uint16_t raw;
    float s;
    uint16_t reg;
    lm75b_info_t info;
    
    /* link interface function */
    DRIVER_LM75B_LINK_INIT(&gs_handle, lm75b_handle_t);
    DRIVER_LM75B_LINK_IIC_INIT(&gs_handle, lm75b_interface_iic_init);
    DRIVER_LM75B_LINK_IIC_DEINIT(&gs_handle, lm75b_interface_iic_deinit);
    DRIVER_LM75B_LINK_IIC_READ(&gs_handle, lm75b_interface_iic_read);
    DRIVER_LM75B_LINK_IIC_WRITE(&gs_handle, lm75b_interface_iic_write);
    DRIVER_LM75B_LINK_DELAY_MS(&gs_handle, lm75b_interface_delay_ms);
    DRIVER_LM75B_LINK_DEBUG_PRINT(&gs_handle, lm75b_interface_debug_print);
    
    /* get lm75b info */
    res = lm75b_info(&info);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: get info failed.\n");
        
        return 1;
    }
    else
    {
        /* print chip information */
        lm75b_interface_debug_print("lm75b: chip is %s.\n", info.chip_name);
        lm75b_interface_debug_print("lm75b: manufacturer is %s.\n", info.manufacturer_name);
        lm75b_interface_debug_print("lm75b: interface is %s.\n", info.interface);
        lm75b_interface_debug_print("lm75b: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        lm75b_interface_debug_print("lm75b: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        lm75b_interface_debug_print("lm75b: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        lm75b_interface_debug_print("lm75b: max current is %0.2fmA.\n", info.max_current_ma);
        lm75b_interface_debug_print("lm75b: max temperature is %0.1fC.\n", info.temperature_max);
        lm75b_interface_debug_print("lm75b: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
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
    res = lm75b_set_interrupt_mode(&gs_handle, mode);
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
    
    /* set os polarity low */
    res = lm75b_set_os_polarity(&gs_handle, LM75B_OS_POLARITY_LOW);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set os polarity failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    
    /* over temperature threshold convert to register */
    res = lm75b_over_temperature_threshold_convert_to_register(&gs_handle, high_threshold, (uint16_t *)&reg);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: over temperature threshold convert to register failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set over temperature threshold */
    res = lm75b_set_over_temperature_threshold(&gs_handle, reg);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set over temperature threshold failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    
    /* hysteresis convert to register */
    res = lm75b_hysteresis_convert_to_register(&gs_handle, low_threshold, (uint16_t *)&reg);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: hysteresis convert to register failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set hysteresis */
    res = lm75b_set_hysteresis(&gs_handle, reg);
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
    
    /* start interrupt test */
    lm75b_interface_debug_print("lm75b: start interrupt test.\n");
    for (i = 0; i < times; i++)
    {
        lm75b_interface_delay_ms(1000);
    
        /* read data */
        res = lm75b_read(&gs_handle, (uint16_t *)&raw, (float *)&s);
        if (res != 0)
        {
            lm75b_interface_debug_print("lm75b: read failed.\n");
            (void)lm75b_deinit(&gs_handle);
            
            return 1;
        }
        lm75b_interface_debug_print("lm75b: temperature is %0.3fC.\n", s);
        if (s > high_threshold)
        {
            lm75b_interface_debug_print("lm75b: temperature is over high threshold.\n");
        }
        if (s < low_threshold)
        {
            lm75b_interface_debug_print("lm75b: temperature is below low threshold.\n");
        }
    }

    /* finish interrupt test */
    lm75b_interface_debug_print("lm75b: finish interrupt test.\n");
    (void)lm75b_deinit(&gs_handle);
    
    return 0;
}
