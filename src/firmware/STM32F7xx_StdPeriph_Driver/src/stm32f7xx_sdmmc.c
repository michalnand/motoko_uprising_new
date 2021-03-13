
/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_sdmmc.h"
#include "stm32f7xx_rcc.h"

/** @addtogroup STM32F7xx_StdPeriph_Driver
  * @{
  */

/** @defgroup SDMMC 
  * @brief SDMMC driver modules
  * @{
  */ 

/* ---------------------- SDMMC registers bit mask ------------------------ */
/* --- CLKCR Register ---*/
/* CLKCR register clear mask */
#define CLKCR_CLEAR_MASK         ((uint32_t)(SDMMC_CLKCR_CLKDIV  | SDMMC_CLKCR_PWRSAV |\
                                             SDMMC_CLKCR_BYPASS  | SDMMC_CLKCR_WIDBUS |\
                                             SDMMC_CLKCR_NEGEDGE | SDMMC_CLKCR_HWFC_EN))
//#define CLKCR_CLEAR_MASK         ((uint32_t)0xFFFF8100) 
/* --- PWRCTRL Register ---*/
/* SDMMC PWRCTRL Mask */
//#define PWR_PWRCTRL_MASK         ((uint32_t)0xFFFFFFFC)

/* --- DCTRL Register ---*/
/* SDMMC DCTRL Clear Mask */
#define DCTRL_CLEAR_MASK         ((uint32_t)(SDMMC_DCTRL_DTEN    | SDMMC_DCTRL_DTDIR |\
                                             SDMMC_DCTRL_DTMODE  | SDMMC_DCTRL_DBLOCKSIZE))
//#define DCTRL_CLEAR_MASK         ((uint32_t)0xFFFFFF08)

/* --- CMD Register ---*/
/* CMD Register clear mask */
#define CMD_CLEAR_MASK           ((uint32_t)(SDMMC_CMD_CMDINDEX | SDMMC_CMD_WAITRESP |\
                                             SDMMC_CMD_WAITINT  | SDMMC_CMD_WAITPEND |\
                                             SDMMC_CMD_CPSMEN   | SDMMC_CMD_SDIOSUSPEND))
//#define CMD_CLEAR_MASK           ((uint32_t)0xFFFFF800)

/* SDMMC RESP Registers Address */
//#define SDMMC_RESP_ADDR           ((uint32_t)(SDMMC_BASE + 0x14))

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup SDMMC_Private_Functions
  * @{
  */

/** @defgroup SDMMC_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim   
 ===============================================================================
              ##### Initialization and Configuration functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the SDMMC peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void SDMMC_DeInit(SDMMC_TypeDef *SDMMCx)
{
  /* Check the parameters */
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  
  if(SDMMCx == SDMMC1)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SDMMC1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SDMMC1, DISABLE);
  }
}

/**
  * @brief  Initializes the SDMMC peripheral according to the specified 
  *         parameters in the SDMMC_InitStruct.
  * @param  SDMMC_InitStruct : pointer to a SDMMC_InitTypeDef structure 
  *         that contains the configuration information for the SDMMC peripheral.
  * @retval None
  */
void SDMMC_Init(SDMMC_TypeDef *SDMMCx, SDMMC_InitTypeDef* SDMMC_InitStruct)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  assert_param(IS_SDMMC_CLOCK_EDGE(SDMMC_InitStruct->SDMMC_ClockEdge));
  assert_param(IS_SDMMC_CLOCK_BYPASS(SDMMC_InitStruct->SDMMC_ClockBypass));
  assert_param(IS_SDMMC_CLOCK_POWER_SAVE(SDMMC_InitStruct->SDMMC_ClockPowerSave));
  assert_param(IS_SDMMC_BUS_WIDE(SDMMC_InitStruct->SDMMC_BusWide));
  assert_param(IS_SDMMC_HARDWARE_FLOW_CONTROL(SDMMC_InitStruct->SDMMC_HardwareFlowControl)); 
   
