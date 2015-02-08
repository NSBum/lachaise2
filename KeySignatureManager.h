#ifndef _CHAIR_AFFAIR_KEY_SIGNATURE_MANAGER
#define _CHAIR_AFFAIR_KEY_SIGNATURE_MANAGER

#include <FastLED.h>

typedef struct key_signature_t {
	CRGB note_do;
	CRGB note_re;
	CRGB note_mi;
	CRGB note_fa;
	CRGB note_sol;
	CRGB note_la;
	CRGB note_ti;
} key_signature_t;

class KeySignatureManager {
public:
	KeySignatureManager();

	static void begin();

	static void toggle();

	static bool update();

	static void palette(CRGB *p);
private:
	static uint8_t _keySignatureIndex;
	static bool _paletteWasUpdated;
};

extern KeySignatureManager Transposer;

#endif