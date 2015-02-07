#include <Arduino.h>
#include "config.h"

typedef struct dx_led_t {
	uint32_t on_time;
	uint32_t off_time;
	int state;
	uint8_t flash_count;
	int pin;
} dx_led_t;

enum {DX_1, DX_2, DX_3};

dx_led_t dx_leds[3];
uint8_t idx_active_dx_led;
IntervalTimer dx_led_timer;

void isr_dx_led();
void init_dx_leds();
void set_dx_led_times(uint8_t idx,uint32_t on, uint32_t off);
void flash(uint8_t idx, uint8_t count);

void isr_dx_led() {
	dx_led_t led = dx_leds[idx_active_dx_led];
	if( led.state == HIGH ) {
		led.state = LOW;
		digitalWrite(led.pin, led.state);
		dx_led_timer.begin(isr_dx_led, led.off_time);
	}
	else {
		led.state = HIGH;
		digitalWrite(led.pin, led.state);
		dx_led_timer.begin(isr_dx_led, led.on_time);
	}
	led.flash_count--;
}

void init_dx_leds() {
	uint8_t hw_pins[3] = {DX_1_LED_PIN, DX_2_LED_PIN, DX_3_LED_PIN};

	for(uint8_t i = 0; i < 3; i++ ) {
		dx_led_t led = dx_leds[i];
		led.pin = hw_pins[i];
		pinMode(led.pin, OUTPUT);
		led.on_time = DEFAULT_DX_LED_ON;
		led.off_time = DEFAULT_DX_LED_OFF;
	}
}

void set_dx_led_times(uint8_t idx,uint32_t on, uint32_t off) {
	dx_leds[idx].on_time = on;
	dx_leds[idx].off_time = off;
}


void flash(uint8_t idx, uint8_t count) {
	dx_led_t led = dx_leds[idx_active_dx_led];
	led.flash_count = count;
	digitalWrite(led.pin, HIGH);
	idx_active_dx_led = idx;
	uint32_t cycle_time = (led.state == HIGH)?led.off_time:led.on_time;
	dx_led_timer.begin(isr_dx_led,cycle_time);
}

