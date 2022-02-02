
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F7xx_DBGMCU_H
#define __STM32F7xx_DBGMCU_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx.h"

/** @addtogroup STM32F7xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup DBGMCU
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup DBGMCU_Exported_Constants
  * @{
  */ 
#define DBGMCU_SLEEP                 (DBGMCU_CR_DBG_SLEEP)
#define DBGMCU_STOP                  (DBGMCU_CR_DBG_STOP)
#define DBGMCU_STANDBY               (DBGMCU_CR_DBG_STANDBY)
#define IS_DBGMCU_PERIPH(PERIPH) ((((PERIPH) & 0xFFFFFFF8) == 0x00) && ((PERIPH) != 0x00))

#define DBGMCU_TIM2_STOP             (DBGMCU_APB1_FZ_DBG_TIM2_STOP)
#define DBGMCU_TIM3_STOP             (DBGMCU_APB1_FZ_DBG_TIM3_STOP)
#define DBGMCU_TIM4_STOP             (DBGMCU_APB1_FZ_DBG_TIM4_STOP)
#define DBGMCU_TIM5_STOP             (DBGMCU_APB1_FZ_DBG_TIM5_STOP)
#define DBGMCU_TIM6_STOP             (DBGMCU_APB1_FZ_DBG_TIM6_STOP)
#define DBGMCU_TIM7_STOP             (DBGMCU_APB1_FZ_DBG_TIM7_STOP)
#define DBGMCU_TIM12_STOP            (DBGMCU_APB1_FZ_DBG_TIM12_STOP)
#define DBGMCU_TIM13_STOP            (DBGMCU_APB1_FZ_DBG_TIM13_STOP)
#define DBGMCU_TIM14_STOP            (DBGMCU_APB1_FZ_DBG_TIM14_STOP)
#define DBGMCU_RTC_STOP              (DBGMCU_APB1_FZ_DBG_RTC_STOP)
#define DBGMCU_WWDG_STOP             (DBGMCU_APB1_FZ_DBG_WWDG_STOP)
#define DBGMCU_IWDG_STOP             (DBGMCU_APB1_FZ_DBG_IWDG_STOP)
#define DBGMCU_I2C1_SMBUS_TIMEOUT    (DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT)
#define DBGMCU_I2C2_SMBUS_TIMEOUT    (DBGMCU_APB1_FZ_DBG_I2C2_SMBUS_TIMEOUT)
#define DBGMCU_I2C3_SMBUS_TIMEOUT    (DBGMCU_APB1_FZ_DBG_I2C3_SMBUS_TIMEOUT)
#define DBGMCU_CAN1_STOP             (DBGMCU_APB1_FZ_DBG_CAN1_STOP)
#define DBGMCU_CAN2_STOP             (DBGMCU_APB1_FZ_DBG_CAN2_STOP)
#define IS_DBGMCU_APB1PERIPH(PERIPH) ((((PERIPH) & 0xF91FE200) == 0x00) && ((PERIPH) != 0x00))

#define DBGMCU_TIM1_STOP             (DBGMCU_APB1_FZ_DBG_TIM1_STOP)
#define DBGMCU_TIM8_STOP             (DBGMCU_APB1_FZ_DBG_TIM8_STOP)
#define DBGMCU_TIM9_STOP             (DBGMCU_APB1_FZ_DBG_TIM9_STOP)
#define DBGMCU_TIM10_STOP            (DBGMCU_APB1_FZ_DBG_TIM10_STOP)
#define DBGMCU_TIM11_STOP            (DBGMCU_APB1_FZ_DBG_TIM11_STOP)
#define IS_DBGMCU_APB2PERIPH(PERIPH) ((((PERIPH) & 0xFFF8FFFC) == 0x00) && ((PERIPH) != 0x00))
/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
uint32_t DBGMCU_GetREVID(void);
uint32_t DBGMCU_GetDEVID(void);
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState);
void DBGMCU_APB1PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState);
void DBGMCU_APB2PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F7xx_DBGMCU_H */

/**
  * @}
  */ 

/**
  * @}
  */ 