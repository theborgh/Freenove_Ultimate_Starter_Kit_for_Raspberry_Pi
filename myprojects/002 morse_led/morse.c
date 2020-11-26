// Take a string as a command line argument and display the corresponding Morse code on the LED
// Expands on Tutorial Project 1
// Compile with: gcc morse.c -o morse -lwiringPi

#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ledPin 0	// define the led pin number (according to wiringPi schema)
#define SHORT 0
#define LONG 1
#define STOP 2

struct MorseLetter {
	char character;
	int code[6];
};

struct MorseLetter morseTable[] = {
	{ character: 'A', code: {SHORT, LONG, STOP}},
	{ character: 'B', code: {LONG, SHORT, SHORT, SHORT, STOP}},
	{ character: 'C', code: {LONG, SHORT, LONG, SHORT, STOP}},
};

int getMorseIndexForLetter(char c) {
	int i;

	for (i = 0; i < 3; i++) {
		if (morseTable[i].character == toupper(c)) {
			return i;
		}
	}

	return -1;
}

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

int main(int argc, char *argv[]) {	
	int i, j, k;

	for (i = 1; i < argc; i++) {
		int length = strlen(argv[i]);
		int morseIndex, codeLength;

		printf("argv[%d]: %s (length: %d)\n", i, argv[i], length);

		// output morse code for this argv
		for (j = 0; j < length; j++) {
			
			// find morseTable item with correct letter
			morseIndex = getMorseIndexForLetter(argv[i][j]);

			printf("Letter %c (index %d) morse code is: ", argv[i][j], morseIndex);
			for (k = 0; morseTable[morseIndex].code[k] != STOP; k++) {
				if(morseTable[morseIndex].code[k] == LONG) putchar('-');
				else putchar('.');
			}
			printf("\n");
		}
		printf("\n");
	}
	

	return 0;
}
