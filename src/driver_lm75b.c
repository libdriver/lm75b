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
 * @file      driver_lm75b.c
 * @brief     driver lm75b source file
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

#include "driver_lm75b.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "NXP LM75B"        /**< chip name */
#define MANUFACTURER_NAME         "NXP"              /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.8f               /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f               /**< chip max supply voltage */
#define MAX_CURRENT               10.0f              /**< chip max current */
#define TEMPERATURE_MIN           -55.0f             /**< chip min operating temperature */
#define TEMPERATURE_MAX           125.0f             /**< chip max operating temperature */
#define DRIVER_VERSION            2000               /**< driver version */

/**
 * @brief chip register definition
 */
#define LM75B_REG_CONF         0x01        /**< configure register */
#define LM75B_REG_TEMP         0x00        /**< temperature register */
#define LM75B_REG_TOS          0x03        /**< TOS register */
#define LM75B_REG_THYST        0x02        /**< THYST register */

/**
 * @brief     set the iic address pin
 * @param[in] *handle points to an lm75b handle structure
 * @param[in] addr_pin is the chip iic address pin
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t lm75b_set_addr_pin(lm75b_handle_t *handle, lm75b_address_t addr_pin)
{
    if (handle == NULL)                       /* check handle */
    {
        return 2;                             /* return error */
    }

    handle->iic_addr = 0x90;                  /* set iic addr */
    handle->iic_addr |= addr_pin << 1;        /* set iic address */
    
    return 0;                                 /* success return 0 */
}

/**
 * @brief      get the iic address pin
 * @param[in]  *handle points to an lm75b handle structure
 * @param[out] *addr_pin points to a chip iic address pin buffer
 * @return      status code
 *              - 0 success
 *              - 2 handle is NULL
 * @note        none
 */
uint8_t lm75b_get_addr_pin(lm75b_handle_t *handle, lm75b_address_t *addr_pin)
{
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }

    *addr_pin = (lm75b_address_t)((handle->iic_addr&(~0x90)) >> 1);        /* get iic address */
    
    return 0;                                                              /* success return 0 */
}

/**
 * @brief      convert the hysteresis value to the register data
 * @param[in]  *handle points to an lm75b handle structure
 * @param[in]  c is the hysteresis value
 * @param[out] *reg points to a register data buffer
 * @return      status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note        none
 */
uint8_t lm75b_hysteresis_convert_to_register(lm75b_handle_t *handle, float c, uint16_t *reg)
{
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    if (c > 0)                                                             /* if positive */
    {
        *reg = ((uint16_t)(c / 0.5f) & 0xFF) << 7;                         /* get reg */
    }
    else                                                                   /* if negtive */
    {
        *reg = (1<<15) | (~(((uint16_t)(-c /0.5f) & 0xFF) - 1))<<7;        /* get reg */
    }
    
    return 0;                                                              /* success return 0 */
}

/**
 * @brief      convert the register raw data to the hysteresis value
 * @param[in]  *handle points to an lm75b handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *c points to a converted hysteresis value buffer
 * @return      status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note        none
 */
uint8_t lm75b_hysteresis_convert_to_data(lm75b_handle_t *handle, uint16_t reg, float *c)
{
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    
    reg = reg >> 7;                                                /* right shift 7 */
    if ((reg & 0x0100) != 0)                                       /* check first bit */
    {
        *c= -0.5f * (float)((uint16_t)((~(reg))&0xFF) + 1);        /* if negtive set convert temp */
    }
    else
    {
        *c = (float)(reg) * 0.5f;                                  /* if positive set convert temp */
    }
    
    return 0;                                                      /* success return 0 */
}

/**
 * @brief     set the hysteresis value
 * @param[in] *handle points to an lm75b handle structure
 * @param[in] hysteresis is the hysteresis value
 * @return    status code
 *            - 0 success
 *            - 1 set hysteresis failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t lm75b_set_hysteresis(lm75b_handle_t *handle, uint16_t hysteresis)
{
    uint8_t res;
    uint8_t buf[2];
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }

    buf[0] = (hysteresis >> 8) & 0xFF;                                                    /* set MSB */
    buf[1] = hysteresis & 0xFF;                                                           /* set LSB */
    res = handle->iic_write(handle->iic_addr, LM75B_REG_THYST, (uint8_t *)buf, 2);        /* set hysteresis */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("lm75b: write hysteresis failed.\n");                         /* write hysteresis failed */
       
        return 1;                                                                         /* return error */
    }
    
    return 0;                                                                             /* success return 0 */
}

