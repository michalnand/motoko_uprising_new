
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F7xx_GPIO_H
#define __STM32F7xx_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx.h"

/** @addtogroup STM32F7xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup GPIO
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

#define IS_GPIO_ALL_PERIPH(PERIPH) (IS_GPIO_ALL_INSTANCE(PERIPH))

/** 
  * @brief  GPIO Configuration Mode enumeration 
  */   
typedef enum
{ 
  GPIO_Mode_IN   = 0x00, /*!< GPIO Input Mode */
  GPIO_Mode_OUT  = 0x01, /*!< GPIO Output Mode */
  GPIO_Mode_AF   = 0x02, /*!< GPIO Alternate function Mode */
  GPIO_Mode_AN   = 0x03  /*!< GPIO Analog Mode */
}GPIOMode_TypeDef;
#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_Mode_IN)  || ((MODE) == GPIO_Mode_OUT) || \
                            ((MODE) == GPIO_Mode_AF)|| ((MODE) == GPIO_Mode_AN))

/** 
  * @brief  GPIO Output type enumeration 
  */  
typedef enum
{ 
  GPIO_OType_PP = 0x00,
  GPIO_OType_OD = 0x01
}GPIOOType_TypeDef;
#define IS_GPIO_OTYPE(OTYPE) (((OTYPE) == GPIO_OType_PP) || ((OTYPE) == GPIO_OType_OD))


/** 
  * @brief  GPIO Output Maximum frequency enumeration 
  */  
typedef enum
{ 
  GPIO_Low_Speed     = 0x00, /*!< Low speed    */
  GPIO_Medium_Speed  = 0x01, /*!< Medium speed */
  GPIO_Fast_Speed    = 0x02, /*!< Fast speed   */
  GPIO_High_Speed    = 0x03  /*!< High speed   */
}GPIOSpeed_TypeDef;

/* Add legacy definition */
//#define  GPIO_Speed_2MHz    GPIO_Low_Speed    
//#define  GPIO_Speed_25MHz   GPIO_Medium_Speed 
//#define  GPIO_Speed_50MHz   GPIO_Fast_Speed 
//#define  GPIO_Speed_100MHz  GPIO_High_Speed  
  
#define IS_GPIO_SPEED(SPEED) (((SPEED) == GPIO_Low_Speed) || ((SPEED) == GPIO_Medium_Speed) || \
                              ((SPEED) == GPIO_Fast_Speed)||  ((SPEED) == GPIO_High_Speed)) 

/** 
  * @brief  GPIO Configuration PullUp PullDown enumeration 
  */ 
typedef enum
{ 
  GPIO_PuPd_NOPULL = 0x00,
  GPIO_PuPd_UP     = 0x01,
  GPIO_PuPd_DOWN   = 0x02
}GPIOPuPd_TypeDef;
#define IS_GPIO_PUPD(PUPD) (((PUPD) == GPIO_PuPd_NOPULL) || ((PUPD) == GPIO_PuPd_UP) || \
                            ((PUPD) == GPIO_PuPd_DOWN))

/** 
  * @brief  GPIO Bit SET and Bit RESET enumeration 
  */ 
typedef enum
{ 
  Bit_RESET = 0,
  Bit_SET
}BitAction;
#define IS_GPIO_BIT_ACTION(ACTION) (((ACTION) == Bit_RESET) || ((ACTION) == Bit_SET))


/** 
  * @brief   GPIO Init structure definition  
  */ 
