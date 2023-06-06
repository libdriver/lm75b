### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

GPIO Pin: INT PB0.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. LM75B

#### 3.1 Command Instruction

1. Show lm75b chip and driver information.

   ```shell
   lm75b (-i | --information)
   ```

2. Show lm75b help.

   ```shell
   lm75b (-h | --help)
   ```

3. Show lm75b pin connections of the current board.

   ```shell
   lm75b (-p | --port)
   ```

4. Run lm75b register test.

   ```shell
   lm75b (-t reg | --test=reg) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
   ```

5. Run lm75b read test, num means test times.

   ```shell
   lm75b (-t read | --test=read) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>]
   ```

6. Run lm75b interrupt test, num means test times, low means low interrupt threshold, high means high interrupt threshold.

   ```shell
   lm75b (-t int | --test=int) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>] [--mode=<CMP | INT>] [--low-threshold=<low>] [--high-threshold=<high>]
   ```

7. Run lm75b read function, num means read times.

   ```shell
   lm75b (-e read | --example=read) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>]
   ```

8. Run lm75b interrupt function, num means read times, low means low interrupt threshold, high means high interrupt threshold.

   ```shell
   lm75b (-e int | --example=int) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>] [--mode=<CMP | INT>] [--low-threshold=<low>] [--high-threshold=<high>]
   ```

#### 3.2 Command Example

```shell
lm75b -i

lm75b: chip is NXP LM75B.
lm75b: manufacturer is NXP.
lm75b: interface is IIC.
lm75b: driver version is 2.0.
lm75b: min supply voltage is 2.8V.
lm75b: max supply voltage is 5.5V.
lm75b: max current is 10.00mA.
lm75b: max temperature is 125.0C.
lm75b: min temperature is -55.0C.
```

```shell
lm75b -p

lm75b: SCL connected to GPIOB PIN8.
lm75b: SDA connected to GPIOB PIN9.
lm75b: OS connected to GPIOB PIN0.
```

```shell
lm75b -t reg --addr=0

lm75b: chip is NXP LM75B.
lm75b: manufacturer is NXP.
lm75b: interface is IIC.
lm75b: driver version is 2.0.
lm75b: min supply voltage is 2.8V.
lm75b: max supply voltage is 5.5V.
lm75b: max current is 10.00mA.
lm75b: max temperature is 125.0C.
lm75b: min temperature is -55.0C.
lm75b: start register test.
lm75b: lm75b_set_addr_pin/lm75b_get_addr_pin test.
lm75b: set addr pin a000.
lm75b: check addr pin ok.
lm75b: set addr pin a001.
lm75b: check addr pin ok.
lm75b: set addr pin a010.
lm75b: check addr pin ok.
lm75b: set addr pin a011.
lm75b: check addr pin ok.
lm75b: set addr pin a100.
lm75b: check addr pin ok.
lm75b: set addr pin a101.
lm75b: check addr pin ok.
lm75b: set addr pin a110.
lm75b: check addr pin ok.
lm75b: set addr pin a111.
lm75b: check addr pin ok.
lm75b: lm75b_set_fault_queue/lm75b_get_fault_queue test.
lm75b: set fault queue 1.
lm75b: check fault queue ok.
lm75b: set fault queue 2.
lm75b: check fault queue ok.
lm75b: set fault queue 3.
lm75b: check fault queue ok.
lm75b: set fault queue 6.
lm75b: check fault queue ok.
lm75b: lm75b_set_os_polarity/lm75b_get_os_polarity test.
lm75b: set os ploarity low.
lm75b: check os polarity ok.
lm75b: set os ploarity high.
lm75b: check os polarity ok.
lm75b: lm75b_set_interrupt_mode/lm75b_get_interrupt_mode test.
lm75b: set comparator mode.
lm75b: check interrupt mode ok.
lm75b: set interrupt mode.
lm75b: check interrupt mode ok.
lm75b: lm75b_set_mode/lm75b_get_mode test.
lm75b: set normal mode.
lm75b: check mode ok.
lm75b: set shut down mode.
lm75b: check mode ok.
lm75b: lm75b_set_hysteresis/lm75b_get_hysteresis test.
lm75b: set hysteresis 0x5600.
lm75b: check hysteresis ok.
lm75b: lm75b_set_over_temperature_threshold/lm75b_get_over_temperature_threshold test.
lm75b: set threshold 0x7180.
lm75b: check threshold ok.
lm75b: lm75b_hysteresis_convert_to_register/lm75b_hysteresis_convert_to_data test.
lm75b: hysteresis data is 13.63.
lm75b: register is 0x0D80.
lm75b: hysteresis check data is 13.50.
lm75b: lm75b_over_temperature_threshold_convert_to_register/lm75b_over_temperature_threshold_convert_to_data test.
lm75b: register is 0xD980.
lm75b: over temperature threshold data is -38.67.
lm75b: over temperature threshold check data is -38.50.
lm75b: finish register test.
```