/**
 * @brief      get the hysteresis value
 * @param[in]  *handle points to an lm75b handle structure
 * @param[out] *hysteresis points to a hysteresis value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get hysteresis failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t lm75b_get_hysteresis(lm75b_handle_t *handle, uint16_t *hysteresis)
{
    uint8_t res;
    uint8_t buf[2];
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    
    res = handle->iic_read(handle->iic_addr, LM75B_REG_THYST, (uint8_t *)buf, 2);        /* get hysteresis */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("lm75b: read hysteresis failed.\n");                         /* read hysteresis failed */
       
        return 1;                                                                        /* return error */
    }
    *hysteresis = (uint16_t)(((uint16_t)buf[0]) << 8) | buf[1];                          /* set data */
    
    return 0;                                                                            /* success return 0 */
}

/**
 * @brief      convert the over temperature threshold to the register data
 * @param[in]  *handle points to an lm75b handle structure
 * @param[in]  c is the over temperature threshold
 * @param[out] *reg points to a register data buffer
 * @return      status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note        none
 */
uint8_t lm75b_over_temperature_threshold_convert_to_register(lm75b_handle_t *handle, float c, uint16_t *reg)
{
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    if (c > 0)                                                             /* if positive */
    {
        *reg = ((uint16_t)(c / 0.5f) & 0xFF) << 7;                         /* get reg */
    }
    else                                                                   /* if negtive */
    {
        *reg = (1<<15) | (~(((uint16_t)(-c /0.5f) & 0xFF) - 1))<<7;        /* get reg */
    }
    
    return 0;                                                              /* success return 0 */
}

/**
 * @brief      convert the register raw data to the over temperature threshold
 * @param[in]  *handle points to an lm75b handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *c points to a converted over temperature threshold buffer
 * @return      status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note        none
 */
uint8_t lm75b_over_temperature_threshold_convert_to_data(lm75b_handle_t *handle, uint16_t reg, float *c)
{
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    
    reg = reg >> 7;                                                /* right shift 7 */
    if ((reg & 0x0100) != 0)                                       /* check first bit */
    {
        *c= -0.5f * (float)((uint16_t)((~(reg))&0xFF) + 1);        /* if negtive set convert temp */
    }
    else
    {
        *c = (float)(reg) * 0.5f;                                  /* if positive set convert temp */
    }
    
    return 0;                                                      /* success return 0 */
}

/**
 * @brief     set the over temperature threshold
 * @param[in] *handle points to an lm75b handle structure
 * @param[in] threshold is the over temperature threshold
 * @return    status code
 *            - 0 success
 *            - 1 set over temperature threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t lm75b_set_over_temperature_threshold(lm75b_handle_t *handle, uint16_t threshold)
{
    uint8_t res;
    uint8_t buf[2];
    
    if (handle == NULL)                                                                 /* check handle */
    {
        return 2;                                                                       /* return error */
    }
    if (handle->inited != 1)                                                            /* check handle initialization */
    {
        return 3;                                                                       /* return error */
    }

    buf[0] = (threshold >> 8) & 0xFF;                                                   /* set MSB */
    buf[1] = threshold & 0xFF;                                                          /* set LSB */
    res = handle->iic_write(handle->iic_addr, LM75B_REG_TOS, (uint8_t *)buf, 2);        /* set threshold */
    if (res != 0)                                                                       /* check result */
    {
        handle->debug_print("lm75b: write tos failed.\n");                              /* write tos failed */
       
        return 1;                                                                       /* return error */
    }
    
    return 0;                                                                           /* success return 0 */
}

