
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F7xx_IWDG_H
#define __STM32F7xx_IWDG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx.h"

/** @addtogroup STM32F7xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup IWDG
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup IWDG_Exported_Constants
  * @{
  */

/** @defgroup IWDG_WriteAccess
  * @{
  */

#define IWDG_WriteAccess_Enable     ((uint32_t)0x5555)
#define IWDG_WriteAccess_Disable    ((uint32_t)0x0000)
#define IS_IWDG_WRITE_ACCESS(ACCESS) (((ACCESS) == IWDG_WriteAccess_Enable) || \
                                      ((ACCESS) == IWDG_WriteAccess_Disable))
/**
  * @}
  */

/** @defgroup IWDG_prescaler 
  * @{
  */

#define IWDG_Prescaler_4            ((uint32_t)0x00)
#define IWDG_Prescaler_8            ((uint32_t)0x01)
#define IWDG_Prescaler_16           ((uint32_t)0x02)
#define IWDG_Prescaler_32           ((uint32_t)0x03)
#define IWDG_Prescaler_64           ((uint32_t)0x04)
#define IWDG_Prescaler_128          ((uint32_t)0x05)
#define IWDG_Prescaler_256          ((uint32_t)0x06)
#define IS_IWDG_PRESCALER(PRESCALER) (((PRESCALER) == IWDG_Prescaler_4)  || \
                                      ((PRESCALER) == IWDG_Prescaler_8)  || \
                                      ((PRESCALER) == IWDG_Prescaler_16) || \
                                      ((PRESCALER) == IWDG_Prescaler_32) || \
                                      ((PRESCALER) == IWDG_Prescaler_64) || \
                                      ((PRESCALER) == IWDG_Prescaler_128)|| \
                                      ((PRESCALER) == IWDG_Prescaler_256))
/**
  * @}
  */

/** @defgroup IWDG_Flag 
  * @{
  */

#define IWDG_FLAG_PVU               ((uint32_t)0x0001)
#define IWDG_FLAG_RVU               ((uint32_t)0x0002)
#define IWDG_FLAG_WVU               ((uint32_t)0x0002)
#define IS_IWDG_FLAG(FLAG) (((FLAG) == IWDG_FLAG_PVU) || ((FLAG) == IWDG_FLAG_RVU)  || \
                            ((FLAG) == IWDG_FLAG_WVU))
/**
  * @}
  */
  
/** @defgroup IWDG_Reload_Value
  * @{
  */
#define IS_IWDG_RELOAD(RELOAD) ((RELOAD) <= 0xFFF)

/**
  * @}
  */

/** @defgroup IWDG_CounterWindow_Value
  * @{
  */
#define IS_IWDG_WINDOW_VALUE(VALUE) ((VALUE) <= 0xFFF)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/* Prescaler and Counter configuration functions ******************************/
void IWDG_WriteAccessCmd(uint32_t IWDG_WriteAccess);
void IWDG_SetPrescaler(uint32_t IWDG_Prescaler);
void IWDG_SetReload(uint32_t Reload);
void IWDG_ReloadCounter(void);
void IWDG_SetWindowValue(uint32_t WindowValue);

/* IWDG activation function ***************************************************/
void IWDG_Enable(void);

/* Flag management function ***************************************************/
FlagStatus IWDG_GetFlagStatus(uint32_t IWDG_FLAG);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F7xx_IWDG_H */

/**
  * @}
  */

/**
  * @}
  */