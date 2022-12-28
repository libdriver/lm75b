### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

GPIO Pin: INT GPIO17.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(lm75b REQUIRED)
```

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
./lm75b -i

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
./lm75b -p

lm75b: SCL connected to GPIO3(BCM).
lm75b: SDA connected to GPIO2(BCM).
lm75b: OS connected to GPIO17(BCM).
```

```shell
./lm75b -t reg --addr=0

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
lm75b: set hysteresis 0x6B80.
lm75b: check hysteresis ok.
lm75b: lm75b_set_over_temperature_threshold/lm75b_get_over_temperature_threshold test.
lm75b: set threshold 0x3200.
lm75b: check threshold ok.
lm75b: lm75b_hysteresis_convert_to_register/lm75b_hysteresis_convert_to_data test.
lm75b: hysteresis data is 25.90.
lm75b: register is 0x1980.
lm75b: hysteresis check data is 25.50.
lm75b: lm75b_over_temperature_threshold_convert_to_register/lm75b_over_temperature_threshold_convert_to_data test.
lm75b: register is 0xC080.
lm75b: over temperature threshold data is -63.83.
lm75b: over temperature threshold check data is -63.50.
lm75b: finish register test.
```

```shell
./lm75b -t read --addr=0 --times=3

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
lm75b: temperature is 29.750C.
lm75b: temperature is 29.875C.
lm75b: temperature is 29.750C.
lm75b: finish read test.
```

```shell
./lm75b -t int --addr=0 --times=3 --mode=INT --low-threshold=25.0 --high-threshold=28.0

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
lm75b: temperature is 29.375C.
lm75b: temperature is over high threshold.
lm75b: temperature is 29.500C.
lm75b: temperature is over high threshold.
lm75b: temperature is 29.500C.
lm75b: temperature is over high threshold.
lm75b: finish interrupt test.
```

```shell
./lm75b -e read --addr=0 --times=3

lm75b: 1/3.
lm75b: temperature is 29.250C.
lm75b: 2/3.
lm75b: temperature is 29.250C.
lm75b: 3/3.
lm75b: temperature is 29.375C.
```

```shell
./lm75b -e int --addr=0 --times=3 --mode=INT --low-threshold=30.0 --high-threshold=50.0

lm75b: 1/3.
lm75b: read is 29.250C.
lm75b: find interrupt.
```

```shell
./lm75b -h

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