/**
 * @brief      get the over temperature threshold
 * @param[in]  *handle points to an lm75b handle structure
 * @param[out] *threshold points to an over temperature threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get over temperature threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t lm75b_get_over_temperature_threshold(lm75b_handle_t *handle, uint16_t *threshold)
{
    uint8_t res;
    uint8_t buf[2];
    
    if (handle == NULL)                                                                /* check handle */
    {
        return 2;                                                                      /* return error */
    }
    if (handle->inited != 1)                                                           /* check handle initialization */
    {
        return 3;                                                                      /* return error */
    }
    
    res = handle->iic_read(handle->iic_addr, LM75B_REG_TOS, (uint8_t *)buf, 2);        /* get threshold */
    if (res != 0)                                                                      /* check result */
    {
        handle->debug_print("lm75b: read tos failed.\n");                              /* read tos failed */
       
        return 1;                                                                      /* return error */
    }
    *threshold = (uint16_t)(((uint16_t)buf[0]) << 8) | buf[1];                         /* set data */
    
    return 0;                                                                          /* success return 0 */
}

/**
 * @brief     set the chip fault queue
 * @param[in] *handle points to an lm75b handle structure
 * @param[in] fault_queue is the chip fault queue
 * @return    status code
 *            - 0 success
 *            - 1 set fault queue failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t lm75b_set_fault_queue(lm75b_handle_t *handle, lm75b_fault_queue_t fault_queue)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }

    res = handle->iic_read(handle->iic_addr, LM75B_REG_CONF, (uint8_t *)&prev, 1);         /* read config */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("lm75b: read configure failed.\n");                            /* read configure failed */
       
        return 1;                                                                          /* return error */
    }
    prev &= ~ (0x03 << 3);                                                                 /* clear fault queue */
    prev |= fault_queue << 3;                                                              /* set queue */
    res = handle->iic_write(handle->iic_addr, LM75B_REG_CONF, (uint8_t *)&prev, 1);        /* write conf */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("lm75b: write configure failed.\n");                           /* write configure failed */
       
        return 1;                                                                          /* return error */
    }
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief      get the chip fault queue
 * @param[in]  *handle points to an lm75b handle structure
 * @param[out] *fault_queue points to a chip fault queue buffer
 * @return     status code
 *             - 0 success
 *             - 1 get fault queue failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t lm75b_get_fault_queue(lm75b_handle_t *handle, lm75b_fault_queue_t *fault_queue)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }

    res = handle->iic_read(handle->iic_addr, LM75B_REG_CONF, (uint8_t *)&prev, 1);         /* read configure */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("lm75b: read configure failed.\n");                            /* read configure failed */
       
        return 1;                                                                          /* return error */
    }
    *fault_queue = (lm75b_fault_queue_t)((prev >> 3) & 0x03);                              /* get fault queue */
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief     set the chip os polarity
 * @param[in] *handle points to an lm75b handle structure
 * @param[in] polarity is the os polarity
 * @return    status code
 *            - 0 success
 *            - 1 set os polarity failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t lm75b_set_os_polarity(lm75b_handle_t *handle, lm75b_os_polarity_t polarity)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }

    res = handle->iic_read(handle->iic_addr, LM75B_REG_CONF, (uint8_t *)&prev, 1);         /* read configure */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("lm75b: read configure failed.\n");                            /* read configure failed */
       
        return 1;                                                                          /* return error */
    }
    prev &= ~ (1 << 2);                                                                    /* clear polarity */
    prev |= polarity << 2;                                                                 /* set polarity */
    res = handle->iic_write(handle->iic_addr, LM75B_REG_CONF, (uint8_t *)&prev, 1);        /* write confure */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("lm75b: write configure failed.\n");                           /* write configure failed */
       
        return 1;                                                                          /* return error */
    }
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief      get the chip os polarity
 * @param[in]  *handle points to an lm75b handle structure
 * @param[out] *polarity points to an os polarity buffer
 * @return     status code
 *             - 0 success
 *             - 1 get os polarity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t lm75b_get_os_polarity(lm75b_handle_t *handle, lm75b_os_polarity_t *polarity)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }

    res = handle->iic_read(handle->iic_addr, LM75B_REG_CONF, (uint8_t *)&prev, 1);         /* read configure */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("lm75b: read configure failed.\n");                            /* read configure failed */
       
        return 1;                                                                          /* return error */
    }
    *polarity = (lm75b_os_polarity_t)((prev >> 2) & 0x01);                                 /* get polarity */
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief     set the chip interrupt mode
 * @param[in] *handle points to an lm75b handle structure
 * @param[in] mode is the interrupt mode
 * @return    status code
 *            - 0 success
 *            - 1 set interrupt mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t lm75b_set_interrupt_mode(lm75b_handle_t *handle, lm75b_os_operation_mode_t mode)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }

    res = handle->iic_read(handle->iic_addr, LM75B_REG_CONF, (uint8_t *)&prev, 1);         /* read configure */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("lm75b: read configure failed.\n");                            /* read configure failed */
       
        return 1;                                                                          /* return error */
    }
    prev &= ~ (1 << 1);                                                                    /* clear mode */
    prev |= mode << 1;                                                                     /* set mode */
    res = handle->iic_write(handle->iic_addr, LM75B_REG_CONF, (uint8_t *)&prev, 1);        /* write configure */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("lm75b: write configure failed.\n");                           /* write configure failed */
       
        return 1;                                                                          /* return error */
    }
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief      get the chip interrupt mode
 * @param[in]  *handle points to an lm75b handle structure
 * @param[out] *mode points to an interrupt mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get interrupt mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t lm75b_get_interrupt_mode(lm75b_handle_t *handle, lm75b_os_operation_mode_t *mode)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }

    res = handle->iic_read(handle->iic_addr, LM75B_REG_CONF, (uint8_t *)&prev, 1);         /* read configure */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("lm75b: read configure failed.\n");                            /* read configure failed */
       
        return 1;                                                                          /* return error */
    }
    *mode = (lm75b_os_operation_mode_t)((prev >> 1) & 0x01);                               /* get mode */
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief     set the chip mode
 * @param[in] *handle points to an lm75b handle structure
 * @param[in] mode is the chip mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t lm75b_set_mode(lm75b_handle_t *handle, lm75b_mode_t mode)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }

    res = handle->iic_read(handle->iic_addr, LM75B_REG_CONF, (uint8_t *)&prev, 1);         /* read configure */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("lm75b: read configure failed.\n");                            /* read configure failed */
       
        return 1;                                                                          /* return error */
    }
    prev &= ~ (1 << 0);                                                                    /* clear mode */
    prev |= mode << 0;                                                                     /* set mode */
    res = handle->iic_write(handle->iic_addr, LM75B_REG_CONF, (uint8_t *)&prev, 1);        /* write conf */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("lm75b: write configure failed.\n");                           /* write configure failed */
       
        return 1;                                                                          /* return error */
    }
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief      get the chip mode
 * @param[in]  *handle points to an lm75b handle structure
 * @param[out] *mode points to a chip mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t lm75b_get_mode(lm75b_handle_t *handle, lm75b_mode_t *mode)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }

    res = handle->iic_read(handle->iic_addr, LM75B_REG_CONF, (uint8_t *)&prev, 1);         /* read configure */
    if (res != 0)                                                                          /* check error */
    {
        handle->debug_print("lm75b: read configure failed.\n");                            /* read config failed */
       
        return 1;                                                                          /* return error */
    }
    *mode = (lm75b_mode_t)((prev >> 0) & 0x01);                                            /* get mode */
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an lm75b handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t lm75b_init(lm75b_handle_t *handle)
{
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->debug_print == NULL)                                /* check debug_print */
    {
        return 3;                                                   /* return error */
    }
    if (handle->iic_init == NULL)                                   /* check iic_init */
    {
        handle->debug_print("lm75b: iic_init is null.\n");          /* iic_init is null */
       
        return 3;                                                   /* return error */
    }
    if (handle->iic_deinit == NULL)                                 /* check iic_deinit */
    {
        handle->debug_print("lm75b: iic_deinit is null.\n");        /* iic_deinit is null */
       
        return 3;                                                   /* return error */
    }
    if (handle->iic_read == NULL)                                   /* check iic_read */
    {
        handle->debug_print("lm75b: iic_read is null.\n");          /* iic_read is null */
       
        return 3;                                                   /* return error */
    }
    if (handle->iic_write == NULL)                                  /* check iic_write */
    {
        handle->debug_print("lm75b: iic_write is null.\n");         /* iic_write is null */
       
        return 3;                                                   /* return error */
    }
    if (handle->delay_ms == NULL)                                   /* check delay_ms */
    {
        handle->debug_print("lm75b: delay_ms is null.\n");          /* delay_ms is null */
       
        return 3;                                                   /* return error */
    }
    
    if (handle->iic_init() != 0)                                    /* initialize iic bus */
    {
        handle->debug_print("lm75b: iic init failed.\n");           /* iic init failed */
        
        return 1;                                                   /* return error */
    }
    handle->inited = 1;                                             /* flag finish initialization */
    
    return 0;                                                       /* success return 0 */
}

