#ifndef _ADC_DRIVER_H_
#define _ADC_DRIVER_H_

#define ADC_LINE_0                 ((unsigned int)ADC_Channel_0)    //PA0
#define ADC_LINE_1                 ((unsigned int)ADC_Channel_1)    //PA1
#define ADC_LINE_2                 ((unsigned int)ADC_Channel_2)    //PA2
#define ADC_LINE_3                 ((unsigned int)ADC_Channel_3)    //PA3
#define ADC_LINE_4                 ((unsigned int)ADC_Channel_4)    //PA4
#define ADC_LINE_5                 ((unsigned int)ADC_Channel_5)    //PA5
#define ADC_LINE_6                 ((unsigned int)ADC_Channel_6)    //PA6
#define ADC_LINE_7                 ((unsigned int)ADC_Channel_7)    //PA7

#define ADC_FRONT                  ((unsigned int)ADC_Channel_14)   
#define ADC_RIGHT                  ((unsigned int)ADC_Channel_15)   
#define ADC_LEFT                   ((unsigned int)ADC_Channel_8)     
 
class ADC_driver
{
    public:
        ADC_driver();
        virtual ~ADC_driver();

        void init();
        int read(unsigned int channel);


    private:
        void adc_init();
        void gpio_init();
};


#endif
