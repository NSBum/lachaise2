#include "KeySignatureManager.h"

#define NUM_PALETTES 5


#define PALETTE_RAINBOW 0
#define PALETTE_BLUES 1
#define PALETTE_GREENS 2
#define PALETTE_REDS 3
#define PALETTE_GREYS 4

uint8_t KeySignatureManager::_keySignatureIndex = 0;
bool KeySignatureManager::_paletteWasUpdated = false;

KeySignatureManager::KeySignatureManager() {
}

void KeySignatureManager::begin() {

}

void KeySignatureManager::toggle() {
	_paletteWasUpdated = true;
	_keySignatureIndex++;
	if( _keySignatureIndex > NUM_PALETTES - 1 ) {
		_keySignatureIndex = 0;
	}
}

bool KeySignatureManager::update() {
	bool temp = _paletteWasUpdated;
	_paletteWasUpdated = false;
	if( _paletteWasUpdated ) {
		Serial.println("oops");
	}
	return temp;
}

void KeySignatureManager::palette(CRGB *p) {
	Serial.print("palette idx = "); Serial.println(_keySignatureIndex);
	switch(_keySignatureIndex) {
		case PALETTE_BLUES: {
			uint8_t hues[7] = {128,137,146,155,164,174,183};
			for(uint8_t i = 0; i < 7; i++ ) {
				p[i] = CHSV(hues[i],0xFF,0xFF);
			}
			break;
		}
		case PALETTE_REDS: {
			uint8_t hues[7] = {0,9,18,27,36,45,54};
			for(uint8_t i = 0; i < 7; i++ ) {
				p[i] = CHSV(hues[i],0xFF,0xFF);
			}
			break;
		}
		case PALETTE_GREENS: {
			uint8_t hues[7] = {64,73,82,91,100,109,118};
			for(uint8_t i = 0; i < 7; i++ ) {
				p[i] = CHSV(hues[i],0xFF,0xFF);
			}
			break;
		}
		case PALETTE_GREYS: {
			uint8_t bright[7] = {10,50,90,130,170,210,255};
			for(uint8_t i = 0; i < 7; i++ ) {
				p[i] = CRGB(bright[i],bright[i],bright[i]);
			}
			break;
		}
		case PALETTE_RAINBOW:
		default: {
			uint8_t hues[7] = {0,36,72,108,144,180,216};
			for(uint8_t i = 0; i < 7; i++ ) {
				p[i] = CHSV(hues[i],0xFF,0xFF);
			}
			break;
		}
	}
}