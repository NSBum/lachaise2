#include "DemoModeManager.h"

uint8_t DemoModeManager::_songIndex;
uint16_t DemoModeManager::_startIndex;
bool DemoModeManager::_override;
bool DemoModeManager::_state;
uint16_t DemoModeManager::_noteIndex;
bool DemoModeManager::_noteState;
uint32_t DemoModeManager::_noteTimer;
bool DemoModeManager::_playingSong;
int DemoModeManager::_led_pin;
demo_mode_t DemoModeManager::_variation;
CRGBPalette16 DemoModeManager::currentPalette;
TBlendType DemoModeManager::currentBlending;

piano_roll_note_t twinkle_theme[] = {
	{ .note = 0, .dur = 1000 }, { .note = 0, .dur = 1000 },
	{ .note = 4, .dur = 1000 }, { .note = 4, .dur = 1000 }, 
	{ .note = 5, .dur = 1000 }, { .note = 5, .dur = 1000 }, 
	{ .note = 4, .dur = 2000 },
	{ .note = 3, .dur = 1000 },	{ .note = 3, .dur = 1000 },
	{ .note = 2, .dur = 1000 }, { .note = 2, .dur = 1000 },
	{ .note = 1, .dur = 1000 }, { .note = 1, .dur = 1000 },
	{ .note = 0, .dur = 2000 },
	{ .note = 4, .dur = 1000 }, { .note = 4, .dur = 1000 },
	{ .note = 3, .dur = 1000 },	{ .note = 3, .dur = 1000 },
	{ .note = 2, .dur = 1000 },	{ .note = 2, .dur = 1000 },
	{ .note = 1, .dur = 2000 },
	{ .note = 4, .dur = 1000 }, { .note = 4, .dur = 1000 },
	{ .note = 3, .dur = 1000 },	{ .note = 3, .dur = 1000 },
	{ .note = 2, .dur = 1000 },	{ .note = 2, .dur = 1000 },
	{ .note = 1, .dur = 2000 },
	{ .note = 0, .dur = 1000 }, { .note = 0, .dur = 1000 },
	{ .note = 4, .dur = 1000 }, { .note = 4, .dur = 1000 }, 
	{ .note = 5, .dur = 1000 }, { .note = 5, .dur = 1000 }, 
	{ .note = 4, .dur = 2000 },
	{ .note = 3, .dur = 1000 },	{ .note = 3, .dur = 1000 },
	{ .note = 2, .dur = 1000 }, { .note = 2, .dur = 1000 },
	{ .note = 1, .dur = 1000 }, { .note = 1, .dur = 1000 },
	{ .note = 0, .dur = 2000 },
	{ .note = 99, .dur = 0}
};

