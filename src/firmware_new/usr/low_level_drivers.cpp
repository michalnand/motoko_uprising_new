#include "low_level_drivers.h"

LowLevel_drivers    low_level_drivers;
 
Terminal                    terminal;
Timer                       timer; 
TI2C<TGPIOD, 1, 2, 50>      i2c;
ADC_driver                  adc_driver;
Motor_driver                motor_driver;
EncoderDriver               encoder_driver;


LowLevel_drivers::LowLevel_drivers()
{
  
}

LowLevel_drivers::~LowLevel_drivers()
{

}
 
  
int LowLevel_drivers::init()
{
    terminal.init(115200, USART1);

    for (unsigned int i = 0; i < 32; i++)
    {
        terminal << "\n\n\n\n";
    }   

    terminal << "terminal init done\n";
    terminal << "CPU clock set to " << SystemCoreClock/1000000 << "MHz\n";

    terminal << "initializing memory \t\t";
    unsigned int mem_res = mem_init();
    terminal << "[done], heap start at " << mem_res << "\n"; 

    terminal << "initializing timer \t\t";
    timer.init();
    terminal << "[done]\n";

    terminal << "initializing i2c \t\t\t";
    i2c.init();
    terminal << "[done]\n";

    terminal << "initializing adc \t\t\t";
    adc_driver.init();
    terminal << "[done]\n";
 
    terminal << "initializing motors \t\t";
    motor_driver.init();
    terminal << "[done]\n";

    terminal << "initializing encoders \t\t";
    encoder_driver.init();
    terminal << "[done]\n";

    timer.delay_ms(100);     
    
    return 0;
}