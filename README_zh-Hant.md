[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver LM75B

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/lm75b/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

LM75B是一款溫度-數字轉換器，使用片上帶隙溫度傳感器和Σ-Δ A/D轉換技術並帶有過熱檢測輸出。 LM75B包含一系列數據寄存器：儲存諸如器件工作模式、OS工作模式、OS極性和OS故障隊列等器件設置的配置寄存器(Conf)；儲存數字溫度讀數的溫度寄存器(Temp)以及儲存可編程過熱關斷和滯後極限的設置點寄存器(Tos和Thyst)，可通過2線串行I²C總線接口與控制器進行通信。該器件還提供開漏輸出(OS)，可在溫度超過編程限值時激活。共有三個可選邏輯地址引腳，因此可在同一總線上連接八個器件而不會發生地址衝突。 LM75B可為不同的工作條件進行配置。可將其設為正常模式以定期監視環境溫度，或設為關斷模式以使功耗最小化。 OS輸出可在兩種可選模式中的任意一種下工作：OS比較器模式或OS中斷模式。其有效狀態可選為高電平或低電平。定義連續故障數以激活OS輸出的故障隊列以及設置點極限均為可編程。溫度寄存器始終存儲11位二進制補碼數據，溫度分辨率為0.125 °C。對於精確測量熱漂移或熱逃逸的應用，這一較高的溫度分辨率尤其有用。當訪問LM75B時，不會中斷進行中的轉換(即，I2C總線部分完全獨立於Σ-Δ轉換器部分)且連續訪問LM75B而無需等待通信之間哪怕一個轉換時間，但這不會妨礙器件使用新的轉換結果更新溫度寄存器。溫度寄存器更新後，可立即使用新的轉換結果。 LM75B上電時處於正常工作模式，即OS處於比較器模式、溫度閾值為80 Cel且滯後為75 Cel，因此可用作帶有那些預定義溫度設置點的獨立恆溫器。 LM75B被用於系統熱管理、個人計算機、電子設備和工業控制器等。

LibDriver LM75B是LibDriver推出的LM75B的全功能驅動，該驅動提供溫度讀取和中斷檢測等功能並且它符合MISRA標準。

### 目录

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example interrupt](#example-interrupt)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver LM75B的源文件。

/interface目錄包含了LibDriver LM75B與平台無關的IIC總線模板。

/test目錄包含了LibDriver LM75B驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver LM75B編程範例。

/doc目錄包含了LibDriver LM75B離線文檔。

/datasheet目錄包含了LM75B數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

### 安裝

參考/interface目錄下與平台無關的IIC總線模板，完成指定平台的IIC總線驅動。

將/src目錄，/interface目錄和/example目錄加入工程。

### 使用

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

### 文檔

在線文檔: https://www.libdriver.com/docs/lm75b/index.html

離線文檔: /doc/html/index.html

### 貢獻

請聯繫lishifenging@outlook.com

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com
