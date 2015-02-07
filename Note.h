#ifndef _CHAIR_AFFAIR_NOTE
#define _CHAIR_AFFAIR_NOTE

#include <inttypes.h>
#include <config.h>
#include <Arduino.h>

#define NUM_NOTES 7

typedef struct note_range_t {
	uint16_t start;
	uint16_t end;
} note_range_t;

class Note {
public:
	Note(uint8_t aHue, uint16_t order, uint16_t ledCount);
	Note();

	void setHue(uint8_t aHue);
	uint8_t hue();

	void setPlaying(boolean flag);
	boolean isPlaying();

	note_range_t range();	

private:
	boolean _playing;
	uint8_t _hue;
	note_range_t _range;
};

#endif