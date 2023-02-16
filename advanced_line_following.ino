#define L1Pin 36 
#define L2Pin 39 
#define M1Pin 34
#define M2Pin 35
#define R1Pin 32
#define R2Pin 33
#define I2C_SLAVE_ADDR 0x04
#include <Wire.h>

int leftMotor_speed = 255;
int rightMotor_speed = 253;
int baseSpeed = 255;
int black_value =2047;
int white_value= 4095; 
int servoAngle;
int centreAngle = 85;
double Kp = 0.5 ;
double Kd = 0;
double Ki = 0 ;
double K = 0.5;
double cumulative_error = 0;
double prev_error = 0;

void setup() {
 Serial.begin(9600);
 Wire.begin();

}

void loop() {
 double Left_1 = map(constrain(analogRead(L1Pin),black_value,white_value),black_value,white_value,5,0);
 double Left_2 = map(constrain(analogRead(L2Pin),black_value,white_value),black_value,white_value,5,0);
 double Mid_1 = map(constrain(analogRead(M1Pin),black_value,white_value),black_value,white_value,5,0);
 double Mid_2 = map(constrain(analogRead(M2Pin),black_value,white_value),black_value,white_value,5,0);
 double Right_1 = map(constrain(analogRead(R1Pin),black_value,white_value),black_value,white_value,5,0);
 double Right_2 = map(constrain(analogRead(R2Pin),black_value,white_value),black_value,white_value,5,0);
 double weighted_avg = ((Left_1*-21)+(Left_2*-12)+(Mid_1*-5)+(Mid_2*5)+(Right_1* 12)+(Right_2* 21))/(Left_1 + Left_2 + Mid_1 + Mid_2 + Right_1 + Right_2);

double error = weighted_avg;

double PID = (Kp*error)+(Ki*cumulative_error)+(Kd*(error-prev_error));
servoAngle = centreAngle +PID;
leftMotor_speed = baseSpeed + K*PID;
rightMotor_speed = baseSpeed - K*PID;

Transmit_to_arduino(leftMotor_speed,  rightMotor_speed, servoAngle);
delay(100);
cumulative_error=cumulative_error+error;
prev_error = error;

}
 void Transmit_to_arduino(int leftMotor_speed, int rightMotor_speed, int servoAngle)

{
  Wire.beginTransmission(I2C_SLAVE_ADDR); // transmit to device 
  Wire.write((byte)((leftMotor_speed & 0x0000FF00) >> 8));    // first byte of x, containing bits 16 to 9
  Wire.write((byte)(leftMotor_speed & 0x000000FF));           // second byte of x, containing the 8 LSB - bits 8 to 1
  Wire.write((byte)((rightMotor_speed & 0x0000FF00) >> 8));   // first byte of y, containing bits 16 to 9
  Wire.write((byte)(rightMotor_speed & 0x000000FF));          // second byte of y, containing the 8 LSB - bits 8 to 1
  Wire.write((byte)((servoAngle & 0x0000FF00) >> 8));    // first byte of x, containing bits 16 to 9
  Wire.write((byte)(servoAngle & 0x000000FF));
  Wire.endTransmission();   // stop transmitting
}