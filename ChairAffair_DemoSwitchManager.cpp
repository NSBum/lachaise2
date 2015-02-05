#include "ChairAffair_DemoSwitchManager.h"
#include <Arduino.h>
#include "config.h"

ChairAffair_DemoSwitchManager::ChairAffair_DemoSwitchManager(uint8_t aPin) {
	_pin = aPin;
	pinMode(_pin, INPUT_PULLUP);
	_last_sw_state = HIGH;
	_sw_state = HIGH;
}

bool ChairAffair_DemoSwitchManager::state() {
	return (_sw_state == LOW)?true:false;
}

void ChairAffair_DemoSwitchManager::update() {
	int reading = digitalRead(_pin);
	if( reading != _last_sw_state ) {
		_last_change_time = millis();
	}

	if( millis() - _last_change_time > DEMO_SW_DEBOUNCE ) {
		_sw_state = reading;
	}
	_last_sw_state = reading;
}