/*---------------------------- SDMMC CLKCR Configuration ------------------------*/  
  /* Get the SDMMC CLKCR value */
  //tmpreg = SDMMCx->CLKCR;
  
  /* Clear CLKDIV, PWRSAV, BYPASS, WIDBUS, NEGEDGE, HWFC_EN bits */
  //tmpreg &= CLKCR_CLEAR_MASK;
  
  /* Set CLKDIV bits according to SDMMC_ClockDiv value */
  /* Set PWRSAV bit according to SDMMC_ClockPowerSave value */
  /* Set BYPASS bit according to SDMMC_ClockBypass value */
  /* Set WIDBUS bits according to SDMMC_BusWide value */
  /* Set NEGEDGE bits according to SDMMC_ClockEdge value */
  /* Set HWFC_EN bits according to SDMMC_HardwareFlowControl value */
  tmpreg |= (SDMMC_InitStruct->SDMMC_ClockDiv  | SDMMC_InitStruct->SDMMC_ClockPowerSave |
             SDMMC_InitStruct->SDMMC_ClockBypass | SDMMC_InitStruct->SDMMC_BusWide |
             SDMMC_InitStruct->SDMMC_ClockEdge | SDMMC_InitStruct->SDMMC_HardwareFlowControl); 
  
  /* Write to SDMMC CLKCR */
  //SDMMCx->CLKCR = tmpreg;
  MODIFY_REG(SDMMCx->CLKCR, CLKCR_CLEAR_MASK, tmpreg);
}

/**
  * @brief  Fills each SDMMC_InitStruct member with its default value.
  * @param  SDMMC_InitStruct: pointer to an SDMMC_InitTypeDef structure which 
  *         will be initialized.
  * @retval None
  */
void SDMMC_StructInit(SDMMC_InitTypeDef* SDMMC_InitStruct)
{
  /* SDMMC_InitStruct members default value */
  SDMMC_InitStruct->SDMMC_ClockDiv = 0x00;
  SDMMC_InitStruct->SDMMC_ClockEdge = SDMMC_ClockEdge_Rising;
  SDMMC_InitStruct->SDMMC_ClockBypass = SDMMC_ClockBypass_Disable;
  SDMMC_InitStruct->SDMMC_ClockPowerSave = SDMMC_ClockPowerSave_Disable;
  SDMMC_InitStruct->SDMMC_BusWide = SDMMC_BusWide_1b;
  SDMMC_InitStruct->SDMMC_HardwareFlowControl = SDMMC_HardwareFlowControl_Disable;
}

/**
  * @brief  Enables or disables the SDMMC Clock.
  * @param  NewState: new state of the SDMMC Clock. 
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SDMMC_ClockCmd(SDMMC_TypeDef *SDMMCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if( NewState != DISABLE )
  {
    SDMMCx->CLKCR |= SDMMC_CLKCR_CLKEN;
  }
  else
  {
    SDMMCx->CLKCR &= ~SDMMC_CLKCR_CLKEN;
  }
  
}

/**
  * @brief  Sets the power status of the controller.
  * @param  SDMMC_PowerState: new state of the Power state. 
  *          This parameter can be one of the following values:
  *            @arg SDMMC_PowerState_OFF: SDMMC Power OFF
  *            @arg SDMMC_PowerState_ON: SDMMC Power ON
  * @retval None
  */
void SDMMC_SetPowerState(SDMMC_TypeDef *SDMMCx, uint32_t SDMMC_PowerState)
{
  /* Check the parameters */
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  assert_param(IS_SDMMC_POWER_STATE(SDMMC_PowerState));
  
  SDMMCx->POWER = SDMMC_PowerState;
}

/**
  * @brief  Gets the power status of the controller.
  * @param  None
  * @retval Power status of the controller. The returned value can be one of the 
  *         following values:
  *            - 0x00: Power OFF
  *            - 0x02: Power UP
  *            - 0x03: Power ON 
  */
uint32_t SDMMC_GetPowerState(SDMMC_TypeDef *SDMMCx)
{
  /* Check the parameters */
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  
  return (SDMMCx->POWER & SDMMC_POWER_PWRCTRL);
}

/**
  * @}
  */

/** @defgroup SDMMC_Group2 Command path state machine (CPSM) management functions
 *  @brief   Command path state machine (CPSM) management functions 
 *
@verbatim   
 ===============================================================================
        ##### Command path state machine (CPSM) management functions #####
 ===============================================================================  

  This section provide functions allowing to program and read the Command path 
  state machine (CPSM).

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the SDMMC Command according to the specified 
  *         parameters in the SDMMC_CmdInitStruct and send the command.
  * @param  SDMMC_CmdInitStruct : pointer to a SDMMC_CmdInitTypeDef 
  *         structure that contains the configuration information for the SDMMC 
  *         command.
  * @retval None
  */
