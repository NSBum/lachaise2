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

### Functional description ###

The chair can be in one of four operational states: `OpStatePoweringUp`, `OpStateInactive`, `OpStateActive`, and `OpStateDemo`.  A fifth state, `OpStateTuneSensors` is useful during touch debugging.

1. `OpStatePoweringUp`

    When power is applied to the device, it starts up in `OpStatePoweringUp`. This allows time for the sensors to autocalibrate.

2. `OpStateInactive`

    In this state, there is no visible display of lights. If the user touches any sensor while the unit is in this state, the state advances to the `OpStateActive` state.

3. `OpStateActive`

    When the unit is in this mode, the pattern of the LEDs shift according to the way the user touches the sensor bars. While in the state, if the user does not touch any sensor for 30 seconds, the device will revert to a nother mode depending on the DEMO SW position. If the DEMO SW is ON, the device will revert to `OpStateDemo`. If it is OFF, the device will revert to `OpStateInactive`. 

4. `OpStateDemo`

	In this state, the color and pattern of the LEDs shifts to provide a demonstration program. This mode can be selected by a pushbutton switch on the back of the chair. An LED on the switch provides visual feedback to the user.

5. `OpStateTuneSensors`

	This is useful for fine-tuning the touch and release thresholds on the sensors.


