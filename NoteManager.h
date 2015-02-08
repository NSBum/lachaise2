#ifndef _CHAIR_AFFAIR_NOTE_MANAGER
#define _CHAIR_AFFAIR_NOTE_MANAGER

#include <FastLED.h>
#define NUM_NOTES 7

/**
 *	A note type
 *
 *	Represents a visual "note" played upon the "keyboard" of the chair.
 *
 */
typedef struct note_t {
	uint16_t start;		/**< linear start location */
	uint16_t end;		/**< linear end location */
	uint8_t hue;		/**< hue of the block */
	bool playing;		/**< true if playing, otherwise false */
} note_t;

/**	
 *	Manages notes on the "keyboard"
 */
class NoteManager {
public:
	/** Constructor */
	NoteManager();

	/** Plays a note at the touch index
	 *
	 *	@param touchIndex The index of the touch sensor
	 *	@note The touchIndex is mapped in reverse order to the LED segments
	 */
	static void play(uint8_t touchIndex);

	/**	Releases a note
	 *
	 *	@param touchIndex The index of the touch sensor being released
	 */
	static void release(uint8_t touchIndex);

	/**	Update the LED strands
	 *
	 *	@param leds The array of LEDs to update
	 */
	static void update(CRGB leds[]);

	/**	Initialization of the notes
	 *
	 *	Must be called to initialize in setup()
	 */
	static void begin();

private:
	static note_t _notes[NUM_NOTES];
	static uint8_t noteIndexForTouch(uint8_t touchIndex);
};

/** Singleton instance of the class */
extern NoteManager Conductor;

#endif
