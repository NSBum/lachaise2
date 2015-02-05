#ifndef _CHAIR_AFFAIR_EEPROM_MGR_
#define _CHAIR_AFFAIR_EEPROM_MGR_

#include <inttypes.h>

class ChairAffair_EEPROMManager {
public:
	ChairAffair_EEPROMManager();
	void begin();
	void writeTouchThreshold(uint8_t sensor, uint16_t threshold);
	void writeReleaseThreshold(uint8_t sensor, uint16_t threshold);
	uint16_t readTouchThreshold(uint8_t sensor);
	uint16_t readReleaseThreshold(uint8_t sensor);
	uint16_t customTouchThresholdFlags();
	uint16_t customReleaseThresholdFlags();

private:
	uint16_t _dummy_int;
};


#endif