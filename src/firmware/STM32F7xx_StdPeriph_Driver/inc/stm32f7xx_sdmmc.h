
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F7xx_SDMMC_H
#define __STM32F7xx_SDMMC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx.h"

/** @addtogroup STM32F7xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup SDMMC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

typedef struct
{
  uint32_t SDMMC_ClockEdge;            /*!< Specifies the clock transition on which the bit capture is made.
                                           This parameter can be a value of @ref SDMMC_Clock_Edge */

  uint32_t SDMMC_ClockBypass;          /*!< Specifies whether the SDMMC Clock divider bypass is
                                           enabled or disabled.
                                           This parameter can be a value of @ref SDMMC_Clock_Bypass */

  uint32_t SDMMC_ClockPowerSave;       /*!< Specifies whether SDMMC Clock output is enabled or
                                           disabled when the bus is idle.
                                           This parameter can be a value of @ref SDMMC_Clock_Power_Save */

  uint32_t SDMMC_BusWide;              /*!< Specifies the SDMMC bus width.
                                           This parameter can be a value of @ref SDMMC_Bus_Wide */

  uint32_t SDMMC_HardwareFlowControl;  /*!< Specifies whether the SDMMC hardware flow control is enabled or disabled.
                                           This parameter can be a value of @ref SDMMC_Hardware_Flow_Control */

  uint8_t SDMMC_ClockDiv;              /*!< Specifies the clock frequency of the SDMMC controller.
                                           This parameter can be a value between 0x00 and 0xFF. */
                                           
} SDMMC_InitTypeDef;

typedef struct
{
  uint32_t SDMMC_Argument;  /*!< Specifies the SDMMC command argument which is sent
                                to a card as part of a command message. If a command
                                contains an argument, it must be loaded into this register
                                before writing the command to the command register */

  uint32_t SDMMC_CmdIndex;  /*!< Specifies the SDMMC command index. It must be lower than 0x40. */

  uint32_t SDMMC_Response;  /*!< Specifies the SDMMC response type.
                                This parameter can be a value of @ref SDMMC_Response_Type */

  uint32_t SDMMC_Wait;      /*!< Specifies whether SDMMC wait for interrupt request is enabled or disabled.
                                This parameter can be a value of @ref SDMMC_Wait_Interrupt_State */

  uint32_t SDMMC_CPSM;      /*!< Specifies whether SDMMC Command path state machine (CPSM)
                                is enabled or disabled.
                                This parameter can be a value of @ref SDMMC_CPSM_State */
} SDMMC_CmdInitTypeDef;

typedef struct
{
  uint32_t SDMMC_DataTimeOut;    /*!< Specifies the data timeout period in card bus clock periods. */

  uint32_t SDMMC_DataLength;     /*!< Specifies the number of data bytes to be transferred. */
 
  uint32_t SDMMC_DataBlockSize;  /*!< Specifies the data block size for block transfer.
                                     This parameter can be a value of @ref SDMMC_Data_Block_Size */
 
  uint32_t SDMMC_TransferDir;    /*!< Specifies the data transfer direction, whether the transfer
                                     is a read or write.
                                     This parameter can be a value of @ref SDMMC_Transfer_Direction */
 
  uint32_t SDMMC_TransferMode;   /*!< Specifies whether data transfer is in stream or block mode.
                                     This parameter can be a value of @ref SDMMC_Transfer_Type */
 
  uint32_t SDMMC_DPSM;           /*!< Specifies whether SDMMC Data path state machine (DPSM)
                                     is enabled or disabled.
                                     This parameter can be a value of @ref SDMMC_DPSM_State */
} SDMMC_DataInitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup SDMMC_Exported_Constants
  * @{
  */

/* SDMMC Initialization Frequency (400KHz max) */
#define SDMMC_INIT_CLK_DIV ((uint8_t)0x76)

/* SDMMC Data Transfer Frequency (25MHz max) */
#define SDMMC_TRANSFER_CLK_DIV ((uint8_t)0x0)

/** @defgroup SDMMC_Clock_Edge 
  * @{
  */

#define SDMMC_ClockEdge_Rising               ((uint32_t)0x00000000)
#define SDMMC_ClockEdge_Falling              ((uint32_t)SDMMC_CLKCR_NEGEDGE)
#define IS_SDMMC_CLOCK_EDGE(EDGE) (((EDGE) == SDMMC_ClockEdge_Rising) || \
                                  ((EDGE) == SDMMC_ClockEdge_Falling))
