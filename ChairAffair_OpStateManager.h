#ifndef _CHAIR_AFFAIR_OP_STATE_MGR
#define _CHAIR_AFFAIR_OP_STATE_MGR

#include <inttypes.h>
#include <stdbool.h>
#include <config.h>

typedef enum OperationalState {
	OpStatePoweringUp,	//	the device is powering up
	OpStateInactive,	//	no recent touches, not in demo
	OpStateActive,		//	the user has touched a sensor recently
	OpStateDemo,		//	the demo switch is LOW
	OpStateTuneSensors	//	mode used to fine tune the touch sensors
} OperationalState;

class ChairAffair_OpStateManager {
public:
	ChairAffair_OpStateManager();
	void update();
	void touched();

	void setState(OperationalState aState);
	OperationalState state();

	void setDemoSwitchState(bool switchState);

private:
	OperationalState _state;
	uint32_t _last_touch_time;
	bool _demo_switch_state;
};
#endif