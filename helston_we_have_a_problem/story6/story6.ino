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

  int distance_forward = sensor.forward();
  Serial.begin(115200);
  pinMode(interrupt_pin_2, INPUT_PULLUP);
  pinMode(interrupt_pin_3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_2), left_motor_pulse_interrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_3), right_motor_pulse_interrupt, RISING);
}

// Draws a star
void loop()

{ 
  forwards();
 int distance_forward = sensor.forward();
  Serial.println(distance_forward);
  if ( distance_forward <= 15 && distance_forward >= 10) {
    Serial.println("stop");
    stop_rover();
    spin();
    stop_rover();
    reverse();
    stop_rover();
    half_spin();
    stop_rover();
    exit (0);
  }  
      
  
} 



// Functions below here

void forwards(){
  left_motor.forward(left_speed);
  right_motor.forward(right_speed);
}

void reverse(){
  left_motor.reverse(255);
  right_motor.reverse(255);
  delay(950);
  
 }

void spin(){
  left_motor.forward(l_reverse);
  right_motor.reverse(r_reverse);
  delay (3500);
}

void half_spin(){
  left_motor.reverse(l_reverse);
  right_motor.forward(r_reverse);
  delay(1600);
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