/**
  * @}
  */

/** @defgroup SDMMC_Clock_Bypass 
  * @{
  */

#define SDMMC_ClockBypass_Disable             ((uint32_t)0x00000000)
#define SDMMC_ClockBypass_Enable              ((uint32_t)SDMMC_CLKCR_BYPASS)    
#define IS_SDMMC_CLOCK_BYPASS(BYPASS) (((BYPASS) == SDMMC_ClockBypass_Disable) || \
                                      ((BYPASS) == SDMMC_ClockBypass_Enable))
/**
  * @}
  */ 

/** @defgroup SDMMC_Clock_Power_Save 
  * @{
  */

#define SDMMC_ClockPowerSave_Disable         ((uint32_t)0x00000000)
#define SDMMC_ClockPowerSave_Enable          ((uint32_t)SDMMC_CLKCR_PWRSAV) 
#define IS_SDMMC_CLOCK_POWER_SAVE(SAVE) (((SAVE) == SDMMC_ClockPowerSave_Disable) || \
                                        ((SAVE) == SDMMC_ClockPowerSave_Enable))
/**
  * @}
  */

/** @defgroup SDMMC_Bus_Wide 
  * @{
  */

#define SDMMC_BusWide_1b                     ((uint32_t)0x00000000)
#define SDMMC_BusWide_4b                     ((uint32_t)SDMMC_CLKCR_WIDBUS_0)
#define SDMMC_BusWide_8b                     ((uint32_t)SDMMC_CLKCR_WIDBUS_1)
#define IS_SDMMC_BUS_WIDE(WIDE) (((WIDE) == SDMMC_BusWide_1b) || ((WIDE) == SDMMC_BusWide_4b) || \
                                ((WIDE) == SDMMC_BusWide_8b))

/**
  * @}
  */

/** @defgroup SDMMC_Hardware_Flow_Control 
  * @{
  */

#define SDMMC_HardwareFlowControl_Disable    ((uint32_t)0x00000000)
#define SDMMC_HardwareFlowControl_Enable     ((uint32_t)SDMMC_CLKCR_HWFC_EN)
#define IS_SDMMC_HARDWARE_FLOW_CONTROL(CONTROL) (((CONTROL) == SDMMC_HardwareFlowControl_Disable) || \
                                                ((CONTROL) == SDMMC_HardwareFlowControl_Enable))
/**
  * @}
  */

/** @defgroup SDMMC_Power_State 
  * @{
  */

#define SDMMC_PowerState_OFF                 ((uint32_t)0x00000000)
#define SDMMC_PowerState_ON                  ((uint32_t)SDMMC_POWER_PWRCTRL)
#define IS_SDMMC_POWER_STATE(STATE) (((STATE) == SDMMC_PowerState_OFF) || ((STATE) == SDMMC_PowerState_ON))
/**
  * @}
  */ 




/** @defgroup SDMMC_Command_Index
  * @{
  */
#define IS_SDMMC_CMD_INDEX(INDEX)            ((INDEX) < 0x40)
/**
  * @}
  */

/** @defgroup SDMMC_Response_Type
  * @{
  */

#define SDMMC_Response_No                    ((uint32_t)0x00000000)
#define SDMMC_Response_Short                 ((uint32_t)SDMMC_CMD_WAITRESP_0)
#define SDMMC_Response_Long                  ((uint32_t)SDMMC_CMD_WAITRESP)
#define IS_SDMMC_RESPONSE(RESPONSE) (((RESPONSE) == SDMMC_Response_No) || \
                                    ((RESPONSE) == SDMMC_Response_Short) || \
                                    ((RESPONSE) == SDMMC_Response_Long))
