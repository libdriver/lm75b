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
 * @file      driver_lm75b.h
 * @brief     driver lm75b header file
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

#ifndef DRIVER_LM75B_H
#define DRIVER_LM75B_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup lm75b_driver lm75b driver function
 * @brief    lm75b driver modules
 * @{
 */

/**
 * @addtogroup lm75b_base_driver 
 * @{
 */

/**
 * @brief lm75b address enumeration definition
 */
typedef enum
{
    LM75B_ADDRESS_A000 = 0,        /**< A2A1A0 000 */
    LM75B_ADDRESS_A001 = 1,        /**< A2A1A0 001 */
    LM75B_ADDRESS_A010 = 2,        /**< A2A1A0 010 */
    LM75B_ADDRESS_A011 = 3,        /**< A2A1A0 011 */
    LM75B_ADDRESS_A100 = 4,        /**< A2A1A0 100 */
    LM75B_ADDRESS_A101 = 5,        /**< A2A1A0 101 */
    LM75B_ADDRESS_A110 = 6,        /**< A2A1A0 110 */
    LM75B_ADDRESS_A111 = 7,        /**< A2A1A0 111 */
} lm75b_address_t;

/**
 * @brief lm75b fault queue enumeration definition
 */
typedef enum
{
    LM75B_FAULT_QUEUE_1 = 0,        /**< fault queue 1 */
    LM75B_FAULT_QUEUE_2 = 1,        /**< fault queue 2 */
    LM75B_FAULT_QUEUE_3 = 2,        /**< fault queue 3 */
    LM75B_FAULT_QUEUE_6 = 3,        /**< fault queue 6 */
} lm75b_fault_queue_t;

/**
 * @brief lm75b os polarity enumeration definition
 */
typedef enum
{
    LM75B_OS_POLARITY_LOW  = 0,        /**< polarity low */
    LM75B_OS_POLARITY_HIGH = 1,        /**< polarity high */
} lm75b_os_polarity_t;

/**
 * @brief lm75b os polarity enumeration definition
 */
typedef enum
{
    LM75B_MODE_NORMAL   = 0,        /**< normal mode */
    LM75B_MODE_SHUTDOWN = 1,        /**< shutdown mode */
} lm75b_mode_t;

/**
 * @brief lm75b os operation enumeration definition
 */
typedef enum
{
    LM75B_OS_OPERATION_COMPARATOR = 0,        /**< comparator operation mode */
    LM75B_OS_OPERATION_INTERRUPT  = 1,        /**< interrupt operation mode */
} lm75b_os_operation_mode_t;

/**
 * @brief lm75b handle structure definition
 */
typedef struct lm75b_handle_s
{
    uint8_t iic_addr;                                                                   /**< iic device address */
    uint8_t (*iic_init)(void);                                                          /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                        /**< point to an iic_deinit function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write function address */
    void (*delay_ms)(uint32_t ms);                                                      /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                    /**< point to a debug_print function address */
    uint8_t inited;                                                                     /**< inited flag */
} lm75b_handle_t;

/**
 * @brief lm75b information structure definition
 */
typedef struct lm75b_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} lm75b_info_t;

/**
 * @}
 */

/**
 * @defgroup lm75b_link_driver lm75b link driver function
 * @brief    lm75b link driver modules
 * @ingroup  lm75b_driver
 * @{
 */

/**
 * @brief     initialize lm75b_handle_t structure
 * @param[in] HANDLE points to an lm75b handle structure
 * @param[in] STRUCTURE is lm75b_handle_t
 * @note      none
 */
#define DRIVER_LM75B_LINK_INIT(HANDLE, STRUCTURE)   memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to an lm75b handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_LM75B_LINK_IIC_INIT(HANDLE, FUC)    (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to an lm75b handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_LM75B_LINK_IIC_DEINIT(HANDLE, FUC)  (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE points to an lm75b handle structure
 * @param[in] FUC points to an iic_read function address
 * @note      none
 */
#define DRIVER_LM75B_LINK_IIC_READ(HANDLE, FUC)    (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE points to an lm75b handle structure
 * @param[in] FUC points to an iic_write function address
 * @note      none
 */
