#include "ColorManager.h"
#include "config.h"
#include <Arduino.h>

ColorManager::ColorManager() {

}

bool ColorManager::isMax() {
	return (_current_value == 0xFF );
}

void ColorManager::update() {
	_update_count++;
	if( _update_count % COLOR_SENSE_INC_RATE == 0 ) {
		if( _increasing ) {
			_current_value++;
		}
		else {
			if( _current_value != _baseline_value ) {
				_current_value--;
			}
		}
		_current_value = min(_current_value, 0xFF);
	}
}

void ColorManager::touch(uint8_t baseline) {
	_baseline_value = baseline;
	_increasing = true;
}

void ColorManager::release() {
	_increasing = false;
	_update_count = 0;
}

uint8_t ColorManager::value() {
	return _current_value;
}