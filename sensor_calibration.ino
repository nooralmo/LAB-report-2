#define L1Pin 36 
#define L2Pin 39 
#define M1Pin 34
#define M2Pin 35
#define R1Pin 32
#define R2Pin 33
#include <Wire.h>

void setup() {
 Serial.begin(9600);
 Wire.begin();
}

void loop() {
Serial.println(analogRead(R2Pin));

}
//B = 2047
//W = 4095

