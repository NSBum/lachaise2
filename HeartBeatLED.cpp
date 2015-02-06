#include "HeartBeatLED.h"



Heartbeat::Heartbeat(uint8_t pin, uint32_t on, uint32_t off) {
	_pin = pin;
	_ledState = LOW;
	_on_time = on;
	_off_time = off;
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, HIGH);
}

void Heartbeat::update() {
	uint32_t current_time = millis();
	if( (_ledState == HIGH) && (current_time - _prev_time >= _on_time) ) {
		_ledState = LOW;
		_prev_time = current_time;
		digitalWrite(_pin, _ledState);
	}
	else if( (_ledState == LOW) && (current_time - _prev_time >= _off_time) ) {
		_ledState = HIGH;
		_prev_time = current_time;
		digitalWrite(_pin, _ledState);
	}
}
