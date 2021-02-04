// TODO: Debounce button
// => https://arduinogetstarted.com/tutorials/arduino-button-debounce

// TODO: Debounce encoder
// ==>> http://www.buxtronix.net/2011/10/rotary-encoders-done-properly.html
// => https://www.best-microcontroller-projects.com/rotary-encoder.html
// => http://practicalusage.com/arduino-using-a-rotary-encoder/
// From bildr article: https://bildr.org/2012/08/rotary-encoder-arduino/

// these pins can not be changed 2/3 are special pins
int encoderPin1 = 2;
int encoderPin2 = 3;
int encoderSwitchPin = 4; // push button switch

volatile int lastEncoded = 0;
volatile long encoderValue = 0;
volatile int motion = 0;

int lastMSB = 0;
int lastLSB = 0;

void setup() {
  Serial.begin(9600);

  pinMode(encoderPin1, INPUT);
  pinMode(encoderPin2, INPUT);

  pinMode(encoderSwitchPin, INPUT);

  digitalWrite(encoderPin1, HIGH); // turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); // turn pullup resistor on

  digitalWrite(encoderSwitchPin, HIGH); // turn pullup resistor on

  // call updateEncoder() when any high/low changed seen
  // on interrupt 0 (pin 2), or interrupt 1 (pin 3)
  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);
}

void loop() {
  // Do stuff here
  if (digitalRead(encoderSwitchPin)) {
    // button is not being pushed
  } else {
    // button is being pushed
    Serial.println("BUTTON PUSHED");
    lastEncoded = 0;
    encoderValue = 0;
    motion = 0;
  }

  // delay(1000); //just here to slow down the output, and show it will work
  // even during a delay
}

void updateEncoder() {
  int MSB = digitalRead(encoderPin1); // MSB = most significant bit
  int LSB = digitalRead(encoderPin2); // LSB = least significant bit

  int encoded = (MSB << 1) | LSB; // converting the 2 pin value to single number
  int sum =
      (lastEncoded << 2) | encoded; // adding it to the previous encoded value

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    encoderValue++;
    motion = 1;
  }
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    encoderValue--;
    motion = -1;
  }
  //log(motion, encoded, lastEncoded, encoderValue);
  Serial.println(encoderValue);
  lastEncoded = encoded; // store this value for next time
}

void log(int motion, int encoded, int lastEncoded, int encoderValue) {
  Serial.print("motion = ");
  Serial.print(motion);
  Serial.print("; encoded = ");
  Serial.print(encoded);
  Serial.print("; lastEncoded = ");
  Serial.print(lastEncoded);
  Serial.print("; encoderValue =");
  Serial.println(encoderValue);
}
