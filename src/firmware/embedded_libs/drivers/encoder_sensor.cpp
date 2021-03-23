#include "encoder_sensor.h"

#include <stm32f7xx_hal.h>

#include <sensors_config.h>

#ifdef __cplusplus
extern "C" {
#endif

volatile long int g_left_encoder, g_right_encoder;

/*
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
*/
#ifdef __cplusplus
}
#endif


EncoderSensor::EncoderSensor()
{

}

EncoderSensor::~EncoderSensor()
{

}


void EncoderSensor::init()
{
    g_left_encoder    = 0;
    g_right_encoder   = 0;

    /*
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
        GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_100MHz;
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
    */

    /*
    {
        GPIO_InitTypeDef GPIO_InitStruct;
        EXTI_InitTypeDef EXTI_InitStruct;
        NVIC_InitTypeDef NVIC_InitStruct;

        GPIO_InitStruct.GPIO_Mode   = GPIO_Mode_IN;
        GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP;
        GPIO_InitStruct.GPIO_Pin    = GPIO_Pin_4;
        GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;
        GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_100MHz;
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
    */

    /*
    //syscfg clock enable
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;


    RCC->AHB1ENR|= RCC_AHB1ENR_GPIOCEN;

    GPIO_InitTypeDef GPIO_left;

    GPIO_left.Pin       = GPIO_PIN_6;
    GPIO_left.Mode      = GPIO_MODE_IT_RISING_FALLING;
    GPIO_left.Pull      = GPIO_PULLUP;
    GPIO_left.Speed     = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIO_left);

    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

    RCC->AHB1ENR|= RCC_AHB1ENR_GPIOBEN;

    GPIO_InitTypeDef GPIO_right;

    GPIO_right.Pin      = GPIO_PIN_4;
    GPIO_right.Mode     = GPIO_MODE_IT_RISING_FALLING;
    GPIO_right.Pull     = GPIO_PULLUP;
    GPIO_right.Speed    = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_right);

    HAL_NVIC_SetPriority(EXTI4_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);
    */
}


int EncoderSensor::get_left()
{
  //__disable_irq();
  int tmp = g_left_encoder;
  //__enable_irq();

  int res = (tmp*ENCODER_SENSOR_WHEEL_CIRCUMFERENCE)/ENCODER_SENSOR_PULSES_PER_ROTATION;
  return res;
}

int EncoderSensor::get_right()
{
  //__disable_irq();
  int tmp = g_right_encoder;
  //__enable_irq();

  int res = (tmp*ENCODER_SENSOR_WHEEL_CIRCUMFERENCE)/ENCODER_SENSOR_PULSES_PER_ROTATION;
  return res;
}

int EncoderSensor::get_distance()
{
  return (get_left() + get_right())/2;
}

int EncoderSensor::get_left_no_atomic()
{
  int tmp = g_left_encoder;
  int res = (tmp*ENCODER_SENSOR_WHEEL_CIRCUMFERENCE)/ENCODER_SENSOR_PULSES_PER_ROTATION;
  return res;
}

int EncoderSensor::get_right_no_atomic()
{
  int tmp = g_right_encoder;
  int res = (tmp*ENCODER_SENSOR_WHEEL_CIRCUMFERENCE)/ENCODER_SENSOR_PULSES_PER_ROTATION;
  return res;
}
