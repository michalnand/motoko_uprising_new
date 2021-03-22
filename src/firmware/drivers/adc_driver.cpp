#include "adc_driver.h"
#include <stdint.h>
#include <stm32f7xx_hal.h>

ADCDriver::ADCDriver()
{

}

ADCDriver::~ADCDriver()
{

}

void ADCDriver::init()
{
    gpio_init();
    adc_init();
}


int ADCDriver::read(unsigned int channel)
{
    /*
    adcChannel.Channel = channel;
    HAL_ADC_ConfigChannel(&AdcHandle, &adcChannel);

    HAL_ADC_Start(&AdcHandle);

    while ((ADC1->SR&ADC_FLAG_EOC) == 0)
    {
        __asm("nop");
    }

    return ADC1->DR;
    */

    ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_15Cycles);
    ADC_SoftwareStartConv(ADC1);

    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
    { 

    }

    return ADC_GetConversionValue(ADC1);
}

void ADCDriver::adc_init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    ADC_InitTypeDef ADC_InitStruct;
    ADC_InitStruct.ADC_ScanConvMode =   DISABLE;
    ADC_InitStruct.ADC_Resolution   =   ADC_Resolution_12b;
    ADC_InitStruct.ADC_ContinuousConvMode   =   DISABLE;
    ADC_InitStruct.ADC_ExternalTrigConv     =   ADC_ExternalTrigConv_T1_CC1;
    ADC_InitStruct.ADC_ExternalTrigConvEdge =   ADC_ExternalTrigConvEdge_None;
    ADC_InitStruct.ADC_DataAlign            =   ADC_DataAlign_Right;
    ADC_InitStruct.ADC_NbrOfConversion      =   1;

    ADC_Init(ADC1, &ADC_InitStruct);
    ADC_Cmd(ADC1, ENABLE);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_15Cycles);

}

void ADCDriver::gpio_init()
{
    RCC->AHB1ENR|=  RCC_AHB1ENR_GPIOAEN|
                    RCC_AHB1ENR_GPIOBEN|
                    RCC_AHB1ENR_GPIOCEN;

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

   


    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
}
