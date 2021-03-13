
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F7xx_SYSCFG_H
#define __STM32F7xx_SYSCFG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx.h"

/** @addtogroup STM32F7xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup SYSCFG
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
  
/** @defgroup SYSCFG_Exported_Constants 
  * @{
  */ 

/** @defgroup SYSCFG_EXTI_Port_Sources 
  * @{
  */ 
#define EXTI_PortSourceGPIOA       ((uint8_t)0x00)
#define EXTI_PortSourceGPIOB       ((uint8_t)0x01)
#define EXTI_PortSourceGPIOC       ((uint8_t)0x02)
#define EXTI_PortSourceGPIOD       ((uint8_t)0x03)
#define EXTI_PortSourceGPIOE       ((uint8_t)0x04)
#define EXTI_PortSourceGPIOF       ((uint8_t)0x05)
#define EXTI_PortSourceGPIOG       ((uint8_t)0x06)
#define EXTI_PortSourceGPIOH       ((uint8_t)0x07)
#define EXTI_PortSourceGPIOI       ((uint8_t)0x08)
#define EXTI_PortSourceGPIOJ       ((uint8_t)0x09)
#define EXTI_PortSourceGPIOK       ((uint8_t)0x0A)

#define IS_EXTI_PORT_SOURCE(PORTSOURCE) (((PORTSOURCE) == EXTI_PortSourceGPIOA) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOB) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOC) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOD) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOE) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOF) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOG) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOH) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOI) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOJ) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOK))
                                         
/**
  * @}
  */ 

/** @defgroup SYSCFG_EXTI_Pin_Sources 
  * @{
  */ 
#define EXTI_PinSource0            ((uint8_t)0x00)
#define EXTI_PinSource1            ((uint8_t)0x01)
#define EXTI_PinSource2            ((uint8_t)0x02)
#define EXTI_PinSource3            ((uint8_t)0x03)
#define EXTI_PinSource4            ((uint8_t)0x04)
#define EXTI_PinSource5            ((uint8_t)0x05)
#define EXTI_PinSource6            ((uint8_t)0x06)
#define EXTI_PinSource7            ((uint8_t)0x07)
#define EXTI_PinSource8            ((uint8_t)0x08)
#define EXTI_PinSource9            ((uint8_t)0x09)
#define EXTI_PinSource10           ((uint8_t)0x0A)
#define EXTI_PinSource11           ((uint8_t)0x0B)
#define EXTI_PinSource12           ((uint8_t)0x0C)
#define EXTI_PinSource13           ((uint8_t)0x0D)
#define EXTI_PinSource14           ((uint8_t)0x0E)
#define EXTI_PinSource15           ((uint8_t)0x0F)
#define IS_EXTI_PIN_SOURCE(PINSOURCE) (((PINSOURCE) == EXTI_PinSource0)  || \
                                       ((PINSOURCE) == EXTI_PinSource1)  || \
                                       ((PINSOURCE) == EXTI_PinSource2)  || \
                                       ((PINSOURCE) == EXTI_PinSource3)  || \
                                       ((PINSOURCE) == EXTI_PinSource4)  || \
                                       ((PINSOURCE) == EXTI_PinSource5)  || \
                                       ((PINSOURCE) == EXTI_PinSource6)  || \
                                       ((PINSOURCE) == EXTI_PinSource7)  || \
                                       ((PINSOURCE) == EXTI_PinSource8)  || \
                                       ((PINSOURCE) == EXTI_PinSource9)  || \
                                       ((PINSOURCE) == EXTI_PinSource10) || \
                                       ((PINSOURCE) == EXTI_PinSource11) || \
                                       ((PINSOURCE) == EXTI_PinSource12) || \
                                       ((PINSOURCE) == EXTI_PinSource13) || \
                                       ((PINSOURCE) == EXTI_PinSource14) || \
                                       ((PINSOURCE) == EXTI_PinSource15))
/**
  * @}
  */ 

/** @defgroup SYSCFG_ETHERNET_Media_Interface 
  * @{
  */ 
#define SYSCFG_ETH_MediaInterface_MII    ((uint32_t)0x00000000)
#define SYSCFG_ETH_MediaInterface_RMII   ((uint32_t)SYSCFG_PMC_MII_RMII_SEL)

#define IS_SYSCFG_ETH_MEDIA_INTERFACE(INTERFACE) (((INTERFACE) == SYSCFG_ETH_MediaInterface_MII) || \
                                                 ((INTERFACE) == SYSCFG_ETH_MediaInterface_RMII))
/**
  * @}
  */ 

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
 
void       SYSCFG_DeInit(void);
void       SYSCFG_FMCMemorySwappingBank(FunctionalState NewState);
void       SYSCFG_EXTILineConfig(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex);
void       SYSCFG_ETH_MediaInterfaceConfig(uint32_t SYSCFG_ETH_MediaInterface); 
void       SYSCFG_CompensationCellCmd(FunctionalState NewState); 
FlagStatus SYSCFG_GetCompensationCellStatus(void);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F7xx_SYSCFG_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
