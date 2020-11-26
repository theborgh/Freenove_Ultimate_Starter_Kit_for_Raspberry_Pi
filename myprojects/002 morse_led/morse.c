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
	{ character: 'D', code: {LONG, SHORT, SHORT, STOP}},
	{ character: 'E', code: {SHORT, STOP}},
	{ character: 'F', code: {SHORT, SHORT, LONG, SHORT, STOP}},
	{ character: 'G', code: {LONG, LONG, SHORT, STOP}},
	{ character: 'H', code: {SHORT, SHORT, SHORT, SHORT, STOP}},
	{ character: 'I', code: {SHORT, SHORT, STOP}},
	{ character: 'J', code: {SHORT, LONG, LONG, LONG, STOP}},
	{ character: 'K', code: {LONG, SHORT, LONG, STOP}},
	{ character: 'L', code: {SHORT, LONG, SHORT, SHORT, STOP}},
	{ character: 'M', code: {LONG, LONG, STOP}},
	{ character: 'N', code: {LONG, SHORT, STOP}},
	{ character: 'O', code: {LONG, LONG, LONG, STOP}},
	{ character: 'P', code: {SHORT, LONG, LONG, SHORT, STOP}},
	{ character: 'Q', code: {LONG, LONG, SHORT, LONG, STOP}},
	{ character: 'R', code: {SHORT, LONG, SHORT, STOP}},
	{ character: 'S', code: {SHORT, SHORT, SHORT, STOP}},
	{ character: 'T', code: {LONG, STOP}},
	{ character: 'U', code: {SHORT, SHORT, LONG, STOP}},
	{ character: 'V', code: {SHORT, SHORT, SHORT, LONG, STOP}},
	{ character: 'W', code: {SHORT, LONG, LONG, STOP}},
	{ character: 'X', code: {LONG, SHORT, SHORT, LONG, STOP}},
	{ character: 'Y', code: {LONG, SHORT, LONG, LONG, STOP}},
	{ character: 'Z', code: {LONG, LONG, SHORT, SHORT, STOP}},
};

int getMorseIndexForLetter(char c) {
	int i;

	for (i = 0; i < 26; i++) {
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

		printf("%s\n", argv[i]);

		// output morse code for this argv
		for (j = 0; j < length; j++) {
			
			// find morseTable item with correct letter
			morseIndex = getMorseIndexForLetter(argv[i][j]);

			printf("%c ", toupper(argv[i][j]));
			for (k = 0; morseTable[morseIndex].code[k] != STOP; k++) {
				if (morseIndex != -1) {
					if (morseTable[morseIndex].code[k] == LONG) {
						putchar('-');
					} else {
						putchar('.');
					}
				} else {
          printf("ERROR: letter %c not found in the morse table\n", argv[i][j]);
        }
			}
      // Break between letters
			printf("\n");
		}
    // Break between words
		printf("\n");
	}
	

	return 0;
}