void SDMMC_SendCommand(SDMMC_TypeDef *SDMMCx, SDMMC_CmdInitTypeDef *SDMMC_CmdInitStruct)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  assert_param(IS_SDMMC_CMD_INDEX(SDMMC_CmdInitStruct->SDMMC_CmdIndex));
  assert_param(IS_SDMMC_RESPONSE(SDMMC_CmdInitStruct->SDMMC_Response));
  assert_param(IS_SDMMC_WAIT(SDMMC_CmdInitStruct->SDMMC_Wait));
  assert_param(IS_SDMMC_CPSM(SDMMC_CmdInitStruct->SDMMC_CPSM));
  
/*---------------------------- SDMMC ARG Configuration ------------------------*/
  /* Set the SDMMC Argument value */
  SDMMCx->ARG = SDMMC_CmdInitStruct->SDMMC_Argument;
  
/*---------------------------- SDMMC CMD Configuration ------------------------*/  
  /* Get the SDMMC CMD value */
  //tmpreg = SDMMCx->CMD;
  /* Clear CMDINDEX, WAITRESP, WAITINT, WAITPEND, CPSMEN bits */
  //tmpreg &= CMD_CLEAR_MASK;
  
  /* Set CMDINDEX bits according to SDMMC_CmdIndex value */
  /* Set WAITRESP bits according to SDMMC_Response value */
  /* Set WAITINT and WAITPEND bits according to SDMMC_Wait value */
  /* Set CPSMEN bits according to SDMMC_CPSM value */
  tmpreg |= (uint32_t)SDMMC_CmdInitStruct->SDMMC_CmdIndex | SDMMC_CmdInitStruct->SDMMC_Response
           | SDMMC_CmdInitStruct->SDMMC_Wait | SDMMC_CmdInitStruct->SDMMC_CPSM;
  
  /* Write to SDMMC CMD */
  //SDMMCx->CMD = tmpreg;
  MODIFY_REG(SDMMCx->CMD, CMD_CLEAR_MASK, tmpreg); 
}

/**
  * @brief  Fills each SDMMC_CmdInitStruct member with its default value.
  * @param  SDMMC_CmdInitStruct: pointer to an SDMMC_CmdInitTypeDef 
  *         structure which will be initialized.
  * @retval None
  */
void SDMMC_CmdStructInit(SDMMC_CmdInitTypeDef* SDMMC_CmdInitStruct)
{
  /* SDMMC_CmdInitStruct members default value */
  SDMMC_CmdInitStruct->SDMMC_Argument = 0x00;
  SDMMC_CmdInitStruct->SDMMC_CmdIndex = 0x00;
  SDMMC_CmdInitStruct->SDMMC_Response = SDMMC_Response_No;
  SDMMC_CmdInitStruct->SDMMC_Wait = SDMMC_Wait_No;
  SDMMC_CmdInitStruct->SDMMC_CPSM = SDMMC_CPSM_Disable;
}

/**
  * @brief  Returns command index of last command for which response received.
  * @param  None
  * @retval Returns the command index of the last command response received.
  */
uint8_t SDMMC_GetCommandResponse(SDMMC_TypeDef *SDMMCx)
{
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  
  return (uint8_t)(SDMMCx->RESPCMD);
}

/**
  * @brief  Returns response received from the card for the last command.
  * @param  SDMMC_RESP: Specifies the SDMMC response register. 
  *          This parameter can be one of the following values:
  *            @arg SDMMC_RESP1: Response Register 1
  *            @arg SDMMC_RESP2: Response Register 2
  *            @arg SDMMC_RESP3: Response Register 3
  *            @arg SDMMC_RESP4: Response Register 4
  * @retval The Corresponding response register value.
  */
uint32_t SDMMC_GetResponse(SDMMC_TypeDef *SDMMCx, uint32_t SDMMC_RESP)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  assert_param(IS_SDMMC_RESP(SDMMC_RESP));

  tmp = (uint32_t)&(SDMMCx->RESP1) + SDMMC_RESP;
  
  return (*(__IO uint32_t *) tmp); 
}

