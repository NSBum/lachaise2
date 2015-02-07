#ifndef _CHAIR_AFFAIR_NOTE_MANAGER
#define _CHAIR_AFFAIR_NOTE_MANAGER

#include <FastLED.h>
#include "Note.h"

class NoteManager {
public:
	NoteManager();
	void play(uint8_t touchIndex);
	void release(uint8_t touchIndex);
	void update(CRGB leds[]);

private:
	Note _notes[NUM_NOTES];
};

#endif