typedef struct
{
  uint32_t GPIO_Pin;              /*!< Specifies the GPIO pins to be configured.
                                       This parameter can be any value of @ref GPIO_pins_define */

  GPIOMode_TypeDef GPIO_Mode;     /*!< Specifies the operating mode for the selected pins.
                                       This parameter can be a value of @ref GPIOMode_TypeDef */

  GPIOSpeed_TypeDef GPIO_Speed;   /*!< Specifies the speed for the selected pins.
                                       This parameter can be a value of @ref GPIOSpeed_TypeDef */

  GPIOOType_TypeDef GPIO_OType;   /*!< Specifies the operating output type for the selected pins.
                                       This parameter can be a value of @ref GPIOOType_TypeDef */

  GPIOPuPd_TypeDef GPIO_PuPd;     /*!< Specifies the operating Pull-up/Pull down for the selected pins.
                                       This parameter can be a value of @ref GPIOPuPd_TypeDef */
}GPIO_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup GPIO_Exported_Constants
  * @{
  */ 

/** @defgroup GPIO_pins_define 
  * @{
  */ 
#define GPIO_Pin_0                 ((uint16_t)0x0001)  /* Pin 0 selected */
#define GPIO_Pin_1                 ((uint16_t)0x0002)  /* Pin 1 selected */
#define GPIO_Pin_2                 ((uint16_t)0x0004)  /* Pin 2 selected */
#define GPIO_Pin_3                 ((uint16_t)0x0008)  /* Pin 3 selected */
#define GPIO_Pin_4                 ((uint16_t)0x0010)  /* Pin 4 selected */
#define GPIO_Pin_5                 ((uint16_t)0x0020)  /* Pin 5 selected */
#define GPIO_Pin_6                 ((uint16_t)0x0040)  /* Pin 6 selected */
#define GPIO_Pin_7                 ((uint16_t)0x0080)  /* Pin 7 selected */
#define GPIO_Pin_8                 ((uint16_t)0x0100)  /* Pin 8 selected */
#define GPIO_Pin_9                 ((uint16_t)0x0200)  /* Pin 9 selected */
#define GPIO_Pin_10                ((uint16_t)0x0400)  /* Pin 10 selected */
#define GPIO_Pin_11                ((uint16_t)0x0800)  /* Pin 11 selected */
#define GPIO_Pin_12                ((uint16_t)0x1000)  /* Pin 12 selected */
#define GPIO_Pin_13                ((uint16_t)0x2000)  /* Pin 13 selected */
#define GPIO_Pin_14                ((uint16_t)0x4000)  /* Pin 14 selected */
#define GPIO_Pin_15                ((uint16_t)0x8000)  /* Pin 15 selected */
#define GPIO_Pin_All               ((uint16_t)0xFFFF)  /* All pins selected */

#define GPIO_PIN_MASK              ((uint32_t)0x0000FFFF) /* PIN mask for assert test */
#define IS_GPIO_PIN(PIN)           (((PIN) & GPIO_PIN_MASK ) != (uint32_t)0x00)
#define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_Pin_0) || \
                              ((PIN) == GPIO_Pin_1) || \
                              ((PIN) == GPIO_Pin_2) || \
                              ((PIN) == GPIO_Pin_3) || \
                              ((PIN) == GPIO_Pin_4) || \
                              ((PIN) == GPIO_Pin_5) || \
                              ((PIN) == GPIO_Pin_6) || \
                              ((PIN) == GPIO_Pin_7) || \
                              ((PIN) == GPIO_Pin_8) || \
                              ((PIN) == GPIO_Pin_9) || \
                              ((PIN) == GPIO_Pin_10) || \
                              ((PIN) == GPIO_Pin_11) || \
                              ((PIN) == GPIO_Pin_12) || \
                              ((PIN) == GPIO_Pin_13) || \
                              ((PIN) == GPIO_Pin_14) || \
                              ((PIN) == GPIO_Pin_15))
/**
  * @}
  */ 


/** @defgroup GPIO_Pin_sources 
  * @{
  */ 
#define GPIO_PinSource0            ((uint8_t)0x00)
#define GPIO_PinSource1            ((uint8_t)0x01)
#define GPIO_PinSource2            ((uint8_t)0x02)
#define GPIO_PinSource3            ((uint8_t)0x03)
#define GPIO_PinSource4            ((uint8_t)0x04)
#define GPIO_PinSource5            ((uint8_t)0x05)
#define GPIO_PinSource6            ((uint8_t)0x06)
#define GPIO_PinSource7            ((uint8_t)0x07)
#define GPIO_PinSource8            ((uint8_t)0x08)
#define GPIO_PinSource9            ((uint8_t)0x09)
#define GPIO_PinSource10           ((uint8_t)0x0A)
#define GPIO_PinSource11           ((uint8_t)0x0B)
#define GPIO_PinSource12           ((uint8_t)0x0C)
#define GPIO_PinSource13           ((uint8_t)0x0D)
#define GPIO_PinSource14           ((uint8_t)0x0E)
#define GPIO_PinSource15           ((uint8_t)0x0F)

