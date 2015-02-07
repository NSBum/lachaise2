#include "Clavier.h"
#include "config.h"

uint16_t Clavier::currtouched;
uint16_t Clavier::lasttouched;
uint16_t Clavier::_new_touches;
uint16_t Clavier::_new_releases;
uint16_t Clavier::activeFlags;
Adafruit_MPR121 Clavier::sensorInterface;
bool Clavier::sensorInterfaceOnline;

Clavier::Clavier() {
	
}

bool Clavier::begin() {
	activeFlags = 0;
	//	region sensors are active
	activeFlags |= (1 << MPR_121_RGN_1);
	activeFlags |= (1 << MPR_121_RGN_2);
	activeFlags |= (1 << MPR_121_RGN_3);
	activeFlags |= (1 << MPR_121_RGN_4);
	activeFlags |= (1 << MPR_121_RGN_5);
	activeFlags |= (1 << MPR_121_RGN_6);
	activeFlags |= (1 << MPR_121_RGN_7);

	//	global function sensors are active too
	activeFlags |= (1 << MPR_121_RYTH);
	activeFlags |= (1 << MPR_121_COLOR);
	activeFlags |= (1 << MRP_121_OTHER);

	sensorInterface = Adafruit_MPR121();

	Serial.println("Created instance of MPR121");

	if( sensorInterface.begin(I2C_ADDRESS_CAP_SENSE) ) {
		sensorInterfaceOnline = true;
	}
	else {
		sensorInterfaceOnline = false;
	}
	Serial.println("Started MRP121");

	for( int i = 0; i < 10; i++ ) {
		digitalWrite(LED_BUILTIN,HIGH);
		delay(100);
		digitalWrite(LED_BUILTIN,LOW);
		delay(75);
	}
}

bool Clavier::sensorOnline() {
	return sensorInterfaceOnline;
}

bool Clavier::update() {
	currtouched = sensorInterface.touched();
	for( uint8_t i = 0; i<12; i++ ) {
    	// it if *is* touched and *wasnt* touched before, alert!
    	if( (currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      		//Serial.print(i); Serial.println(" touched");
      		_new_touches |= _BV(i);
    	}
    	// if it *was* touched and now *isnt*, alert!
    	if( !(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      		//Serial.print(i); Serial.println(" released");
      		_new_releases |= _BV(i);
    	}
	}
	lasttouched = currtouched; 
	//Serial.print("("); Serial.print(lasttouched,HEX); Serial.println(")");
}

uint16_t Clavier::newTouches() {
	uint16_t temp = _new_touches;
	_new_touches = 0;
	return temp;
}

uint16_t Clavier::newReleases() {
	uint16_t temp = _new_releases;
	_new_releases = 0;
	return temp;
}