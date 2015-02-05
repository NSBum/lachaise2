#ifndef _CHAIR_AFFAIR_COLOR_COORDINATOR
#define _CHAIR_AFFAIR_COLOR_COORDINATOR

#include "ChairAffair_ColorManager.h"
#include <FastLED.h>

enum {RED, GREEN, BLUE};

/**
 *		Color coordinating class
 *
 *		Coordinates the colors of the lights depending
 *		on the status of the touch sensors.
 */
class ChairAffair_ColorCoordinator {
public:
	/**		Constructor */
	ChairAffair_ColorCoordinator();
	/**		Flags a color touch sensor as having been touched.
	 *
	 *		@param aColor A color, one of RED, GREEN, BLUE
	 */
	void colorTouch(uint8_t aColor);

	/**		Flags a color touch sensor as having been released.
	 *
	 *		@param aColor A color, one of RED, GREEN, BLUE
	 */
	void colorRelease(uint8_t aColor);

	/**		Returns the current driving color */
	CRGB drivingColor();

	/**		Sets the baseline color
	 *
	 *		@param baselineColor The current color before driving
	 */
	void setBaselineColor(CRGB baselineColor);

	/**		Completes periodic update; should be called in loop() */
	void update();

private:
	ChairAffair_ColorManager _red_mgr;
	ChairAffair_ColorManager _grn_mgr;
	ChairAffair_ColorManager _blu_mgr;
	CRGB _baseline_color;
};

#endif