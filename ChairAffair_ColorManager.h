#ifndef _CHAIR_AFFAIR_COLOR_MGR
#define _CHAIR_AFFAIR_COLOR_MGR

#include <inttypes.h>

class ChairAffair_ColorManager {
public:
	ChairAffair_ColorManager();
	bool isMax();
	void update();
	void touch(uint8_t component_value);
	void release();
	uint8_t value();

private:
	uint8_t _baseline_value;	//	value
	uint8_t _current_value;
	bool _increasing;
	uint32_t _update_count;
};

#endif