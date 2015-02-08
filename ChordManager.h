#ifndef _CHAIR_AFFAIR_CHORD_MANAGER
#define _CHAIR_AFFAIR_CHORD_MANAGER

#include <FastLED.h>

class ChordManager {
public:
	ChordManager();
	static void begin();
	static void play();
	static void release();
	static void update(CRGB leds[]);
private:
	static bool _state;
	static uint8_t _startIndex;
	static uint32_t _lastChange;
	static CRGBPalette16 currentPalette;
	static TBlendType    currentBlending;
	static void fillFromPaletteColors(uint8_t colorIndex,CRGB leds[]);
};

extern ChordManager Chord;

#endif