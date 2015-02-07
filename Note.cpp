#include "Note.h"

Note::Note(uint8_t aHue, uint16_t order, uint16_t ledCount) {
	_hue = aHue;
	uint8_t length = ledCount/NUM_NOTES;
	_range.start = order * length;
	_range.end = _range.start + length;
	if( order == NUM_NOTES - 1 ) {
		_range.end = _range.end + 1;
	}
}

Note::Note() {

}

note_range_t Note::range() {
	return _range;
}

void Note::setHue(uint8_t aHue) {
	_hue = aHue;
}

uint8_t Note::hue() {
	return _hue;
}

void Note::setPlaying(boolean flag) {
	_playing = flag;
}

boolean Note::isPlaying() {
	return _playing;
}