#define DRIVER_LM75B_LINK_IIC_WRITE(HANDLE, FUC)   (HANDLE)->iic_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to an lm75b handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_LM75B_LINK_DELAY_MS(HANDLE, FUC)    (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to an lm75b handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_LM75B_LINK_DEBUG_PRINT(HANDLE, FUC) (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup lm75b_base_driver lm75b base driver function
 * @brief    lm75b base driver modules
 * @ingroup  lm75b_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to an lm75b info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t lm75b_info(lm75b_info_t *info);

/**
 * @brief     set the iic address pin
 * @param[in] *handle points to an lm75b handle structure
 * @param[in] addr_pin is the chip iic address pin
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t lm75b_set_addr_pin(lm75b_handle_t *handle, lm75b_address_t addr_pin);

/**
 * @brief      get the iic address pin
 * @param[in]  *handle points to an lm75b handle structure
 * @param[out] *addr_pin points to a chip iic address pin buffer
 * @return      status code
 *              - 0 success
 *              - 2 handle is NULL
 * @note        none
 */
uint8_t lm75b_get_addr_pin(lm75b_handle_t *handle, lm75b_address_t *addr_pin);

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
uint8_t lm75b_init(lm75b_handle_t *handle);

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
uint8_t lm75b_deinit(lm75b_handle_t *handle);

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
uint8_t lm75b_read(lm75b_handle_t *handle, uint16_t *raw, float *s);

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
uint8_t lm75b_set_mode(lm75b_handle_t *handle, lm75b_mode_t mode);

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
uint8_t lm75b_get_mode(lm75b_handle_t *handle, lm75b_mode_t *mode);

/**
 * @}
 */

/**
 * @defgroup lm75b_interrupt_driver lm75b interrupt driver function
 * @brief    lm75b interrupt driver modules
 * @ingroup  lm75b_driver
 * @{
 */

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
uint8_t lm75b_set_fault_queue(lm75b_handle_t *handle, lm75b_fault_queue_t fault_queue);

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
uint8_t lm75b_get_fault_queue(lm75b_handle_t *handle, lm75b_fault_queue_t *fault_queue);

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
uint8_t lm75b_hysteresis_convert_to_register(lm75b_handle_t *handle, float c, uint16_t *reg);

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
uint8_t lm75b_hysteresis_convert_to_data(lm75b_handle_t *handle, uint16_t reg, float *c);

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
uint8_t lm75b_set_hysteresis(lm75b_handle_t *handle, uint16_t hysteresis);

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
uint8_t lm75b_get_hysteresis(lm75b_handle_t *handle, uint16_t *hysteresis);

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
uint8_t lm75b_over_temperature_threshold_convert_to_register(lm75b_handle_t *handle, float c, uint16_t *reg);

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
uint8_t lm75b_over_temperature_threshold_convert_to_data(lm75b_handle_t *handle, uint16_t reg, float *c);

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
uint8_t lm75b_set_over_temperature_threshold(lm75b_handle_t *handle, uint16_t threshold);

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
uint8_t lm75b_get_over_temperature_threshold(lm75b_handle_t *handle, uint16_t *threshold);

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
uint8_t lm75b_set_os_polarity(lm75b_handle_t *handle, lm75b_os_polarity_t polarity);

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
uint8_t lm75b_get_os_polarity(lm75b_handle_t *handle, lm75b_os_polarity_t *polarity);

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
uint8_t lm75b_set_interrupt_mode(lm75b_handle_t *handle, lm75b_os_operation_mode_t mode);

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
uint8_t lm75b_get_interrupt_mode(lm75b_handle_t *handle, lm75b_os_operation_mode_t *mode);

/**
 * @}
 */

/**
 * @defgroup lm75b_extern_driver lm75b extern driver function
 * @brief    lm75b extern driver modules
 * @ingroup  lm75b_driver
 * @{
 */

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
uint8_t lm75b_set_reg(lm75b_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

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
uint8_t lm75b_get_reg(lm75b_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
