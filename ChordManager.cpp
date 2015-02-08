#import "ChordManager.h"
#include "config.h"

bool ChordManager::_state;
uint8_t ChordManager::_startIndex;
uint32_t ChordManager::_lastChange;
CRGBPalette16 ChordManager::currentPalette;
TBlendType ChordManager::currentBlending;

ChordManager::ChordManager() {

}

void ChordManager::begin() {
	_state = false;
	currentPalette = RainbowColors_p;
  	currentBlending = BLEND;
}

void ChordManager::play() {
	_state = true;
	_startIndex = 0;
	_lastChange = millis();
}

void ChordManager::release() {
	_state = false;
}

void ChordManager::update(CRGB leds[]) {
	if( _state == false ) { return; }
	if( millis() - _lastChange >= 5 )
		_startIndex++;
		fillFromPaletteColors(_startIndex,leds);
}

void ChordManager::fillFromPaletteColors(uint8_t colorIndex,CRGB leds[]) {
	for(uint8_t i = 0; i < NUM_LEDS; i++ ) {
		leds[i] = ColorFromPalette(currentPalette, colorIndex, 0x50, currentBlending);
		colorIndex += 3;
	}
}