#ifndef     _DEVICE_CONFIG_H_
#define     _DEVICE_CONFIG_H_

#define F_CPU               ((unsigned int)216000000)
//#define F_CPU             ((unsigned int)312000000)
#define TIMERS_COUNT        ((unsigned int)16)

#define LED_GPIO        TGPIOD
#define LED_PIN         0

#define KEY_GPIO                    TGPIOC
#define KEY_PIN                     12


//use usart1, on pins PA9 and PA10
#define   USART      USART1
#define   USART_BAUD            115200



#endif