#include <stdint.h>
#include <adc_driver.h>
#include <gpio.h>


volatile uint32_t g_adc_current_idx;
volatile uint16_t g_adc_channels[ADC_CHANNELS_COUNT];
volatile uint16_t g_adc_result[ADC_CHANNELS_COUNT];

#ifdef __cplusplus
extern "C" {
#endif

void AdcScanningDoneHandler() __attribute__ ((weak));

void AdcScanningDoneHandler()
{
    //called when all conversions done done
}
 
void ADC_IRQHandler(void)
{
    //read value
    g_adc_result[g_adc_current_idx] = ADC_GetConversionValue(ADC1);

    ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);

    g_adc_current_idx = (g_adc_current_idx + 1)%ADC_CHANNELS_COUNT;

    //callback call if cycle done
    if (g_adc_current_idx == 0)
    {
        AdcScanningDoneHandler();
    } 

    //triger next conversion
    ADC_RegularChannelConfig(ADC1, g_adc_channels[g_adc_current_idx], 1, ADC_SampleTime_480Cycles);
    ADC_SoftwareStartConv(ADC1);
}

#ifdef __cplusplus
}
#endif

ADC_driver::ADC_driver()
{

}

ADC_driver::~ADC_driver()
{

}

void ADC_driver::init()
{
    //clear results

    g_adc_current_idx  = 0; 

    for (unsigned int i = 0; i < ADC_CHANNELS_COUNT; i++)
    {
        g_adc_result[i] = 0;
    }

    //configure pins to analog input mode
    Gpio<TGPIOA, 0, GPIO_MODE_AN> adc_0;
    Gpio<TGPIOA, 1, GPIO_MODE_AN> adc_1;
    Gpio<TGPIOA, 2, GPIO_MODE_AN> adc_2;
    Gpio<TGPIOA, 3, GPIO_MODE_AN> adc_3;
    Gpio<TGPIOA, 4, GPIO_MODE_AN> adc_4;
    Gpio<TGPIOA, 5, GPIO_MODE_AN> adc_5;
    Gpio<TGPIOA, 6, GPIO_MODE_AN> adc_6;
    Gpio<TGPIOA, 7, GPIO_MODE_AN> adc_7;

    Gpio<TGPIOC, 4, GPIO_MODE_AN> ir_front;
    Gpio<TGPIOB, 0, GPIO_MODE_AN> adc_right;
    Gpio<TGPIOC, 5, GPIO_MODE_AN> adc_left;

    //channels mapping
    g_adc_channels[0]   = ADC_LINE_0;
    g_adc_channels[1]   = ADC_LINE_1;
    g_adc_channels[2]   = ADC_LINE_2;
    g_adc_channels[3]   = ADC_LINE_3;
    g_adc_channels[4]   = ADC_LINE_4;
    g_adc_channels[5]   = ADC_LINE_5;
    g_adc_channels[6]   = ADC_LINE_6;
    g_adc_channels[7]   = ADC_LINE_7;

    g_adc_channels[8]   = ADC_FRONT;
    g_adc_channels[9]   = ADC_RIGHT;
    g_adc_channels[10]  = ADC_LEFT;
    
    //ADC init
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);


    ADC_CommonInitTypeDef ADC_CommonInitStruct;
    ADC_CommonInitStruct.ADC_Mode               =   ADC_Mode_Independent;
    ADC_CommonInitStruct.ADC_Prescaler          =   ADC_Prescaler_Div8; 
    ADC_CommonInitStruct.ADC_DMAAccessMode      =   ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStruct.ADC_TwoSamplingDelay   =   ADC_TwoSamplingDelay_5Cycles;

    ADC_CommonInit(&ADC_CommonInitStruct);


    ADC_InitTypeDef ADC_InitStruct;
    ADC_InitStruct.ADC_ScanConvMode         =   DISABLE;
    ADC_InitStruct.ADC_Resolution           =   ADC_Resolution_12b;
    ADC_InitStruct.ADC_ContinuousConvMode   =   DISABLE;
    ADC_InitStruct.ADC_ExternalTrigConv     =   ADC_ExternalTrigConv_T1_CC1;
    ADC_InitStruct.ADC_ExternalTrigConvEdge =   ADC_ExternalTrigConvEdge_None;
    ADC_InitStruct.ADC_DataAlign            =   ADC_DataAlign_Right;
    ADC_InitStruct.ADC_NbrOfConversion      =   1;

    ADC_Init(ADC1, &ADC_InitStruct);

    ADC_RegularChannelConfig(ADC1, g_adc_channels[0], 1, ADC_SampleTime_15Cycles);
    ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);

    ADC_Cmd(ADC1, ENABLE);

    //configure and enable ADC1 interrupt
    NVIC_InitTypeDef         NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel                      = ADC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority           = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                   = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    //start first conversion
    ADC_SoftwareStartConv(ADC1);
}

uint16_t* ADC_driver::read()
{
    return (uint16_t*)g_adc_result;
}

/*
int ADC_driver::read_single(unsigned int channel)
{
    ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_15Cycles);
    ADC_SoftwareStartConv(ADC1);

    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
    { 

    }

    return ADC_GetConversionValue(ADC1);
}
*/
