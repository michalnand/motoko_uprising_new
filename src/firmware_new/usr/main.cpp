#include "device.h"
#include <clock.h>
#include <gpio.h>
#include <low_level_drivers.h>

#include <motor_controll.h>

#include <fmath.h>

 
#define LED_GPIO        TGPIOD
#define LED_PIN         0

#define KEY_GPIO        TGPIOC
#define KEY_PIN         12
  

void speed_control()
{
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
    __asm("nop");
  }
}



void position_controll()
{
  float p = 0.055;
  float i = -0.01;
  float d = -0.002; 
 
  float k1 = p;
  float k2 = -p + i;
  float k3 = d;

  
  unsigned int step = 0;
  while (1)
  {
    float required_position = 0;

    switch(step)
    { 
      case 0: required_position = ENCODER_DRIVER_WHEEL_CIRCUMFERENCE/4; break;
      case 1: required_position = 0; break;
      case 2: required_position = -ENCODER_DRIVER_WHEEL_CIRCUMFERENCE/4; break;
      case 3: required_position = 0; break;
    }
 
    for (unsigned int i = 0; i < 200; i++) 
    {
      float position = encoder_driver.get_left();
      float speed    = encoder_driver.get_left_speed();

      float u = k1*required_position + k2*position + k3*speed;

      motor_driver.left_set(u*MOTOR_PWM_MAX);

      timer.delay_ms(2);
    }

    step = (step+1)%4;
  }
}


void identification(unsigned int total_steps)
{

  float brace = 78;


  float values[] = {0.0, -0.2, -0.3, -0.35, -0.4, -0.45, 0.2, 0.3, 0.35, 0.4, 0.45};

  float ul = 0.0;
  float ur = 0.0; 

  for (unsigned int step = 0; step < total_steps; step++)
  {
    if ((step%50) == 0)
    {
      ul = values[rand()%11];
      ur = values[rand()%11];
    }

    auto left_speed     = encoder_driver.get_left_speed();
    auto right_speed    = encoder_driver.get_right_speed();

    auto left_position  = encoder_driver.get_left();
    auto right_position = encoder_driver.get_right();

    auto speed          = (left_speed + right_speed)/2.0;
    auto angular_rate   = (right_speed - left_speed)/brace;
    auto angle          = (right_position - left_position)/brace;

    terminal << step << ", " << timer.get_time() << ", " << ul << ", " << ur << ", " ;
    terminal << left_speed << ", " << right_speed << ", ";
    terminal << left_position << ", " << left_position << ", ";
    terminal << speed << ", " << angular_rate << ", " << angle << "\n";

    timer.delay_ms(4);

    motor_driver.left_set(ul*MOTOR_PWM_MAX);
    motor_driver.right_set(ur*MOTOR_PWM_MAX);
  }

  motor_driver.left_set(0);
  motor_driver.left_set(0);
}


        
int main(void) 
{
  SetSysClock(SysClok216_8HSE);

  Gpio<LED_GPIO, LED_PIN, GPIO_MODE_OUT> led;        //user led
  led = 1; 

  low_level_drivers.init(); 

  terminal << "machine ready\n\n";
  
  //Gpio<KEY_GPIO, KEY_PIN, GPIO_MODE_IN_PULLUP> key;  //user button
  //Gpio<TGPIOE, 14, GPIO_MODE_OUT> sensor_led;        //sensor white led

  timer.delay_ms(1000);
  
  identification(2000);

  while (1)
  {
    led = 1; 
    timer.delay_ms(100);

    led = 0; 
    timer.delay_ms(100); 
  }

  return 0;
} 