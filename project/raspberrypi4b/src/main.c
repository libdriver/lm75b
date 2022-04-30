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
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-03-10
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date         <th>Version  <th>Author      <th>Description
 * <tr><td>2021/03/10   <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_lm75b_basic.h"
#include "driver_lm75b_interrupt.h"
#include "driver_lm75b_register_test.h"
#include "driver_lm75b_read_test.h"
#include "driver_lm75b_interrupt_test.h"
#include "gpio.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_flag;            /**< interrupt flag */

/**
 * @brief     lm75b full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t lm75b(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            lm75b_info_t info;
            
            /* print lm75b info */
            lm75b_info(&info);
            lm75b_interface_debug_print("lm75b: chip is %s.\n", info.chip_name);
            lm75b_interface_debug_print("lm75b: manufacturer is %s.\n", info.manufacturer_name);
            lm75b_interface_debug_print("lm75b: interface is %s.\n", info.interface);
            lm75b_interface_debug_print("lm75b: driver version is %d.%d.\n", info.driver_version/1000, (info.driver_version%1000)/100);
            lm75b_interface_debug_print("lm75b: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            lm75b_interface_debug_print("lm75b: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            lm75b_interface_debug_print("lm75b: max current is %0.2fmA.\n", info.max_current_ma);
            lm75b_interface_debug_print("lm75b: max temperature is %0.1fC.\n", info.temperature_max);
            lm75b_interface_debug_print("lm75b: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            lm75b_interface_debug_print("lm75b: SCL connected to GPIO3(BCM).\n");
            lm75b_interface_debug_print("lm75b: SDA connected to GPIO2(BCM).\n");
            lm75b_interface_debug_print("lm75b: OS connected to GPIO17(BCM).\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show lm75b help */
            
            help:
            
            lm75b_interface_debug_print("lm75b -i\n\tshow lm75b chip and driver information.\n");
            lm75b_interface_debug_print("lm75b -h\n\tshow lm75b help.\n");
            lm75b_interface_debug_print("lm75b -p\n\tshow lm75b pin connections of the current board.\n");
            lm75b_interface_debug_print("lm75b -t reg -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)\n\trun lm75b register test.\n");
            lm75b_interface_debug_print("lm75b -t read <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)\n\trun lm75b read test."
                                        "times means test times.\n");
            lm75b_interface_debug_print("lm75b -t int <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7) -m (COMPARATOR | INTERRUPT) "
                                        "<lowthreshold> <highthreshold>\n\t");
            lm75b_interface_debug_print("run lm75b interrupt test.times means test times.lowthreshold means low interrupt threshold."
                                        "highthreshold means high interrupt threshold.\n");
            lm75b_interface_debug_print("lm75b -c read <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)\n\trun lm75b read function."
                                        "times means read times.\n");
            lm75b_interface_debug_print("lm75b -c int <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7) -m (COMPARATOR  | INTERRUPT) "
                                        "<lowthreshold> <highthreshold>\n\t");
            lm75b_interface_debug_print("run lm75b interrupt function.times means read times.lowthreshold means low interrupt threshold."
                                        "highthreshold means high interrupt threshold.");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 5)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* reg test */
            if (strcmp("reg", argv[2]) == 0)
            {
                lm75b_address_t addr;
                
                if (strcmp("-a", argv[3]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[4]) == 0)
                {
                    addr = LM75B_ADDRESS_A000;
                }
                else if (strcmp("1", argv[4]) == 0)
                {
                    addr = LM75B_ADDRESS_A001;
                }
                else if (strcmp("2", argv[4]) == 0)
                {
                    addr = LM75B_ADDRESS_A010;
                }
                else if (strcmp("3", argv[4]) == 0)
                {
                    addr = LM75B_ADDRESS_A011;
                }
                else if (strcmp("4", argv[4]) == 0)
                {
                    addr = LM75B_ADDRESS_A100;
                }
                else if (strcmp("5", argv[4]) == 0)
                {
                    addr = LM75B_ADDRESS_A101;
                }
                else if (strcmp("6", argv[4]) == 0)
                {
                    addr = LM75B_ADDRESS_A110;
                }
                else if (strcmp("7", argv[4]) == 0)
                {
                    addr = LM75B_ADDRESS_A111;
                }
                else
                {
                    lm75b_interface_debug_print("lm75b: iic address is invalid.\n");
                    
                    return 5;
                }
                /* run reg test */
                if (lm75b_register_test(addr) != 0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 6)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* read test */
            if (strcmp("read", argv[2]) == 0)
            {
                lm75b_address_t addr;
                
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A000;
                }
                else if (strcmp("1", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A001;
                }
                else if (strcmp("2", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A010;
                }
                else if (strcmp("3", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A011;
                }
                else if (strcmp("4", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A100;
                }
                else if (strcmp("5", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A101;
                }
                else if (strcmp("6", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A110;
                }
                else if (strcmp("7", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A111;
                }
                else
                {
                    lm75b_interface_debug_print("lm75b: iic address is invalid.\n");
                    
                    return 5;
                }
                
                /* run read test */
                if (lm75b_read_test(addr, atoi(argv[3])) != 0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* run function */
        else if (strcmp("-c", argv[1]) == 0)
        {
            /* read function */
            if (strcmp("read", argv[2]) == 0)
            {
                uint8_t res;
                uint32_t times;
                uint32_t i;
                float t;
                lm75b_address_t addr;
                
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A000;
                }
                else if (strcmp("1", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A001;
                }
                else if (strcmp("2", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A010;
                }
                else if (strcmp("3", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A011;
                }
                else if (strcmp("4", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A100;
                }
                else if (strcmp("5", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A101;
                }
                else if (strcmp("6", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A110;
                }
                else if (strcmp("7", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A111;
                }
                else
                {
                    lm75b_interface_debug_print("lm75b: iic address is invalid.\n");
                    
                    return 5;
                }
                
                res = lm75b_basic_init(addr);
                if (res != 0)
                {
                    return 1;
                }
                times = atoi(argv[3]);
                for (i = 0; i < times; i++)
                {
                    lm75b_interface_delay_ms(1000);
                    res = lm75b_basic_read((float *)&t);
                    if (res != 0)
                    {
                        (void)lm75b_basic_deinit();
                        
                        return 1;
                    }
                    lm75b_interface_debug_print("lm75b: %d/%d.\n", (uint32_t)(i+1), (uint32_t)times);
                    lm75b_interface_debug_print("lm75b: temperature is %0.3fC.\n", t);
                }
                (void)lm75b_basic_deinit();
                
                return 0;
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 10)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* int */
            if (strcmp("int", argv[2]) == 0)
            {
                uint8_t res;
                lm75b_address_t addr;
                lm75b_os_operation_mode_t mode;
                
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A000;
                }
                else if (strcmp("1", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A001;
                }
                else if (strcmp("2", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A010;
                }
                else if (strcmp("3", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A011;
                }
                else if (strcmp("4", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A100;
                }
                else if (strcmp("5", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A101;
                }
                else if (strcmp("6", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A110;
                }
                else if (strcmp("7", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A111;
                }
                else
                {
                    lm75b_interface_debug_print("lm75b: iic address is invalid.\n");
                    
                    return 5;
                }
                if (strcmp("-m", argv[6]) != 0)
                {
                    return 5;
                }
                if (strcmp("INTERRUPT", argv[7]) == 0)
                {
                    mode = LM75B_OS_OPERATION_INTERRUPT;
                }
                else if (strcmp("COMPARATOR", argv[7]) == 0)
                {
                    mode = LM75B_OS_OPERATION_COMPARATOR;
                }
                else
                {
                    lm75b_interface_debug_print("lm75b: interrupt mode is invalid.\n");
                    
                    return 5;
                }
                res = gpio_interrupt_init();
                if (res != 0)
                {
                    return 1;
                }
                res = lm75b_interrupt_test(addr, mode, (float)atof(argv[8]), (float)atof(argv[9]), atoi(argv[3]));
                if (res != 0)
                {
                    (void)gpio_interrupt_deinit();
                    
                    return 1;
                }
                (void)gpio_interrupt_deinit();
                
                return 0;
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* run function */
        else if (strcmp("-c", argv[1]) == 0)
        {
             /* int */
            if (strcmp("int", argv[2]) == 0)
            {
                uint8_t res;
                uint32_t times;
                uint32_t i;
                float t;
                lm75b_address_t addr;
                lm75b_os_operation_mode_t mode;
                
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A000;
                }
                else if (strcmp("1", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A001;
                }
                else if (strcmp("2", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A010;
                }
                else if (strcmp("3", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A011;
                }
                else if (strcmp("4", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A100;
                }
                else if (strcmp("5", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A101;
                }
                else if (strcmp("6", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A110;
                }
                else if (strcmp("7", argv[5]) == 0)
                {
                    addr = LM75B_ADDRESS_A111;
                }
                else
                {
                    lm75b_interface_debug_print("lm75b: iic address is invalid.\n");
                    
                    return 5;
                }
                if (strcmp("-m", argv[6]) != 0)
                {
                    return 5;
                }
                if (strcmp("INTERRUPT", argv[7]) == 0)
                {
                    mode = LM75B_OS_OPERATION_INTERRUPT;
                }
                else if (strcmp("COMPARATOR", argv[7]) == 0)
                {
                    mode = LM75B_OS_OPERATION_COMPARATOR;
                }
                else
                {
                    lm75b_interface_debug_print("lm75b: interrupt mode is invalid.\n");
                    
                    return 5;
                }
                times = atoi(argv[3]);
                res = gpio_interrupt_init();
                if (res != 0)
                {
                    return 1;
                }
                res = lm75b_interrupt_init(addr, mode, (float)atof(argv[8]), (float)atof(argv[9]));
                if (res != 0)
                {
                    (void)gpio_interrupt_deinit();
                    
                    return 1;
                }
                g_flag = 0;
                for (i = 0; i < times; i++)
                {
                    lm75b_interface_delay_ms(1000);
                    res = lm75b_interrupt_read((float *)&t);
                    if (res != 0)
                    {
                        (void)gpio_interrupt_deinit();
                        (void)lm75b_interrupt_deinit();
                        
                        return 1;
                    }
                    lm75b_interface_debug_print("lm75b: %d/%d.\n", (uint32_t)(i+1), (uint32_t)times);
                    lm75b_interface_debug_print("lm75b: read is %0.3fC.\n", t);
                    if (g_flag != 0)
                    {
                        lm75b_interface_debug_print("lm75b: find interrupt.\n");
                        
                        break;
                    }
                }
                (void)gpio_interrupt_deinit();
                (void)lm75b_interrupt_deinit();
                
                return 0;
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = lm75b(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        lm75b_interface_debug_print("lm75b: run failed.\n");
    }
    else if (res == 5)
    {
        lm75b_interface_debug_print("lm75b: param is invalid.\n");
    }
    else
    {
        lm75b_interface_debug_print("lm75b: unknow status code.\n");
    }

    return 0;
}