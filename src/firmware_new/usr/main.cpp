#include "device.h"
#include <clock.h>
#include <gpio.h>
#include <low_level_drivers.h>

#include <motor_controll.h>
 
#define LED_GPIO        TGPIOD
#define LED_PIN         0

#define KEY_GPIO        TGPIOC
#define KEY_PIN         12
  
  
        
int main(void) 
{
  SetSysClock(SysClok216_8HSE);

  Gpio<LED_GPIO, LED_PIN, GPIO_MODE_OUT> led;        //user led
  led = 1; 

  low_level_drivers.init(); 

  terminal << "machine ready\n\n";
  
  //Gpio<KEY_GPIO, KEY_PIN, GPIO_MODE_IN_PULLUP> key;  //user button
  //Gpio<TGPIOE, 14, GPIO_MODE_OUT> sensor_led;        //sensor white led
  
  float speed_max      = 0.0;
  float dt             = 4;
  float t              = 0.0;
  float required_speed = 800.0;

  
  MotorControll motor_controll;
 

  motor_controll.init(0.0065, -0.0065 + 0.002, 0.02, 0.1); 

  motor_controll.left_set(required_speed);

  for (unsigned int i = 0; i < 100; i++)
  {
    float speed = encoder_driver.get_left_speed();
    terminal << t << " " << speed << "\n";
    

    t+= dt;

    if (speed > speed_max)
    {
      speed_max = speed;
    }

    timer.delay_ms(dt);
  }
  

  terminal << "\n\n";
  terminal << "speed_max = " << speed_max << "\n";

  motor_controll.left_set(0.0);

  while (1)
  {
    led = 1; 
    timer.delay_ms(100);

    led = 0; 
    timer.delay_ms(100); 
  }

  return 0;
} 