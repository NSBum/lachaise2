#ifndef __CONFIG_CHAIR_H
#define __CONFIG_CHAIR_H

#define CHAIR_DEBUG

#define NUM_LEDS 			120
#define DATA_PIN 			11			//	on the Teensy 3.1, use the hardware DOUT pin (11)
#define CHIPSET				WS2812B		//	using the Pololu strips, select the driver chip that it uses.
#define BRIGHTNESS  		200			//	global brightness
#define COLOR_ORDER 		GRB			//	color order in the data
#define FRAMES_PER_SECOND 	60			//	display frames

//	-----------	I2C Addresses -----------
#define I2C_ADDRESS_CAP_SENSE	0x5A

//	----------- EEPROM Addresses -----------
//	if 0xEE is written into EEPROM_ADDR_WAS_INIT, we know that EEPROM was initialized
#define EEPROM_ADDR_WAS_INIT	0x00
//	12-bit field of sensors for which custom tch thresholds were set
#define EEPROM_ADDR_TCH_THRSH	0x01
//	12-bit field of sensors for which custom release threshold were set
#define EEPROM_ADDR_REL_THRSH	0x03
//	base address for custom touch thresholds. individual sensor address are:
//	given by EEPROM_ADDR_TCH_BASE + 2 * i where i is the sensor number on the
//	MRP121
#define EEPROM_ADDR_TCH_BASE	0x05
//	base address for custom release thresholds. Individual sensor addresses are
//	given by EEPROM_ADDR_REL_BASE + 2 * i where i is the sensor number on the
//	MRP121
#define EEPROM_ADDR_REL_BASE	0x1D

#define EEPROM_INIT_FLAG		0xEE

//	----------- CAP SENSE -----------
#define CAP_SENSE_NUM_ACTIVE	7
#define MPR_121_RED				1
#define MPR_121_GRN				2
#define MPR_121_BLU				3
#define MPR_121_RGT				4
#define MPR_121_MID				6
#define MPR_121_LFT				7
#define MPR_121_LCK				8

//	----------- TIMNG AND DELAYS ----------- 
#define ACTIVE_MODE_TIMEOUT 	15000		//	15000 ms = 15 seconds
#define DEMO_SW_DEBOUNCE		50			//	50 ms debounce
#define COLOR_SENSE_INC_RATE	2 		//  how many cycles between increments

//	----------- PIN ASSIGNMENTS -----------
#define DEMO_SW_PIN			2
#define DEMO_MODE_LED_PIN	3
#define DX_1_LED_PIN		4
#define DX_2_LED_PIN		5
#define DX_3_LED_PIN		6

//	----------- DEFAULT DX LED CYCLES ----------- 
#define DEFAULT_DX_LED_ON	150000UL
#define DEFAULT_DX_LED_OFF	100000UL

#endif 