#define IS_GPIO_PIN_SOURCE(PINSOURCE) (((PINSOURCE) == GPIO_PinSource0) || \
                                       ((PINSOURCE) == GPIO_PinSource1) || \
                                       ((PINSOURCE) == GPIO_PinSource2) || \
                                       ((PINSOURCE) == GPIO_PinSource3) || \
                                       ((PINSOURCE) == GPIO_PinSource4) || \
                                       ((PINSOURCE) == GPIO_PinSource5) || \
                                       ((PINSOURCE) == GPIO_PinSource6) || \
                                       ((PINSOURCE) == GPIO_PinSource7) || \
                                       ((PINSOURCE) == GPIO_PinSource8) || \
                                       ((PINSOURCE) == GPIO_PinSource9) || \
                                       ((PINSOURCE) == GPIO_PinSource10) || \
                                       ((PINSOURCE) == GPIO_PinSource11) || \
                                       ((PINSOURCE) == GPIO_PinSource12) || \
                                       ((PINSOURCE) == GPIO_PinSource13) || \
                                       ((PINSOURCE) == GPIO_PinSource14) || \
                                       ((PINSOURCE) == GPIO_PinSource15))
/**
  * @}
  */ 

/** @defgroup GPIO_LL_EC_AF Alternate Function
  * @{
  */
#define GPIO_AF0                        (0x00U) /*!< Select alternate function 0 */
#define GPIO_AF1                        (0x01U) /*!< Select alternate function 1 */
#define GPIO_AF2                        (0x02U) /*!< Select alternate function 2 */
#define GPIO_AF3                        (0x03U) /*!< Select alternate function 3 */
#define GPIO_AF4                        (0x04U) /*!< Select alternate function 4 */
#define GPIO_AF5                        (0x05U) /*!< Select alternate function 5 */
#define GPIO_AF6                        (0x06U) /*!< Select alternate function 6 */
#define GPIO_AF7                        (0x07U) /*!< Select alternate function 7 */
#define GPIO_AF8                        (0x08U) /*!< Select alternate function 8 */
#define GPIO_AF9                        (0x09U) /*!< Select alternate function 9 */
#define GPIO_AF10                       (0x0AU) /*!< Select alternate function 10 */
#define GPIO_AF11                       (0x0BU) /*!< Select alternate function 11 */
#define GPIO_AF12                       (0x0CU) /*!< Select alternate function 12 */
#define GPIO_AF13                       (0x0DU) /*!< Select alternate function 13 */
#define GPIO_AF14                       (0x0EU) /*!< Select alternate function 14 */
#define GPIO_AF15                       (0x0FU) /*!< Select alternate function 15 */
/**
  * @}
  */

/** @defgroup GPIO_Alternate_function_selection GPIO Alternate Function Selection
  * @{
  */  

/** 
  * @brief   AF 0 selection  
  */ 
#define GPIO_AF0_RTC_50Hz      ((uint8_t)GPIO_AF0)  /* RTC_50Hz Alternate Function mapping              */
#define GPIO_AF0_MCO           ((uint8_t)GPIO_AF0)  /* MCO (MCO1 and MCO2) Alternate Function mapping   */
#define GPIO_AF0_SWJ           ((uint8_t)GPIO_AF0)  /* SWJ (SWD and JTAG) Alternate Function mapping    */
#define GPIO_AF0_TRACE         ((uint8_t)GPIO_AF0)  /* TRACE Alternate Function mapping                 */

/** 
  * @brief   AF 1 selection  
  */ 
#define GPIO_AF1_TIM1          ((uint8_t)GPIO_AF1)  /* TIM1 Alternate Function mapping */
#define GPIO_AF1_TIM2          ((uint8_t)GPIO_AF1)  /* TIM2 Alternate Function mapping */
#if defined(STM32F765xx) || defined(STM32F767xx) || defined(STM32F768Ax) || defined(STM32F769xx) || \
    defined(STM32F777xx) || defined(STM32F778Ax) || defined(STM32F779xx)