```shell
lm75b -t read --addr=0 --times=3

lm75b: chip is NXP LM75B.
lm75b: manufacturer is NXP.
lm75b: interface is IIC.
lm75b: driver version is 2.0.
lm75b: min supply voltage is 2.8V.
lm75b: max supply voltage is 5.5V.
lm75b: max current is 10.00mA.
lm75b: max temperature is 125.0C.
lm75b: min temperature is -55.0C.
lm75b: start read test.
lm75b: temperature is 29.375C.
lm75b: temperature is 29.375C.
lm75b: temperature is 29.250C.
lm75b: finish read test.
```

```shell
lm75b -t int --addr=0 --times=3 --mode=INT --low-threshold=25.0 --high-threshold=28.0

lm75b: chip is NXP LM75B.
lm75b: manufacturer is NXP.
lm75b: interface is IIC.
lm75b: driver version is 2.0.
lm75b: min supply voltage is 2.8V.
lm75b: max supply voltage is 5.5V.
lm75b: max current is 10.00mA.
lm75b: max temperature is 125.0C.
lm75b: min temperature is -55.0C.
lm75b: start interrupt test.
lm75b: temperature is 29.125C.
lm75b: temperature is over high threshold.
lm75b: temperature is 29.125C.
lm75b: temperature is over high threshold.
lm75b: temperature is 29.125C.
lm75b: temperature is over high threshold.
lm75b: finish interrupt test.
```

```shell
lm75b -e read --addr=0 --times=3

lm75b: 1/3.
lm75b: temperature is 28.750C.
lm75b: 2/3.
lm75b: temperature is 28.875C.
lm75b: 3/3.
lm75b: temperature is 28.875C.
```

```shell
lm75b -e int --addr=0 --times=3 --mode=INT --low-threshold=30.0 --high-threshold=50.0

lm75b: 1/3.
lm75b: read is 28.625C.
lm75b: find interrupt.
```

```shell
lm75b -h

Usage:
  lm75b (-i | --information)
  lm75b (-h | --help)
  lm75b (-p | --port)
  lm75b (-t reg | --test=reg) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
  lm75b (-t read | --test=read) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>]
  lm75b (-t int | --test=int) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>]
        [--mode=<CMP | INT>] [--low-threshold=<low>] [--high-threshold=<high>]
  lm75b (-e read | --example=read) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>]
  lm75b (-e int | --example=int) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>]
        [--mode=<CMP | INT>] [--low-threshold=<low>] [--high-threshold=<high>]

Options:
      --addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>
                                 Set the addr pin.([default: 0])
  -e <read | int>, --example=<read | int>
                                 Run the driver example.
  -h, --help                     Show the help.
      --high-threshold=<high>    Set the interrupt high threshold.([default: 28.0f])
  -i, --information              Show the chip information.
      --low-threshold=<low>      Set the interrupt low threshold.([default: 25.0f])
      --mode=<CMP | INT>         Set the interrupt mode.([default: INT])
  -p, --port                     Display the pin connections of the current board.
  -t <reg | read | init>, --test=<reg | read | int>
                                 Run the driver test.
      --times=<num>              Set the running times.([default: 3])
```

