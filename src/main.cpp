
/*
 * Example using the Rotary library, dumping integers to the serial
 * port. The integers increment or decrement depending on the direction
 * of rotation.
 *
 * This example uses interrupts rather than polling.
 */

#include <Arduino.h>
#include <Rotary.h>

void rotate();

// Rotary encoder is wired with the common to ground and the two
// outputs to pins 2 and 3.
Rotary rotary = Rotary(2, 3);

// Counter that will be incremented or decremented by rotation.
volatile int counter = 0;

void setup() {
  Serial.begin(57600);
  attachInterrupt(0, rotate, CHANGE);
  attachInterrupt(1, rotate, CHANGE);
}

void loop() {
}

// rotate is called anytime the rotary inputs change state.
void rotate() {
  unsigned char result = rotary.process();
  if (result == DIR_CW) {
    counter++;
    Serial.println(counter);
  } else if (result == DIR_CCW) {
    counter--;
    Serial.println(counter);
  }
}
