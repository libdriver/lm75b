[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver LM75B

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/lm75b/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

LM75B는 과열 감지 출력이 있는 온칩 밴드 갭 온도 센서와 시그마-델타 A-D 변환 기술을 사용하는 온도-디지털 변환기입니다. LM75B에는 여러 데이터 레지스터가 포함되어 있습니다. 데이터시트에 설명된 대로 장치 작동 모드, OS 작동 모드, OS 극성 및 OS 오류 대기열과 같은 장치 설정을 저장하기 위한 구성 레지스터(Conf). 디지털을 저장하기 위한 온도 레지스터(Temp) 온도 판독 및 2선 직렬 I2C 버스 인터페이스를 통해 컨트롤러에서 통신할 수 있는 프로그래밍 가능한 과열 셧다운 및 히스테리시스 한계를 저장하기 위한 설정점 레지스터(Tos 및 Thyst). 이 장치에는 온도가 프로그래밍된 한계를 초과할 때 활성화되는 오픈 드레인 출력(OS)도 포함되어 있습니다. 3개의 선택 가능한 논리 주소 핀이 있어 8개의 장치를 주소 충돌 없이 동일한 버스에 연결할 수 있습니다. LM75B는 다른 작동 조건에 대해 구성할 수 있습니다. 주변 온도를 주기적으로 모니터링하기 위해 일반 모드로 설정하거나 전력 소비를 최소화하기 위해 셧다운 모드로 설정할 수 있습니다. OS 출력은 선택 가능한 두 가지 모드(OS 비교기 모드 또는 OS 인터럽트 모드)에서 작동합니다. 활성 상태는 HIGH 또는 LOW로 선택할 수 있습니다. OS 출력을 활성화하기 위해 연속적인 오류의 수를 정의하는 오류 대기열은 설정값 제한뿐만 아니라 프로그래밍할 수 있습니다. 온도 레지스터는 항상 0.125C의 온도 분해능을 제공하는 11비트 2의 보수 데이터를 저장합니다. 이 고온 분해능은 열 드리프트 또는 폭주를 정밀하게 측정하는 애플리케이션에 특히 유용합니다. LM75B에 액세스할 때 처리 중인 변환이 중단되지 않고(즉, I2C 버스 섹션이 시그마-델타 변환기 섹션과 완전히 독립적임) LM75B에 계속 액세스하여 통신 간 변환 시간을 한 번 이상 기다리면 장치가 새로운 변환 결과로 Temp 레지스터를 업데이트하지 못하도록 합니다. 새로운 변환 결과는 Temp 레지스터가 업데이트된 직후에 사용할 수 있습니다. LM75B는 OS가 비교기 모드이고 온도 임계값이 80C이고 히스테리시스가 75C인 일반 작동 모드에서 전원이 켜집니다. 따라서 사전 정의된 온도 설정 포인트로 독립형 온도 조절기로 사용할 수 있습니다.LM75B는 시스템 열 관리, 개인용 컴퓨터, 전자 장비 및 산업용 컨트롤러에 사용됩니다.

LibDriver LM75B는 LibDriver에서 출시한 LM75B의 전체 기능 드라이버입니다. 온도 판독 및 인터럽트 감지와 같은 기능을 제공합니다. LibDriver는 MISRA를 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
    - [example interrupt](#example-interrupt)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver LM75B의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver LM75B용 플랫폼 독립적인 IIC버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver LM75B드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver LM75B프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver LM75B오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 LM75B데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

### 설치

/interface 디렉토리에서 플랫폼 독립적인IIC 버스 템플릿을 참조하여 지정된 플랫폼에 대한 IIC버스 드라이버를 완성하십시오.

/src 디렉토리, /interface 디렉토리 및 /example 디렉토리를 프로젝트에 추가하십시오.

### 사용

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

```c
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

### 문서

온라인 문서: [https://www.libdriver.com/docs/lm75b/index.html](https://www.libdriver.com/docs/lm75b/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.