#define GPIO_AF1_I2C4          ((uint8_t)GPIO_AF1)  /* I2C4 Alternate Function mapping */
#define GPIO_AF1_UART5         ((uint8_t)GPIO_AF1)  /* UART5 Alternate Function mapping */
#endif /* STM32F765xx || STM32F767xx || STM32F768Ax || STM32F769xx */


/** 
  * @brief   AF 2 selection  
  */ 
#define GPIO_AF2_TIM3          ((uint8_t)GPIO_AF2)  /* TIM3 Alternate Function mapping */
#define GPIO_AF2_TIM4          ((uint8_t)GPIO_AF2)  /* TIM4 Alternate Function mapping */
#define GPIO_AF2_TIM5          ((uint8_t)GPIO_AF2)  /* TIM5 Alternate Function mapping */

/** 
  * @brief   AF 3 selection  
  */ 
#define GPIO_AF3_TIM8          ((uint8_t)GPIO_AF3)  /* TIM8 Alternate Function mapping  */
#define GPIO_AF3_TIM9          ((uint8_t)GPIO_AF3)  /* TIM9 Alternate Function mapping  */
#define GPIO_AF3_TIM10         ((uint8_t)GPIO_AF3)  /* TIM10 Alternate Function mapping */
#define GPIO_AF3_TIM11         ((uint8_t)GPIO_AF3)  /* TIM11 Alternate Function mapping */
#define GPIO_AF3_LPTIM1        ((uint8_t)GPIO_AF3)  /* LPTIM1 Alternate Function mapping */

#if defined(STM32F745xx) || defined(STM32F746xx) || defined(STM32F756xx) || defined(STM32F765xx) || \
    defined(STM32F767xx) || defined(STM32F768Ax) || defined(STM32F769xx) || defined(STM32F777xx) || \
    defined(STM32F778Ax) || defined(STM32F779xx)
#define GPIO_AF3_CEC           ((uint8_t)GPIO_AF3)  /* CEC Alternate Function mapping */
#endif
      
#if defined(STM32F765xx) || defined(STM32F767xx) || defined(STM32F768Ax) || defined(STM32F769xx) || \
    defined(STM32F777xx) || defined(STM32F778Ax) || defined(STM32F779xx)
#define GPIO_AF3_DFSDM1        ((uint8_t)GPIO_AF3)  /* DFSDM1 Alternate Function mapping */
#endif

/** 
  * @brief   AF 4 selection  
  */ 
#define GPIO_AF4_I2C1          ((uint8_t)GPIO_AF4)  /* I2C1 Alternate Function mapping */
#define GPIO_AF4_I2C2          ((uint8_t)GPIO_AF4)  /* I2C2 Alternate Function mapping */
#define GPIO_AF4_I2C3          ((uint8_t)GPIO_AF4)  /* I2C3 Alternate Function mapping */

#if defined(STM32F722xx) || defined(STM32F723xx) || defined(STM32F732xx) || defined(STM32F733xx) || \
    defined(STM32F765xx) || defined(STM32F767xx) || defined(STM32F768Ax) || defined(STM32F769xx) || \
    defined(STM32F777xx) || defined(STM32F778Ax) || defined(STM32F779xx)
#define GPIO_AF4_USART1        ((uint8_t)GPIO_AF4)  /* USART1 Alternate Function mapping */
#endif

#if defined(STM32F745xx) || defined(STM32F746xx) || defined(STM32F756xx) || defined(STM32F765xx) || \
    defined(STM32F767xx) || defined(STM32F768Ax) || defined(STM32F769xx) || defined(STM32F777xx) || \
    defined(STM32F778Ax) || defined(STM32F779xx)
#define GPIO_AF4_I2C4          ((uint8_t)GPIO_AF4)  /* I2C4 Alternate Function mapping */
#define GPIO_AF4_CEC           ((uint8_t)GPIO_AF4)  /* CEC Alternate Function mapping */
#endif

/** 
  * @brief   AF 5 selection  
  */ 
