#ifndef _CHAIR_AFFAIR_NOTE_MANAGER
#define _CHAIR_AFFAIR_NOTE_MANAGER

#include <FastLED.h>
#include <vector>
#define NUM_NOTES 7

typedef enum {
	FadeIn,
	FadeOut,
	FadeNone
} fade_dir_t;

/**
 *	A note type
 *
 *	Represents a visual "note" played upon the "keyboard" of the chair.
 *
 */
typedef struct note_t {
	uint16_t start;		/**< linear start location */
	uint16_t end;		/**< linear end location */
	bool playing;		/**< true if playing, otherwise false */
	CRGB color;
	uint8_t fade;		/**< fade if slow mode */
	fade_dir_t fadeDirection;
	uint32_t lastFadeTime;
} note_t;

typedef std::vector<note_t> note_vec_t;

/**
 *	Echo
 *
 *	After a note is touched, depending on the global echo setting,
 *	it may generate an "echo". These echoes propagate down the 
 *	LED string with diminishing brightness and length until they
 *	completely fade out, or reach the end of the string.
 *
 */
typedef struct echo_t {
	uint8_t noteIndex;			/**< index of the keyboard note */
	uint16_t spatialOffset;		/**< current linear delta */
	bool currentState;			/**< true is ON, false is OFF */
	uint32_t lastChangeTime;	/**< millisecond stamp at last state change */ 
	uint8_t currentBrightness;	/**< brightness factor */
	uint8_t echoCount;			/**< number of echoes displayed */
} echo_t;

typedef std::vector<echo_t> echo_vec_t;

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

	static void setColor(uint8_t noteIndex, CRGB color);

	static void toggleSlowMode();

	static void toggleEcho();

	/**	Initialization of the notes
	 *
	 *	Must be called to initialize in setup()
	 */
	static void begin();

private:
	static note_vec_t _notes;
	static bool _slowMode;
	static bool _echo;
	static echo_vec_t _echoes;
	static uint8_t noteIndexForTouch(uint8_t touchIndex);
};

/** Singleton instance of the class */
extern NoteManager Conductor;

#endif
