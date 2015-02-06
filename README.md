## About lachaise2

This is the firmware for the HGA entry in local Boys and Girls Club of Rochester, MN Chair Affair. A touch responsive visual musical instrument.

This firmware runs on a MK20DX256VLH7 Cortex-M4 ARM processor on a Teensy 3.1 board. The primary interaces to the outside world are tactile and visual. The MCU interaces to an MPR121 multi-channel capacitive touch sensor, reading capacitance values from 10 metal strips that form a part of the chair. Inside the chair are 120 RGB LEDs that light in patterns dictated by the user's touch.

![](https://raw.githubusercontent.com/NSBum/lachaise2/master/chairboard.png)

### Board diagram ###

| Components 	| Description                                 	|
|------------	|---------------------------------------------	|
| U1         	| Microcontroller, ARM Cortex M4 (Teensy 3.1) 	|
| U2         	| MPR121 Capacitive touch sensor board        	|
| J1         	| Touch sensor header                         	|
| J2         	| RGD LED strip                               	|
| J3         	| DEMO MODE LED                               	|
| J4         	| DEMO MODE SW                                	|
| J5         	| PWR IN                                      	|
| J6         	| PWR LED                                     	|