/**
  * @}
  */

/** @defgroup SDMMC_Wait_Interrupt_State
  * @{
  */

#define SDMMC_Wait_No                        ((uint32_t)0x00000000) /*!< SDMMC No Wait, TimeOut is enabled */
#define SDMMC_Wait_IT                        ((uint32_t)SDMMC_CMD_WAITINT) /*!< SDMMC Wait Interrupt Request */
#define SDMMC_Wait_Pend                      ((uint32_t)SDMMC_CMD_WAITPEND) /*!< SDMMC Wait End of transfer */
#define IS_SDMMC_WAIT(WAIT) (((WAIT) == SDMMC_Wait_No) || ((WAIT) == SDMMC_Wait_IT) || \
                            ((WAIT) == SDMMC_Wait_Pend))
/**
  * @}
  */

/** @defgroup SDMMC_CPSM_State
  * @{
  */

#define SDMMC_CPSM_Disable                    ((uint32_t)0x00000000)
#define SDMMC_CPSM_Enable                     ((uint32_t)SDMMC_CMD_CPSMEN)
#define IS_SDMMC_CPSM(CPSM) (((CPSM) == SDMMC_CPSM_Enable) || ((CPSM) == SDMMC_CPSM_Disable))
/**
  * @}
  */ 

/** @defgroup SDMMC_Response_Registers
  * @{
  */

#define SDMMC_RESP1                          ((uint32_t)0x00000000)
#define SDMMC_RESP2                          ((uint32_t)0x00000004)
#define SDMMC_RESP3                          ((uint32_t)0x00000008)
#define SDMMC_RESP4                          ((uint32_t)0x0000000C)
#define IS_SDMMC_RESP(RESP) (((RESP) == SDMMC_RESP1) || ((RESP) == SDMMC_RESP2) || \
                            ((RESP) == SDMMC_RESP3) || ((RESP) == SDMMC_RESP4))
/**
  * @}
  */

/** @defgroup SDMMC_Data_Length 
  * @{
  */

#define IS_SDMMC_DATA_LENGTH(LENGTH) ((LENGTH) <= 0x01FFFFFF)
/**
  * @}
  */

/** @defgroup SDMMC_LL_Data_Block_Size  Data Block Size
  * @{
  */
#define SDMMC_DataBlockSize_1b               ((uint32_t)0x00000000)
#define SDMMC_DataBlockSize_2b               SDMMC_DCTRL_DBLOCKSIZE_0
#define SDMMC_DataBlockSize_4b               SDMMC_DCTRL_DBLOCKSIZE_1
#define SDMMC_DataBlockSize_8b               (SDMMC_DCTRL_DBLOCKSIZE_0|SDMMC_DCTRL_DBLOCKSIZE_1)
#define SDMMC_DataBlockSize_16b              SDMMC_DCTRL_DBLOCKSIZE_2
#define SDMMC_DataBlockSize_32b              (SDMMC_DCTRL_DBLOCKSIZE_0|SDMMC_DCTRL_DBLOCKSIZE_2)
#define SDMMC_DataBlockSize_64b              (SDMMC_DCTRL_DBLOCKSIZE_1|SDMMC_DCTRL_DBLOCKSIZE_2)
#define SDMMC_DataBlockSize_128b             (SDMMC_DCTRL_DBLOCKSIZE_0|SDMMC_DCTRL_DBLOCKSIZE_1|SDMMC_DCTRL_DBLOCKSIZE_2)
#define SDMMC_DataBlockSize_256b             SDMMC_DCTRL_DBLOCKSIZE_3
#define SDMMC_DataBlockSize_512b             (SDMMC_DCTRL_DBLOCKSIZE_0|SDMMC_DCTRL_DBLOCKSIZE_3)
#define SDMMC_DataBlockSize_1024b            (SDMMC_DCTRL_DBLOCKSIZE_1|SDMMC_DCTRL_DBLOCKSIZE_3)
#define SDMMC_DataBlockSize_2048b            (SDMMC_DCTRL_DBLOCKSIZE_0|SDMMC_DCTRL_DBLOCKSIZE_1|SDMMC_DCTRL_DBLOCKSIZE_3) 
#define SDMMC_DataBlockSize_4096b            (SDMMC_DCTRL_DBLOCKSIZE_2|SDMMC_DCTRL_DBLOCKSIZE_3)
#define SDMMC_DataBlockSize_8192b            (SDMMC_DCTRL_DBLOCKSIZE_0|SDMMC_DCTRL_DBLOCKSIZE_2|SDMMC_DCTRL_DBLOCKSIZE_3)
#define SDMMC_DataBlockSize_16384b           (SDMMC_DCTRL_DBLOCKSIZE_1|SDMMC_DCTRL_DBLOCKSIZE_2|SDMMC_DCTRL_DBLOCKSIZE_3)

