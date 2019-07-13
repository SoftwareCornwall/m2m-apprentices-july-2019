#include <NewPing.h>
#include "Arduino.h"
#include "Sensor.h"

namespace {
  
}

Sensor::Sensor(){
  
}

float Sensor::forward()
{
  NewPing forward_sensor(forward_trigger, forward_echo, max_distance);
  return forward_sensor.ping() / US_ROUNDTRIP_CM;
}

float Sensor::down()
{
  NewPing down_sensor(down_trigger, down_echo, max_drop);
  return down_sensor.ping() / US_ROUNDTRIP_CM;
}

float Sensor::left_light_sensor()
{ 
  return analogRead(left_light_pin);
}

float Sensor::center_light_sensor()
{ 
  return analogRead(center_light_pin);
}

float Sensor::right_light_sensor()
{
  return analogRead(right_light_pin);
}

