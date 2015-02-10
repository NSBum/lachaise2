#ifndef _CHAIR_AFFAIR_PEDAL_MANAGER
#define _CHAIR_AFFAIR_PEDAL_MANAGER

#include <FastLED.h>

typedef enum PedalFunction {
	PedalNoFunction = 0,
	PedalChangePalette,
	PedalToggleEcho,
	PedalToggleFade,
};	

/**	Pedal manager
 *
 *	Manages the "pedals" which correspond to the rightmost three bands
 *	as one faces the chair.
 */
class PedalManager {
public:
	/** Constructor */
	PedalManager();

	/** Depress a pedal
	 *
	 *	This function is called when a touch occurs on a pedal band
	 *	@param touchIndex The index of the touch sensor being activated.
	 */
	static void depress(uint8_t touchIndex);

	/**	Release a pedal
	 *
	 *	This function is called when a touch is released on a pedal band.
	 *	@param touchIndex the index of the touch sensor being released
	 */
	static void release(uint8_t touchIndex);

	/**	Update the pedal status
	 *
	 *	This function must be called on the pedal manager with each pass through the 
	 *	main loop. It returns the current pedal function. If the function is other than \c PedalNoFunction then
	 *	this function will only return that function once before reverting to \c PedalNoFunction.
	 */
	static PedalFunction update();

	/**	Begin the pedal interface
	 *	
	 *	Starts the pedal interface. The base implementation does nothing.
	 */
	static void begin();

private:
	static PedalFunction _function;
};

extern PedalManager PedalBoard;

#endif