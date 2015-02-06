#include <Note.h>

#define NUM_NOTES 7

Note::Note(CRGB aColor, uint16_t order, uint16_t ledCount) {
	_color = aColor;
	uint8_t length = ledCount/NUM_NOTES;
	_range.start = order * length;
	_range.end = _range.start + length;
	if( order == NUM_NOTES - 1 ) {
		_range.end = _range.end + 1;
	}
}

Note::setColor(CRGB aColor) {
	_color = aColor;
}

