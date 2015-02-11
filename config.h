#ifndef __CONFIG_CHAIR_H
#define __CONFIG_CHAIR_H

#define CHAIR_DEBUG

#define NOP __asm__ __volatile__ ("nop\n\t")

#ifdef CHAIR_DEBUG
#define DEBUG_PRINT(x) 			Serial.print(x)
#define DEBUG_PRINTLN(x)		Serial.println(x)
#define DEBUG_PRINT_F(x,f)		Serial.print(x,f)
#define DEBUG_PRINTLN_F(x,f)	Serial.println(x,f)
#else
#define DEBUG_PRINT(x) 			NOP
#define DEBUG_PRINTLN(x)		NOP
#define DEBUG_PRINT_F(x,f)		NOP
#define DEBUG_PRINTLN_F(x,f)	NOP
#endif

#define NUM_LEDS 			120
#define DATA_PIN 			11			//	on the Teensy 3.1, use the hardware DOUT pin (11)
#define CHIPSET				WS2812B		//	using the Pololu strips, select the driver chip that it uses.
#define BRIGHTNESS  		0xFF		//	global brightness
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
#define CAP_SENSE_NUM_ACTIVE	10
#define MPR_121_RGN_1			0 		//	region 1
#define MPR_121_RGN_2			1 		//	region 2
#define MPR_121_RGN_3			2 		//  region 3
#define MPR_121_RGN_4			3 		//	region 4
#define MPR_121_RGN_5			4 		//	region 5
#define MPR_121_RGN_6			5 		//	region 6
#define MPR_121_RGN_7			6 		//	region 7
#define MPR_121_RYTH			7 		//	rhythm
#define MPR_121_COLOR 			8 		//	color
#define MRP_121_OTHER			9		//	TBD

#define MAX_TOUCH_IDX			MRP_121_OTHER

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