/**
 * @brief     close the chip
 * @param[in] *handle points to an lm75b handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t lm75b_deinit(lm75b_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }
    
    res = handle->iic_read(handle->iic_addr, LM75B_REG_CONF, (uint8_t *)&prev, 1);         /* read config */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("lm75b: read configure failed.\n");                            /* read config failed */
       
        return 1;                                                                          /* return error */
    }
    prev &= ~(1 << 0);                                                                     /* clear mode */
    res = handle->iic_write(handle->iic_addr, LM75B_REG_CONF, (uint8_t *)&prev, 1);        /* write configure */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("lm75b: write configure failed.\n");                           /* write configigure failed */
       
        return 1;                                                                          /* return error */
    }
    if (handle->iic_deinit() != 0)                                                         /* close iic bus */
    {
        handle->debug_print("lm75b: iic deinit failed.\n");                                /* iic deinit failed */
        
        return 1;                                                                          /* return error */
    }
    handle->inited = 0;                                                                    /* flag close */
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief      read data from the chip
 * @param[in]  *handle points to an lm75b handle structure
 * @param[out] *raw points to a raw temperature buffer
 * @param[out] *s points to a converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t lm75b_read(lm75b_handle_t *handle, uint16_t *raw, float *s)
{
    uint8_t res;
    uint8_t buf[2];
    
    if (handle == NULL)                                                                 /* check handle */
    {
        return 2;                                                                       /* return error */
    }
    if (handle->inited != 1)                                                            /* check handle initialization */
    {
        return 3;                                                                       /* return error */
    }
    
    memset(buf, 0, sizeof(uint8_t) * 2);                                                /* clear the buffer */
    res = handle->iic_read(handle->iic_addr, LM75B_REG_TEMP, (uint8_t *)buf, 2);        /* get temperature */
    if (res != 0)                                                                       /* check result */
    {
        handle->debug_print("lm75b: read temp failed.\n");                              /* read temp failed */
       
        return 1;                                                                       /* return error */
    }
    *raw = (uint16_t)(((uint16_t)buf[0]) << 8) | buf[1];                                /* set raw data */
    *raw = (*raw) >> 5;                                                                 /* right shift 5 */
    if (((*raw) & 0x0400) != 0)                                                         /* check first bit */
    {
        *raw = (*raw) | 0xF800U;                                                        /* set negtive part */
        *s = (float)(-(~(*raw) + 1)) * 0.125f;                                          /* if negtive set convert temp */
    }
    else
    {
        *s = (float)(*raw) * 0.125f;                                                    /* if positive set convert temp */
    }
    
    return 0;                                                                           /* success return 0 */
}

