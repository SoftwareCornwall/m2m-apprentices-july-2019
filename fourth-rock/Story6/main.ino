#include "Arduino.h"
#include "Motor.h"
#include "Sensor.h"
// Too much on right turns, too much on left turns. Check video for ref
namespace
{
  const byte interrupt_pin_2 = 2;
  const byte interrupt_pin_3 = 3;

  auto speed = 200;
  auto speed_right = speed-10;
  auto speed_left = speed+10;
  boolean forward = false;
  //1 = forwards. 2 = right. 3 = left. 4 = stop. 5 = reverse.
  unsigned long last_complete = 0;
  int sequence[] = {
    1,4,2,2,2,2,4,5,4,2,2,4
  };
  int sequence_position = 0;

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
  left_motor.reset_pulse_count();
  right_motor.reset_pulse_count();
  sensor.forward();
}

//Figure of 8 task
void loop()
{
  if (sequence[sequence_position] == 1){
    //Makes the robot go forward
    if (left_motor.get_pulse_count() < right_motor.get_pulse_count()){
      right_motor.stop();
      left_motor.forward(speed_left);
    }
    if (left_motor.get_pulse_count() > right_motor.get_pulse_count()){
        left_motor.stop();
        right_motor.forward(speed_right);
    }
    if (left_motor.get_pulse_count() == right_motor.get_pulse_count()){
        left_motor.forward(speed_left);
        right_motor.forward(speed_right);
    }
    if (sensor.forward() < 20){
      left_motor.stop();
      right_motor.stop();
      last_complete = millis();
      sequence_position++; 
      left_motor.reset_pulse_count();
      right_motor.reset_pulse_count();
    }
  }
  //Reverse
    if (sequence[sequence_position] == 5){
    if (left_motor.get_pulse_count() < right_motor.get_pulse_count()){
      right_motor.stop();
      left_motor.reverse(speed_left);
    }
    if (left_motor.get_pulse_count() > right_motor.get_pulse_count()){
        left_motor.stop();
        right_motor.reverse(speed_right);
    }
    if (left_motor.get_pulse_count() == right_motor.get_pulse_count()){
        left_motor.reverse(speed_left);
        right_motor.reverse(speed_right);
    }
    if (last_complete + 1000 < millis()){
      left_motor.stop();
      right_motor.stop();
      last_complete = millis();
      sequence_position++; 
      left_motor.reset_pulse_count();
      right_motor.reset_pulse_count();
    }
  }
  //Right Turn
  if (sequence[sequence_position] == 2){
    left_motor.forward(speed_left);
    right_motor.reverse(speed_right);
    
    if (last_complete + 900 < millis()){
      left_motor.stop();
      right_motor.stop();
      last_complete = millis();
      sequence_position++; 
      left_motor.reset_pulse_count();
      right_motor.reset_pulse_count();
    }
  }
  //Left Turn
  if (sequence[sequence_position] == 3){
    right_motor.forward(speed_right);
    left_motor.reverse(speed_left);
    if (last_complete + 900 < millis()){
      left_motor.stop();
      right_motor.stop();
      last_complete = millis();
      sequence_position++;
      left_motor.reset_pulse_count();
      right_motor.reset_pulse_count();
    }
  }
  if (sequence[sequence_position] == 4){
      delay(1000);
      sequence_position++;
      last_complete = millis();
    }
    
  if (sequence_position > sizeof(sequence)){
    left_motor.stop();
    right_motor.stop();
  }
}

void left_motor_pulse_interrupt()
{
  left_motor.inc_pulse();
  
}

void right_motor_pulse_interrupt()
{
  right_motor.inc_pulse();
  right_motor.get_pulse_count();
}

/*
 
 {
  Stop the robots motors and wait a smidge
  

  Turn right for half a second
  

  Move robot backwards for one second
  left_motor.reverse(speed);
  right_motor.reverse(speed);
  delay(1000);
  
    // Turns the robot
  left_motor.forward(speed);
  right_motor.reverse(speed);
  delay(7500);
 }

  
 */
 

