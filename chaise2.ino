#include <FastLED.h>
#include "config.h"
#include <stdlib.h>
#include <bitset>
#include <Wire.h>
#include <EEPROM.h>

#include <Clavier.h>

#include "HeartBeatLED.h"
#include "ChairAffair_LightBar.h"
#include "OpStateManager.h"
#include "DemoSwitchManager.h"
#include "ColorCoordinator.h"
//#include "SerialDebugger.h"
#include "DxLEDTimers.h"
#include "Note.h" 			//	a "note" played on the "keys"
#include "NoteManager.h"	//	manages/coordinates the notes

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
uint16_t loop_count = 0;

CRGB leds[NUM_LEDS];
Note notes[NUM_NOTES];

void welcomePrint() {
	DEBUG_PRINTLN("Kalimba Chair Software");
	DEBUG_PRINTLN("Software version 1.0.0");
	DEBUG_PRINTLN("by Alan K. Duncan");
	DEBUG_PRINTLN("==========");
	DEBUG_PRINT("Checking I2C interface to cap touch sensor...");
}

void setup() {
	delay(10);

	init_dx_leds();
	flash(DX_1,2);

	delay(1000);
	Serial.begin(115200);
	Klavier.begin();

	#ifdef CHAIR_DEBUG 
	
	delay(2000);		//	ample time to get the serial interface started on the host.
	#endif
	digitalWrite(LED_BUILTIN,LOW);
	welcomePrint();

	if( Klavier.sensorOnline() ) {
		DEBUG_PRINTLN("OK");
		flash(DX_1,2);
	}
	else {
		DEBUG_PRINTLN("FAILED");
		flash(DX_2,2);
	}
	
	FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
	memset8( leds, 0, NUM_LEDS * sizeof(CRGB));
}

void loop() {
	uint16_t n = Klavier.newTouches();
	if( n != 0 ) {
		//Serial.print("New touches = "); Serial.println(n,HEX);
		std::bitset<10> b_n (n);
		for(uint16_t i = 0; i <= MAX_TOUCH_IDX; i++) {
			if( b_n.test(i) ) {
				//Serial.print("will play "); Serial.println(i);
				Conductor.play(i);
			}
		}
	}
	uint16_t r = Klavier.newReleases();
	if( r != 0 ) {
		//Serial.print("New releases = "); Serial.println(r,HEX);
		std::bitset<10> b_r (r);
		for(uint16_t i = 0; i <= MAX_TOUCH_IDX; i++) {
			if( b_r.test(i) ) {
				Conductor.release(i);
			}
		}
	}
		
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
	// #ifdef CHAIR_DEBUG
	// switch( SerialDebugger.currentCommand() ) {
	// 	case NO_CMD: {
	// 		NOP;
	// 		break;
	// 	}
	// 	case FORCE_DEMO: {
	// 		break;
	// 	}
	// 	case FORCE_INACTIVE: {
	// 		break;
	// 	}
	// 	case CSET: {
	// 		for(uint16_t i = 0; i < NUM_LEDS; i++) {
	// 			leds[i] = SerialDebugger.commandColor();
	// 		}
	// 		break;
	// 	}
	// 	case FTUNE: {
	// 		DEBUG_PRINTLN("Kalimba Chair: Fine tuning mode");
	// 		DEBUG_PRINT("FTUNE> ");
	// 	}
	// 	default: {
	// 		DEBUG_PRINTLN("Unrecognized cmd");
	// 		break;
	// 	}
	// }
	// #endif

	//	clear the buffer
	memset8( leds, 0, NUM_LEDS * sizeof(CRGB));
	//	update the note manager *before* showing leds
	Conductor.update(leds);

	// if( loop_count++ % 1000 == 0 ) {
	// 	for(uint16_t i = 0; i < NUM_LEDS; i++ ) {
	// 		Serial.println(leds[i].red);
	// 	}
	// }

	noInterrupts();
    FastLED.show();
    interrupts();
    FastLED.delay(40);

	// DemoSwitchManager.update();	//	update the status of debounced demo switch
	// OpStateManager.update();	//	update operational state manager
	// ColorCoordinator.update();	//	update the color coordinator
	heartbeat.update();
	Klavier.update();		//	update touch manager
	//delay(250);
	// SerialDebugger.update();
}

// #ifdef CHAIR_DEBUG
// 	void serialEvent() {
// 		while( Serial.available() ) {
// 			char in_char = (char)Serial.read(); 
// 			SerialDebugger.addChar(in_char);
// 		}
// 	}
// #endif