piano_roll_note_t twinkle_A[] = {
	{.note = 0, .dur = 200},{.note = 0, .dur = 200},{.note = 0, .dur = 200},{.note = 0, .dur = 200},
	{.note = 0, .dur = 400},{.note = 0, .dur = 400},
	{.note = 4, .dur = 200},{.note = 4, .dur = 200},{.note = 4, .dur = 200},{.note = 4, .dur = 200},
	{.note = 4, .dur = 400},{.note = 4, .dur = 400},
	{.note = 5, .dur = 200},{.note = 5, .dur = 200},{.note = 5, .dur = 200},{.note = 5, .dur = 200},
	{.note = 5, .dur = 400},{.note = 5, .dur = 400},
	{.note = 4, .dur = 200},{.note = 4, .dur = 200},{.note = 4, .dur = 200},{.note = 4, .dur = 200},
	{.note = 4, .dur = 400},{.note = 4, .dur = 400},
	{.note = 3, .dur = 200},{.note = 3, .dur = 200},{.note = 3, .dur = 200},{.note = 3, .dur = 200},
	{.note = 3, .dur = 400},{.note = 3, .dur = 400},
	{.note = 2, .dur = 200},{.note = 2, .dur = 200},{.note = 2, .dur = 200},{.note = 2, .dur = 200},
	{.note = 2, .dur = 400},{.note = 2, .dur = 400},
	{.note = 1, .dur = 200},{.note = 1, .dur = 200},{.note = 1, .dur = 200},{.note = 1, .dur = 200},
	{.note = 1, .dur = 400},{.note = 1, .dur = 400},
	{.note = 0, .dur = 200},{.note = 0, .dur = 200},{.note = 0, .dur = 200},{.note = 0, .dur = 200},
	{.note = 0, .dur = 400},{.note = 0, .dur = 400},
	{.note = 4, .dur = 200},{.note = 4, .dur = 200},{.note = 4, .dur = 200},{.note = 4, .dur = 200},
	{.note = 4, .dur = 400},{.note = 4, .dur = 400},
	{.note = 3, .dur = 200},{.note = 3, .dur = 200},{.note = 3, .dur = 200},{.note = 3, .dur = 200},
	{.note = 3, .dur = 400},{.note = 3, .dur = 400},
	{.note = 2, .dur = 200},{.note = 2, .dur = 200},{.note = 2, .dur = 200},{.note = 2, .dur = 200},
	{.note = 2, .dur = 400},{.note = 2, .dur = 400},
	{.note = 1, .dur = 200},{.note = 1, .dur = 200},{.note = 1, .dur = 200},{.note = 1, .dur = 200},
	{.note = 1, .dur = 400},{.note = 1, .dur = 400},
	{.note = 4, .dur = 200},{.note = 4, .dur = 200},{.note = 4, .dur = 200},{.note = 4, .dur = 200},
	{.note = 4, .dur = 400},{.note = 4, .dur = 400},
	{.note = 3, .dur = 200},{.note = 3, .dur = 200},{.note = 3, .dur = 200},{.note = 3, .dur = 200},
	{.note = 3, .dur = 400},{.note = 3, .dur = 400},
	{.note = 2, .dur = 200},{.note = 2, .dur = 200},{.note = 2, .dur = 200},{.note = 2, .dur = 200},
	{.note = 2, .dur = 400},{.note = 2, .dur = 400},
	{.note = 1, .dur = 200},{.note = 1, .dur = 200},{.note = 1, .dur = 200},{.note = 1, .dur = 200},
	{.note = 1, .dur = 400},{.note = 1, .dur = 400},
	{.note = 0, .dur = 200},{.note = 0, .dur = 200},{.note = 0, .dur = 200},{.note = 0, .dur = 200},
	{.note = 0, .dur = 400},{.note = 0, .dur = 400},
	{.note = 4, .dur = 200},{.note = 4, .dur = 200},{.note = 4, .dur = 200},{.note = 4, .dur = 200},
	{.note = 4, .dur = 400},{.note = 4, .dur = 400},
	{.note = 5, .dur = 200},{.note = 5, .dur = 200},{.note = 5, .dur = 200},{.note = 5, .dur = 200},
	{.note = 5, .dur = 400},{.note = 5, .dur = 400},
	{.note = 4, .dur = 200},{.note = 4, .dur = 200},{.note = 4, .dur = 200},{.note = 4, .dur = 200},
	{.note = 4, .dur = 400},{.note = 4, .dur = 400},
	{.note = 3, .dur = 200},{.note = 3, .dur = 200},{.note = 3, .dur = 200},{.note = 3, .dur = 200},
	{.note = 3, .dur = 400},{.note = 3, .dur = 400},
	{.note = 2, .dur = 200},{.note = 2, .dur = 200},{.note = 2, .dur = 200},{.note = 2, .dur = 200},
	{.note = 2, .dur = 400},{.note = 2, .dur = 400},
	{.note = 1, .dur = 200},{.note = 1, .dur = 200},{.note = 1, .dur = 200},{.note = 1, .dur = 200},
	{.note = 1, .dur = 400},{.note = 1, .dur = 400},
	{.note = 0, .dur = 200},{.note = 0, .dur = 200},{.note = 0, .dur = 200},{.note = 0, .dur = 200},
	{.note = 0, .dur = 400},{.note = 0, .dur = 400},
	{ .note = 99, .dur = 0}
};

DemoModeManager::DemoModeManager(int ledPin) {
	_playingSong = false;
	_state = false;
	_override = true;
	_led_pin = ledPin;
	_startIndex = 0;
	pinMode(_led_pin,OUTPUT);
	digitalWrite(_led_pin,LOW);

	currentPalette = RainbowColors_p;
	currentBlending = BLEND;
}

