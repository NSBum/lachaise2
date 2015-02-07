#ifndef _CHAIR_AFFAIR_CLAVIER
#define _CHAIR_AFFAIR_CLAVIER

#include <inttypes.h>
#include <config.h>
#include <Adafruit_MPR121.h>

uint16_t _currtouched;
uint16_t _lasttouched;
uint16_t _active_flags;
uint16_t _new_touches;
uint16_t _new_releases;

Adafruit_MPR121 _sensor_interface;
boolean _sensor_interface_online;

void clavier_begin() {
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
}

boolean clavier_sensor_online() {
	return _sensor_interface_online;
}

void clavier_update() {
	_currtouched = _sensor_interface.touched();
	for( uint8_t i = 0; i<12; i++ ) {
    	// it if *is* touched and *wasnt* touched before, alert!
    	if( (_currtouched & _BV(i)) && !(_lasttouched & _BV(i)) ) {
      		Serial.print(i); Serial.println(" touched");
      		_new_touches |= _BV(i);
    	}
    	// if it *was* touched and now *isnt*, alert!
    	if( !(_currtouched & _BV(i)) && (_lasttouched & _BV(i)) ) {
      		Serial.print(i); Serial.println(" released");
      		_new_releases |= _BV(i);
    	}
	}
	_lasttouched = _currtouched; 
	Serial.print("("); Serial.print(_lasttouched,HEX); Serial.println(")");
}

uint16_t clavier_new_touches() {
	uint16_t temp = _new_touches;
	_new_touches = 0;
	return temp;
}

uint16_t clavier_new_releases() {
	uint16_t temp = _new_releases;
	_new_releases = 0;
	return temp;
}

#endif