#include "EEPROMManager.h"
#include <EEPROM.h>
#include "config.h"
#include "EEPROMAnything.h"

EEPROMManager::EEPROMManager() {
	return;
}

void EEPROMManager::begin() {
	//	has the EEPROM been initialized?
	uint8_t flag = EEPROM.read(EEPROM_ADDR_WAS_INIT);
	if( flag != EEPROM_ADDR_WAS_INIT ) {
		//	we have not been initialized so set bit fields to 0 (no custom thresholds);
		EEPROM_writeAnything(EEPROM_ADDR_TCH_THRSH,(uint16_t)0);
		EEPROM_writeAnything(EEPROM_ADDR_REL_THRSH,(uint16_t)0);
	}
}

void EEPROMManager::writeTouchThreshold(uint8_t sensor, uint16_t threshold) {
	uint32_t addr = EEPROM_ADDR_TCH_BASE + 2 * sensor;
	EEPROM_writeAnything(addr,threshold);

	//	manage flags
	uint16_t flags = EEPROM_readAnything(EEPROM_ADDR_TCH_THRSH, _dummy_int);
	flags |= sensor;
	EEPROM_writeAnything(EEPROM_ADDR_TCH_THRSH, flags);
}

void EEPROMManager::writeReleaseThreshold(uint8_t sensor, uint16_t threshold) {
	uint32_t addr = EEPROM_ADDR_REL_BASE + 2 * sensor;
	EEPROM_writeAnything(addr,threshold);

	//	manage flags
	uint16_t flags = EEPROM_readAnything(EEPROM_ADDR_REL_THRSH, _dummy_int);
	flags |= sensor;
	EEPROM_writeAnything(EEPROM_ADDR_REL_THRSH, flags);
}

uint16_t EEPROMManager::readTouchThreshold(uint8_t sensor) {
	uint32_t addr = EEPROM_ADDR_TCH_BASE + 2 * sensor;
	uint16_t val = EEPROM_readAnything(addr, _dummy_int);
	return val;
}

uint16_t EEPROMManager::readReleaseThreshold(uint8_t sensor) {
	uint32_t addr = EEPROM_ADDR_REL_BASE + 2 * sensor;
	uint16_t val = EEPROM_readAnything(addr, _dummy_int);
	return val;
}

uint16_t EEPROMManager::customTouchThresholdFlags() {
	uint16_t val = EEPROM_readAnything(EEPROM_ADDR_TCH_THRSH, _dummy_int);
	return val;
}

uint16_t EEPROMManager::customReleaseThresholdFlags() {
	uint16_t val = EEPROM_readAnything(EEPROM_ADDR_REL_THRSH, _dummy_int);
	return val;
}


