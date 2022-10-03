### 1. Chip

#### 1.1 Chip Info

chip name : Raspberry Pi 4B.

iic pin: SCL/SDA GPIO3/GPIO2.

gpio pin: INT GPIO17.

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

​          lm75b is a basic command which can test all lm75b driver function:

​           -i        show lm75b chip and driver information.

​           -h       show lm75b help.

​           -p       show lm75b pin connections of the current board.

​           -t (reg -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7) | read <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7) | int <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7) -m (COMPARATOR  | INTERRUPT) <lowthreshold> <highthreshold>) 

​           -t reg -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)        run lm75b register test.

​           -t read <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)         run lm75b read test. times means test times.

​           -t int <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7) -m (COMPARATOR  | INTERRUPT) <lowthreshold> <highthreshold>        run lm75b interrupt test. times means test times. lowthreshold means low interrupt threshold. highthreshold means high interrupt threshold.

​           -c (read <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7) | int <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7) -m (COMPARATOR  | INTERRUPT) <lowthreshold> <highthreshold>)

​           -c read <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)        run lm75b read function. times means read times.

​           -c int <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7) -m (COMPARATOR  | INTERRUPT) <lowthreshold> <highthreshold>        run lm75b interrupt function. times means read times. lowthreshold means low interrupt threshold. highthreshold means high interrupt threshold.

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
lm75b: INT connected to GPIO17(BCM).
```

```shell
./lm75b -t reg -a 0

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
./lm75b -t read 3 -a 0

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
lm75b: temperature is 29.000.
lm75b: temperature is 29.125.
lm75b: temperature is 29.000.
lm75b: finish read test.
```

```shell
./lm75b -t int 3 -a 0 -m INTERRUPT 25.0 28.0

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
lm75b: temperature is 28.500.
lm75b: temperature is over high threshold.
lm75b: temperature is 28.625.
lm75b: temperature is over high threshold.
lm75b: temperature is 28.625.
lm75b: temperature is over high threshold.
lm75b: finish interrupt test.
```

```shell
./lm75b -c read 3 -a 0

lm75b: 1/3.
lm75b: temperature is 28.875C.
lm75b: 2/3.
lm75b: temperature is 28.750C.
lm75b: 3/3.
lm75b: temperature is 28.750C.
```

```shell
./lm75b -c int 3 -a 0 -m INTERRUPT 30.0 50.0

lm75b: 1/3.
lm75b: read is 28.500C.
lm75b: find interrupt.
```

```shell
./lm75b -h

lm75b -i
	show lm75b chip and driver information.
lm75b -h
	show lm75b help.
lm75b -p
	show lm75b pin connections of the current board.
lm75b -t reg -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)
	run lm75b register test.
lm75b -t read <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)
	run lm75b read test.times means test times.
lm75b -t int <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7) -m (COMPARATOR | INTERRUPT) <lowthreshold> <highthreshold>
	run lm75b interrupt test.times means test times.lowthreshold means low interrupt threshold.highthreshold means high interrupt threshold.
lm75b -c read <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)
	run lm75b read function.times means read times.
lm75b -c int <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7) -m (COMPARATOR  | INTERRUPT) <lowthreshold> <highthreshold>
	run lm75b interrupt function.times means read times.lowthreshold means low interrupt threshold.highthreshold means high interrupt threshold.
```

