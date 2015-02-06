#ifndef _CHAIR_AFFAIR_TOUCH_MGR
#define _CHAIR_AFFAIR_TOUCH_MGR

#include <inttypes.h>
#include <config.h>
#include <Adafruit_MPR121.h>
#include <map>

enum {SENSOR_IDX_RED, SENSOR_IDX_GRN, SENSOR_IDX_BLU, 
	SENSOR_IDX_RGT, SENSOR_IDX_MID, SENSOR_IDX_LFT,
	SENSOR_IDX_LCK
};

//	touch sensor states
typedef enum SensorState {
	SensorStateInactive,
	SensorStateFirstTouch,
	SensorStateTouching
} SensorState;

typedef struct {
	uint8_t mpr_121_pin;
	bool first_tch;
	uint32_t first_tch_time;
	uint32_t touch_time;
	SensorState state;
} tch_sensor_t;

class TouchManager {
public:
	/**		Constructor	*/
	TouchManager();

	/**		Update touch status. 
	 *
	 *		@note Should be called with each main loop
	 */
	void update();

	/**		Returns the status of the hardware sensor */
	boolean sensorOnline();

	/**		Returns the sensors newly touched as a bit field	*/
	uint16_t newTouches();

	/**		Returns the sensors newly released as a bit field	*/
	uint16_t newReleases();

	void setTouchThreshold(uint8_t sensor, uint16_t touch, uint16_t release);

	void begin();

	uint16_t sensorIndexForHardwareIndex(uint16_t mpr121_idx);

private:
	uint16_t _currtouched;
	uint16_t _lasttouched;
	uint16_t _active_flags;
	uint16_t _new_touches;
	uint16_t _new_releases;
	Adafruit_MPR121 _sensor_interface;
	boolean _sensor_interface_online;
	uint8_t _sensor_map[CAP_SENSE_NUM_ACTIVE];
	tch_sensor_t _sensors[CAP_SENSE_NUM_ACTIVE];
};

#endif