
#include <FastLED.h>
#include "DemoSwitchManager.h"
#include "config.h"
#include <stdlib.h>
#include <bitset>
#include <Wire.h>
#include <EEPROM.h>

#include <Clavier.h>

#include "HeartBeatLED.h"
#include "ChairAffair_LightBar.h"
#include "OpStateManager.h"

#include "ColorCoordinator.h"
//#include "SerialDebugger.h"
#include "DxLEDTimers.h"
#include "NoteManager.h"	//	manages/coordinates the notes
#include "PedalManager.h"
#include "KeySignatureManager.h"
#include "ChordManager.h"
#include "DemoModeManager.h"

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

//	
Heartbeat heartbeat(LED_BUILTIN,250,2000);
DemoSwitchManager DemoButton(DEMO_SW_PIN);
DemoModeManager DemoMode(DEMO_MODE_LED_PIN);
uint16_t loop_count = 0;
demo_sw_t lastDemoSwitchState = DemoSwitchUnchanged;

//	ms timestamp at the last touch
uint32_t lastTouchTime;
CRGB leds[NUM_LEDS];

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

	Conductor.begin();
	PedalBoard.begin();
	Transposer.begin();
	Chord.begin();

	lastTouchTime = 0;
}

void loop() {
	//	see if demo switch was thrown
	demo_sw_t demoSwitchState = DemoButton.state();
	if( lastDemoSwitchState != demoSwitchState ) {
		switch( demoSwitchState ) {
			case DemoSwitchTurnedOn: {
				DEBUG_PRINTLN("DEMO SW ON");
				DemoMode.start();
				break;
			}
			case DemoSwitchTurnedOff: {
				DEBUG_PRINTLN("DEMO SW OFF");
				DemoMode.stop();
				break;
			}
			default: {
				break;
			}
		}
		lastDemoSwitchState = demoSwitchState;
	}
	

	uint16_t n = Klavier.newTouches();
	if( n != 0 ) {
		//Serial.print("New touches = "); Serial.println(n,HEX);
		std::bitset<10> b_n (n);
		for(uint16_t i = 0; i <= MAX_TOUCH_IDX; i++) {
			if( b_n.test(i) ) {
				//	something was touched, record the time
				lastTouchTime = millis();
				//	do we need to override the demo mode?
				if( DemoMode.state() ) {
					DemoMode.override();
				}
				//	route the message to either the Conductor
				//	or the PedalBoard
				if( i < NUM_NOTES ) 
					Conductor.play(i);
				else if( i == 7 ) {
					Chord.play();
				}
				else {
					PedalBoard.depress(i);
				}
			}
		}
	}
	uint16_t r = Klavier.newReleases();
	if( r != 0 ) {
		//Serial.print("New releases = "); Serial.println(r,HEX);
		std::bitset<10> b_r (r);
		for(uint16_t i = 0; i <= MAX_TOUCH_IDX; i++) {
			if( b_r.test(i) ) {
				if( i < NUM_NOTES )
					Conductor.release(i);
				else if( i == 7 ) {
					Chord.release();
				}
				else {
					PedalBoard.release(i);
				}
			}
		}
	}

	//	clear the buffer
	memset8( leds, 0, NUM_LEDS * sizeof(CRGB));
	//	update the chord manger before showing leds
	Chord.update(leds);
	//	update the note manager *before* showing leds
	Conductor.update(leds);

	noInterrupts();
    FastLED.show();
    interrupts();
    FastLED.delay(40);

	heartbeat.update();
	Klavier.update();		//	update touch manager
	PedalFunction pedal = PedalBoard.update();
	if( pedal == PedalChangePalette ) {
		Transposer.toggle();
	}
	else if( pedal == PedalToggleEcho ) {
		Conductor.toggleEcho();
	}
	else if( pedal == PedalToggleFade) {
		Conductor.toggleSlowMode();
	}
	if( Transposer.update() ) {
		CRGB palette[7];
		Serial.println("Transposer updated");
		Transposer.palette(palette);
		for(uint8_t i = 0; i < 7; i++ ) {
			//Serial.print(palette[i].hue); Serial.print(" ");
			Conductor.setColor(i, palette[i]);
		}
		DEBUG_PRINTLN("");
	}
	DemoButton.update();
	uint16_t noteIdx = DemoMode.update();
	if( noteIdx != DEMO_MODE_NO_NOTE ) {
		//	we need to play a real note
		Conductor.play(noteIdx);
	}
	else {
		//	release every note if demo manager has nothing for us
		// 	** unless ** we are in demo override
		if( lastTouchTime == 0 ) {
			for(uint8_t i = 0; i < NUM_NOTES; i++ ) {
				Conductor.release(i);
			}
		}
	}
	//	are we in Demo override?
	if( lastTouchTime != 0 ) {
		if( millis() - lastTouchTime > 15000 ) {
			if( DemoMode.overrideState() ) {
				DemoMode.start();
			}
			lastTouchTime = 0;
		}
	}
	loop_count++;
}