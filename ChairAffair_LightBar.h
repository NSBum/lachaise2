#ifndef _CHAIR_AFFAIR_LIGHTBAR_H
#define _CHAIR_AFFAIR_LIGHTBAR_H

#include <FastLED.h>
#include "config.h"
#include <inttypes.h>

/**		A bar of same-hue LEDs with anti-aliasing features */
class ChairAffair_LightBar {
public:
	/**		Constructor
	 *
	 *		@param pos16 The leading edge of the bar in 16ths of a pixel
	 *		@param width The width of the bar in whole pixels
	 *		@param delta16 The amount of linear change per loop in 16ths of a pixel
	 *		@param hue16 The current hue
	 */
	ChairAffair_LightBar(uint32_t pos16, uint16_t width, uint16_t delta16, uint16_t hue16);

	/**		Returns the current position in 16ths of a pixel */
	uint32_t position_16();

	/**		Returns the width of the bar */
	uint16_t width();

	/**		Returns the per-cycle change in position */
	uint16_t delta_16();

	/**		Returns the hue of the bar */
	uint16_t hue_16();

	/**		Increments the position of the bar
	 *
	 *		@param inc The amount to add to the current position
	 */
	void addPosition(uint16_t inc);

	/**		Increments the hue of the bar
	 *	
	 *		@param inc The amount to add to the current hue
	 */
	void addHue(uint16_t inc);

	/**		Sets the position
	 *
	 *		@param aPos The desired position in 16ths of a pixel
	 */
	void setPosition(uint32_t aPos);

	/**		Sets the hue
	 *
	 *		@param aHue The desired hue
	 */
	void setHue(uint16_t aHue);

	/**		Draw antialiased bar
	 *
	 *		leds An array of LEDs to which we should write
	 */
	void drawAntiAliasedBar(CRGB leds[NUM_LEDS]);

private:
	uint32_t _position_16;
	uint16_t _width;
	uint16_t _delta_16;
	uint16_t _hue_16;
};

#endif