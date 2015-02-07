#ifndef _CHAIR_AFFAIR_NOTE_MANAGER
#define _CHAIR_AFFAIR_NOTE_MANAGER

#include <FastLED.h>
#include "Note.h"

typedef struct note_t {
	uint16_t start;
	uint16_t end;
	uint8_t hue;
	bool playing;
}

class NoteManager {
public:
	NoteManager();
	static void play(uint8_t touchIndex);
	static void release(uint8_t touchIndex);
	static void update(CRGB leds[]);

private:
	static const Note *_notes;
	static uint8_t noteIndexForTouch(uint8_t touchIndex);
};

extern NoteManager Conductor;

#endif