#define IS_SDMMC_BLOCK_SIZE(SIZE) (((SIZE) == SDMMC_DataBlockSize_1b)    || \
                                  ((SIZE) == SDMMC_DataBlockSize_2b)    || \
                                  ((SIZE) == SDMMC_DataBlockSize_4b)    || \
                                  ((SIZE) == SDMMC_DataBlockSize_8b)    || \
                                  ((SIZE) == SDMMC_DataBlockSize_16b)   || \
                                  ((SIZE) == SDMMC_DataBlockSize_32b)   || \
                                  ((SIZE) == SDMMC_DataBlockSize_64b)   || \
                                  ((SIZE) == SDMMC_DataBlockSize_128b)  || \
                                  ((SIZE) == SDMMC_DataBlockSize_256b)  || \
                                  ((SIZE) == SDMMC_DataBlockSize_512b)  || \
                                  ((SIZE) == SDMMC_DataBlockSize_1024b) || \
                                  ((SIZE) == SDMMC_DataBlockSize_2048b) || \
                                  ((SIZE) == SDMMC_DataBlockSize_4096b) || \
                                  ((SIZE) == SDMMC_DataBlockSize_8192b) || \
                                  ((SIZE) == SDMMC_DataBlockSize_16384b)) 
/**
  * @}
  */

/** @defgroup SDMMC_Transfer_Direction 
  * @{
  */

#define SDMMC_TransferDir_ToCard             ((uint32_t)0x00000000)
#define SDMMC_TransferDir_ToSDMMC             ((uint32_t)SDMMC_DCTRL_DTDIR)
#define IS_SDMMC_TRANSFER_DIR(DIR) (((DIR) == SDMMC_TransferDir_ToCard) || \
                                   ((DIR) == SDMMC_TransferDir_ToSDMMC))
/**
  * @}
  */

/** @defgroup SDMMC_Transfer_Type 
  * @{
  */

#define SDMMC_TransferMode_Block             ((uint32_t)0x00000000)
#define SDMMC_TransferMode_Stream            ((uint32_t)SDMMC_DCTRL_DTMODE)
#define IS_SDMMC_TRANSFER_MODE(MODE) (((MODE) == SDMMC_TransferMode_Stream) || \
                                     ((MODE) == SDMMC_TransferMode_Block))
/**
  * @}
  */

/** @defgroup SDMMC_DPSM_State 
  * @{
  */

#define SDMMC_DPSM_Disable                    ((uint32_t)0x00000000)
#define SDMMC_DPSM_Enable                     ((uint32_t)SDMMC_DCTRL_DTEN)
#define IS_SDMMC_DPSM(DPSM) (((DPSM) == SDMMC_DPSM_Enable) || ((DPSM) == SDMMC_DPSM_Disable))
/**
  * @}
  */



  
/** @defgroup SDMMC_Read_Wait_Mode 
  * @{
  */

#define SDMMC_ReadWaitMode_DATA2             ((uint32_t)0x00000000)
#define SDMMC_ReadWaitMode_CLK               ((uint32_t)SDMMC_DCTRL_RWMOD)
#define IS_SDMMC_READWAIT_MODE(MODE) (((MODE) == SDMMC_ReadWaitMode_CLK) || \
                                     ((MODE) == SDMMC_ReadWaitMode_DATA2))
