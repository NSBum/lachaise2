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

	static void release(uint8_t touchIndex);

	static PedalFunction update();

	static void begin();

private:
	static PedalFunction _function;
};

extern PedalManager PedalBoard;

#endif