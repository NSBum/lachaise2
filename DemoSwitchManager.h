#ifndef _CHAIR_AFFAIR_DEMO_SW_MGR
#define _CHAIR_AFFAIR_DEMO_SW_MGR

#include <inttypes.h>
#include "config.h"

typedef enum {
	DemoSwitchTurnedOn,
	DemoSwitchTurnedOff,
	DemoSwitchUnchanged
} demo_sw_t;

class DemoSwitchManager {
public:
	DemoSwitchManager(uint8_t aPin);
	void update();

	demo_sw_t state();

private:
	static demo_sw_t _manager_state;
	static int _sw_state;
	static int _last_sw_state;
	static uint32_t _last_change_time;
	static uint8_t _pin;
};

#endif