#include "encoder_driver.h"
#include <device.h>
#include <timer.h>

extern Timer                        timer;

#ifdef __cplusplus
extern "C" {
#endif

volatile long int g_left_encoder_prev, g_right_encoder_prev;
volatile long int g_left_encoder, g_right_encoder;

volatile float g_left_speed, g_right_speed;

void EXTI9_5_IRQHandler(void)
{
    unsigned int tmp = GPIOC->IDR;

    int way;
    if ( (((tmp&(1<<6)) == 0) && ((tmp&(1<<7)) == 0)) ||
         (((tmp&(1<<6)) != 0) && ((tmp&(1<<7)) != 0)) )
    {
        way = 1;
    }
    else
    {
        way = -1;
    }

    g_left_encoder+= way;

    EXTI_ClearITPendingBit(EXTI_Line6);
}

void EXTI4_IRQHandler()
{
    unsigned int tmp = GPIOB->IDR;

    int way;
    if ( (((tmp&(1<<4)) == 0) && ((tmp&(1<<5)) == 0)) ||
         (((tmp&(1<<4)) != 0) && ((tmp&(1<<5)) != 0)) )
    {
        way = -1;
    }
    else
    {
        way = 1;
    }

    g_right_encoder+= way;

    EXTI_ClearITPendingBit(EXTI_Line4);
}

#ifdef __cplusplus
}
#endif


EncoderDriver::EncoderDriver()
              :Thread()
{

}

EncoderDriver::~EncoderDriver()
{

}



void EncoderDriver::init()
{
    g_left_encoder_prev    = 0;
    g_right_encoder_prev   = 0;
    g_left_encoder         = 0;
    g_right_encoder        = 0;

    g_left_speed           = 0;
    g_right_speed          = 0;

    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    {
        GPIO_InitTypeDef GPIO_InitStruct;
        EXTI_InitTypeDef EXTI_InitStruct;
        NVIC_InitTypeDef NVIC_InitStruct;

        GPIO_InitStruct.GPIO_Mode   = GPIO_Mode_IN;
        GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP;
        GPIO_InitStruct.GPIO_Pin    = GPIO_Pin_6;
        GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;
        GPIO_InitStruct.GPIO_Speed  = GPIO_Fast_Speed;
        GPIO_Init(GPIOC, &GPIO_InitStruct);

        SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource6);

        EXTI_InitStruct.EXTI_Line = EXTI_Line6;
        EXTI_InitStruct.EXTI_LineCmd = ENABLE;
        EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
        EXTI_Init(&EXTI_InitStruct);

        NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
        NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
        NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;
        NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStruct);
    }

    {
        GPIO_InitTypeDef GPIO_InitStruct;
        EXTI_InitTypeDef EXTI_InitStruct;
        NVIC_InitTypeDef NVIC_InitStruct;

        GPIO_InitStruct.GPIO_Mode   = GPIO_Mode_IN;
        GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP;
        GPIO_InitStruct.GPIO_Pin    = GPIO_Pin_4;
        GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;
        GPIO_InitStruct.GPIO_Speed  = GPIO_Fast_Speed;
        GPIO_Init(GPIOB, &GPIO_InitStruct);

        SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource4);

        EXTI_InitStruct.EXTI_Line = EXTI_Line4;
        EXTI_InitStruct.EXTI_LineCmd = ENABLE;
        EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
        EXTI_Init(&EXTI_InitStruct);

        NVIC_InitStruct.NVIC_IRQChannel = EXTI4_IRQn;
        NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
        NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;
        NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStruct);
    }
    
    timer.add_task(this, ENCODER_SAMPLING_MS);
}


int EncoderDriver::get_left()
{
  //__disable_irq();
  int tmp = g_left_encoder;
  //__enable_irq();

  int res = (tmp*ENCODER_DRIVER_WHEEL_CIRCUMFERENCE)/ENCODER_DRIVER_PULSES_PER_ROTATION;
  return res;
}

int EncoderDriver::get_right()
{
  //__disable_irq();
  int tmp = g_right_encoder;
  //__enable_irq(); 

  int res = (tmp*ENCODER_DRIVER_WHEEL_CIRCUMFERENCE)/ENCODER_DRIVER_PULSES_PER_ROTATION;
  return res;
}

int EncoderDriver::get_distance()
{
  return (get_left() + get_right())/2;
}

int EncoderDriver::get_left_no_atomic()
{
  int tmp = g_left_encoder;
  int res = (tmp*ENCODER_DRIVER_WHEEL_CIRCUMFERENCE)/ENCODER_DRIVER_PULSES_PER_ROTATION;
  return res;
}

float EncoderDriver::get_left_speed()
{
  return g_left_speed;
}

float EncoderDriver::get_right_speed()
{
  return g_right_speed; 
} 


int EncoderDriver::get_right_no_atomic()
{
  int tmp = g_right_encoder;
  int res = (tmp*ENCODER_DRIVER_WHEEL_CIRCUMFERENCE)/ENCODER_DRIVER_PULSES_PER_ROTATION;
  return res;
} 

void EncoderDriver::main()
{
  //encoder pulses and time in [ms] to RPM speed
  int left_speed_   = ((g_left_encoder  - g_left_encoder_prev)*60*1000)/(ENCODER_SAMPLING_MS*ENCODER_DRIVER_PULSES_PER_ROTATION);
  int right_speed_  = ((g_right_encoder - g_right_encoder_prev)*60*1000)/(ENCODER_SAMPLING_MS*ENCODER_DRIVER_PULSES_PER_ROTATION);

  g_left_speed    = ENCODER_FILTER_K*g_left_speed   + (1.0 - ENCODER_FILTER_K)*left_speed_;
  g_right_speed   = ENCODER_FILTER_K*g_right_speed  + (1.0 - ENCODER_FILTER_K)*right_speed_;
  
  g_left_encoder_prev   = g_left_encoder;
  g_right_encoder_prev  = g_right_encoder;
}