/**
  * @}
  */

/** @defgroup SDMMC_Interrupt_sources
  * @{
  */

#define SDMMC_IT_CCRCFAIL                    SDMMC_STA_CCRCFAIL
#define SDMMC_IT_DCRCFAIL                    SDMMC_STA_DCRCFAIL
#define SDMMC_IT_CTIMEOUT                    SDMMC_STA_CTIMEOUT
#define SDMMC_IT_DTIMEOUT                    SDMMC_STA_DTIMEOUT
#define SDMMC_IT_TXUNDERR                    SDMMC_STA_TXUNDERR
#define SDMMC_IT_RXOVERR                     SDMMC_STA_RXOVERR
#define SDMMC_IT_CMDREND                     SDMMC_STA_CMDREND
#define SDMMC_IT_CMDSENT                     SDMMC_STA_CMDSENT
#define SDMMC_IT_DATAEND                     SDMMC_STA_DATAEND
#define SDMMC_IT_DBCKEND                     SDMMC_STA_DBCKEND
#define SDMMC_IT_CMDACT                      SDMMC_STA_CMDACT
#define SDMMC_IT_TXACT                       SDMMC_STA_TXACT
#define SDMMC_IT_RXACT                       SDMMC_STA_RXACT
#define SDMMC_IT_TXFIFOHE                    SDMMC_STA_TXFIFOHE
#define SDMMC_IT_RXFIFOHF                    SDMMC_STA_RXFIFOHF
#define SDMMC_IT_TXFIFOF                     SDMMC_STA_TXFIFOF
#define SDMMC_IT_RXFIFOF                     SDMMC_STA_RXFIFOF
#define SDMMC_IT_TXFIFOE                     SDMMC_STA_TXFIFOE
#define SDMMC_IT_RXFIFOE                     SDMMC_STA_RXFIFOE
#define SDMMC_IT_TXDAVL                      SDMMC_STA_TXDAVL
#define SDMMC_IT_RXDAVL                      SDMMC_STA_RXDAVL
#define SDMMC_IT_SDIOIT                      SDMMC_STA_SDIOIT
#define IS_SDMMC_IT(IT) ((((IT) & (uint32_t)0xFF000000) == 0x00) && ((IT) != (uint32_t)0x00))
/**
  * @}
  */ 
    
/** @defgroup SDMMC_Flags 
  * @{
  */