bool DemoModeManager::state() {
	return _state;
}

void DemoModeManager::override() {
	_override = true;
	_noteIndex = 0;
	_noteState = false;
	_noteTimer = 0;
	_playingSong = false;
	//	but don't change the switch LED
}

bool DemoModeManager::overrideState() {
	return _override;
}

void DemoModeManager::start() {
	_state = true;
	_override = false;
	_noteIndex = 0;
	_noteState = false;
	_noteTimer = 0;
	_playingSong = false;
	digitalWrite(_led_pin,HIGH);
}

void DemoModeManager::stop() {
	_state = false;
	_noteIndex = 0;
	_noteState = false;
	_noteTimer = 0;
	_playingSong = false;
	digitalWrite(_led_pin,LOW);
}

uint8_t DemoModeManager::update(CRGB leds[]) {
	if( !_state | (_state & _override) ) { return DEMO_MODE_NO_NOTE; }
	if( _playingSong ) {
		if( _noteState == false ) {
			//	we're in a rest
			if( millis() - _noteTimer > 100 ) {
				//	//rest is over, play the note
				piano_roll_note_t n = noteFromSongWithIndex(_songIndex,_noteIndex);
				_noteIndex++;
				if( n.note != 99 ) {
					//	this is a valid note
					//	start timer
					_noteTimer = millis();
					_noteState = true;
					return n.note;
				}
				else {
					//	this is the end of the song
					_noteIndex = 0;
					_noteState = false;
					_noteTimer = 0;
					_playingSong = false;
					return DEMO_MODE_NO_NOTE;
				}
			}
		} // not playing a note
		else {
			//	we're in a note
			piano_roll_note_t n = noteFromSongWithIndex(_songIndex,_noteIndex);
			if( millis() - _noteTimer > n.dur ) {
				//	note is over
				_noteTimer = millis();
				_noteState = false;
				return DEMO_MODE_NO_NOTE;
			}
			else {
				return n.note;
			}
		} // playing a note
	} // playing a song
	else {
		//	
		_startIndex++;
		fillLEDsFromPaletteColors(leds,_startIndex);
	} // *not* playing a song
	changeDemoModePeriodically();
	
}

piano_roll_note_t DemoModeManager::noteFromSongWithIndex(uint8_t aSongIndex,uint16_t aNoteIndex) {
	if( aSongIndex == 0 ) {
		return twinkle_theme[aNoteIndex];
	}
	else if( aSongIndex == 1 ) {
		return twinkle_A[aNoteIndex];
	}
	piano_roll_note_t randomNote = {.note = random(0,6), .dur = random(250,200) };
}

void DemoModeManager::changeDemoModePeriodically() {
	uint8_t minuteHand = (millis() / 60000 ) % 6;
	static uint8_t lastMinute = 99;

	DEBUG_PRINT("DEMO | new minute");
	if( lastMinute != minuteHand ) {
		lastMinute = minuteHand;
		if( minuteHand == 0 ) {
			DEBUG_PRINT("DEMO | rainbow blended palette");
			currentPalette = RainbowColors_p;
			currentBlending = BLEND;
		}
		else if( minuteHand == 2 ) {
			DEBUG_PRINT("DEMO | rainbow stripe no blend");
			currentPalette = RainbowStripeColors_p;
			currentBlending = NOBLEND;
		}
		else if( minuteHand == 4 ) {
			DEBUG_PRINT("DEMO | rainbow stripe with blend");
			currentPalette = RainbowStripeColors_p;
			currentBlending = BLEND;
		}

		if( random(0,10) < 4 ) {
			_playingSong = true;
			//	choose a song (theme or variation A)
			_songIndex = (random(100) < 50)?0:1;
		}
		else {
			_playingSong = false;
		}
	}
}

void DemoModeManager::fillLEDsFromPaletteColors(CRGB leds[],uint16_t colorIndex) {
	uint8_t bright = 0xFF;
	for(uint16_t i = 0; i < NUM_LEDS; i++ ) {
		leds[i] = ColorFromPalette(currentPalette,colorIndex,bright,currentBlending);
		colorIndex += 3;
	}
}