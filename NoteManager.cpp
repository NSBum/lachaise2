#include "NoteManager.h"
#include "config.h"

//	define this symbols to debug to serial connection
#undef DEBUG_NOTE_CREATION
#undef DEBUG_NOTE_PLAYING

note_vec_t NoteManager::_notes;
bool NoteManager::_slowMode;
bool NoteManager::_echo;
echo_vec_t NoteManager::_echoes;

NoteManager::NoteManager() {
	
}

void NoteManager::begin() {
	//	make room for notes
	_notes.reserve(7);

	_slowMode = false;
	_echo = false;

	//	make room for an echo queue
	_echoes.reserve(20);

	uint8_t rainbow_hues[7] = {0,36,72,108,144,180,216};
	// uint8_t hue_inc = 0;
	// if( NUM_NOTES != 0 )
	// 	hue_inc = 0xFF / NUM_NOTES;
	// else
	// 	hue_inc = 0x11;
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
		temp_note.fade = 0;
		temp_note.fadeDirection = FadeNone;
		//temp_note.hue = hue_inc * i;
		temp_note.color = CHSV(rainbow_hues[i],0xFF,0xFF);
		temp_note.playing = false;
		_notes.push_back(temp_note);	
		
		#ifdef DEBUG_NOTE_CREATION
		note_t n = _notes[i];
			//Serial.print("touch idx = "); Serial.println(touchIndex);
			Serial.print("note idx = "); Serial.println(i);
			Serial.print("range: "); Serial.print(n.start); Serial.print("->"); Serial.println(n.end);
			Serial.println("");
		#endif
	}
}

void NoteManager::update(CRGB leds[]) {
	//	update our LEDs based on which notes are playing
	std::vector<note_t>::iterator it;
	for(it = _notes.begin(); it != _notes.end(); ++it) {
	//for(uint8_t i = 0; i < NUM_NOTES; i++ ) {
		//note_t note = _notes[i];
		uint16_t start = it->start;
		uint16_t end = it->end;
		if( it->playing ) {
			

			uint8_t bright;
			if( !_slowMode ) {
				bright = 0xFF;
				for(uint16_t i = start; i <= end; i++ ) {
					leds[i] = it->color;
				}
			}
			else {
				//	slow mode is on
				if( it->fadeDirection == FadeIn ) {
					//	time for an update?
					uint32_t currentTime = millis();
					if( 1 ) {
						//Serial.print("Fade in: "); Serial.println(it->fade);
						for(uint16_t i = start; i <= end; i++ ) {
							leds[i] = it->color;//.fadeLightBy(255 - it->fade);
							leds[i].fadeToBlackBy(255 - it->fade);
						}
						it->lastFadeTime = currentTime;
						if( it->fade < 245 ) {
							it->fade = it->fade + 10;
							//Serial.print("increased note.fade to "); Serial.println(it->fade);
						}
						else {
							//Serial.println("will note increase note.fade");
						}
					}
					
				}

			}
			//	if we are echoing, then we have some modifications to make
		}
		else if( it->fadeDirection == FadeOut ) {
			//	time to update?
			uint32_t currentTime = millis();
			if( 1 ) {
				for(uint16_t i = start; i <= end; i++ ) {
					leds[i] = it->color;
					leds[i].fadeToBlackBy(it->fade);
					Serial.print("Fade out: "); Serial.println(it->fade);
				}
				it->lastFadeTime = currentTime;
			}
			if( it->fade <= 245 ) {
				it->fade = it->fade + 10;
			}
			else {
				it->fadeDirection == FadeNone;
			}
		}
	}

	//	process any echoes as needed
	if( _echo ) {
		std::vector<echo_t>::iterator it = _echoes.begin();
		for(; it != _echoes.end(); ) {
			uint32_t currentTime = millis();

			//	time for a change?
			if( currentTime - it->lastChangeTime >= 75 ) {
				//	toggle the current state & record the time
				it->currentState = !it->currentState;
				it->lastChangeTime = currentTime;

				//	do we need to "play" the echo?
				if( it->currentState ) {
					Serial.print("echo #"); Serial.println(it->echoCount);
					it->spatialOffset -= 10;
					it->echoCount++;
					if( it->echoCount > 4 )
						it->echoCount = 4;

					//	what note are we referencing?
					note_t note = _notes[it->noteIndex];
					CRGB color = note.color;

					//	dim it according to the echo count
					uint8_t dims[5] = {30,64,128,192,230};
					color = color.fadeToBlackBy(dims[it->echoCount]);

					//	displace the echo, but don't go beyond the end
					uint16_t start = note.start + it->spatialOffset;
					if( start > NUM_LEDS ) 
						start = NUM_LEDS;
					uint16_t end = note.end + it->spatialOffset;
					if( end > NUM_LEDS )
						end = NUM_LEDS;
					for(uint16_t i = start; i <= end; i++ ) {
						leds[i] = color;
					}
				}
			}
			if( it->echoCount >= 4 ) {
				it = _echoes.erase(it);
			}
			else {
				it++;
			}
		}
	}
}

void NoteManager::setColor(uint8_t noteIndex, CRGB color) {
	_notes[noteIndex].color = color;
}

void NoteManager::play(uint8_t touchIndex) {
	if( touchIndex >= NUM_NOTES ) {
		return;
	}
	uint8_t noteIndex = noteIndexForTouch(touchIndex);
	_notes[noteIndex].playing = true;

	//	if we're in slow mode, then note has to fade in
	if( _slowMode ) {
		_notes[noteIndex].lastFadeTime = millis();
		_notes[noteIndex].fadeDirection = FadeIn;
		_notes[noteIndex].fade = 0;
		Serial.println("Fade set to 0");
	}

	//	if _echo is on, we need to push a new echo
	if( _echo ) {
		echo_t e ;
		e.noteIndex = noteIndex;
		e.lastChangeTime = millis();
		e.currentState = true;
		e.spatialOffset = 0;
		e.echoCount = 0;

		//	push it onto the stack
		_echoes.push_back(e);
	}

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

	if( _slowMode ) {
		_notes[noteIndex].lastFadeTime = millis();
		_notes[noteIndex].fadeDirection = FadeOut;
		_notes[noteIndex].fade = 0;
	}
}

void NoteManager::toggleSlowMode() {
	_slowMode = !_slowMode;
	if( _slowMode ) Serial.println("SLOWMODE -> ON");
	else Serial.println("SLOWMODE -> OFF");
}

void NoteManager::toggleEcho() {
	_echo = !_echo;
}

uint8_t NoteManager::noteIndexForTouch(uint8_t touchIndex) {
	if( touchIndex > NUM_NOTES ) 
		return 0;
	return NUM_NOTES - touchIndex - 1;
}