#define SDMMC_FLAG_CCRCFAIL                  SDMMC_STA_CCRCFAIL
#define SDMMC_FLAG_DCRCFAIL                  SDMMC_STA_DCRCFAIL
#define SDMMC_FLAG_CTIMEOUT                  SDMMC_STA_CTIMEOUT
#define SDMMC_FLAG_DTIMEOUT                  SDMMC_STA_DTIMEOUT
#define SDMMC_FLAG_TXUNDERR                  SDMMC_STA_TXUNDERR
#define SDMMC_FLAG_RXOVERR                   SDMMC_STA_RXOVERR
#define SDMMC_FLAG_CMDREND                   SDMMC_STA_CMDREND
#define SDMMC_FLAG_CMDSENT                   SDMMC_STA_CMDSENT
#define SDMMC_FLAG_DATAEND                   SDMMC_STA_DATAEND
#define SDMMC_FLAG_DBCKEND                   SDMMC_STA_DBCKEND
#define SDMMC_FLAG_CMDACT                    SDMMC_STA_CMDACT
#define SDMMC_FLAG_TXACT                     SDMMC_STA_TXACT
#define SDMMC_FLAG_RXACT                     SDMMC_STA_RXACT
#define SDMMC_FLAG_TXFIFOHE                  SDMMC_STA_TXFIFOHE
#define SDMMC_FLAG_RXFIFOHF                  SDMMC_STA_RXFIFOHF
#define SDMMC_FLAG_TXFIFOF                   SDMMC_STA_TXFIFOF
#define SDMMC_FLAG_RXFIFOF                   SDMMC_STA_RXFIFOF
#define SDMMC_FLAG_TXFIFOE                   SDMMC_STA_TXFIFOE
#define SDMMC_FLAG_RXFIFOE                   SDMMC_STA_RXFIFOE
#define SDMMC_FLAG_TXDAVL                    SDMMC_STA_TXDAVL
#define SDMMC_FLAG_RXDAVL                    SDMMC_STA_RXDAVL
#define SDMMC_FLAG_SDIOIT                    SDMMC_STA_SDIOIT
#define IS_SDMMC_FLAG(FLAG) (((FLAG)  == SDMMC_FLAG_CCRCFAIL) || \
                            ((FLAG)  == SDMMC_FLAG_DCRCFAIL) || \
                            ((FLAG)  == SDMMC_FLAG_CTIMEOUT) || \
                            ((FLAG)  == SDMMC_FLAG_DTIMEOUT) || \
                            ((FLAG)  == SDMMC_FLAG_TXUNDERR) || \
                            ((FLAG)  == SDMMC_FLAG_RXOVERR) || \
                            ((FLAG)  == SDMMC_FLAG_CMDREND) || \
                            ((FLAG)  == SDMMC_FLAG_CMDSENT) || \
                            ((FLAG)  == SDMMC_FLAG_DATAEND) || \
                            ((FLAG)  == SDMMC_FLAG_DBCKEND) || \
                            ((FLAG)  == SDMMC_FLAG_CMDACT) || \
                            ((FLAG)  == SDMMC_FLAG_TXACT) || \
                            ((FLAG)  == SDMMC_FLAG_RXACT) || \
                            ((FLAG)  == SDMMC_FLAG_TXFIFOHE) || \
                            ((FLAG)  == SDMMC_FLAG_RXFIFOHF) || \
                            ((FLAG)  == SDMMC_FLAG_TXFIFOF) || \
                            ((FLAG)  == SDMMC_FLAG_RXFIFOF) || \
                            ((FLAG)  == SDMMC_FLAG_TXFIFOE) || \
                            ((FLAG)  == SDMMC_FLAG_RXFIFOE) || \
                            ((FLAG)  == SDMMC_FLAG_TXDAVL) || \
                            ((FLAG)  == SDMMC_FLAG_RXDAVL) || \
                            ((FLAG)  == SDMMC_FLAG_SDIOIT))

#define IS_SDMMC_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFF3FF800) == 0x00) && ((FLAG) != (uint32_t)0x00))

#define IS_SDMMC_GET_IT(IT) (((IT)  == SDMMC_IT_CCRCFAIL) || \
                            ((IT)  == SDMMC_IT_DCRCFAIL) || \
                            ((IT)  == SDMMC_IT_CTIMEOUT) || \
                            ((IT)  == SDMMC_IT_DTIMEOUT) || \
                            ((IT)  == SDMMC_IT_TXUNDERR) || \
                            ((IT)  == SDMMC_IT_RXOVERR) || \
                            ((IT)  == SDMMC_IT_CMDREND) || \
                            ((IT)  == SDMMC_IT_CMDSENT) || \
                            ((IT)  == SDMMC_IT_DATAEND) || \
                            ((IT)  == SDMMC_IT_DBCKEND) || \
                            ((IT)  == SDMMC_IT_CMDACT) || \
                            ((IT)  == SDMMC_IT_TXACT) || \
                            ((IT)  == SDMMC_IT_RXACT) || \
                            ((IT)  == SDMMC_IT_TXFIFOHE) || \
                            ((IT)  == SDMMC_IT_RXFIFOHF) || \
                            ((IT)  == SDMMC_IT_TXFIFOF) || \
                            ((IT)  == SDMMC_IT_RXFIFOF) || \
                            ((IT)  == SDMMC_IT_TXFIFOE) || \
                            ((IT)  == SDMMC_IT_RXFIFOE) || \
                            ((IT)  == SDMMC_IT_TXDAVL) || \
                            ((IT)  == SDMMC_IT_RXDAVL) || \
                            ((IT)  == SDMMC_IT_SDIOIT))