/**
  * @}
  */

/** @defgroup SDMMC_Group3 Data path state machine (DPSM) management functions
 *  @brief   Data path state machine (DPSM) management functions
 *
@verbatim   
 ===============================================================================
         ##### Data path state machine (DPSM) management functions #####
 ===============================================================================  

  This section provide functions allowing to program and read the Data path 
  state machine (DPSM).

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the SDMMC data path according to the specified 
  *         parameters in the SDMMC_DataInitStruct.
  * @param  SDMMC_DataInitStruct : pointer to a SDMMC_DataInitTypeDef structure 
  *         that contains the configuration information for the SDMMC command.
  * @retval None
  */
void SDMMC_DataConfig(SDMMC_TypeDef *SDMMCx, SDMMC_DataInitTypeDef* SDMMC_DataInitStruct)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  assert_param(IS_SDMMC_DATA_LENGTH(SDMMC_DataInitStruct->SDMMC_DataLength));
  assert_param(IS_SDMMC_BLOCK_SIZE(SDMMC_DataInitStruct->SDMMC_DataBlockSize));
  assert_param(IS_SDMMC_TRANSFER_DIR(SDMMC_DataInitStruct->SDMMC_TransferDir));
  assert_param(IS_SDMMC_TRANSFER_MODE(SDMMC_DataInitStruct->SDMMC_TransferMode));
  assert_param(IS_SDMMC_DPSM(SDMMC_DataInitStruct->SDMMC_DPSM));

/*---------------------------- SDMMC DTIMER Configuration ---------------------*/
  /* Set the SDMMC Data TimeOut value */
  SDMMCx->DTIMER = SDMMC_DataInitStruct->SDMMC_DataTimeOut;

/*---------------------------- SDMMC DLEN Configuration -----------------------*/
  /* Set the SDMMC DataLength value */
  SDMMCx->DLEN = SDMMC_DataInitStruct->SDMMC_DataLength;

/*---------------------------- SDMMC DCTRL Configuration ----------------------*/  
  /* Get the SDMMC DCTRL value */
  //tmpreg = SDMMCx->DCTRL;
  /* Clear DEN, DTMODE, DTDIR and DBCKSIZE bits */
  //tmpreg &= DCTRL_CLEAR_MASK;
  /* Set DEN bit according to SDMMC_DPSM value */
  /* Set DTMODE bit according to SDMMC_TransferMode value */
  /* Set DTDIR bit according to SDMMC_TransferDir value */
  /* Set DBCKSIZE bits according to SDMMC_DataBlockSize value */
  tmpreg |= (uint32_t)SDMMC_DataInitStruct->SDMMC_DataBlockSize | SDMMC_DataInitStruct->SDMMC_TransferDir
           | SDMMC_DataInitStruct->SDMMC_TransferMode | SDMMC_DataInitStruct->SDMMC_DPSM;

  /* Write to SDMMC DCTRL */
  //SDMMCx->DCTRL = tmpreg;
  MODIFY_REG(SDMMCx->DCTRL, DCTRL_CLEAR_MASK, tmpreg);
}

/**
  * @brief  Fills each SDMMC_DataInitStruct member with its default value.
  * @param  SDMMC_DataInitStruct: pointer to an SDMMC_DataInitTypeDef structure 
  *         which will be initialized.
  * @retval None
  */
void SDMMC_DataStructInit(SDMMC_DataInitTypeDef* SDMMC_DataInitStruct)
{
  /* SDMMC_DataInitStruct members default value */
  SDMMC_DataInitStruct->SDMMC_DataTimeOut = 0xFFFFFFFF;
  SDMMC_DataInitStruct->SDMMC_DataLength = 0x00;
  SDMMC_DataInitStruct->SDMMC_DataBlockSize = SDMMC_DataBlockSize_1b;
  SDMMC_DataInitStruct->SDMMC_TransferDir = SDMMC_TransferDir_ToCard;
  SDMMC_DataInitStruct->SDMMC_TransferMode = SDMMC_TransferMode_Block;  
  SDMMC_DataInitStruct->SDMMC_DPSM = SDMMC_DPSM_Disable;
}

/**
  * @brief  Returns number of remaining data bytes to be transferred.
  * @param  None
  * @retval Number of remaining data bytes to be transferred
  */
