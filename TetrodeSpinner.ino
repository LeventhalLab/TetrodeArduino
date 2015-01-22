#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);

const int switch1 = 12;
int forwardRot = 20;
int backwardRot = 0;

void setup() {
  pinMode(switch1, INPUT);
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  //myMotor->setSpeed(500);  // not sure what max rpm is
}

void loop() {
  if(digitalRead(switch1) == HIGH) {
      //single vs double doesn't matter
      //using RPM isn't as smooth, this implements a hardware step, which
      //just gives us better control over everything
      for(int i=1;i<forwardRot*200;i++) {
        myMotor->onestep(FORWARD,SINGLE);
      }
      for(int i=1;i<backwardRot*200;i++) {
        myMotor->onestep(BACKWARD,SINGLE);
      }
  }
}
