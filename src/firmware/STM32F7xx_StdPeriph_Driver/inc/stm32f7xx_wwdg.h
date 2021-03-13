
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F7xx_WWDG_H
#define __STM32F7xx_WWDG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx.h"

/** @addtogroup STM32F7xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup WWDG
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup WWDG_Exported_Constants
  * @{
  */ 
  
/** @defgroup WWDG_Prescaler 
  * @{
  */
  
#define WWDG_Prescaler_1    ((uint32_t)0x00000000)
#define WWDG_Prescaler_2    ((uint32_t)WWDG_CFR_WDGTB_0)
#define WWDG_Prescaler_4    ((uint32_t)WWDG_CFR_WDGTB_1)
#define WWDG_Prescaler_8    ((uint32_t)WWDG_CFR_WDGTB)
#define IS_WWDG_PRESCALER(PRESCALER) (((PRESCALER) == WWDG_Prescaler_1) || \
                                      ((PRESCALER) == WWDG_Prescaler_2) || \
                                      ((PRESCALER) == WWDG_Prescaler_4) || \
                                      ((PRESCALER) == WWDG_Prescaler_8))
#define IS_WWDG_WINDOW_VALUE(VALUE) ((VALUE) <= 0x7F)
#define IS_WWDG_COUNTER(COUNTER) (((COUNTER) >= 0x40) && ((COUNTER) <= 0x7F))

/**
  * @}
  */ 

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
  
/*  Function used to set the WWDG configuration to the default reset state ****/  
void WWDG_DeInit(void);

/* Prescaler, Refresh window and Counter configuration functions **************/
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler);
void WWDG_SetWindowValue(uint32_t WindowValue);
void WWDG_EnableIT(void);
void WWDG_SetCounter(uint32_t Counter);

/* WWDG activation function ***************************************************/
void WWDG_Enable(uint32_t Counter);

/* Interrupts and flags management functions **********************************/
FlagStatus WWDG_GetFlagStatus(void);
void WWDG_ClearFlag(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F7xx_WWDG_H */

/**
  * @}
  */ 

/**
  * @}
  */ 