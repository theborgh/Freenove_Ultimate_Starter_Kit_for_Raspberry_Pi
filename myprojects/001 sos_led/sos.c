// Take a pattern array of high/low times and display a blinking LED light with that pattern
// Expands on Tutorial Project 1

#include <wiringPi.h>
#include <stdio.h>

#define ledPin 0	// define the led pin number (according to wiringPi schema)

void blinkWithArrayPattern(int intervalArray[], int length, int repeat) {
	int i;
	int level;
	
	do {
		level = LOW;
		
		for (i = 0; i < length; i++) {
			level = level == HIGH ? LOW : HIGH;
			digitalWrite(ledPin, level); // Writes HIGH (high voltage) or LOW (low voltage) to the specified wiringPi pin. The pin must have been previouly set to output mode.
			delay(intervalArray[i]);
		}
	} while (repeat);
}

void main(void)
{	
	// SOS signal pattern array
	int patternArray[] = {200, 200, 200, 200, 200, 800, 800, 800, 800, 800, 800, 800, 200, 200, 200, 200, 200, 2000};
	int length = sizeof(patternArray)/sizeof(int);

	wiringPiSetup(); // Initialize wiringPi (required for each wiringPi program)
	pinMode(ledPin, OUTPUT); // Set the pin mode (required after the setup call)
	printf("Using wiringPi pin %d in output mode\n", ledPin);
	
	blinkWithArrayPattern(patternArray, length, 1);
}
