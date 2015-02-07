#include "NoteManager.h"

Note* NoteManager::_notes;

NoteManager::NoteManager() {
	uint8_t hue_inc = 0;
	if( NUM_NOTES != 0 )
		hue_inc = 0xFF / NUM_NOTES;
	else
		hue_inc = 0x11;
	for(uint8_t i = 0; i < NUM_NOTES; i++ ) {
		_notes[i] = Note(hue_inc * i, i, NUM_LEDS);
	}
}

void NoteManager::update(CRGB leds[]) {
	//	update our LEDs based on which notes are playing
	for(uint8_t i = 0; i < NUM_NOTES; i++ ) {
		Note note = _notes[i];
		if( note.isPlaying() ) {
			uint16_t start = note.range().start;
			uint16_t end = note.range().end;
			uint8_t hue = note.hue();
			uint8_t bright = 0xFF;
			for(uint16_t i = start; i <= end; i++ ) {
				leds[i] = CHSV(hue,255,255);
			}
		}
	}
}

void NoteManager::play(uint8_t touchIndex) {
	if( touchIndex >= NUM_NOTES ) {
		return;
	}
	_notes[touchIndex].setPlaying(true);
}

void NoteManager::release(uint8_t touchIndex) {
	if( touchIndex >= NUM_NOTES ) {
		return;
	}
	_notes[touchIndex].setPlaying(false);
}

uint8_t NoteManager::noteIndexForTouch(uint8_t touchIndex) {
	if( touchIndex > NUM_NOTES ) 
		return NUM_NOTES - touchIndex;
	else 
		return 0;
}