uint32_t SDMMC_GetDataCounter(SDMMC_TypeDef *SDMMCx)
{
  /* Check the parameters */
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  
  return SDMMCx->DCOUNT;
}

/**
  * @brief  Read one data word from Rx FIFO.
  * @param  None
  * @retval Data received
  */
uint32_t SDMMC_ReadData(SDMMC_TypeDef *SDMMCx)
{
  /* Check the parameters */
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  
  return SDMMCx->FIFO;
}

/**
  * @brief  Write one data word to Tx FIFO.
  * @param  Data: 32-bit data word to write.
  * @retval None
  */
void SDMMC_WriteData(SDMMC_TypeDef *SDMMCx, uint32_t Data)
{
  /* Check the parameters */
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  
  SDMMCx->FIFO = Data;
}

/**
  * @brief  Returns the number of words left to be written to or read from FIFO.	
  * @param  None
  * @retval Remaining number of words.
  */
uint32_t SDMMC_GetFIFOCount(SDMMC_TypeDef *SDMMCx)
{
  /* Check the parameters */
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  
  return SDMMCx->FIFOCNT;
}

/**
  * @}
  */

/** @defgroup SDMMC_Group4 SDMMC IO Cards mode management functions
 *  @brief   SDMMC IO Cards mode management functions
 *
@verbatim   
 ===============================================================================
               ##### SDMMC IO Cards mode management functions #####
 ===============================================================================  

  This section provide functions allowing to program and read the SDMMC IO Cards.

@endverbatim
  * @{
  */

/**
  * @brief  Starts the SD I/O Read Wait operation.	
  * @param  NewState: new state of the Start SDMMC Read Wait operation. 
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SDMMC_StartSDMMCReadWait(SDMMC_TypeDef *SDMMCx, FunctionalState NewState)
{ 
  /* Check the parameters */
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if( NewState != DISABLE )
  {
    SDMMCx->DCTRL |= SDMMC_DCTRL_RWSTART;
  }
  else
  {
    SDMMCx->DCTRL &= ~SDMMC_DCTRL_RWSTART;
  }
}

/**
  * @brief  Stops the SD I/O Read Wait operation.	
  * @param  NewState: new state of the Stop SDMMC Read Wait operation. 
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SDMMC_StopSDMMCReadWait(SDMMC_TypeDef *SDMMCx, FunctionalState NewState)
{ 
  /* Check the parameters */
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if( NewState != DISABLE )
  {
    SDMMCx->DCTRL |= SDMMC_DCTRL_RWSTOP;
  }
  else
  {
    SDMMCx->DCTRL &= ~SDMMC_DCTRL_RWSTOP;
  }
}

/**
  * @brief  Sets one of the two options of inserting read wait interval.
  * @param  SDMMC_ReadWaitMode: SD I/O Read Wait operation mode.
  *          This parameter can be:
  *            @arg SDMMC_ReadWaitMode_CLK: Read Wait control by stopping SDMMCCLK
  *            @arg SDMMC_ReadWaitMode_DATA2: Read Wait control using SDMMC_DATA2
  * @retval None
  */
void SDMMC_SetSDMMCReadWaitMode(SDMMC_TypeDef *SDMMCx, uint32_t SDMMC_ReadWaitMode)
{
  /* Check the parameters */
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  assert_param(IS_SDMMC_READWAIT_MODE(SDMMC_ReadWaitMode));
  
  if( SDMMC_ReadWaitMode == SDMMC_ReadWaitMode_CLK )
  {
    SDMMCx->DCTRL |= SDMMC_DCTRL_RWMOD;
  }
  else
  {
    SDMMCx->DCTRL &= ~SDMMC_DCTRL_RWMOD;
  }
}

/**
  * @brief  Enables or disables the SD I/O Mode Operation.
  * @param  NewState: new state of SDMMC specific operation. 
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SDMMC_SetSDMMCOperation(SDMMC_TypeDef *SDMMCx, FunctionalState NewState)
{ 
  /* Check the parameters */
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if( NewState != DISABLE )
  {
    SDMMCx->DCTRL |= SDMMC_DCTRL_SDIOEN;
  }
  else
  {
    SDMMCx->DCTRL &= ~SDMMC_DCTRL_SDIOEN;
  }
}

