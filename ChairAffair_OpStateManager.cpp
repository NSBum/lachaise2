#include "ChairAffair_OpStateManager.h"
#include <Arduino.h>

ChairAffair_OpStateManager::ChairAffair_OpStateManager() {
	//	initialize in powering up state
	_state = OpStatePoweringUp;
	_last_touch_time = UINT32_MAX;
}

void ChairAffair_OpStateManager::setState(OperationalState aState) {
	_state = aState;
}

OperationalState ChairAffair_OpStateManager::state() {
	return _state;
}

void ChairAffair_OpStateManager::touched() {
	//	if we're touched, we're in active mode
	_state = OpStateActive;
	_last_touch_time = millis();
}

void ChairAffair_OpStateManager::setDemoSwitchState(bool switchState) {
	_demo_switch_state = switchState;
}

void ChairAffair_OpStateManager::update() {
	//	update our current state depending on present state
	uint32_t current_time = millis();
	switch(_state) {
		case OpStatePoweringUp:
			break;
		case OpStateActive: {
			if( current_time - _last_touch_time >= ACTIVE_MODE_TIMEOUT ) {
				//	we timed out in active mode
				//	drop into inactive unless demo switch is on
				if( _demo_switch_state == true ) {
					_state = OpStateDemo;
				}
				else {
					_state = OpStateInactive;
				}
			}
			break;
		}
		case OpStateDemo: {
			//	if we're in demo mode, only turning off the switch or touching
			//	a sensor will force us out
			if( _demo_switch_state == false ) {
				_state = OpStateInactive;
			}
			break;
		}
		case OpStateInactive: {
			//	if we're inactive, only a touch or turning on the demo sw
			//	will force us out
			if( _demo_switch_state == true ) {
				_state = OpStateDemo;
			}
			break;
		}
	}
}