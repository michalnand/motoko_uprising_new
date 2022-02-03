#ifndef _ADC_DRIVER_H_
#define _ADC_DRIVER_H_ 

#define ADC_CHANNELS_COUNT  ((uint32_t)(8 + 3))

//sensor indices in order as readed into result
#define IR_SENSOR_LINE_0                 ((unsigned int)0)    
#define IR_SENSOR_LINE_1                 ((unsigned int)1)
#define IR_SENSOR_LINE_2                 ((unsigned int)2)
#define IR_SENSOR_LINE_3                 ((unsigned int)3)
#define IR_SENSOR_LINE_4                 ((unsigned int)4)
#define IR_SENSOR_LINE_5                 ((unsigned int)5)
#define IR_SENSOR_LINE_6                 ((unsigned int)6)
#define IR_SENSOR_LINE_7                 ((unsigned int)7)

#define IR_SENSOR_FRONT                  ((unsigned int)8)   
#define IR_SENSOR_RIGHT                  ((unsigned int)9)   
#define IR_SENSOR_LEFT                   ((unsigned int)10)


//sensors physical channels
#define ADC_LINE_0                 ((unsigned int)ADC_Channel_0)    //PA0
#define ADC_LINE_1                 ((unsigned int)ADC_Channel_1)    //PA1
#define ADC_LINE_2                 ((unsigned int)ADC_Channel_2)    //PA2
#define ADC_LINE_3                 ((unsigned int)ADC_Channel_3)    //PA3
#define ADC_LINE_4                 ((unsigned int)ADC_Channel_4)    //PA4
#define ADC_LINE_5                 ((unsigned int)ADC_Channel_5)    //PA5
#define ADC_LINE_6                 ((unsigned int)ADC_Channel_6)    //PA6
#define ADC_LINE_7                 ((unsigned int)ADC_Channel_7)    //PA7

#define ADC_FRONT                  ((unsigned int)ADC_Channel_14)   //PC4
#define ADC_RIGHT                  ((unsigned int)ADC_Channel_15)   //PB0
#define ADC_LEFT                   ((unsigned int)ADC_Channel_8)    //PC5



class ADC_driver
{
    public:
        ADC_driver();
        virtual ~ADC_driver();

        void init();
        uint16_t* get();
};


#endif
