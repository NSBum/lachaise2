#include "PedalManager.h"

#undef WANTS_SENSOR_7_CHANGE_PALETTE

#ifdef WANTS_SENSOR_7_CHANGE_PALETTE
#define SENSOR_CHANGE_PALETTE 7
#endif

#define SENSOR_TOGGLE_ECHO 8
#define SENSOR_TOGGLE_FADE 9

PedalFunction PedalManager::_function = PedalNoFunction;

PedalManager::PedalManager() {

}

void PedalManager::begin() {

}

void PedalManager::depress(uint8_t touchIndex) {
	switch(touchIndex) {
		#ifdef WANTS_SENSOR_7_CHANGE_PALETTE
		case SENSOR_CHANGE_PALETTE: {
			_function = PedalChangePalette;
			Serial.println("PED | Palette chg");
			break;
		}
		#endif
		case SENSOR_TOGGLE_ECHO: {
			_function = PedalToggleEcho;
			break;
		}
		case SENSOR_TOGGLE_FADE: {
			_function = PedalToggleFade;
			break;
		}
		default: {
			_function = PedalNoFunction;
			break;
		}
	}
}

void PedalManager::release(uint8_t touchIndex) {

}

PedalFunction PedalManager::update() {
	PedalFunction temp = _function;
	_function = PedalNoFunction;
	return temp;
}