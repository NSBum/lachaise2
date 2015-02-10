#include "DemoModeManager.h"

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

DemoModeManager::DemoModeManager(int ledPin) {
	_playingSong = false;
	_state = false;
	_override = true;
	_led_pin = ledPin;
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
	_playingSong = true;
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

uint8_t DemoModeManager::update() {
	if( !_state | (_state & _override) ) { return DEMO_MODE_NO_NOTE; }
	if( _noteState == false ) {
		//	we're in a rest
		if( millis() - _noteTimer > 100 ) {
			//	//rest is over, play the note
			piano_roll_note_t n = twinkle_theme[_noteIndex++];
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
	}
	else {
		//	we're in a note
		piano_roll_note_t n = twinkle_theme[_noteIndex];
		if( millis() - _noteTimer > n.dur ) {
			//	note is over
			_noteTimer = millis();
			_noteState = false;
			return DEMO_MODE_NO_NOTE;
		}
		else {
			return n.note;
		}
	}
}

void DemoModeManager::changeDemoModePeriodically() {

}