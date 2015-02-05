#include "ChairAffair_ColorCoordinator.h"

ChairAffair_ColorCoordinator::ChairAffair_ColorCoordinator() {
	_red_mgr = ColorManager();
	_grn_mgr = ColorManager();
	_blu_mgr = ColorManager();


}

void ChairAffair_ColorCoordinator::colorTouch(uint8_t aColor) {
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
	
void ChairAffair_ColorCoordinator::colorRelease(uint8_t aColor) {
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

void ChairAffair_ColorCoordinator::update() {
	_red_mgr.update();
	_grn_mgr.update();
	_blu_mgr.update();
}

void ChairAffair_ColorCoordinator::setBaselineColor(CRGB aColor) {
	_baseline_color = aColor;
}
	
CRGB ChairAffair_ColorCoordinator::drivingColor() {
	return CRGB(_red_mgr.value(), _grn_mgr.value(), _blu_mgr.value());
}