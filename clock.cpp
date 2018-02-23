#include "clock.hpp"

int hours = 0;
int minutes = 0;
int seconds = 0;

// Increment seconds and handle overflow.
void incrementSeconds() {
	seconds = seconds + 1;
	if (seconds >= 60) {
		seconds = 0;
		incrementMinutes();
	}
}

// Increment minutes and handle overflow.
void incrementMinutes() {
	minutes = minutes + 1;
	if (minutes >= 60) {
		minutes = 0;
		incrementHours();
	}
}

// Increment hours and handle overflow.
void incrementHours() {
	hours = hours + 1;
	if (hours >= 24) {
		hours = 0;
	}
}

/*	Grab the value of the digit that should be displayed at a specified index on the LED display.
 *	The indexes of the digits are as follows:
 *		0 - The tens place of the hours segment of a clock.
 *		1 - The ones place of the hours segment of a clock.
 *		2 - The tens place of the minutes segment of a clock.
 *		3 - The ones place of the minutes segment of a clock.
 *	Special Note:
 *		When selecting 0 as the index of the clock
 */
int getDigit(int index) {
	if (index < 2) {
		int mod12 = hours % 12;
		if (index == 0) {
			if (mod12 > 9 || mod12 == 0) {
				return 1;
			} else {
				return 0;
			}
		} else {
			return mod12 % 10;
		}
	} else if (index == 2) {
		return minutes / 10;
	} else if (index == 3) {
		return minutes % 10;
	}
}

//	Determines if the time is AM (0) or PM (1).
int AMOrPM() {
	return (hours > 10) ? 1 : 0;
}
