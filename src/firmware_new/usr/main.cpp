#include "device.h"
#include <clock.h>
#include <gpio.h>
#include <low_level_drivers.h>
 
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
  
  Gpio<KEY_GPIO, KEY_PIN, GPIO_MODE_IN_PULLUP> key;  //user button
  Gpio<TGPIOE, 14, GPIO_MODE_OUT> sensor_led;        //sensor white led
 
  sensor_led  = 1; 
   
  while (1)
  {

    led = 1; 
    timer.delay_ms(100);

    led = 0; 
    timer.delay_ms(900);

    terminal << "conversion result \n";

    for (unsigned int i = 0; i < ADC_CHANNELS_COUNT; i++)
    {
      terminal << adc_driver.get()[i] << " ";
    }
    terminal << "\n";
    terminal << "time = " << timer.get_time() << "\n";

    terminal << "\n\n\n";    
  }
  

  return 0;
} 