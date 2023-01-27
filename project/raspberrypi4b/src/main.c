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
#include <getopt.h>
#include <stdlib.h>

/**
 * @brief global var definition
 */
volatile uint8_t g_flag;            /**< interrupt flag */

/**
 * @brief     lm75b full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t lm75b(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"addr", required_argument, NULL, 1},
        {"high-threshold", required_argument, NULL, 2},
        {"low-threshold", required_argument, NULL, 3},
        {"mode", required_argument, NULL, 4},
        {"times", required_argument, NULL, 5},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknow";
    uint32_t times = 3;
    lm75b_address_t addr = LM75B_ADDRESS_A000;
    lm75b_os_operation_mode_t mode = LM75B_OS_OPERATION_INTERRUPT;
    float high_threshold = 28.0f;
    float low_threshold = 25.0f;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* addr */
            case 1 :
            {
                if (strcmp("0", optarg) == 0)
                {
                    addr = LM75B_ADDRESS_A000;
                }
                else if (strcmp("1", optarg) == 0)
                {
                    addr = LM75B_ADDRESS_A001;
                }
                else if (strcmp("2", optarg) == 0)
                {
                    addr = LM75B_ADDRESS_A010;
                }
                else if (strcmp("3", optarg) == 0)
                {
                    addr = LM75B_ADDRESS_A011;
                }
                else if (strcmp("4", optarg) == 0)
                {
                    addr = LM75B_ADDRESS_A100;
                }
                else if (strcmp("5", optarg) == 0)
                {
                    addr = LM75B_ADDRESS_A101;
                }
                else if (strcmp("6", optarg) == 0)
                {
                    addr = LM75B_ADDRESS_A110;
                }
                else if (strcmp("7", optarg) == 0)
                {
                    addr = LM75B_ADDRESS_A111;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* high threshold */
            case 2 :
            {
                high_threshold = atof(optarg);
                
                break;
            }
             
            /* low threshold */
            case 3 :
            {
                low_threshold = atof(optarg);
                
                break;
            }
            
            /* mode */
            case 4 :
            {
                /* set the mode */
                if (strcmp("CMP", optarg) == 0)
                {
                    mode = LM75B_OS_OPERATION_COMPARATOR;
                }
                else if (strcmp("INT", optarg) == 0)
                {
                    mode = LM75B_OS_OPERATION_INTERRUPT;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* running times */
            case 5 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
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
    else if (strcmp("t_read", type) == 0)
    {
        /* run read test */
        if (lm75b_read_test(addr, times) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("t_int", type) == 0)
    {
        uint8_t res;
        
        /* gpio init */
        res = gpio_interrupt_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* run interrupt test */
        res = lm75b_interrupt_test(addr, mode, low_threshold, high_threshold, times);
        if (res != 0)
        {
            (void)gpio_interrupt_deinit();
            
            return 1;
        }
        
        /* gpio deinit */
        (void)gpio_interrupt_deinit();
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float t;
        
        /* basic init */
        res = lm75b_basic_init(addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            lm75b_interface_delay_ms(1000);
            
            /* read data */
            res = lm75b_basic_read((float *)&t);
            if (res != 0)
            {
                (void)lm75b_basic_deinit();
                
                return 1;
            }
            
            /* output */
            lm75b_interface_debug_print("lm75b: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
            lm75b_interface_debug_print("lm75b: temperature is %0.3fC.\n", t);
        }
        (void)lm75b_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_int", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float t;
        
        /* gpio init */
        res = gpio_interrupt_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* interrupt init */
        res = lm75b_interrupt_init(addr, mode, low_threshold, high_threshold);
        if (res != 0)
        {
            (void)gpio_interrupt_deinit();
            
            return 1;
        }
        
        /* loop */
        g_flag = 0;
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            lm75b_interface_delay_ms(1000);
            
            /* read data */
            res = lm75b_interrupt_read((float *)&t);
            if (res != 0)
            {
                (void)gpio_interrupt_deinit();
                (void)lm75b_interrupt_deinit();
                
                return 1;
            }
            
            /* output */
            lm75b_interface_debug_print("lm75b: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
            lm75b_interface_debug_print("lm75b: read is %0.3fC.\n", t);
            if (g_flag != 0)
            {
                lm75b_interface_debug_print("lm75b: find interrupt.\n");
                
                break;
            }
        }
        
        /* deinit */
        (void)gpio_interrupt_deinit();
        (void)lm75b_interrupt_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        lm75b_interface_debug_print("Usage:\n");
        lm75b_interface_debug_print("  lm75b (-i | --information)\n");
        lm75b_interface_debug_print("  lm75b (-h | --help)\n");
        lm75b_interface_debug_print("  lm75b (-p | --port)\n");
        lm75b_interface_debug_print("  lm75b (-t reg | --test=reg) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]\n");
        lm75b_interface_debug_print("  lm75b (-t read | --test=read) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>]\n");
        lm75b_interface_debug_print("  lm75b (-t int | --test=int) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>]\n");
        lm75b_interface_debug_print("        [--mode=<CMP | INT>] [--low-threshold=<low>] [--high-threshold=<high>]\n");
        lm75b_interface_debug_print("  lm75b (-e read | --example=read) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>]\n");
        lm75b_interface_debug_print("  lm75b (-e int | --example=int) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>]\n");
        lm75b_interface_debug_print("        [--mode=<CMP | INT>] [--low-threshold=<low>] [--high-threshold=<high>]\n");
        lm75b_interface_debug_print("\n");
        lm75b_interface_debug_print("Options:\n");
        lm75b_interface_debug_print("      --addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>\n");
        lm75b_interface_debug_print("                                 Set the addr pin.([default: 0])\n");
        lm75b_interface_debug_print("  -e <read | int>, --example=<read | int>\n");
        lm75b_interface_debug_print("                                 Run the driver example.\n");
        lm75b_interface_debug_print("  -h, --help                     Show the help.\n");
        lm75b_interface_debug_print("      --high-threshold=<high>    Set the interrupt high threshold.([default: 28.0f])\n");
        lm75b_interface_debug_print("  -i, --information              Show the chip information.\n");
        lm75b_interface_debug_print("      --low-threshold=<low>      Set the interrupt low threshold.([default: 25.0f])\n");
        lm75b_interface_debug_print("      --mode=<CMP | INT>         Set the interrupt mode.([default: INT])\n");
        lm75b_interface_debug_print("  -p, --port                     Display the pin connections of the current board.\n");
        lm75b_interface_debug_print("  -t <reg | read | init>, --test=<reg | read | int>\n");
        lm75b_interface_debug_print("                                 Run the driver test.\n");
        lm75b_interface_debug_print("      --times=<num>              Set the running times.([default: 3])\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        lm75b_info_t info;
        
        /* print lm75b info */
        lm75b_info(&info);
        lm75b_interface_debug_print("lm75b: chip is %s.\n", info.chip_name);
        lm75b_interface_debug_print("lm75b: manufacturer is %s.\n", info.manufacturer_name);
        lm75b_interface_debug_print("lm75b: interface is %s.\n", info.interface);
        lm75b_interface_debug_print("lm75b: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        lm75b_interface_debug_print("lm75b: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        lm75b_interface_debug_print("lm75b: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        lm75b_interface_debug_print("lm75b: max current is %0.2fmA.\n", info.max_current_ma);
        lm75b_interface_debug_print("lm75b: max temperature is %0.1fC.\n", info.temperature_max);
        lm75b_interface_debug_print("lm75b: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        lm75b_interface_debug_print("lm75b: SCL connected to GPIO3(BCM).\n");
        lm75b_interface_debug_print("lm75b: SDA connected to GPIO2(BCM).\n");
        lm75b_interface_debug_print("lm75b: OS connected to GPIO17(BCM).\n");
        
        return 0;
    }
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
