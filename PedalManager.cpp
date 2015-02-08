#include "PedalManager.h"

#define SENSOR_CHANGE_PALETTE 7
#define SENSOR_TOGGLE_ECHO 8
#define SENSOR_TOGGLE_FADE 9

PedalManager::PedalManager() {

}

void PedalManager::begin() {

}

void PedalManager::depress(uint8_t touchIndex) {
	switch(touchIndex) {
		case SENSOR_CHANGE_PALETTE: {
			_function = PedalChangePalette;
			break;
		}
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
	return _function;
}