#define GPIO_AF5_SPI1          ((uint8_t)GPIO_AF5)  /* SPI1/I2S1 Alternate Function mapping   */
#define GPIO_AF5_SPI2          ((uint8_t)GPIO_AF5)  /* SPI2/I2S2 Alternate Function mapping   */
#define GPIO_AF5_SPI3          ((uint8_t)GPIO_AF5)  /* SPI3/I2S3 Alternate Function mapping   */
#define GPIO_AF5_SPI4          ((uint8_t)GPIO_AF5)  /* SPI4 Alternate Function mapping        */
#define GPIO_AF5_SPI5          ((uint8_t)GPIO_AF5)  /* SPI5 Alternate Function mapping        */
#if defined(STM32F745xx) || defined(STM32F746xx) || defined(STM32F756xx) || defined(STM32F765xx) || \
    defined(STM32F767xx) || defined(STM32F768Ax) || defined(STM32F769xx) || defined(STM32F777xx) || \
    defined(STM32F778Ax) || defined(STM32F779xx)
#define GPIO_AF5_SPI6          ((uint8_t)GPIO_AF5)  /* SPI6 Alternate Function mapping        */
#endif
/** 
  * @brief   AF 6 selection  
  */ 

#define GPIO_AF6_SPI3           ((uint8_t)GPIO_AF6)  /* SPI3/I2S3 Alternate Function mapping  */
#define GPIO_AF6_SAI1           ((uint8_t)GPIO_AF6)  /* SAI1 Alternate Function mapping       */

#if defined(STM32F722xx) || defined(STM32F723xx) || defined(STM32F732xx) || defined(STM32F733xx) || \
    defined(STM32F765xx) || defined(STM32F767xx) || defined(STM32F768Ax) || defined(STM32F769xx) || \
    defined(STM32F777xx) || defined(STM32F778Ax) || defined(STM32F779xx)
#define GPIO_AF6_UART4          ((uint8_t)GPIO_AF6)  /* UART4 Alternate Function mapping  */
#endif
#if defined(STM32F765xx) || defined(STM32F767xx) || defined(STM32F768Ax) || defined(STM32F769xx) || \
    defined(STM32F777xx) || defined(STM32F778Ax) || defined(STM32F779xx)
#define GPIO_AF6_DFSDM1         ((uint8_t)GPIO_AF6)  /* DFSDM1 Alternate Function mapping  */
#endif
      
/** 
  * @brief   AF 7 selection  
  */ 
#define GPIO_AF7_USART1        ((uint8_t)GPIO_AF7)  /* USART1 Alternate Function mapping     */
#define GPIO_AF7_USART2        ((uint8_t)GPIO_AF7)  /* USART2 Alternate Function mapping     */
#define GPIO_AF7_USART3        ((uint8_t)GPIO_AF7)  /* USART3 Alternate Function mapping     */
#define GPIO_AF7_UART5         ((uint8_t)GPIO_AF7)  /* UART5 Alternate Function mapping      */
#define GPIO_AF7_SPI2          ((uint8_t)GPIO_AF7)  /* SPI2 Alternate Function mapping       */
#define GPIO_AF7_SPI3          ((uint8_t)GPIO_AF7)  /* SPI3 Alternate Function mapping       */
#if defined(STM32F745xx) || defined(STM32F746xx) || defined(STM32F756xx) || defined(STM32F765xx) || \
    defined(STM32F767xx) || defined(STM32F768Ax) || defined(STM32F769xx) || defined(STM32F777xx) || \
    defined(STM32F778Ax) || defined(STM32F779xx)
#define GPIO_AF7_SPDIFRX        ((uint8_t)GPIO_AF7)  /* SPDIF-RX Alternate Function mapping   */
#endif
#if defined(STM32F765xx) || defined(STM32F767xx) || defined(STM32F768Ax) || defined(STM32F769xx) || \
    defined(STM32F777xx) || defined(STM32F778Ax) || defined(STM32F779xx)
