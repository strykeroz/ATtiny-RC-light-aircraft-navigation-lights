#include <avr/sleep.h>
// ATtiny85 RC aircraft navigation lights
//
// Wingtip navigation lights, headlights, and a flashing tail beacon for RC light aircraft.
// ATtiny85 initially checks for daylight using an LDR, and if it is bright powers off entirely so
// flight time in daylight is not impacted.  Since RC flights are typically under 20mins it was
// preferable to save battery power than to have the possibility of lights turning on during the flight
// as light fades.
//
// If sufficiently dark, it powers down the LDR and runs the lights.

// note these LED pins are ATtiny locations
const int wingTips = 0;                     // IC leg 5; red and green 3mm LED navigation lights for wingtips
const int LDRpower = 4;                     // IC leg 3; power for LDR, turned off if it's daylight
const int lightSensor = 3;                  // IC leg 2; LDR sensor reading
const int redBeacon = 1;                    // IC leg 6; flashing red 3mm LED on tail
const int headlight = 2;                    // IC leg 7; 2x 5mm white LEDs for landing lights
// IC leg 1 is reset, 4 is GND, 8 is VCC, so all but reset is used here

unsigned long timerStart = millis();
unsigned long beaconCycle = 500;          // <100 times per minute
boolean beaconState = false;

void setup() {

  pinMode(headlight, OUTPUT);
  pinMode(wingTips, OUTPUT);
  pinMode(LDRpower, OUTPUT);
  pinMode(redBeacon, OUTPUT);

  // confirm startup by flashing all lights 3 times, after 5 sec
  delay(5000);
  for(int i = 0; i < 3; i++) {
    digitalWrite(headlight, HIGH);
    digitalWrite(wingTips, HIGH);
    digitalWrite(redBeacon, HIGH);
    delay(1000);
    digitalWrite(headlight, LOW);
    digitalWrite(wingTips, LOW);
    digitalWrite(redBeacon, LOW);
    delay(1000);
  }

  digitalWrite(LDRpower, HIGH);                // power up LDR
  // Vcc = 3.7V
  // the LDR used is 8kR up to 24kR used in a voltage divider with 10kR at other end
  // reads 562 / 1023 at 8k (bright) and 0 / 1023 at 24k (black)
  // but through testing, 572 appears a decent value.  Change to suit your LDR or taste.
  if(analogRead(lightSensor)-562 > 10) {      // check reading
    // it is bright, so flash lights again 3 times faster &
    // enter sleep mode, forever
    for(int i = 0; i < 3; i++) {              // 3 short pulses, 1sec apart
      digitalWrite(headlight, HIGH);
      digitalWrite(wingTips, HIGH);
      digitalWrite(redBeacon, HIGH);
      delay(250); 
      digitalWrite(headlight, LOW);
      digitalWrite(wingTips, LOW);
      digitalWrite(redBeacon, LOW);
      delay(1000); 
    }
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);       // sleep mode is set here
    sleep_enable();                            // and activated here
    sleep_mode();                              // and...sleep.
    // execution ends at this point if bright light detected.     
  } else {
    //  turn on static lights, and enter loop() to flash strobe
    digitalWrite(headlight, HIGH);
    digitalWrite(wingTips, HIGH);
  }
  digitalWrite(LDRpower, LOW);                // turn off power to LDR
}

void loop() {
  if(millis() - timerStart >= beaconCycle) {          // time to cycle the beacon
    beaconState = !beaconState;                       // cycle beacon state
    timerStart = millis();                            // reset timer
    digitalWrite(redBeacon, beaconState);
  }
}