/**
 * @brief     set the chip register
 * @param[in] *handle points to an lm75b handle structure
 * @param[in] reg is the iic register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t lm75b_set_reg(lm75b_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->inited != 1)                                        /* check handle initialization */
    {
        return 3;                                                   /* return error */
    }
  
    if (handle->iic_write(handle->iic_addr, reg, buf, len) != 0)    /* write register */
    {
        handle->debug_print("lm75b: write failed.\n");              /* write failed */
       
        return 1;                                                   /* return error */
    }
    else
    {
        return 0;                                                   /* success return 0 */
    }
}

/**
 * @brief      get the chip register
 * @param[in]  *handle points to an lm75b handle structure
 * @param[in]  reg is the iic register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t lm75b_get_reg(lm75b_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
  
    if (handle->iic_read(handle->iic_addr, reg, buf, len) != 0)    /* read register */
    {
        handle->debug_print("lm75b: read failed.\n");              /* read failed */
       
        return 1;                                                  /* return error */
    }
    else
    {
        return 0;                                                  /* success return 0 */
    }
}

/**
 * @brief      get chip's information
 * @param[out] *info points to an lm75b info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t lm75b_info(lm75b_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(lm75b_info_t));                          /* initialize lm75b info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver verison */
    
    return 0;                                                       /* success return 0 */
}
