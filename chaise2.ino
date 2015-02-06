
#include <FastLED.h>
#include "config.h"
#include <stdlib.h>
#include <Wire.h>
#include <EEPROM.h>

#include "HeartBeatLED.h"
#include "ChairAffair_LightBar.h"
#include "ChairAffair_TouchManager.h"
#include "ChairAffair_OpStateManager.h"
#include "ChairAffair_DemoSwitchManager.h"
#include "TouchManager.h"
#include "ColorCoordinator.h"
#include "SerialDebugger.h"
#include "DxLEDTimers.h"

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

Heartbeat heartbeat(LED_BUILTIN,250,2000);
// ChairAffair_LightBar DemoBar(0,10, NUM_LEDS >> 2,10);
// ChairAffair_OpStateManager OpStateManager = ChairAffair_OpStateManager();
// ChairAffair_DemoSwitchManager DemoSwitchManager = ChairAffair_DemoSwitchManager(DEMO_SW_PIN);
// ChairAffair_ColorCoordinator ColorCoordinator = ChairAffair_ColorCoordinator();
TouchManager TouchManager = TouchManager();
SerialDebugger SerialDebugger = SerialDebugger();
uint16_t loop_count = 0;

CRGB leds[NUM_LEDS];

#ifdef CHAIR_DEBUG
ChairAffair_SerialDebugger SerialDebugger = ChairAffair_SerialDebugger();
#endif

void setup() {
	delay(10);

	init_dx_leds();
	flash(GRN_DX,2);

	delay(1000);
	Serial.begin(115200);
	TouchManager.begin();

	#ifdef CHAIR_DEBUG 
	
	delay(2000);		//	ample time to get the serial interface started on the host.
	#endif
	digitalWrite(LED_BUILTIN,LOW);
	DEBUG_PRINTLN("Kalimba Chair Software");
	DEBUG_PRINTLN("Software version 1.0.0");
	DEBUG_PRINTLN("by Alan K. Duncan");
	DEBUG_PRINTLN("==========");
	DEBUG_PRINT("Checking I2C interface to cap touch sensor...");

	
	if( TouchManager.sensorOnline() ) {
		DEBUG_PRINTLN("OK");
		flash(GRN_DX,2);
	}
	else {
		DEBUG_PRINTLN("FAILED");
		flash(RED_DX,2);
	}
	
	//	when we're done with setup advance the op state
	// OpStateManager.setState(OpStateInactive);
}

void loop() {
	
	// switch( OpStateManager.state() ) {
	// 	case OpStatePoweringUp: {
	// 		DEBUG_PRINTLN("Op state: powering up");
	// 		break;
	// 	}
	// 	case OpStateInactive: {
	// 		//	handle updating inactive state
	// 		break;
	// 	}
	// 	case OpStateActive: {
	// 		//	handle active state
	// 		break;
	// 	}
	// 	case OpStateDemo: {
	// 		//	in the demo state, 
	// 		//	possibly shift it even faster (or slower)
	// 		int rand_shift = random(1000);
	// 		int16_t inc = DemoBar.delta_16();
	// 		if( rand_shift < 100 ) {
	// 			if( rand_shift < 10 ) {
	// 				inc = 0;
	// 			}
	// 			else {
	// 				inc = inc >> 2;
	// 			}
	// 		}
	// 		DemoBar.addPosition(inc);
	// 		if( DemoBar.position_16() >= (NUM_LEDS << 4) ) {
	// 			DemoBar.addPosition(0 - (NUM_LEDS << 4));
	// 		}
			
	// 		//	clear the pixel buffer
	// 		memset8( leds, 0, NUM_LEDS * sizeof(CRGB));
	// 		//	slowly shift the hue
	// 		DemoBar.addHue((loop_count % 4 == 0)?1:0);

	// 		//	draw background (DemoBar);
	// 		DemoBar.drawAntiAliasedBar(&leds[NUM_LEDS]);
	// 		break;

	// 		//	update the color coordinator
	// 		CRGB currentColor = CHSV(DemoBar.hue_16(),0xFF, 0xFF);
	// 		ColorCoordinator.setBaselineColor(currentColor);
	// 	}
	// }
	#ifdef CHAIR_DEBUG
	switch( SerialDebugger.currentCommand() ) {
		case NO_CMD: {
			NOP;
			break;
		}
		case FORCE_DEMO: {
			break;
		}
		case FORCE_INACTIVE: {
			break;
		}
		case CSET: {
			for(uint16_t i = 0; i < NUM_LEDS; i++) {
				leds[i] = SerialDebugger.commandColor();
			}
			break;
		}
		case FTUNE: {
			DEBUG_PRINTLN("Kalimba Chair: Fine tuning mode");
			DEBUG_PRINT("FTUNE> ");
		}
		default: {
			DEBUG_PRINTLN("Unrecognized cmd");
			break;
		}
	}
	#endif

	// noInterrupts();
 //    FastLED.show();
 //    interrupts();
 //    FastLED.delay(40);

	// DemoSwitchManager.update();	//	update the status of debounced demo switch
	// OpStateManager.update();	//	update operational state manager
	// ColorCoordinator.update();	//	update the color coordinator
	heartbeat.update();
	TouchManager.update();		//	update touch manager
	SerialDebugger.update();
}

#ifdef CHAIR_DEBUG
	void serialEvent() {
		while( Serial.available() ) {
			char in_char = (char)Serial.read(); 
			SerialDebugger.addChar(in_char);
		}
	}
#endif