#ifndef _CHAIR_AFFAIR_DEMO_SW_MGR
#define _CHAIR_AFFAIR_DEMO_SW_MGR

#include <inttypes.h>

class DemoSwitchManager {
public:
	DemoSwitchManager(uint8_t aPin);
	void update();

	bool state();

private:
	int _sw_state;
	int _last_sw_state;
	uint32_t _last_change_time;
	uint8_t _pin;
};

#endif