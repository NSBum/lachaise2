#ifndef _CHAIR_AFFAIR_CHORD_MANAGER
#define _CHAIR_AFFAIR_CHORD_MANAGER

#include <FastLED.h>

/**	Manager for "chords"
 *
 *	This class manages background chords, a sort of "polyphonic" background.
 */
class ChordManager {
public:
	/**	Constructor */
	ChordManager();

	/**	Begins interaction with the chord manager
	 *
	 *	Sets the baseline palette and blending mode
	 */
	static void begin();

	/**	Plays the chord */
	static void play();

	/**	Stops playing the chord */
	static void release();

	/**	Updates the leds
	 *
	 *	This function must be called with each pass of the loop
	 *	to update the leds for the background effect.
	 */
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