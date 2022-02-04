#ifndef _LOW_LEVEL_DRIVERS_H_
#define _LOW_LEVEL_DRIVERS_H_

#include <gpio.h> 
#include <device.h> 

#include <thread.h>

#include <terminal.h>
#include <mem.h>
#include <timer.h>
#include <i2c.h>
#include <adc_driver.h>
#include <motor_driver.h>
#include <encoder_driver.h>



class LowLevel_drivers
{   
    public:
        LowLevel_drivers();
        virtual ~LowLevel_drivers();

        int init(); 
};

extern LowLevel_drivers low_level_drivers;

extern Terminal                     terminal;
extern Timer                        timer;
extern TI2C<TGPIOD, 1, 2, 50>       i2c;
extern ADC_driver                   adc_driver; 
extern Motor_driver                 motor_driver;
extern EncoderDriver                encoder_driver;
 

#endif