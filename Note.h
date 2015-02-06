#ifndef _CHAIR_AFFAIR_NOTE
#define _CHAIR_AFFAIR_NOTE

#include <inttypes.h>
#include <config.h>
#include <FastLED.h>

typedef struct note_range_t {
	uint16_t start;
	uint16_t end;
} note_range_t;

class Note {
public:
	Note(CRGB aColor, uint16_t order, uint16_t ledCount);

	void setColor(CRGB aColor);

private:
	CRGB _color;
	note_range_t _range;
};

#endif