#define GPIO_AF7_SPI6           ((uint8_t)GPIO_AF7)  /* SPI6 Alternate Function mapping  */
#define GPIO_AF7_DFSDM1         ((uint8_t)GPIO_AF7)  /* DFSDM1 Alternate Function mapping  */
#endif

/** 
  * @brief   AF 8 selection  
  */ 
#define GPIO_AF8_UART4         ((uint8_t)GPIO_AF8)  /* UART4 Alternate Function mapping  */
#define GPIO_AF8_UART5         ((uint8_t)GPIO_AF8)  /* UART5 Alternate Function mapping  */
#define GPIO_AF8_USART6        ((uint8_t)GPIO_AF8)  /* USART6 Alternate Function mapping */
#define GPIO_AF8_UART7         ((uint8_t)GPIO_AF8)  /* UART7 Alternate Function mapping  */
#define GPIO_AF8_UART8         ((uint8_t)GPIO_AF8)  /* UART8 Alternate Function mapping  */
#define GPIO_AF8_SAI2          ((uint8_t)GPIO_AF8)  /* SAI2 Alternate Function mapping  */

#if defined(STM32F745xx) || defined(STM32F746xx) || defined(STM32F756xx) || defined(STM32F765xx) || \
    defined(STM32F767xx) || defined(STM32F768Ax) || defined(STM32F769xx) || defined(STM32F777xx) || \
    defined(STM32F778Ax) || defined(STM32F779xx)
#define GPIO_AF8_SPDIFRX       ((uint8_t)GPIO_AF8)  /* SPIDIF-RX Alternate Function mapping  */
#endif
      
#if defined(STM32F765xx) || defined(STM32F767xx) || defined(STM32F768Ax) || defined(STM32F769xx) || \
    defined(STM32F777xx) || defined(STM32F778Ax) || defined(STM32F779xx)
#define GPIO_AF8_SPI6           ((uint8_t)GPIO_AF8)  /* SPI6 Alternate Function mapping  */
#define GPIO_AF8_DFSDM1         ((uint8_t)GPIO_AF8)  /* DFSDM1 Alternate Function mapping  */
#endif
    
/** 
  * @brief   AF 9 selection 
  */ 
#define GPIO_AF9_CAN1          ((uint8_t)GPIO_AF9)  /* CAN1 Alternate Function mapping    */
#define GPIO_AF9_TIM12         ((uint8_t)GPIO_AF9)  /* TIM12 Alternate Function mapping   */
#define GPIO_AF9_TIM13         ((uint8_t)GPIO_AF9)  /* TIM13 Alternate Function mapping   */
#define GPIO_AF9_TIM14         ((uint8_t)GPIO_AF9)  /* TIM14 Alternate Function mapping   */
#define GPIO_AF9_QUADSPI       ((uint8_t)GPIO_AF9)  /* QUADSPI Alternate Function mapping */

#if defined(STM32F745xx) || defined(STM32F746xx) || defined(STM32F756xx) || defined(STM32F765xx) || \
    defined(STM32F767xx) || defined(STM32F768Ax) || defined(STM32F769xx) || defined(STM32F777xx) || \
    defined(STM32F778Ax) || defined(STM32F779xx) 
#define GPIO_AF9_CAN2          ((uint8_t)GPIO_AF9)  /* CAN2 Alternate Function mapping    */
#endif
#if defined(STM32F746xx) || defined(STM32F756xx) || defined(STM32F767xx) || defined(STM32F768Ax) || \
    defined(STM32F769xx) || defined(STM32F777xx) || defined(STM32F778Ax) || defined(STM32F779xx)
#define GPIO_AF9_LTDC          ((uint8_t)GPIO_AF9)  /* LCD-TFT Alternate Function mapping */
#endif
#if defined(STM32F765xx) || defined(STM32F767xx) || defined(STM32F768Ax) || defined(STM32F769xx) || \
    defined(STM32F777xx) || defined(STM32F778Ax) || defined(STM32F779xx)
#define GPIO_AF9_FMC           ((uint8_t)GPIO_AF9)  /* FMC Alternate Function mapping */
#endif
      
/** 
  * @brief   AF 10 selection  
  */ 
