[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver LM75B

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/lm75b/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der LM75B ist ein Temperatur-Digital-Wandler, der einen On-Chip-Bandlücken-Temperatursensor und eine Sigma-Delta-A/D-Wandlungstechnik mit einem Übertemperatur-Erkennungsausgang verwendet. Der LM75B enthält eine Reihe von Datenregistern: Konfigurationsregister (Conf) zum Speichern der Geräteeinstellungen wie Gerätebetriebsmodus, Betriebssystembetriebsmodus, Betriebssystempolarität und Betriebssystemfehlerwarteschlange, wie im Datenblatt beschrieben. Temperaturregister (Temp) zum Speichern der digitalen Temperaturmesswert und Sollwertregister (Tos und Thyst) zum Speichern programmierbarer Übertemperatur-Abschalt- und Hysteresegrenzen, die von einem Controller über die serielle 2-Draht-I2C-Bus-Schnittstelle kommuniziert werden können. Das Gerät enthält auch einen Open-Drain-Ausgang (OS), der aktiv wird, wenn die Temperatur die programmierten Grenzen überschreitet. Es gibt drei wählbare Pins für logische Adressen, sodass acht Geräte ohne Adresskonflikt an denselben Bus angeschlossen werden können. Der LM75B kann für unterschiedliche Betriebsbedingungen konfiguriert werden. Es kann in den Normalmodus versetzt werden, um die Umgebungstemperatur regelmäßig zu überwachen, oder in den Abschaltmodus, um den Stromverbrauch zu minimieren. Der OS-Ausgang arbeitet in einem von zwei wählbaren Modi: dem OS-Komparatormodus oder dem OS-Unterbrechungsmodus. Sein aktiver Zustand kann entweder als HIGH oder LOW ausgewählt werden. Die Fehlerwarteschlange, die die Anzahl aufeinanderfolgender Fehler definiert, um den OS-Ausgang zu aktivieren, ist ebenso programmierbar wie die Sollwertgrenzen. Das Temperaturregister speichert immer 11-Bit-Zweierkomplementdaten mit einer Temperaturauflösung von 0,125 °C. Diese hohe Temperaturauflösung ist besonders nützlich bei Anwendungen zur präzisen Messung der thermischen Drift oder des Durchgehens. Wenn auf den LM75B zugegriffen wird, wird die laufende Konvertierung nicht unterbrochen (d. h. der I2C-Bus-Abschnitt ist völlig unabhängig vom Sigma-Delta-Konverterabschnitt), und ein kontinuierlicher Zugriff auf den LM75B, ohne mindestens eine Konvertierungszeit zwischen den Kommunikationen abzuwarten, wird dies nicht verhindern verhindert, dass das Temp-Register mit einem neuen Konvertierungsergebnis aktualisiert wird. Das neue Konvertierungsergebnis ist sofort verfügbar, nachdem das Temp-Register aktualisiert wurde. Der LM75B wird im normalen Betriebsmodus mit dem Betriebssystem im Komparatormodus, Temperaturschwelle von 80 ° C und Hysterese von 75 ° C eingeschaltet, sodass er als eigenständiger Thermostat mit diesen vordefinierten Temperatursollwerten verwendet werden kann. LM75B ist verwendet in Systemwärmemanagement, Personalcomputern, elektronischen Geräten und Industriesteuerungen.

LibDriver LM75B ist der voll funktionsfähige Treiber von LM75B, der von LibDriver gestartet wurde. Er bietet Funktionen wie Temperaturmessung und Interrupt-Erkennung. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
    - [example interrupt](#example-interrupt)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver LM75B-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver LM75B IIC.

/test enthält den Testcode des LibDriver LM75B-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver LM75B-Beispielcode.

/doc enthält das LibDriver LM75B-Offlinedokument.

/Datenblatt enthält LM75B-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie /src, /interface und /example zu Ihrem Projekt hinzu.

### Nutzung

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/lm75b/index.html](https://www.libdriver.com/docs/lm75b/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.