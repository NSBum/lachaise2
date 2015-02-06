#include "ColorCoordinator.h"

ColorCoordinator::olorCoordinator() {
	_red_mgr = ColorManager();
	_grn_mgr = ColorManager();
	_blu_mgr = ColorManager();


}

void ColorCoordinator::colorTouch(uint8_t aColor) {
	switch( aColor ) {
		case RED: {
			_red_mgr.touch(_baseline_color.red);
			break;
		}
		case GREEN: {
			_grn_mgr.touch(_baseline_color.green);
			break;
		}
		case BLUE: {
			_blu_mgr.touch(_baseline_color.blue);
		}
	}
}
	
void ColorCoordinator::colorRelease(uint8_t aColor) {
	switch( aColor ) {
		case RED: {
			_red_mgr.release();
			break;
		}
		case GREEN: {
			_grn_mgr.release();
			break;
		}
		case BLUE: {
			_blu_mgr.release();
			break;
		}
	}
}

void ColorCoordinator::update() {
	_red_mgr.update();
	_grn_mgr.update();
	_blu_mgr.update();
}

void ColorCoordinator::setBaselineColor(CRGB aColor) {
	_baseline_color = aColor;
}
	
CRGB ChairAffair_ColorCoordinator::drivingColor() {
	return CRGB(_red_mgr.value(), _grn_mgr.value(), _blu_mgr.value());
}