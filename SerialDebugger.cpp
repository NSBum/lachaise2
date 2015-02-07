#if 0
#include "SerialDebugger.h"


SerialDebugger::SerialDebugger() {
	_current_cmd = NO_CMD;
	_serial_in_complete = false;
	_serial_in_str = "";
}

void SerialDebugger::update() {
	if( !_serial_in_complete ) {
		return;
	}
	_serial_in_str.trim();

	if( _serial_in_str == "MODE>DEMO") {
		//	force demo mode
		// _current_cmd = FORCE_DEMO;
	}
	else if ( _serial_in_str == "MODE>INAC" ) {
		// _current_cmd = FORCE_INACTIVE;
	}
	else if( _serial_in_str.startsWith("CSET>") ) {
		char hex_str_red[3], hex_str_grn[3], hex_str_blu[3];
		_serial_in_str.substring(5,7).toCharArray(hex_str_red,3);
		_serial_in_str.substring(7,9).toCharArray(hex_str_grn,3);
		_serial_in_str.substring(9,11).toCharArray(hex_str_blu,3);
		uint8_t red_val = (uint8_t)strtoul(hex_str_red,NULL,16);
		uint8_t grn_val = (uint8_t)strtoul(hex_str_grn,NULL,16);
		uint8_t blu_val = (uint8_t)strtoul(hex_str_blu,NULL,16);
		_cmd_color = CRGB(red_val,grn_val,blu_val);
	}
	else if( _serial_in_str == "FTUNE" ) {
		//_current_cmd = FTUNE;
	}
}

serial_debug_cmd_t SerialDebugger::currentCommand() {
	if( _serial_in_complete ) {
		_serial_in_complete = false;
		_serial_in_str = "";
	}
	//	after we return the command, reset it to no command
	serial_debug_cmd_t temp_cmd = _current_cmd;
	//_current_cmd = NO_CMD;
	return temp_cmd;
}

void SerialDebugger::addChar(char inChar) {
	_serial_in_str += inChar;
	if( inChar == '\n' ) {
		_serial_in_complete = true;
	}
}

#endif