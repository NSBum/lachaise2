

#ifndef _CLAVIER_H
#define _CLAVIER_H

#include <Arduino.h>
#include <Adafruit_MPR121.h>

/**
 * 	Represents a virtual keyboard
 *
 *	The programmatic interface to the capacitive touch sensor
 */
class Clavier {
public:
	/**	Constructor */
	Clavier();

	/** Begins the interaction with the MPR121 capacitive touch sensor
	 *
	 *	@return Returns true if the interaction begins correctly, false otherwise.
	 */
	static bool begin();

	/**	Status of the touch sensor
	 *
	 *	Returns true if the sensor is online, false otherwise
	 */
	static bool sensorOnline();

	/** Update the status of the sensors
	 *
	 *	*return Returns true if a sensor changed since the last update.
	 *	@note This must be called with each cycle of the run loop.
	 */
	static bool update();

	/**	New touches
	 *
	 *	Returns the new touches on the sensors as a bitfield.
	 */
	static uint16_t newTouches();

	/** New releases
	 *
	 *	Returns the new releases on the sensors as a bitfield.
	 */
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

/**	Singleton instance */
extern Clavier Klavier;

#endif