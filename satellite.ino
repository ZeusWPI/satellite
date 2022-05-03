#include <avr/interrupt.h>
#include <avr/sleep.h>
// Pin 4 for LED
int led = 4;
ISR(WDT_vect) {
	digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
	delay(1000);               // wait for a second
	digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
}

void setup() {
	// initialize the digital pin as an output.
	pinMode(led, OUTPUT);

    for (int i = 0; i < 5; i++) {
        digitalWrite(led, HIGH);
        delay(250);
        digitalWrite(led, LOW);
        delay(250);
    }
    
	// prescale timer to 8s so we can measure current
	WDTCR |= (1<<WDP3 )|(0<<WDP2 )|(0<<WDP1)|(1<<WDP0); // 8s
	// Enable watchdog timer interrupts
	WDTCR |= (1<<WDTIE);
	sei(); // Enable global interrupts
	// Use the Power Down sleep mode
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	for (;;) {
		sleep_mode();   // go to sleep and wait for interrupt...
	}
}
// the loop routine will not run
void loop() {
}