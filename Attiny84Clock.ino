#include "clock.hpp"

// Setting up pin numbers.

/*  These pins send data about the currently displayed digit.
 *  Note: They are set in this order to more closely match the inputs of the 4511 ic.
 */ 
const int B = 10;
const int C = 9;
const int D = 8;
const int A = 7;

// These pins are meant to turn on/off transistors used to sink current from the display.
const int digit0 = 0;
const int digit1 = 1;
const int digit2 = 2;
const int digit3 = 3;

unsigned long lastCountTick = 0;
unsigned long lastDisplayUpdate = 0;

int digitToDisplay = 0;

void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);

  pinMode(digit0, OUTPUT);
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);

  lastCountTick = millis();
  lastDisplayUpdate = micros();
}

void loop() {

  unsigned long now = millis();
  unsigned long nowMicros = micros();

  if ((unsigned long)(now - lastCountTick) > 1000) {
    lastCountTick = now;
    incrementSeconds();
  }

  if ((unsigned long)(nowMicros - lastDisplayUpdate) > 300) {
    lastDisplayUpdate = nowMicros;
    digitToDisplay = (digitToDisplay + 1) % 4;
    int digitValue = getDigit(digitToDisplay);
    blankDisplayDigit(); 
    setBCDOutput(digitValue);
    if (digitValue == 0 && digitToDisplay == 0) {
      blankDisplayDigit();
    } else {
      setDisplayDigit(digitToDisplay);
    }
  }
  
}

// Precondition: num < 9
void setBCDOutput(int num) {
  digitalWrite(A, (num & 0x1) ? HIGH : LOW);
  digitalWrite(B, (num & 0x2) ? HIGH : LOW);
  digitalWrite(C, (num & 0x4) ? HIGH : LOW);
  digitalWrite(D, (num & 0x8) ? HIGH : LOW);
}

void setDisplayDigit(int num) {
  digitalWrite(digit0, (num == 0) ? HIGH : LOW);
  digitalWrite(digit1, (num == 1) ? HIGH : LOW);
  digitalWrite(digit2, (num == 2) ? HIGH : LOW);
  digitalWrite(digit3, (num == 3) ? HIGH : LOW);
}

void blankDisplayDigit() {
  digitalWrite(digit0, LOW);
  digitalWrite(digit1, LOW);
  digitalWrite(digit2, LOW);
  digitalWrite(digit3, LOW);
}

