#include "NoteManager.h"

//	define this symbols to debug to serial connection
#undef DEBUG_NOTE_CREATION
#undef DEBUG_NOTE_PLAYING

note_t NoteManager::_notes[NUM_NOTES];

NoteManager::NoteManager() {
	
}

void NoteManager::begin() {
	uint8_t hue_inc = 0;
	if( NUM_NOTES != 0 )
		hue_inc = 0xFF / NUM_NOTES;
	else
		hue_inc = 0x11;
	for(uint8_t i = 0; i < NUM_NOTES; i++ ) {
		uint8_t length = NUM_LEDS / NUM_NOTES;
		uint16_t start = i * length;
		uint16_t end = start + length;
		if( i == NUM_NOTES - 1 ) {
			end++;
		}
		note_t temp_note;
		temp_note.start = start;
		temp_note.end = end;
		temp_note.hue = hue_inc * i;
		temp_note.playing = false;
		_notes[i] = temp_note;	
		note_t n = _notes[i];
		#ifdef DEBUG_NOTE_CREATION
			//Serial.print("touch idx = "); Serial.println(touchIndex);
			Serial.print("note idx = "); Serial.println(i);
			Serial.print("range: "); Serial.print(n.start); Serial.print("->"); Serial.println(n.end);
			Serial.println("");
		#endif
	}
}

void NoteManager::update(CRGB leds[]) {
	//	update our LEDs based on which notes are playing
	for(uint8_t i = 0; i < NUM_NOTES; i++ ) {
		note_t note = _notes[i];
		if( note.playing ) {
			uint16_t start = note.start;
			uint16_t end = note.end;
			uint8_t hue = note.hue;
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
	uint8_t noteIndex = noteIndexForTouch(touchIndex);
	_notes[noteIndex].playing = true;

	#ifdef DEBUG_NOTE_PLAYING
		note_t n = _notes[noteIndex];
		Serial.print("touch idx = "); Serial.println(touchIndex);
		Serial.print("note idx = "); Serial.println(noteIndex);
		Serial.print("range: "); Serial.print(n.start); Serial.print("->"); Serial.println(n.end);
		Serial.println("");
	#endif
	
}

void NoteManager::release(uint8_t touchIndex) {
	if( touchIndex >= NUM_NOTES ) {
		return;
	}
	uint8_t noteIndex = noteIndexForTouch(touchIndex);
	_notes[noteIndex].playing = false;
}

uint8_t NoteManager::noteIndexForTouch(uint8_t touchIndex) {
	if( touchIndex > NUM_NOTES ) 
		return 0;
	return NUM_NOTES - touchIndex - 1;
}
