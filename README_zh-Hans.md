[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver LM75B

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/lm75b/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

LM75B是一款温度-数字转换器，使用片上温度传感器和Σ-Δ A/D转换技术并带有过热检测输出。LM75B包含一系列数据寄存器：数据储存寄存器，器件工作模式寄存器、OS工作模式寄存器、OS极性和OS故障队列等；储存数字温度读数的温度寄存器(Temp)以及储存可编程过热关断和滞后极限的设置点寄存器(Tos和Thyst)，可通过2线串行I²C总线接口与控制器进行通信。该器件还提供开漏输出(OS)，可在温度超过编程限值时激活。共有三个可选逻辑地址引脚，因此可在同一总线上连接八个器件而不会发生地址冲突。LM75B可为不同的工作条件进行配置。可将其设为正常模式以定期监视环境温度，或设为关断模式以使功耗最小化。OS输出可在两种可选模式中的任意一种下工作：OS比较器模式或OS中断模式。其有效状态可选为高电平或低电平。定义连续故障数以激活OS输出的故障队列以及设置点极限均为可编程。温度寄存器始终存储11位二进制补码数据，温度分辨率为0.125 °C。对于精确测量热漂移或热逃逸的应用，这一较高的温度分辨率尤其有用。当访问LM75B时，不会中断进行中的转换(即，I2C总线部分完全独立于Σ-Δ转换器部分)且连续访问LM75B无需等待，IIC访问不会妨碍器件更新转换结果到温度寄存器。温度寄存器更新后，可立即使用新的转换结果。LM75B上电时处于正常工作模式，即OS处于比较器模式、温度阈值为80 Cel且滞后为75 Cel，因此可用作带有那些预定义温度设置点的独立恒温器。LM75B被用于系统热管理、个人计算机、电子设备和工业控制器等。

LibDriver LM75B是LibDriver推出的LM75B的全功能驱动，该驱动提供温度读取和中断检测等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example interrupt](#example-interrupt)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver LM75B的源文件。

/interface目录包含了LibDriver LM75B与平台无关的IIC总线模板。

/test目录包含了LibDriver LM75B驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver LM75B编程范例。

/doc目录包含了LibDriver LM75B离线文档。

/datasheet目录包含了LM75B数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的IIC总线模板，完成指定平台的IIC总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

#### example basic

```C
#include "driver_lm75b_basic.h"

uint8_t res;
uint8_t i;
float t;

res = lm75b_basic_init(LM75B_ADDRESS_A000);
if (res != 0)
{
    return 1;
}

...

for (i = 0; i < 3; i++)
{
    lm75b_interface_delay_ms(1000);
    res = lm75b_basic_read((float *)&t);
    if (res != 0)
    {
        (void)lm75b_basic_deinit();

        return 1;
    }
    lm75b_interface_debug_print("lm75b: temperature is %0.3fC.\n", t);

    ...
    
}

...

(void)lm75b_basic_deinit();

return 0;
```

#### example interrupt

```C
#include "driver_lm75b_interrupt.h"

uint8_t res;
uint8_t i;
float t;
uint8_t g_flag;

res = gpio_interrupt_init();
if (res != 0)
{
    return 1;
}
res = lm75b_interrupt_init(LM75B_ADDRESS_A000, LM75B_OS_OPERATION_INTERRUPT, 22.5, 32.1);
if (res != 0)
{
    (void)gpio_interrupt_deinit();

    return 1;
}

...
    
for (i = 0; i < 3; i++)
{
    lm75b_interface_delay_ms(1000);
    res = lm75b_interrupt_read((float *)&t);
    if (res != 0)
    {
        (void)gpio_interrupt_deinit();
        (void)lm75b_interrupt_deinit();

        return 1;
    }
    lm75b_interface_debug_print("lm75b: read is %0.3fC.\n", t);
    
    ...
    
    if (g_flag != 0)
    {
        lm75b_interface_debug_print("lm75b: find interrupt.\n");

        break;
    }
    
    ...
    
}

...

(void)gpio_interrupt_deinit();
(void)lm75b_interrupt_deinit();

return 0;
```

### 文档

在线文档: [https://www.libdriver.com/docs/lm75b/index.html](https://www.libdriver.com/docs/lm75b/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。