#define IS_SDMMC_CLEAR_IT(IT) ((((IT) & (uint32_t)0xFF3FF800) == 0x00) && ((IT) != (uint32_t)0x00))

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/*  Function used to set the SDMMC configuration to the default reset state ****/
void SDMMC_DeInit(SDMMC_TypeDef *SDMMCx);

/* Initialization and Configuration functions *********************************/
void SDMMC_Init(SDMMC_TypeDef *SDMMCx, SDMMC_InitTypeDef* SDMMC_InitStruct);
void SDMMC_StructInit(SDMMC_InitTypeDef* SDMMC_InitStruct);
void SDMMC_ClockCmd(SDMMC_TypeDef *SDMMCx, FunctionalState NewState);
void SDMMC_SetPowerState(SDMMC_TypeDef *SDMMCx, uint32_t SDMMC_PowerState);
uint32_t SDMMC_GetPowerState(SDMMC_TypeDef *SDMMCx);

/* Command path state machine (CPSM) management functions *********************/
void SDMMC_SendCommand(SDMMC_TypeDef *SDMMCx, SDMMC_CmdInitTypeDef *SDMMC_CmdInitStruct);
void SDMMC_CmdStructInit(SDMMC_CmdInitTypeDef* SDMMC_CmdInitStruct);
uint8_t SDMMC_GetCommandResponse(SDMMC_TypeDef *SDMMCx);
uint32_t SDMMC_GetResponse(SDMMC_TypeDef *SDMMCx, uint32_t SDMMC_RESP);

/* Data path state machine (DPSM) management functions ************************/
void SDMMC_DataConfig(SDMMC_TypeDef *SDMMCx, SDMMC_DataInitTypeDef* SDMMC_DataInitStruct);
void SDMMC_DataStructInit(SDMMC_DataInitTypeDef* SDMMC_DataInitStruct);
uint32_t SDMMC_GetDataCounter(SDMMC_TypeDef *SDMMCx);
uint32_t SDMMC_ReadData(SDMMC_TypeDef *SDMMCx);
void SDMMC_WriteData(SDMMC_TypeDef *SDMMCx, uint32_t Data);
uint32_t SDMMC_GetFIFOCount(SDMMC_TypeDef *SDMMCx);

/* SDMMC IO Cards mode management functions ************************************/
void SDMMC_StartSDMMCReadWait(SDMMC_TypeDef *SDMMCx, FunctionalState NewState);
void SDMMC_StopSDMMCReadWait(SDMMC_TypeDef *SDMMCx, FunctionalState NewState);
void SDMMC_SetSDMMCReadWaitMode(SDMMC_TypeDef *SDMMCx, uint32_t SDMMC_ReadWaitMode);
void SDMMC_SetSDMMCOperation(SDMMC_TypeDef *SDMMCx, FunctionalState NewState);
void SDMMC_SendSDIOSuspendCmd(SDMMC_TypeDef *SDMMCx, FunctionalState NewState);

/* DMA transfers management functions *****************************************/
void SDMMC_DMACmd(SDMMC_TypeDef *SDMMCx, FunctionalState NewState);

/* Interrupts and flags management functions **********************************/
void SDMMC_ITConfig(SDMMC_TypeDef *SDMMCx, uint32_t SDMMC_IT, FunctionalState NewState);
FlagStatus SDMMC_GetFlagStatus(SDMMC_TypeDef *SDMMCx, uint32_t SDMMC_FLAG);
void SDMMC_ClearFlag(SDMMC_TypeDef *SDMMCx, uint32_t SDMMC_FLAG);
ITStatus SDMMC_GetITStatus(SDMMC_TypeDef *SDMMCx, uint32_t SDMMC_IT);
void SDMMC_ClearITPendingBit(SDMMC_TypeDef *SDMMCx, uint32_t SDMMC_IT);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F7xx_SDMMC_H */

/**
  * @}
  */

/**
  * @}
  */