#define GPIO_AF10_OTG_FS        ((uint8_t)GPIO_AF10)  /* OTG_FS Alternate Function mapping */
#define GPIO_AF10_OTG_HS        ((uint8_t)GPIO_AF10)  /* OTG_HS Alternate Function mapping */
#define GPIO_AF10_QUADSPI       ((uint8_t)GPIO_AF10)  /* QUADSPI Alternate Function mapping */
#define GPIO_AF10_SAI2          ((uint8_t)GPIO_AF10)  /* SAI2 Alternate Function mapping */
#if defined(STM32F722xx) || defined(STM32F723xx) || defined(STM32F732xx) || defined(STM32F733xx) || \
    defined(STM32F765xx) || defined(STM32F767xx) || defined(STM32F768Ax) || defined(STM32F769xx) || \
    defined(STM32F777xx) || defined(STM32F778Ax) || defined(STM32F779xx)
#define GPIO_AF10_SDMMC2        ((uint8_t)GPIO_AF10)  /* SDMMC2 Alternate Function mapping */
#endif
#if defined(STM32F765xx) || defined(STM32F767xx) || defined(STM32F768Ax) || defined(STM32F769xx) || \
    defined(STM32F777xx) || defined(STM32F778Ax) || defined(STM32F779xx)
#define GPIO_AF10_DFSDM1        ((uint8_t)GPIO_AF10)  /* DFSDM1 Alternate Function mapping */
#endif
#if defined(STM32F767xx) || defined(STM32F768Ax) || defined(STM32F769xx) || defined(STM32F777xx) || \
    defined(STM32F778Ax) || defined(STM32F779xx)
#define GPIO_AF10_LTDC          ((uint8_t)GPIO_AF10)  /* LCD-TFT Alternate Function mapping */
#endif

/** 
  * @brief   AF 11 selection  
  */ 
#if defined(STM32F722xx) || defined(STM32F723xx) || defined(STM32F732xx) || defined(STM32F733xx) || \
    defined(STM32F765xx) || defined(STM32F767xx) || defined(STM32F768Ax) || defined(STM32F769xx) || \
    defined(STM32F777xx) || defined(STM32F778Ax) || defined(STM32F779xx)
#define GPIO_AF11_SDMMC2        ((uint8_t)GPIO_AF11)  /* SDMMC2 Alternate Function mapping */
#endif
#if defined(STM32F745xx) || defined(STM32F746xx) || defined(STM32F756xx) || defined(STM32F765xx) || \
    defined(STM32F767xx) || defined(STM32F768Ax) || defined(STM32F769xx) || defined(STM32F777xx) || \
    defined(STM32F778Ax) || defined(STM32F779xx)
#define GPIO_AF11_ETH           ((uint8_t)GPIO_AF11)  /* ETHERNET Alternate Function mapping */
#endif
#if defined(STM32F765xx) || defined(STM32F767xx) || defined(STM32F768Ax) || defined(STM32F769xx) || \
    defined(STM32F777xx) || defined(STM32F778Ax) || defined(STM32F779xx)
#define GPIO_AF11_I2C4          ((uint8_t)GPIO_AF11)  /* I2C4 Alternate Function mapping */
#define GPIO_AF11_CAN3          ((uint8_t)GPIO_AF11)  /* CAN3 Alternate Function mapping */
#endif
/** 
  * @brief   AF 12 selection  
  */ 
#define GPIO_AF12_FMC           ((uint8_t)GPIO_AF12)  /* FMC Alternate Function mapping                      */
#define GPIO_AF12_OTG_HS_FS     ((uint8_t)GPIO_AF12)  /* OTG HS configured in FS, Alternate Function mapping */
#define GPIO_AF12_SDMMC1        ((uint8_t)GPIO_AF12)  /* SDMMC1 Alternate Function mapping                   */
#if defined(STM32F765xx) || defined(STM32F767xx) || defined(STM32F768Ax) || defined(STM32F769xx) || \
    defined(STM32F777xx) || defined(STM32F778Ax) || defined(STM32F779xx)
#define GPIO_AF12_UART7         ((uint8_t)GPIO_AF12)  /* UART7 Alternate Function mapping */
#endif
      
/** 
  * @brief   AF 13 selection  
  */ 
