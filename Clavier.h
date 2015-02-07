

#ifndef _CLAVIER_H
#define _CLAVIER_H

#include <Arduino.h>
#include <Adafruit_MPR121.h>



class Clavier {
public:
	Clavier();
	static bool begin();
	static bool sensorOnline();
	static bool update();
	static uint16_t newTouches();
	static uint16_t newReleases();
private:
	static uint16_t currtouched;
	static uint16_t lasttouched;
	static uint16_t _new_touches;
	static uint16_t _new_releases;
	static uint16_t activeFlags;
	static Adafruit_MPR121 sensorInterface;
	static bool sensorInterfaceOnline;
};

extern Clavier Klavier;

#endif