/**
  * @brief  Enables or disables the SD I/O Mode suspend command sending.
  * @param  NewState: new state of the SD I/O Mode suspend command.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SDMMC_SendSDIOSuspendCmd(SDMMC_TypeDef *SDMMCx, FunctionalState NewState)
{ 
  /* Check the parameters */
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if( NewState != DISABLE )
  {
    SDMMCx->CMD |= SDMMC_CMD_SDIOSUSPEND;
  }
  else
  {
    SDMMCx->CMD &= ~SDMMC_CMD_SDIOSUSPEND;
  }
}

/** @defgroup SDMMC_Group6 DMA transfers management functions
 *  @brief   DMA transfers management functions
 *
@verbatim   
 ===============================================================================
                  ##### DMA transfers management functions #####
 ===============================================================================  

  This section provide functions allowing to program SDMMC DMA transfer.

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the SDMMC DMA request.
  * @param  NewState: new state of the selected SDMMC DMA request.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SDMMC_DMACmd(SDMMC_TypeDef *SDMMCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if( NewState != DISABLE )
  {
    SDMMCx->DCTRL |= SDMMC_DCTRL_DMAEN;
  }
  else
  {
    SDMMCx->DCTRL &= ~SDMMC_DCTRL_DMAEN;
  }
}

/**
  * @}
  */

/** @defgroup SDMMC_Group7 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions  
 *
@verbatim   
 ===============================================================================
              ##### Interrupts and flags management functions #####
 ===============================================================================  


@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the SDMMC interrupts.
  * @param  SDMMC_IT: specifies the SDMMC interrupt sources to be enabled or disabled.
  *          This parameter can be one or a combination of the following values:
  *            @arg SDMMC_IT_CCRCFAIL: Command response received (CRC check failed) interrupt
  *            @arg SDMMC_IT_DCRCFAIL: Data block sent/received (CRC check failed) interrupt
  *            @arg SDMMC_IT_CTIMEOUT: Command response timeout interrupt
  *            @arg SDMMC_IT_DTIMEOUT: Data timeout interrupt
  *            @arg SDMMC_IT_TXUNDERR: Transmit FIFO underrun error interrupt
  *            @arg SDMMC_IT_RXOVERR:  Received FIFO overrun error interrupt
  *            @arg SDMMC_IT_CMDREND:  Command response received (CRC check passed) interrupt
  *            @arg SDMMC_IT_CMDSENT:  Command sent (no response required) interrupt
  *            @arg SDMMC_IT_DATAEND:  Data end (data counter, SDIDCOUNT, is zero) interrupt
  *            @arg SDMMC_IT_DBCKEND:  Data block sent/received (CRC check passed) interrupt
  *            @arg SDMMC_IT_CMDACT:   Command transfer in progress interrupt
  *            @arg SDMMC_IT_TXACT:    Data transmit in progress interrupt
  *            @arg SDMMC_IT_RXACT:    Data receive in progress interrupt
  *            @arg SDMMC_IT_TXFIFOHE: Transmit FIFO Half Empty interrupt
  *            @arg SDMMC_IT_RXFIFOHF: Receive FIFO Half Full interrupt
  *            @arg SDMMC_IT_TXFIFOF:  Transmit FIFO full interrupt
  *            @arg SDMMC_IT_RXFIFOF:  Receive FIFO full interrupt
  *            @arg SDMMC_IT_TXFIFOE:  Transmit FIFO empty interrupt
  *            @arg SDMMC_IT_RXFIFOE:  Receive FIFO empty interrupt
  *            @arg SDMMC_IT_TXDAVL:   Data available in transmit FIFO interrupt
  *            @arg SDMMC_IT_RXDAVL:   Data available in receive FIFO interrupt
  *            @arg SDMMC_IT_SDIOIT:   SD I/O interrupt received interrupt
  * @param  NewState: new state of the specified SDMMC interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None 
  */
