#ifndef _CHAIR_AFFAIR_DEMO_MODE_MANAGER
#define _CHAIR_AFFAIR_DEMO_MODE_MANAGER

#include <FastLED.h>
#include <Arduino.h>
#include <inttypes.h>
#include "config.h"

#define DEMO_MODE_NO_NOTE 99

typedef enum {
	DemoModeRainbow,
	DemoModeCloud,
	DemoModeTwinkleTheme,
	DemoModeTwinkleA,
	DemoModeTwinkleB,
	DemoModeTwinkleC,
	DemoModeTwinkleD,
	DemoModeTwinkleE
} demo_mode_t;

typedef struct piano_roll_note_t {
	uint8_t note;
	uint32_t dur;		//	milliseconds
} piano_roll_note_t;

class DemoModeManager {
public:
	DemoModeManager(int ledPin);
	uint8_t update();
	void start();
	void stop();
	bool state();
	void override();
	bool overrideState();
private:
	static bool _override;
	static uint16_t _noteIndex;
	static bool _noteState;
	static uint32_t _noteTimer;
	static bool _playingSong;
	static int _led_pin;
	static bool _state;
	static demo_mode_t _variation;
	static CRGBPalette16 currentPalette;
	static TBlendType currentBlending;
	static void changeDemoModePeriodically();
};

#endif