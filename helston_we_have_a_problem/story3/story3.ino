#include "Arduino.h"
#include "Motor.h"
#include "Sensor.h"

namespace
{
  const byte interrupt_pin_2 = 2;
  const byte interrupt_pin_3 = 3;

  int left_speed = 200;
  int right_speed = 220;
  int r_reverse = 200;
  int l_reverse = 200;
  // Instantiate the two motor objects, passing in the side of the robot the motor is on
  Motor left_motor{"left"};
  Motor right_motor{"right"};

  // Instantiate a sensor object
  Sensor sensor{};
}

void setup()
{
  Serial.begin(115200);
  pinMode(interrupt_pin_2, INPUT_PULLUP);
  pinMode(interrupt_pin_3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_2), left_motor_pulse_interrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_3), right_motor_pulse_interrupt, RISING);
}

// Draws a star
void loop()
{

  // Go forward
  forwards();
  // Stop
  stop_rover();
  // Turn right
  turn_r();
  // stop
  stop_rover();


  // Go forward
  forwards();
  // Stop
  stop_rover();
  // Turn right
  turn_r();
  // stop
  stop_rover();

  
  // Go forward
  forwards();
  // Stop
  stop_rover();
  // Turn right
  turn_r();
  // stop
  stop_rover();


    // Go forward
  forwards();
  // Stop
  stop_rover();

  
  //go forward
  forwards();
  // stop
  stop_rover();
  // Turn left
  turn_l();
  // stop
  stop_rover();
  

  // Go forward
  forwards();
  // Stop
  stop_rover();
  // Turn left
  turn_l();
  // stop
  stop_rover();

  
  //forwards
  forwards();
  //stop
  stop_rover();
 //turn
  turn_l();
 //stop
  stop_rover();
 //forwards
  forwards();

  stop_rover();
    stop_rover();
      stop_rover();
        stop_rover();
  fullstop();
/*
  if (left_motor.get_pulse_count() > 950) {
    left_motor.stop();
    right_motor.stop();
    delay(1000000);
  }*/
}





/*
  stop_rover();
  forwards();
  stop_rover();
  turn_r();
  stop_rover();
  forwards();
  stop_rover();
  turn_r();
  stop_rover();
  forwards();
  stop_rover();
  turn_r();
  // Move robot forwards for one second


  /*
  left_motor.forward(left_speed);
  right_motor.forward(right_speed);

    // Turn right for half a second
  left_motor.forward(l_reverse);
  right_motor.reverse(r_reverse);
  delay(500);

/*  cout << "right speed equals" right_speed << "\n";
Serial.println("left motor speed");

Serial.println(left_speed);
Serial.println("right motor speed");
Serial.println(right_speed);

 if (left_motor.get_pulse_count() > right_motor.get_pulse_count()){
    // go forwarsd
    left_speed=left_speed-5;     
  }
 if (left_motor.get_pulse_count() < right_motor.get_pulse_count()){
    //go forwards
      right_speed=right_speed-5;     
  }

  if (left_speed==right_speed){
    }
  //delay(10000);
*/


  

  /*
  
  // Stop the robots motors and wait a smidge
  
  // Turn right for half a second
  left_motor.forward(speed);
  right_motor.reverse(speed);
  delay(500);




  // Move robot backwards for one second
  left_motor.reverse(speed);
  right_motor.reverse(speed);
  delay(1000);

  // Stop the robots motors
  stop_rover() */


// Functions below here

void forwards(){
  left_motor.forward(left_speed);
  right_motor.forward(right_speed);
  delay(2000);
 }

void turn_r(){
  left_motor.forward(l_reverse);
  right_motor.reverse(r_reverse);
  delay(975);
}

void turn_l(){
  left_motor.reverse(l_reverse);
  right_motor.forward(r_reverse);
  delay(800);
}
void stop_rover(){
  left_motor.stop();
  right_motor.stop();
  delay(900);
}
void fullstop(){
  left_motor.stop();
  right_motor.stop();
  }


void left_motor_pulse_interrupt()
{
  left_motor.inc_pulse();
}

void right_motor_pulse_interrupt()
{
  right_motor.inc_pulse();
}