void SDMMC_ITConfig(SDMMC_TypeDef *SDMMCx, uint32_t SDMMC_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  assert_param(IS_SDMMC_IT(SDMMC_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the SDMMC interrupts */
    SDMMCx->MASK |= SDMMC_IT;
  }
  else
  {
    /* Disable the SDMMC interrupts */
    SDMMCx->MASK &= ~SDMMC_IT;
  } 
}

/**
  * @brief  Checks whether the specified SDMMC flag is set or not.
  * @param  SDMMC_FLAG: specifies the flag to check. 
  *          This parameter can be one of the following values:
  *            @arg SDMMC_FLAG_CCRCFAIL: Command response received (CRC check failed)
  *            @arg SDMMC_FLAG_DCRCFAIL: Data block sent/received (CRC check failed)
  *            @arg SDMMC_FLAG_CTIMEOUT: Command response timeout
  *            @arg SDMMC_FLAG_DTIMEOUT: Data timeout
  *            @arg SDMMC_FLAG_TXUNDERR: Transmit FIFO underrun error
  *            @arg SDMMC_FLAG_RXOVERR:  Received FIFO overrun error
  *            @arg SDMMC_FLAG_CMDREND:  Command response received (CRC check passed)
  *            @arg SDMMC_FLAG_CMDSENT:  Command sent (no response required)
  *            @arg SDMMC_FLAG_DATAEND:  Data end (data counter, SDIDCOUNT, is zero)
  *            @arg SDMMC_FLAG_DBCKEND:  Data block sent/received (CRC check passed)
  *            @arg SDMMC_FLAG_CMDACT:   Command transfer in progress
  *            @arg SDMMC_FLAG_TXACT:    Data transmit in progress
  *            @arg SDMMC_FLAG_RXACT:    Data receive in progress
  *            @arg SDMMC_FLAG_TXFIFOHE: Transmit FIFO Half Empty
  *            @arg SDMMC_FLAG_RXFIFOHF: Receive FIFO Half Full
  *            @arg SDMMC_FLAG_TXFIFOF:  Transmit FIFO full
  *            @arg SDMMC_FLAG_RXFIFOF:  Receive FIFO full
  *            @arg SDMMC_FLAG_TXFIFOE:  Transmit FIFO empty
  *            @arg SDMMC_FLAG_RXFIFOE:  Receive FIFO empty
  *            @arg SDMMC_FLAG_TXDAVL:   Data available in transmit FIFO
  *            @arg SDMMC_FLAG_RXDAVL:   Data available in receive FIFO
  *            @arg SDMMC_FLAG_SDIOIT:   SD I/O interrupt received
  * @retval The new state of SDMMC_FLAG (SET or RESET).
  */
FlagStatus SDMMC_GetFlagStatus(SDMMC_TypeDef *SDMMCx, uint32_t SDMMC_FLAG)
{ 
  FlagStatus bitstatus = RESET;
  
  /* Check the parameters */
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  assert_param(IS_SDMMC_FLAG(SDMMC_FLAG));
  
  if ((SDMMCx->STA & SDMMC_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the SDMMC's pending flags.
  * @param  SDMMC_FLAG: specifies the flag to clear.  
  *          This parameter can be one or a combination of the following values:
  *            @arg SDMMC_FLAG_CCRCFAIL: Command response received (CRC check failed)
  *            @arg SDMMC_FLAG_DCRCFAIL: Data block sent/received (CRC check failed)
  *            @arg SDMMC_FLAG_CTIMEOUT: Command response timeout
  *            @arg SDMMC_FLAG_DTIMEOUT: Data timeout
  *            @arg SDMMC_FLAG_TXUNDERR: Transmit FIFO underrun error
  *            @arg SDMMC_FLAG_RXOVERR:  Received FIFO overrun error
  *            @arg SDMMC_FLAG_CMDREND:  Command response received (CRC check passed)
  *            @arg SDMMC_FLAG_CMDSENT:  Command sent (no response required)
  *            @arg SDMMC_FLAG_DATAEND:  Data end (data counter, SDIDCOUNT, is zero)
  *            @arg SDMMC_FLAG_DBCKEND:  Data block sent/received (CRC check passed)
  *            @arg SDMMC_FLAG_SDIOIT:   SD I/O interrupt received
  * @retval None
  */
void SDMMC_ClearFlag(SDMMC_TypeDef *SDMMCx, uint32_t SDMMC_FLAG)
{ 
  /* Check the parameters */
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  assert_param(IS_SDMMC_CLEAR_FLAG(SDMMC_FLAG));
   
  SDMMCx->ICR = SDMMC_FLAG;
}

/**
  * @brief  Checks whether the specified SDMMC interrupt has occurred or not.
  * @param  SDMMC_IT: specifies the SDMMC interrupt source to check. 
  *          This parameter can be one of the following values:
  *            @arg SDMMC_IT_CCRCFAIL: Command response received (CRC check failed) interrupt
  *            @arg SDMMC_IT_DCRCFAIL: Data block sent/received (CRC check failed) interrupt
  *            @arg SDMMC_IT_CTIMEOUT: Command response timeout interrupt
  *            @arg SDMMC_IT_DTIMEOUT: Data timeout interrupt
  *            @arg SDMMC_IT_TXUNDERR: Transmit FIFO underrun error interrupt
  *            @arg SDMMC_IT_RXOVERR:  Received FIFO overrun error interrupt
  *            @arg SDMMC_IT_CMDREND:  Command response received (CRC check passed) interrupt
  *            @arg SDMMC_IT_CMDSENT:  Command sent (no response required) interrupt
  *            @arg SDMMC_IT_DATAEND:  Data end (data counter, SDIDCOUNT, is zero) interrupt
  *            @arg SDMMC_IT_DBCKEND:  Data block sent/received (CRC check passed) interrupt
  *            @arg SDMMC_IT_CMDACT:   Command transfer in progress interrupt
  *            @arg SDMMC_IT_TXACT:    Data transmit in progress interrupt
  *            @arg SDMMC_IT_RXACT:    Data receive in progress interrupt
  *            @arg SDMMC_IT_TXFIFOHE: Transmit FIFO Half Empty interrupt
  *            @arg SDMMC_IT_RXFIFOHF: Receive FIFO Half Full interrupt
  *            @arg SDMMC_IT_TXFIFOF:  Transmit FIFO full interrupt
  *            @arg SDMMC_IT_RXFIFOF:  Receive FIFO full interrupt
  *            @arg SDMMC_IT_TXFIFOE:  Transmit FIFO empty interrupt
  *            @arg SDMMC_IT_RXFIFOE:  Receive FIFO empty interrupt
  *            @arg SDMMC_IT_TXDAVL:   Data available in transmit FIFO interrupt
  *            @arg SDMMC_IT_RXDAVL:   Data available in receive FIFO interrupt
  *            @arg SDMMC_IT_SDIOIT:   SD I/O interrupt received interrupt
  * @retval The new state of SDMMC_IT (SET or RESET).
  */
ITStatus SDMMC_GetITStatus(SDMMC_TypeDef *SDMMCx, uint32_t SDMMC_IT)
{ 
  ITStatus bitstatus = RESET;
  
  /* Check the parameters */
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  assert_param(IS_SDMMC_GET_IT(SDMMC_IT));
  if ((SDMMCx->STA & SDMMC_IT) != (uint32_t)RESET)  
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the SDMMC's interrupt pending bits.
  * @param  SDMMC_IT: specifies the interrupt pending bit to clear. 
  *          This parameter can be one or a combination of the following values:
  *            @arg SDMMC_IT_CCRCFAIL: Command response received (CRC check failed) interrupt
  *            @arg SDMMC_IT_DCRCFAIL: Data block sent/received (CRC check failed) interrupt
  *            @arg SDMMC_IT_CTIMEOUT: Command response timeout interrupt
  *            @arg SDMMC_IT_DTIMEOUT: Data timeout interrupt
  *            @arg SDMMC_IT_TXUNDERR: Transmit FIFO underrun error interrupt
  *            @arg SDMMC_IT_RXOVERR:  Received FIFO overrun error interrupt
  *            @arg SDMMC_IT_CMDREND:  Command response received (CRC check passed) interrupt
  *            @arg SDMMC_IT_CMDSENT:  Command sent (no response required) interrupt
  *            @arg SDMMC_IT_DATAEND:  Data end (data counter, SDMMC_DCOUNT, is zero) interrupt
  *            @arg SDMMC_IT_SDIOIT:   SD I/O interrupt received interrupt
  * @retval None
  */
void SDMMC_ClearITPendingBit(SDMMC_TypeDef *SDMMCx, uint32_t SDMMC_IT)
{ 
  /* Check the parameters */
  assert_param(IS_SDMMC_ALL_INSTANCE(SDMMCx));
  assert_param(IS_SDMMC_CLEAR_IT(SDMMC_IT));
   
  SDMMCx->ICR = SDMMC_IT;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */