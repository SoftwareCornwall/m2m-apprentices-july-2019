#include "Arduino.h"
#include "Motor.h"
#include "Sensor.h"

namespace
{
  const byte interrupt_pin_2 = 2;
  const byte interrupt_pin_3 = 3;
  bool move_complete = false;
  auto left_speed = 181;
  auto right_speed = 200;
  

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
  delay(3000);
  pinMode(LED_BUILTIN, OUTPUT);
  int distanced = sensor.down(); //initialise
  int distancef = sensor.forward(); //initialise
}
 
void loop()
{
  sensordownsequence();
  moonwalk();
  leftninety();
  goforward(7000);
  figureeight();
  wheelie();
  wheelie();
  threesixty();
  wheelie();
  wheelie();
  spin();
  delay(20000);
}

void left_motor_pulse_interrupt()
{
     left_motor.inc_pulse();
}

void right_motor_pulse_interrupt()
{
    right_motor.inc_pulse();
}

//Figure of eight sequence
void figureeight()
{
  goforward(2000);
  leftninety();
  goforward(2000);
  leftninety();
  goforward(2000);
  leftninety();
  goforward(4000);
  rightninety();
  goforward(2000);
  rightninety();
  goforward(2000);
  rightninety();
  goforward(2000);
  stopmotors(500);
}

//Turn left ninety degrees
void leftninety()
{
  left_motor.reverse(left_speed);
  right_motor.forward(right_speed);
  delay (830);
  left_motor.stop();
  right_motor.stop();
  delay(500);
}

//Turn right ninety degrees
void rightninety()
{
  left_motor.forward(left_speed);
  right_motor.reverse(right_speed);
  delay (1000);
  left_motor.stop();
  right_motor.stop();
  delay(500);
}

//Timed go forward sequence
void goforward(int mydelay)
{
  left_motor.forward(left_speed);
  right_motor.forward(right_speed);
  delay(mydelay);
  left_motor.stop();
  right_motor.stop();
  delay (500);
}

//Timed period for motors to stop
void stopmotors(int mydelay)
{
  left_motor.stop();
  right_motor.stop();
  delay(mydelay);
} 

//Timed go backwards sequence
void gobackwards(int mydelay)
{
  left_motor.reverse(left_speed);
  right_motor.reverse(right_speed);
  delay(mydelay);
}

//Sensor down drop sequence 
void sensordownsequence()
{ 
  left_motor.forward(left_speed);
  right_motor.forward(right_speed);
  while(sensor.down()<15){delay(10);}
  stopmotors(2000);
  gobackwards(550);
  stopmotors(1000);
  oneeighty();
  goforward(2000);
 }

//Rover wheelie sequence
void wheelie()
{ 
  left_motor.reverse(255);
  right_motor.reverse(255);
  delay(200);
  left_motor.forward(255);
  right_motor.forward(255);
  delay(300);
  left_motor.stop();
  right_motor.stop();
  delay(300);
}

//Three hundred and sixty degree turn to the left
void threesixty()
{
  left_motor.reverse(left_speed);
  right_motor.forward(right_speed);
  delay (3600);
  left_motor.stop();
  right_motor.stop();
  delay(500);
}
//Constant spin
void spin()
{
  left_motor.reverse(255);
  right_motor.forward(255);
  delay (18000);
  left_motor.stop();
  right_motor.stop();
}

//One hundred and eighty degree turn to the left
void oneeighty()
{
  left_motor.reverse(left_speed);
  right_motor.forward(right_speed);
  delay (1950);
  left_motor.stop();
  right_motor.stop();
  delay(500);
}

//Rover moonwalk sequence
void moonwalk()
{
  left_motor.forward(left_speed);
  right_motor.forward(right_speed);
  while(sensor.forward()>9){delay(10);}
  threesixty();
  gobackwards(2000);
  oneeighty();
  delay(1000);
}

//Rover go forward with light
void followinglight()
{
//Scan Function
  float SL = sensor.left_light_sensor();
  float SC = sensor.center_light_sensor();
  float SR = sensor.right_light_sensor();
   float stot =SL+SC+SR;
  Serial.print ("LCR="); 
  Serial.print (SL);
  Serial.print(" ");
  Serial.print (SC);
  Serial.print(" ");
  Serial.print (SR);
  Serial.println(stot);
  
  if (stot < 600)
{ 
  left_motor.forward(left_speed);
  right_motor.forward(right_speed);
}
else{  
  left_motor.stop();
  right_motor.stop();
  delay(100);
}}
