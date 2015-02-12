#ifndef _CHAIR_AFFAIR_HEARTBEAT_H
#define _CHAIR_AFFAIR_HEARTBEAT_H

#include <inttypes.h>
#include <Arduino.h>

/**	Heartbeat LED
 *
 *	This class manages the heartbeat LED that informs the observer
 *	that the hardware is alive.
 */
class Heartbeat {
public:
	/**	Constructor
	 *
	 *	@param led_pin the pin to which the LED is attached
	 *	@param on the number of milliseconds that the LED should remain on in each cycle
	 *	@param off the number of milliseconds that the LED should remain off in each cycle
	 */
	Heartbeat(uint8_t led_pin, uint32_t on, uint32_t off);

	/**	Update
	 *
	 *	This function must be called with each pass of the main run loop to update
	 *	the status of the heartbeat LED.
	 */
	void update();


private:
	uint8_t _pin;
	int _ledState;
	uint32_t _on_time;
	uint32_t _off_time;
	uint32_t _prev_time;
};


#endif