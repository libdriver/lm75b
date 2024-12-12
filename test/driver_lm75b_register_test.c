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
 * @file      driver_lm75b_register_test.c
 * @brief     driver lm75b register test source file
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

#include "driver_lm75b_register_test.h"
#include <stdlib.h>

static lm75b_handle_t gs_handle;        /**< lm75b handle */

/**
 * @brief     register test
 * @param[in] addr iic address pin
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t lm75b_register_test(lm75b_address_t addr)
{
    uint8_t res; 
    uint16_t hysteresis;
    uint16_t threshold;
    uint16_t hysteresis_check;
    uint16_t threshold_check;
    float c;
    float c_check;
    uint16_t reg;
    lm75b_info_t info;
    lm75b_address_t addr_pin;
    lm75b_fault_queue_t fault_queue;
    lm75b_os_polarity_t polarity;
    lm75b_mode_t mode;
    lm75b_os_operation_mode_t interrupt_mode;
    
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
    
    /* start register test */
    lm75b_interface_debug_print("lm75b: start register test.\n");
    
    /* lm75b_set_addr_pin/lm75b_get_addr_pin test */
    lm75b_interface_debug_print("lm75b: lm75b_set_addr_pin/lm75b_get_addr_pin test.\n");
    
    /* set a000 */
    res = lm75b_set_addr_pin(&gs_handle, LM75B_ADDRESS_A000);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set addr pin failed.\n");
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: set addr pin a000.\n");
    res = lm75b_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: get addr pin failed.\n");
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: check addr pin %s.\n", addr_pin==LM75B_ADDRESS_A000?"ok":"error");
    
    /* set a001 */
    res = lm75b_set_addr_pin(&gs_handle, LM75B_ADDRESS_A001);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set addr pin failed.\n");
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: set addr pin a001.\n");
    res = lm75b_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: get addr pin failed.\n");
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: check addr pin %s.\n", addr_pin==LM75B_ADDRESS_A001?"ok":"error");
    
    /* set a010 */
    res = lm75b_set_addr_pin(&gs_handle, LM75B_ADDRESS_A010);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set addr pin failed.\n");
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: set addr pin a010.\n");
    res = lm75b_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: get addr pin failed.\n");
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: check addr pin %s.\n", addr_pin==LM75B_ADDRESS_A010?"ok":"error");
    
    /* set a011 */
    res = lm75b_set_addr_pin(&gs_handle, LM75B_ADDRESS_A011);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set addr pin failed.\n");
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: set addr pin a011.\n");
    res = lm75b_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: get addr pin failed.\n");
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: check addr pin %s.\n", addr_pin==LM75B_ADDRESS_A011?"ok":"error");
    
    /* set a100 */
    res = lm75b_set_addr_pin(&gs_handle, LM75B_ADDRESS_A100);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set addr pin failed.\n");
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: set addr pin a100.\n");
    res = lm75b_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: get addr pin failed.\n");
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: check addr pin %s.\n", addr_pin==LM75B_ADDRESS_A100?"ok":"error");
    
    /* set a101 */
    res = lm75b_set_addr_pin(&gs_handle, LM75B_ADDRESS_A101);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set addr pin failed.\n");
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: set addr pin a101.\n");
    res = lm75b_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: get addr pin failed.\n");
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: check addr pin %s.\n", addr_pin==LM75B_ADDRESS_A101?"ok":"error");
    
    /* set a110 */
    res = lm75b_set_addr_pin(&gs_handle, LM75B_ADDRESS_A110);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set addr pin failed.\n");
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: set addr pin a110.\n");
    res = lm75b_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: get addr pin failed.\n");
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: check addr pin %s.\n", addr_pin==LM75B_ADDRESS_A110?"ok":"error");
    
    /* set a111 */
    res = lm75b_set_addr_pin(&gs_handle, LM75B_ADDRESS_A111);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set addr pin failed.\n");
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: set addr pin a111.\n");
    res = lm75b_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: get addr pin failed.\n");
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: check addr pin %s.\n", addr_pin==LM75B_ADDRESS_A111?"ok":"error");
    
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
    
    /* lm75b_set_fault_queue/lm75b_get_fault_queue test */
    lm75b_interface_debug_print("lm75b: lm75b_set_fault_queue/lm75b_get_fault_queue test.\n");
    
    /* fault queue 1 */
    res = lm75b_set_fault_queue(&gs_handle, LM75B_FAULT_QUEUE_1);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set fault queue failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: set fault queue 1.\n");
    res = lm75b_get_fault_queue(&gs_handle, (lm75b_fault_queue_t *)&fault_queue);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: get fault queue failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: check fault queue %s.\n", fault_queue==LM75B_FAULT_QUEUE_1?"ok":"error");
    
    /* fault queue 2 */
    res = lm75b_set_fault_queue(&gs_handle, LM75B_FAULT_QUEUE_2);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set fault queue failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: set fault queue 2.\n");
    res = lm75b_get_fault_queue(&gs_handle, (lm75b_fault_queue_t *)&fault_queue);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: get fault queue failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: check fault queue %s.\n", fault_queue==LM75B_FAULT_QUEUE_2?"ok":"error");
    
    /* fault queue 3 */
    res = lm75b_set_fault_queue(&gs_handle, LM75B_FAULT_QUEUE_3);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set fault queue failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: set fault queue 3.\n");
    res = lm75b_get_fault_queue(&gs_handle, (lm75b_fault_queue_t *)&fault_queue);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: get fault queue failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: check fault queue %s.\n", fault_queue==LM75B_FAULT_QUEUE_3?"ok":"error");
    
    /* fault queue 6 */
    res = lm75b_set_fault_queue(&gs_handle, LM75B_FAULT_QUEUE_6);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set fault queue failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: set fault queue 6.\n");
    res = lm75b_get_fault_queue(&gs_handle, (lm75b_fault_queue_t *)&fault_queue);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: get fault queue failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: check fault queue %s.\n", fault_queue==LM75B_FAULT_QUEUE_6?"ok":"error");
    
    /* lm75b_set_os_polarity/lm75b_get_os_polarity test */
    lm75b_interface_debug_print("lm75b: lm75b_set_os_polarity/lm75b_get_os_polarity test.\n");
    
    /* set os polarity low */
    res = lm75b_set_os_polarity(&gs_handle, LM75B_OS_POLARITY_LOW);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set os polarity failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: set os polarity low.\n");
    res = lm75b_get_os_polarity(&gs_handle, (lm75b_os_polarity_t *)&polarity);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: get os polarity failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: check os polarity %s.\n", polarity==LM75B_OS_POLARITY_LOW?"ok":"error");
    
    /* set os polarity high */
    res = lm75b_set_os_polarity(&gs_handle, LM75B_OS_POLARITY_HIGH);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set os polarity failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: set os polarity high.\n");
    res = lm75b_get_os_polarity(&gs_handle, (lm75b_os_polarity_t *)&polarity);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: get os polarity failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: check os polarity %s.\n", polarity==LM75B_OS_POLARITY_HIGH?"ok":"error");
    
    /* lm75b_set_interrupt_mode/lm75b_get_interrupt_mode test */
    lm75b_interface_debug_print("lm75b: lm75b_set_interrupt_mode/lm75b_get_interrupt_mode test.\n");
    
    /* comparator */
    res = lm75b_set_interrupt_mode(&gs_handle, LM75B_OS_OPERATION_COMPARATOR);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set interrupt mode failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: set comparator mode.\n");
    res = lm75b_get_interrupt_mode(&gs_handle, (lm75b_os_operation_mode_t *)&interrupt_mode);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: get interrupt mode failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: check interrupt mode %s.\n", interrupt_mode==LM75B_OS_OPERATION_COMPARATOR?"ok":"error");
    
    /* interrupt */
    res = lm75b_set_interrupt_mode(&gs_handle, LM75B_OS_OPERATION_INTERRUPT);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set interrupt mode failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: set interrupt mode.\n");
    res = lm75b_get_interrupt_mode(&gs_handle, (lm75b_os_operation_mode_t *)&interrupt_mode);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: get interrupt mode failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: check interrupt mode %s.\n", interrupt_mode==LM75B_OS_OPERATION_INTERRUPT?"ok":"error");
    lm75b_interface_debug_print("lm75b: lm75b_set_mode/lm75b_get_mode test.\n");
    
    /* normal mode */
    res = lm75b_set_mode(&gs_handle, LM75B_MODE_NORMAL);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set mode failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: set normal mode.\n");
    res = lm75b_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: get mode failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: check mode %s.\n", mode==LM75B_MODE_NORMAL?"ok":"error");
    
    /* shut down mode */
    res = lm75b_set_mode(&gs_handle, LM75B_MODE_SHUTDOWN);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set mode failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: set shut down mode.\n");
    res = lm75b_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: get mode failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: check mode %s.\n", mode==LM75B_MODE_SHUTDOWN?"ok":"error");
    lm75b_interface_debug_print("lm75b: lm75b_set_hysteresis/lm75b_get_hysteresis test.\n");
    hysteresis = (rand() / 65535) & 0xFF80U;
    res = lm75b_set_hysteresis(&gs_handle, hysteresis);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set hysteresis failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: set hysteresis 0x%04X.\n", hysteresis);
    res = lm75b_get_hysteresis(&gs_handle, (uint16_t *)&hysteresis_check);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: get hysteresis failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: check hysteresis %s.\n", hysteresis_check==hysteresis?"ok":"error");
    
    /* lm75b_set_over_temperature_threshold/lm75b_get_over_temperature_threshold test */
    lm75b_interface_debug_print("lm75b: lm75b_set_over_temperature_threshold/lm75b_get_over_temperature_threshold test.\n");
    threshold = (rand() / 65535) & 0xFF80U;
    res = lm75b_set_over_temperature_threshold(&gs_handle, threshold);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: set threshold failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: set threshold 0x%04X.\n", threshold);
    res = lm75b_get_over_temperature_threshold(&gs_handle, (uint16_t *)&threshold_check);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: get threshold failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: check threshold %s.\n", threshold_check==threshold?"ok":"error");
    
    /* lm75b_hysteresis_convert_to_register/lm75b_hysteresis_convert_to_data test */
    lm75b_interface_debug_print("lm75b: lm75b_hysteresis_convert_to_register/lm75b_hysteresis_convert_to_data test.\n");
    c = (float)(rand() % 3000) / 30.0f;
    res = lm75b_hysteresis_convert_to_register(&gs_handle, c, (uint16_t *)&reg);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: hysteresis convert to register failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: hysteresis data is %0.2f.\n", c);
    lm75b_interface_debug_print("lm75b: register is 0x%04X.\n", reg);
    res = lm75b_hysteresis_convert_to_data(&gs_handle, reg, (float *)&c_check);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: hysteresis convert to data failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: hysteresis check data is %0.2f.\n", c_check);
    
    /* lm75b_over_temperature_threshold_convert_to_register/lm75b_over_temperature_threshold_convert_to_data test */
    lm75b_interface_debug_print("lm75b: lm75b_over_temperature_threshold_convert_to_register/lm75b_over_temperature_threshold_convert_to_data test.\n");
    c = -(float)(rand() % 3000) / 30.0f;
    res = lm75b_over_temperature_threshold_convert_to_register(&gs_handle, c, (uint16_t *)&reg);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: over temperature threshold convert to register failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: register is 0x%04X.\n", reg);
    lm75b_interface_debug_print("lm75b: over temperature threshold data is %0.2f.\n", c);
    res = lm75b_over_temperature_threshold_convert_to_data(&gs_handle, reg, (float *)&c_check);
    if (res != 0)
    {
        lm75b_interface_debug_print("lm75b: over temperature threshold convert to data failed.\n");
        (void)lm75b_deinit(&gs_handle);
        
        return 1;
    }
    lm75b_interface_debug_print("lm75b: over temperature threshold check data is %0.2f.\n", c_check);
    
    /* finish register test */
    lm75b_interface_debug_print("lm75b: finish register test.\n");
    (void)lm75b_deinit(&gs_handle);
    
    return 0;
}
