#include "DemoSwitchManager.h"
#include <Arduino.h>

demo_sw_t DemoSwitchManager::_manager_state;
int DemoSwitchManager::_sw_state;
int DemoSwitchManager::_last_sw_state;
uint32_t DemoSwitchManager::_last_change_time;
uint8_t DemoSwitchManager::_pin;

DemoSwitchManager::DemoSwitchManager(uint8_t aPin) {
	_pin = aPin;
	pinMode(_pin, INPUT_PULLUP);
	_last_sw_state = HIGH;
	_sw_state = HIGH;
	_manager_state = DemoSwitchUnchanged;
}

demo_sw_t DemoSwitchManager::state() {
	//	after the state is returned, revert to unchanged
	demo_sw_t temp = _manager_state;
	_manager_state = DemoSwitchUnchanged;
	return temp;
}

void DemoSwitchManager::update() {
	int reading = digitalRead(_pin);
	if( reading != _last_sw_state ) {
		_last_change_time = millis();
	}

	if( millis() - _last_change_time > DEMO_SW_DEBOUNCE ) {
		_sw_state = reading;
		_manager_state = (_sw_state == LOW)?DemoSwitchTurnedOn:DemoSwitchTurnedOff;
	}
	_last_sw_state = reading;
}