#define GPIO_AF13_DCMI          ((uint8_t)GPIO_AF13)  /* DCMI Alternate Function mapping */
#if defined(STM32F767xx) || defined(STM32F768Ax) || defined(STM32F769xx) || defined(STM32F777xx) || \
    defined(STM32F778Ax) || defined(STM32F779xx)
#define GPIO_AF13_LTDC          ((uint8_t)GPIO_AF13)  /* LTDC Alternate Function mapping */
#define GPIO_AF13_DSI           ((uint8_t)GPIO_AF13)  /* DSI Alternate Function mapping */
#endif
      
/** 
  * @brief   AF 14 selection  
  */
#if defined(STM32F746xx) || defined(STM32F756xx) || defined(STM32F767xx) || defined(STM32F768Ax) || \
    defined(STM32F769xx) || defined(STM32F777xx) || defined(STM32F778Ax) || defined(STM32F779xx)
#define GPIO_AF14_LTDC          ((uint8_t)GPIO_AF14)  /* LCD-TFT Alternate Function mapping */
#endif /* STM32F756xx || STM32F746xx */

/** 
  * @brief   AF 15 selection  
  */ 
#define GPIO_AF15_EVENTOUT      ((uint8_t)GPIO_AF15)  /* EVENTOUT Alternate Function mapping */


/**
  * @}
  */ 

/** @defgroup GPIOEx_IS_Alternat_function_selection GPIO Check Alternate Function
  * @{
  */
#if defined(STM32F722xx) || defined(STM32F723xx) || defined(STM32F732xx) || defined(STM32F733xx)
#define IS_GPIO_AF(AF)   (((AF) == GPIO_AF0) || ((AF) == GPIO_AF1) || ((AF) == GPIO_AF2) || \
                          ((AF) == GPIO_AF3) || ((AF) == GPIO_AF4) || ((AF) == GPIO_AF5) || \
                          ((AF) == GPIO_AF6) || ((AF) == GPIO_AF7) || ((AF) == GPIO_AF8) || \
                          ((AF) == GPIO_AF9) || ((AF) == GPIO_AF10)|| ((AF) == GPIO_AF11)|| \
                          ((AF) == GPIO_AF12)|| ((AF) == GPIO_AF15))
#endif
#if defined(STM32F745xx) || defined(STM32F746xx) || defined(STM32F756xx) || defined(STM32F765xx) || \
    defined(STM32F767xx) || defined(STM32F768Ax) || defined(STM32F769xx) || defined(STM32F777xx) || \
    defined(STM32F778Ax) || defined(STM32F779xx) 
#define IS_GPIO_AF(AF)   (((AF) == GPIO_AF0) || ((AF) == GPIO_AF1) || ((AF) == GPIO_AF2) || \
                          ((AF) == GPIO_AF3) || ((AF) == GPIO_AF4) || ((AF) == GPIO_AF5) || \
                          ((AF) == GPIO_AF6) || ((AF) == GPIO_AF7) || ((AF) == GPIO_AF8) || \
                          ((AF) == GPIO_AF9) || ((AF) == GPIO_AF10)|| ((AF) == GPIO_AF11)|| \
                          ((AF) == GPIO_AF12)|| ((AF) == GPIO_AF13)|| ((AF) == GPIO_AF14)|| \
                          ((AF) == GPIO_AF15))
#endif
/**
  * @}
  */ 

/** @defgroup GPIO_Legacy 
  * @{
  */
    
#define GPIO_Mode_AIN           GPIO_Mode_AN

#define GPIO_AF_OTG1_FS         GPIO_AF_OTG_FS
#define GPIO_AF_OTG2_HS         GPIO_AF_OTG_HS
#define GPIO_AF_OTG2_FS         GPIO_AF_OTG_HS_FS

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/*  Function used to set the GPIO configuration to the default reset state ****/
void GPIO_DeInit(GPIO_TypeDef* GPIOx);

/* Initialization and Configuration functions *********************************/
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/* GPIO Read and Write functions **********************************************/
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/* GPIO Alternate functions configuration function ****************************/
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F7xx_GPIO_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
