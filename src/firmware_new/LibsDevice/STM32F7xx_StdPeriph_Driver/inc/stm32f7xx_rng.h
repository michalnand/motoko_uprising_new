
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F7xx_RNG_H
#define __STM32F7xx_RNG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx.h"

/** @addtogroup STM32F7xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup RNG
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/ 

/** @defgroup RNG_Exported_Constants
  * @{
  */
  
/** @defgroup RNG_flags_definition  
  * @{
  */ 
#define RNG_FLAG_DRDY               (RNG_SR_DRDY) /*!< Data ready */
#define RNG_FLAG_CECS               (RNG_SR_CECS) /*!< Clock error current status */
#define RNG_FLAG_SECS               (RNG_SR_SECS) /*!< Seed error current status */

#define IS_RNG_GET_FLAG(RNG_FLAG) (((RNG_FLAG) == RNG_FLAG_DRDY) || \
                                   ((RNG_FLAG) == RNG_FLAG_CECS) || \
                                   ((RNG_FLAG) == RNG_FLAG_SECS))
#define IS_RNG_CLEAR_FLAG(RNG_FLAG) (((RNG_FLAG) == RNG_FLAG_CECS) || \
                                    ((RNG_FLAG) == RNG_FLAG_SECS))
/**
  * @}
  */ 

/** @defgroup RNG_interrupts_definition   
  * @{
  */  
#define RNG_IT_CEI                  (RNG_SR_CEIS) /*!< Clock error interrupt */
#define RNG_IT_SEI                  (RNG_SR_SEIS) /*!< Seed error interrupt */

#define IS_RNG_IT(IT) (((IT) == RNG_IT_CEI) || \
                       ((IT) == RNG_IT_SEI))
#define IS_RNG_GET_IT(RNG_IT) (((RNG_IT) == RNG_IT_CEI) || ((RNG_IT) == RNG_IT_SEI))
/**
  * @}
  */ 

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 

/*  Function used to set the RNG configuration to the default reset state *****/ 
void RNG_DeInit(void);

/* Configuration function *****************************************************/
void RNG_Cmd(FunctionalState NewState);

/* Get 32 bit Random number function ******************************************/
uint32_t RNG_GetRandomNumber(void);

/* Interrupts and flags management functions **********************************/
void RNG_ITConfig(FunctionalState NewState);
FlagStatus RNG_GetFlagStatus(uint32_t RNG_FLAG);
void RNG_ClearFlag(uint32_t RNG_FLAG);
ITStatus RNG_GetITStatus(uint32_t RNG_IT);
void RNG_ClearITPendingBit(uint32_t RNG_IT);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F7xx_RNG_H */

/**
  * @}
  */ 

/**
  * @}
  */ 