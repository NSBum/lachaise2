#if 0
#ifndef __SERIAL_DEBUGGER
#define __SERIAL_DEBUGGER

#include "config.h"
#include <Arduino.h>
#include <FastLED.h>


typedef enum serial_debug_cmd_t {
	NO_CMD
} serial_debug_cmd_t;

class SerialDebugger {
public:
	SerialDebugger();
	serial_debug_cmd_t currentCommand();
	void addChar(char inChar);
	void update();

private:
	//	serial input string if we are debugging
	String _serial_in_str = "";
	//	flag for completion of serial input stream
	boolean _serial_in_complete = false;

	serial_debug_cmd_t _current_cmd;

	CRGB _cmd_color;
};


#endif
#endif