#define IR_RECEIVE_PIN 2
#define IR_USE_AVR_TIMER1 //must be defined before including libraries to avoid conflicting timers

#include <AFMotor.h>
#include <IRremote.hpp>

#define MOTOR_SPEED 255

//defining remote protocols for different motor movements
#define PAUSE 64
#define UP 70
#define DOWN 21
#define LEFT 68
#define RIGHT 67

AF_DCMotor m1(1); //top right
AF_DCMotor m2(2); //top left
AF_DCMotor m3(3); //bottom left
AF_DCMotor m4(4); //bottom right

void stop(){
  m1.run(RELEASE);
  m2.run(RELEASE);
  m3.run(RELEASE);
  m4.run(RELEASE);
}

void moveForward(){
  m1.run(BACKWARD);
  m2.run(BACKWARD);
  delay(200);

  m3.run(FORWARD);
  m4.run(FORWARD);

}

void turnLeft(){
  m1.run(BACKWARD);
  m2.run(RELEASE);
  m3.run(RELEASE);
  m4.run(FORWARD);
}

void turnRight(){
  m1.run(RELEASE);
  m2.run(BACKWARD);

  delay(200);

  m3.run(FORWARD);
  m4.run(RELEASE);
}

void reverse(){
  m1.run(FORWARD);
  m2.run(FORWARD);

  delay(200);

  m3.run(BACKWARD);
  m4.run(BACKWARD);
}
 
void setup() {
  Serial.begin(9600);
  delay(200);

  m1.setSpeed(MOTOR_SPEED);
  m2.setSpeed(MOTOR_SPEED);
  m3.setSpeed(MOTOR_SPEED);
  m4.setSpeed(MOTOR_SPEED);

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  Serial.println("IR Receiver Button Decode");


 
}

void loop() {
  
  if (IrReceiver.decode()){
    auto command = IrReceiver.decodedIRData.command;
    Serial.println(command);

    switch (command){
      case (PAUSE)://stops/ pauses
        stop();
        break;

      case (UP): //moves forward
        moveForward();
        break;
      
      case (DOWN): //reverse
        reverse();
        break;
      case (LEFT): //turn left
        turnLeft();
        break;
      case (RIGHT): //turn right
        turnRight();
        break;
    }

    IrReceiver.resume();
  }

  
}