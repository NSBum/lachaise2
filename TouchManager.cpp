#include "TouchManager.h"
#include <Wire.h>
#include <Arduino.h>


TouchManager::TouchManager() {
	// _sensor_map[MPR_121_RED] = SENSOR_IDX_RED;
	// _sensor_map[MPR_121_GRN] = SENSOR_IDX_GRN;
	// _sensor_map[MPR_121_BLU] = SENSOR_IDX_BLU;
}

void TouchManager::begin() {
	_active_flags = 0;
	//	region sensors are active
	_active_flags |= (1 << MPR_121_RGN_1);
	_active_flags |= (1 << MPR_121_RGN_2);
	_active_flags |= (1 << MPR_121_RGN_3);
	_active_flags |= (1 << MPR_121_RGN_4);
	_active_flags |= (1 << MPR_121_RGN_5);
	_active_flags |= (1 << MPR_121_RGN_6);
	_active_flags |= (1 << MPR_121_RGN_7);

	//	global function sensors are active too
	_active_flags |= (1 << MPR_121_RYTH);
	_active_flags |= (1 << MPR_121_COLOR);
	_active_flags |= (1 << MRP_121_OTHER);

	_sensor_interface = Adafruit_MPR121();

	Serial.println("Created instance of MPR121");

	if( _sensor_interface.begin(0x5A) ) {
		_sensor_interface_online = true;
	}
	else {
		_sensor_interface_online = false;
	}
	Serial.println("Started MRP121");

	for( int i = 0; i < 10; i++ ) {
		digitalWrite(LED_BUILTIN,HIGH);
		delay(100);
		digitalWrite(LED_BUILTIN,LOW);
		delay(75);
	}

	//	start with nothing touched (hopefully?!)
	for( uint8_t i = 0; i < 12; i++) {
		if( !(_active_flags & _BV(i)) ) {
			continue;
		}
		_sensors[i].state = SensorStateInactive;
	}
}

boolean TouchManager::sensorOnline() {
	return _sensor_interface_online;
}

void TouchManager::update() {
	_currtouched = _sensor_interface.touched();
	uint32_t current_time = millis();

	//	loop through all the touch pins, skipping ones that aren't active
	for( uint8_t i = 0; i < 12; i++) {
		if( !(_active_flags & _BV(i)) ) {
			continue;
		}

		if( _sensors[i].state == SensorStateFirstTouch ) {
			//	this pin was touched and *may* be valid; is it still touched?
			if( _currtouched & _BV(i) ) {
				// still touched, but for how long?
				if( current_time - _sensors[i].first_tch_time > 500 ) {
					// this is a real touch b/c longer than 500 ms
					_sensors[i].state = SensorStateTouching;
					_sensors[i].first_tch_time = UINT32_MAX;
				}
			}
		}
		//	if *is* touched and *wasnt* touched before, this is a new TOUCH
		if( (_currtouched & _BV(i)) && !(_lasttouched & _BV(i)) ) {
			_sensors[i].state = SensorStateFirstTouch;
			_sensors[i].first_tch_time = current_time;
			//	record this as a new touch
			_new_touches |= _BV(i);
		}
		//	if it *was* touched and now *isnt*, this is a release
		if( !(_currtouched & _BV(i)) & (_lasttouched & _BV(i)) ) {
			_sensors[i].state = SensorStateInactive;
			_sensors[i].first_tch_time = 0;
			//	record this as a new release
			_new_releases |= _BV(i);
		}
	}
}

void TouchManager::setTouchThreshold(uint8_t sensor, uint16_t touch, uint16_t release) {
	_sensor_interface.writeRegister(MPR121_TOUCHTH_0 + 2*sensor, touch);
    _sensor_interface.writeRegister(MPR121_RELEASETH_0 + 2*sensor, release);
}

uint16_t TouchManager::newTouches() {
	uint16_t temp_new_tch = _new_touches;
	_new_touches = 0;	//	reset the new touches after we deliver
	return temp_new_tch;
}

uint16_t TouchManager::newReleases() {
	uint16_t temp_new_rel = _new_releases;
	_new_releases = 0;	//	reset new releases after we deliver
	return temp_new_rel;
}

uint16_t TouchManager::sensorIndexForHardwareIndex(uint16_t mpr121_idx) {

}