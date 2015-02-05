#include "ChairAffair_LightBar.h"

ChairAffair_LightBar::ChairAffair_LightBar(uint32_t pos16, uint16_t width, uint16_t delta16, uint16_t hue16) {
	_position_16 = pos16;
	_width = width;
	_delta_16 = delta16;
	_hue_16 = hue16;
}

void ChairAffair_LightBar::drawAntiAliasedBar(CRGB leds[NUM_LEDS]) {
	//	convert the fractional position to a raw pixel #
	int i = _position_16 >> 4;
	//	extract the fractional part of the position
	uint8_t frac = _position_16 & 0b00001111;

	uint8_t first_pixel_bright = 255 - (frac << 4);
	uint8_t last_pixel_bright = 255 - first_pixel_bright;

	uint8_t bright;
	for( int n = 0; n <= _width; n++ )
	{
		if( n == 0 )
		{
			//	first pixel in the bar
			bright = first_pixel_bright;
		}
		else if( n == _width ) 
		{
			bright = last_pixel_bright;
		}
		else 
		{
			bright = 255;
		}

		leds[i] += CHSV(_hue_16,255,bright);
		i++;
		if( i == NUM_LEDS )
		{
			i = 0;
		}
	}
}

uint32_t ChairAffair_LightBar::position_16() {
	return _position_16;
}

uint16_t ChairAffair_LightBar::width() {
	return _width;
}

uint16_t ChairAffair_LightBar::hue_16() {
	return _hue_16;
}

uint16_t ChairAffair_LightBar::delta_16() {
	return _delta_16;
}

void ChairAffair_LightBar::addPosition(uint16_t inc) {
	_position_16 += inc;
}

void ChairAffair_LightBar::addHue(uint16_t inc) {
	_hue_16 += inc;
}

void ChairAffair_LightBar::setPosition(uint32_t aPos) {
	_position_16 = aPos;
}

void ChairAffair_LightBar::setHue(uint16_t aHue) {
	_hue_16 = aHue;
}