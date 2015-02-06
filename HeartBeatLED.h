#ifndef _CHAIR_AFFAIR_HEARTBEAT_H
#define _CHAIR_AFFAIR_HEARTBEAT_H

#include <inttypes.h>
#include <Arduino.h>

class Heartbeat {
public:
	Heartbeat(uint8_t led_pin, uint32_t on, uint32_t off);
	void update();


private:
	uint8_t _pin;
	int _ledState;
	uint32_t _on_time;
	uint32_t _off_time;
	uint32_t _prev_time;
};


#endif