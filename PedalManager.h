#ifndef _CHAIR_AFFAIR_PEDAL_MANAGER
#define _CHAIR_AFFAIR_PEDAL_MANAGER

#include <FastLED.h>

typedef enum PedalFunction {
	PedalNoFunction = 0,
	PedalChangePalette,
	PedalToggleEcho,
	PedalToggleFade,
};	

class PedalManager {
public:
	PedalManager();

	static void depress(uint8_t touchIndex);

	static void release(uint8_t touchIndex);

	static PedalFunction update();

	static void begin();

private:
	static PedalFunction _function;
};

extern PedalManager PedalBoard;

#endif