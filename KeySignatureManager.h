#ifndef _CHAIR_AFFAIR_KEY_SIGNATURE_MANAGER
#define _CHAIR_AFFAIR_KEY_SIGNATURE_MANAGER

#include <FastLED.h>

typedef struct key_signature_t {
	CRGB note_do;
	CRGB note_re;
	CRGB note_mi;
	CRGB note_fa;
	CRGB note_sol;
	CRGB note_la;
	CRGB note_ti;
} key_signature_t;

/**	Key signature manager
 *
 *	The key signature is represented by the palette of colors that are
 *	assigned to the notes on the main sensor bands. One of the pedal bands
 *	can be assigned to modulate the key signature.
 */
class KeySignatureManager {
public:
	/**	Constructor */
	KeySignatureManager();

	/** Begins interaction with the manager
	 *
	 *	@note The base implementation does nothing.
	 */
	static void begin();

	/**	Toggles the key signature
	 *
	 *	This function should be called to change the key signature.
	 */
	static void toggle();

	/**	Updates the status of the manager
	 *
	 *	This member function must be called with each pass of the run loop.
	 */
	static bool update();

	/**	Current palette
	 *
	 *	@return The current palette as a pointer to CRGB entities.
	 */
	static void palette(CRGB *p);
private:
	static uint8_t _keySignatureIndex;
	static bool _paletteWasUpdated;
};

extern KeySignatureManager Transposer;

#endif