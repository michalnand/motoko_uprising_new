
/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_cryp.h"
#include "stm32f7xx_rcc.h"

/** @addtogroup STM32F7xx_StdPeriph_Driver
  * @{
  */
#if defined(CRYP)

/** @defgroup CRYP 
  * @brief CRYP driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define FLAG_MASK     ((uint8_t)0x20)
#define MAX_TIMEOUT   ((uint16_t)0xFFFF)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup CRYP_Private_Functions
  * @{
  */ 

/** @defgroup CRYP_Group1 Initialization and Configuration functions
 *  @brief    Initialization and Configuration functions 
 *
@verbatim    
 ===============================================================================
             ##### Initialization and Configuration functions #####
 ===============================================================================  
 [..] This section provides functions allowing to 
   (+) Initialize the cryptographic Processor using CRYP_Init() function 
       (++)  Encrypt or Decrypt 
       (++)  mode : TDES-ECB, TDES-CBC, 
                    DES-ECB, DES-CBC, 
                    AES-ECB, AES-CBC, AES-CTR, AES-Key, AES-GCM, AES-CCM 
       (++) DataType :  32-bit data, 16-bit data, bit data or bit-string
       (++) Key Size (only in AES modes)
   (+) Configure the Encrypt or Decrypt Key using CRYP_KeyInit() function 
   (+) Configure the Initialization Vectors(IV) for CBC and CTR modes using 
       CRYP_IVInit() function.  
   (+) Flushes the IN and OUT FIFOs : using CRYP_FIFOFlush() function.                         
   (+) Enable or disable the CRYP Processor using CRYP_Cmd() function 
       
@endverbatim
  * @{
  */
/**
  * @brief  Deinitializes the CRYP peripheral registers to their default reset values
  * @param  None
  * @retval None
  */
void CRYP_DeInit(void)
{
  /* Enable CRYP reset state */
  RCC_AHB2PeriphResetCmd(RCC_AHB2Periph_CRYP, ENABLE);

  /* Release CRYP from reset state */
  RCC_AHB2PeriphResetCmd(RCC_AHB2Periph_CRYP, DISABLE);
}

/**
  * @brief  Initializes the CRYP peripheral according to the specified parameters
  *         in the CRYP_InitStruct.
  * @param  CRYP_InitStruct: pointer to a CRYP_InitTypeDef structure that contains
  *         the configuration information for the CRYP peripheral.
  * @retval None
  */
void CRYP_Init(CRYP_InitTypeDef* CRYP_InitStruct)
{
  /* Check the parameters */
  assert_param(IS_CRYP_ALGOMODE(CRYP_InitStruct->CRYP_AlgoMode));
  assert_param(IS_CRYP_DATATYPE(CRYP_InitStruct->CRYP_DataType));
  assert_param(IS_CRYP_ALGODIR(CRYP_InitStruct->CRYP_AlgoDir));

  /* Select Algorithm mode*/  
  CRYP->CR &= ~CRYP_CR_ALGOMODE;
  CRYP->CR |= CRYP_InitStruct->CRYP_AlgoMode;

  /* Select dataType */ 
  CRYP->CR &= ~CRYP_CR_DATATYPE;
  CRYP->CR |= CRYP_InitStruct->CRYP_DataType;

  /* select Key size (used only with AES algorithm) */
  if ((CRYP_InitStruct->CRYP_AlgoMode != CRYP_AlgoMode_TDES_ECB) &&
      (CRYP_InitStruct->CRYP_AlgoMode != CRYP_AlgoMode_TDES_CBC) &&
      (CRYP_InitStruct->CRYP_AlgoMode != CRYP_AlgoMode_DES_ECB) &&
      (CRYP_InitStruct->CRYP_AlgoMode != CRYP_AlgoMode_DES_CBC))
  {
    assert_param(IS_CRYP_KEYSIZE(CRYP_InitStruct->CRYP_KeySize));
    CRYP->CR &= ~CRYP_CR_KEYSIZE;
    CRYP->CR |= CRYP_InitStruct->CRYP_KeySize; /* Key size and value must be 
                                                  configured once the key has 
                                                  been prepared */
  }

  /* Select data Direction */ 
  CRYP->CR &= ~CRYP_CR_ALGODIR;
  CRYP->CR |= CRYP_InitStruct->CRYP_AlgoDir;
}

/**
  * @brief  Fills each CRYP_InitStruct member with its default value.
  * @param  CRYP_InitStruct: pointer to a CRYP_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void CRYP_StructInit(CRYP_InitTypeDef* CRYP_InitStruct)
{
  /* Initialize the CRYP_AlgoDir member */
  CRYP_InitStruct->CRYP_AlgoDir = CRYP_AlgoDir_Encrypt;

  /* initialize the CRYP_AlgoMode member */
  CRYP_InitStruct->CRYP_AlgoMode = CRYP_AlgoMode_TDES_ECB;

  /* initialize the CRYP_DataType member */
  CRYP_InitStruct->CRYP_DataType = CRYP_DataType_32b;
  
  /* Initialize the CRYP_KeySize member */
  CRYP_InitStruct->CRYP_KeySize = CRYP_KeySize_128b;
}

/**
  * @brief  Initializes the CRYP Keys according to the specified parameters in
  *         the CRYP_KeyInitStruct.
  * @param  CRYP_KeyInitStruct: pointer to a CRYP_KeyInitTypeDef structure that
  *         contains the configuration information for the CRYP Keys.
  * @retval None
  */
void CRYP_KeyInit(CRYP_KeyInitTypeDef* CRYP_KeyInitStruct)
{
  /* Key Initialisation */
  CRYP->K0LR = CRYP_KeyInitStruct->CRYP_Key0Left;
  CRYP->K0RR = CRYP_KeyInitStruct->CRYP_Key0Right;
  CRYP->K1LR = CRYP_KeyInitStruct->CRYP_Key1Left;
  CRYP->K1RR = CRYP_KeyInitStruct->CRYP_Key1Right;
  CRYP->K2LR = CRYP_KeyInitStruct->CRYP_Key2Left;
  CRYP->K2RR = CRYP_KeyInitStruct->CRYP_Key2Right;
  CRYP->K3LR = CRYP_KeyInitStruct->CRYP_Key3Left;
  CRYP->K3RR = CRYP_KeyInitStruct->CRYP_Key3Right;
}

/**
  * @brief  Fills each CRYP_KeyInitStruct member with its default value.
  * @param  CRYP_KeyInitStruct: pointer to a CRYP_KeyInitTypeDef structure 
  *         which will be initialized.
  * @retval None
  */
void CRYP_KeyStructInit(CRYP_KeyInitTypeDef* CRYP_KeyInitStruct)
{
  CRYP_KeyInitStruct->CRYP_Key0Left  = 0;
  CRYP_KeyInitStruct->CRYP_Key0Right = 0;
  CRYP_KeyInitStruct->CRYP_Key1Left  = 0;
  CRYP_KeyInitStruct->CRYP_Key1Right = 0;
  CRYP_KeyInitStruct->CRYP_Key2Left  = 0;
  CRYP_KeyInitStruct->CRYP_Key2Right = 0;
  CRYP_KeyInitStruct->CRYP_Key3Left  = 0;
  CRYP_KeyInitStruct->CRYP_Key3Right = 0;
}
/**
  * @brief  Initializes the CRYP Initialization Vectors(IV) according to the
  *         specified parameters in the CRYP_IVInitStruct.
  * @param  CRYP_IVInitStruct: pointer to a CRYP_IVInitTypeDef structure that contains
  *         the configuration information for the CRYP Initialization Vectors(IV).
  * @retval None
  */
void CRYP_IVInit(CRYP_IVInitTypeDef* CRYP_IVInitStruct)
{
  CRYP->IV0LR = CRYP_IVInitStruct->CRYP_IV0Left;
  CRYP->IV0RR = CRYP_IVInitStruct->CRYP_IV0Right;
  CRYP->IV1LR = CRYP_IVInitStruct->CRYP_IV1Left;
  CRYP->IV1RR = CRYP_IVInitStruct->CRYP_IV1Right;
}

/**
  * @brief  Fills each CRYP_IVInitStruct member with its default value.
  * @param  CRYP_IVInitStruct: pointer to a CRYP_IVInitTypeDef Initialization 
  *         Vectors(IV) structure which will be initialized.
  * @retval None
  */
void CRYP_IVStructInit(CRYP_IVInitTypeDef* CRYP_IVInitStruct)
{
  CRYP_IVInitStruct->CRYP_IV0Left  = 0;
  CRYP_IVInitStruct->CRYP_IV0Right = 0;
  CRYP_IVInitStruct->CRYP_IV1Left  = 0;
  CRYP_IVInitStruct->CRYP_IV1Right = 0;
}

/**
  * @brief  Configures the AES-CCM and AES-GCM phases
  * @note   This function is used only with AES-CCM or AES-GCM Algorithms  
  * @param  CRYP_Phase: specifies the CRYP AES-CCM and AES-GCM phase to be configured.
  *           This parameter can be one of the following values:
  *            @arg CRYP_Phase_Init: Initialization phase
  *            @arg CRYP_Phase_Header: Header phase
  *            @arg CRYP_Phase_Payload: Payload phase
  *            @arg CRYP_Phase_Final: Final phase 
  * @retval None
  */
void CRYP_PhaseConfig(uint32_t CRYP_Phase)
{ uint32_t tempcr = 0;

  /* Check the parameter */
  assert_param(IS_CRYP_PHASE(CRYP_Phase));

  /* Get the CR register */
  tempcr = CRYP->CR;
  
  /* Reset the phase configuration bits: GCMP_CCMPH */
  tempcr &= (uint32_t)(~CRYP_CR_GCM_CCMPH);
  /* Set the selected phase */
  tempcr |= (uint32_t)CRYP_Phase;

  /* Set the CR register */ 
  CRYP->CR = tempcr;    
}

/**
  * @brief  Flushes the IN and OUT FIFOs (that is read and write pointers of the 
  *         FIFOs are reset)
  * @note   The FIFOs must be flushed only when BUSY flag is reset.  
  * @param  None
  * @retval None
  */
void CRYP_FIFOFlush(void)
{
  /* Reset the read and write pointers of the FIFOs */
  CRYP->CR |= CRYP_CR_FFLUSH;
}

/**
  * @brief  Enables or disables the CRYP peripheral.
  * @param  NewState: new state of the CRYP peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CRYP_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the Cryptographic processor */
    CRYP->CR |= CRYP_CR_CRYPEN;
  }
  else
  {
    /* Disable the Cryptographic processor */
    CRYP->CR &= ~CRYP_CR_CRYPEN;
  }
}
/**
  * @}
  */
  
/** @defgroup CRYP_Group2 CRYP Data processing functions
 *  @brief    CRYP Data processing functions
 *
@verbatim    
 ===============================================================================
                    ##### CRYP Data processing functions #####
 ===============================================================================  
 [..] This section provides functions allowing the encryption and decryption 
      operations: 
   (+) Enter data to be treated in the IN FIFO : using CRYP_DataIn() function.
   (+) Get the data result from the OUT FIFO : using CRYP_DataOut() function.

@endverbatim
  * @{
  */

/**
  * @brief  Writes data in the Data Input register (DIN).
  * @note   After the DIN register has been read once or several times, 
  *         the FIFO must be flushed (using CRYP_FIFOFlush() function).  
  * @param  Data: data to write in Data Input register
  * @retval None
  */
void CRYP_DataIn(uint32_t Data)
{
  CRYP->DR = Data;
}

/**
  * @brief  Returns the last data entered into the output FIFO.
  * @param  None
  * @retval Last data entered into the output FIFO.
  */
uint32_t CRYP_DataOut(void)
{
  return CRYP->DOUT;
}
/**
  * @}
  */
  
/** @defgroup CRYP_Group3 Context swapping functions
 *  @brief   Context swapping functions
 *
@verbatim   
 ===============================================================================
                      ##### Context swapping functions #####
 ===============================================================================  
 [..] This section provides functions allowing to save and store CRYP Context

 [..] It is possible to interrupt an encryption/ decryption/ key generation process 
      to perform another processing with a higher priority, and to complete the 
      interrupted process later on, when the higher-priority task is complete. To do 
      so, the context of the interrupted task must be saved from the CRYP registers 
      to memory, and then be restored from memory to the CRYP registers.
   
   (#) To save the current context, use CRYP_SaveContext() function
   (#) To restore the saved context, use CRYP_RestoreContext() function 

@endverbatim
  * @{
  */
  
/**
  * @brief  Saves the CRYP peripheral Context. 
  * @note   This function stops DMA transfer before to save the context. After 
  *         restoring the context, you have to enable the DMA again (if the DMA
  *         was previously used).
  * @param  CRYP_ContextSave: pointer to a CRYP_Context structure that contains
  *         the repository for current context.
  * @param  CRYP_KeyInitStruct: pointer to a CRYP_KeyInitTypeDef structure that 
  *         contains the configuration information for the CRYP Keys.  
  * @retval None
  */
ErrorStatus CRYP_SaveContext(CRYP_Context* CRYP_ContextSave,
                             CRYP_KeyInitTypeDef* CRYP_KeyInitStruct)
{
  __IO uint32_t timeout = 0;
  uint32_t ckeckmask = 0, bitstatus;    
  ErrorStatus status = ERROR;

  /* Stop DMA transfers on the IN FIFO by clearing the DIEN bit in the CRYP_DMACR */
  CRYP->DMACR &= ~(uint32_t)CRYP_DMACR_DIEN;
    
  /* Wait until both the IN and OUT FIFOs are empty  
    (IFEM=1 and OFNE=0 in the CRYP_SR register) and the 
     BUSY bit is cleared. */

  if ((CRYP->CR & (uint32_t)(CRYP_CR_ALGOMODE_TDES_ECB | CRYP_CR_ALGOMODE_TDES_CBC)) != (uint32_t)0 )/* TDES */
  { 
    ckeckmask =  CRYP_SR_IFEM | CRYP_SR_BUSY ;
  }
  else /* AES or DES */
  {
    ckeckmask =  CRYP_SR_IFEM | CRYP_SR_BUSY | CRYP_SR_OFNE;
  }           
   
  do 
  {
    bitstatus = CRYP->SR & ckeckmask;
    timeout++;
  }
  while ((timeout != MAX_TIMEOUT) && (bitstatus != CRYP_SR_IFEM));
     
  if ((CRYP->SR & ckeckmask) != CRYP_SR_IFEM)
  {
    status = ERROR;
  }
  else
  {      
    /* Stop DMA transfers on the OUT FIFO by 
       - writing the DOEN bit to 0 in the CRYP_DMACR register 
       - and clear the CRYPEN bit. */

    CRYP->DMACR &= ~(uint32_t)CRYP_DMACR_DOEN;
    CRYP->CR &= ~(uint32_t)CRYP_CR_CRYPEN;

    /* Save the current configuration (bit 19, bit[17:16] and bits [9:2] in the CRYP_CR register) */
    CRYP_ContextSave->CR_CurrentConfig  = CRYP->CR & (CRYP_CR_GCM_CCMPH |
                                                      CRYP_CR_KEYSIZE  |
                                                      CRYP_CR_DATATYPE |
                                                      CRYP_CR_ALGOMODE |
                                                      CRYP_CR_ALGODIR);

    /* and, if not in ECB mode, the initialization vectors. */
    CRYP_ContextSave->CRYP_IV0LR = CRYP->IV0LR;
    CRYP_ContextSave->CRYP_IV0RR = CRYP->IV0RR;
    CRYP_ContextSave->CRYP_IV1LR = CRYP->IV1LR;
    CRYP_ContextSave->CRYP_IV1RR = CRYP->IV1RR;

    /* save The key value */
    CRYP_ContextSave->CRYP_K0LR = CRYP_KeyInitStruct->CRYP_Key0Left; 
    CRYP_ContextSave->CRYP_K0RR = CRYP_KeyInitStruct->CRYP_Key0Right; 
    CRYP_ContextSave->CRYP_K1LR = CRYP_KeyInitStruct->CRYP_Key1Left; 
    CRYP_ContextSave->CRYP_K1RR = CRYP_KeyInitStruct->CRYP_Key1Right; 
    CRYP_ContextSave->CRYP_K2LR = CRYP_KeyInitStruct->CRYP_Key2Left; 
    CRYP_ContextSave->CRYP_K2RR = CRYP_KeyInitStruct->CRYP_Key2Right; 
    CRYP_ContextSave->CRYP_K3LR = CRYP_KeyInitStruct->CRYP_Key3Left; 
    CRYP_ContextSave->CRYP_K3RR = CRYP_KeyInitStruct->CRYP_Key3Right; 

    /* Save the content of context swap registers */
    CRYP_ContextSave->CRYP_CSGCMCCMR[0] = CRYP->CSGCMCCM0R;
    CRYP_ContextSave->CRYP_CSGCMCCMR[1] = CRYP->CSGCMCCM1R;
    CRYP_ContextSave->CRYP_CSGCMCCMR[2] = CRYP->CSGCMCCM2R;
    CRYP_ContextSave->CRYP_CSGCMCCMR[3] = CRYP->CSGCMCCM3R;
    CRYP_ContextSave->CRYP_CSGCMCCMR[4] = CRYP->CSGCMCCM4R;
    CRYP_ContextSave->CRYP_CSGCMCCMR[5] = CRYP->CSGCMCCM5R;
    CRYP_ContextSave->CRYP_CSGCMCCMR[6] = CRYP->CSGCMCCM6R;
    CRYP_ContextSave->CRYP_CSGCMCCMR[7] = CRYP->CSGCMCCM7R;
    
    CRYP_ContextSave->CRYP_CSGCMR[0] = CRYP->CSGCM0R;
    CRYP_ContextSave->CRYP_CSGCMR[1] = CRYP->CSGCM1R;
    CRYP_ContextSave->CRYP_CSGCMR[2] = CRYP->CSGCM2R;
    CRYP_ContextSave->CRYP_CSGCMR[3] = CRYP->CSGCM3R;
    CRYP_ContextSave->CRYP_CSGCMR[4] = CRYP->CSGCM4R;
    CRYP_ContextSave->CRYP_CSGCMR[5] = CRYP->CSGCM5R;
    CRYP_ContextSave->CRYP_CSGCMR[6] = CRYP->CSGCM6R;
    CRYP_ContextSave->CRYP_CSGCMR[7] = CRYP->CSGCM7R;
    
   /* When needed, save the DMA status (pointers for IN and OUT messages, 
      number of remaining bytes, etc.) */
     
    status = SUCCESS;
  }

   return status;
}

/**
  * @brief  Restores the CRYP peripheral Context.
  * @note   Since the DMA transfer is stopped in CRYP_SaveContext() function,
  *         after restoring the context, you have to enable the DMA again (if the
  *         DMA was previously used).  
  * @param  CRYP_ContextRestore: pointer to a CRYP_Context structure that contains
  *         the repository for saved context.
  * @note   The data that were saved during context saving must be rewritten into
  *         the IN FIFO.
  * @retval None
  */
void CRYP_RestoreContext(CRYP_Context* CRYP_ContextRestore)  
{

  /* Configure the processor with the saved configuration */
  CRYP->CR = CRYP_ContextRestore->CR_CurrentConfig;

  /* restore The key value */
  CRYP->K0LR = CRYP_ContextRestore->CRYP_K0LR; 
  CRYP->K0RR = CRYP_ContextRestore->CRYP_K0RR;
  CRYP->K1LR = CRYP_ContextRestore->CRYP_K1LR;
  CRYP->K1RR = CRYP_ContextRestore->CRYP_K1RR;
  CRYP->K2LR = CRYP_ContextRestore->CRYP_K2LR;
  CRYP->K2RR = CRYP_ContextRestore->CRYP_K2RR;
  CRYP->K3LR = CRYP_ContextRestore->CRYP_K3LR;
  CRYP->K3RR = CRYP_ContextRestore->CRYP_K3RR;

  /* and the initialization vectors. */
  CRYP->IV0LR = CRYP_ContextRestore->CRYP_IV0LR;
  CRYP->IV0RR = CRYP_ContextRestore->CRYP_IV0RR;
  CRYP->IV1LR = CRYP_ContextRestore->CRYP_IV1LR;
  CRYP->IV1RR = CRYP_ContextRestore->CRYP_IV1RR;

  /* Restore the content of context swap registers */
  CRYP->CSGCMCCM0R = CRYP_ContextRestore->CRYP_CSGCMCCMR[0];
  CRYP->CSGCMCCM1R = CRYP_ContextRestore->CRYP_CSGCMCCMR[1];
  CRYP->CSGCMCCM2R = CRYP_ContextRestore->CRYP_CSGCMCCMR[2];
  CRYP->CSGCMCCM3R = CRYP_ContextRestore->CRYP_CSGCMCCMR[3];
  CRYP->CSGCMCCM4R = CRYP_ContextRestore->CRYP_CSGCMCCMR[4];
  CRYP->CSGCMCCM5R = CRYP_ContextRestore->CRYP_CSGCMCCMR[5];
  CRYP->CSGCMCCM6R = CRYP_ContextRestore->CRYP_CSGCMCCMR[6];
  CRYP->CSGCMCCM7R = CRYP_ContextRestore->CRYP_CSGCMCCMR[7];
  
  CRYP->CSGCM0R = CRYP_ContextRestore->CRYP_CSGCMR[0];
  CRYP->CSGCM1R = CRYP_ContextRestore->CRYP_CSGCMR[1];
  CRYP->CSGCM2R = CRYP_ContextRestore->CRYP_CSGCMR[2];
  CRYP->CSGCM3R = CRYP_ContextRestore->CRYP_CSGCMR[3];
  CRYP->CSGCM4R = CRYP_ContextRestore->CRYP_CSGCMR[4];
  CRYP->CSGCM5R = CRYP_ContextRestore->CRYP_CSGCMR[5];
  CRYP->CSGCM6R = CRYP_ContextRestore->CRYP_CSGCMR[6];
  CRYP->CSGCM7R = CRYP_ContextRestore->CRYP_CSGCMR[7];
  
  /* Enable the cryptographic processor */
  CRYP->CR |= CRYP_CR_CRYPEN;
}
/**
  * @}
  */

/** @defgroup CRYP_Group4 CRYP's DMA interface Configuration function
 *  @brief   CRYP's DMA interface Configuration function 
 *
@verbatim   
 ===============================================================================
             ##### CRYP's DMA interface Configuration function #####
 ===============================================================================  
 [..] This section provides functions allowing to configure the DMA interface for 
      CRYP data input and output transfer.
   
 [..] When the DMA mode is enabled (using the CRYP_DMACmd() function), data can be 
      transferred:
   (+) From memory to the CRYP IN FIFO using the DMA peripheral by enabling 
       the CRYP_DMAReq_DataIN request.
   (+) From the CRYP OUT FIFO to the memory using the DMA peripheral by enabling 
       the CRYP_DMAReq_DataOUT request.

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the CRYP DMA interface.
  * @param  CRYP_DMAReq: specifies the CRYP DMA transfer request to be enabled or disabled.
  *           This parameter can be any combination of the following values:
  *            @arg CRYP_DMAReq_DataOUT: DMA for outgoing(Tx) data transfer
  *            @arg CRYP_DMAReq_DataIN: DMA for incoming(Rx) data transfer
  * @param  NewState: new state of the selected CRYP DMA transfer request.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CRYP_DMACmd(uint8_t CRYP_DMAReq, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_CRYP_DMAREQ(CRYP_DMAReq));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected CRYP DMA request */
    CRYP->DMACR |= CRYP_DMAReq;
  }
  else
  {
    /* Disable the selected CRYP DMA request */
    CRYP->DMACR &= (uint8_t)~CRYP_DMAReq;
  }
}
/**
  * @}
  */

/** @defgroup CRYP_Group5 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions
 *
@verbatim   
 ===============================================================================
              ##### Interrupts and flags management functions #####
 ===============================================================================  
 
 [..] This section provides functions allowing to configure the CRYP Interrupts and 
      to get the status and Interrupts pending bits.

 [..] The CRYP provides 2 Interrupts sources and 7 Flags:

 *** Flags : ***
 ===============
 [..] 
   (#) CRYP_FLAG_IFEM :  Set when Input FIFO is empty. This Flag is cleared only
       by hardware.
      
   (#) CRYP_FLAG_IFNF :  Set when Input FIFO is not full. This Flag is cleared 
       only by hardware.


   (#) CRYP_FLAG_INRIS  : Set when Input FIFO Raw interrupt is pending it gives 
       the raw interrupt state prior to masking of the input FIFO service interrupt.
       This Flag is cleared only by hardware.
     
   (#) CRYP_FLAG_OFNE   : Set when Output FIFO not empty. This Flag is cleared 
       only by hardware.
        
   (#) CRYP_FLAG_OFFU   : Set when Output FIFO is full. This Flag is cleared only 
       by hardware.
                           
   (#) CRYP_FLAG_OUTRIS : Set when Output FIFO Raw interrupt is pending it gives 
       the raw interrupt state prior to masking of the output FIFO service interrupt.
       This Flag is cleared only by hardware.
                               
   (#) CRYP_FLAG_BUSY   : Set when the CRYP core is currently processing a block 
       of data or a key preparation (for AES decryption). This Flag is cleared 
       only by hardware. To clear it, the CRYP core must be disabled and the last
       processing has completed. 

 *** Interrupts : ***
 ====================
 [..]
   (#) CRYP_IT_INI   : The input FIFO service interrupt is asserted when there 
      are less than 4 words in the input FIFO. This interrupt is associated to 
      CRYP_FLAG_INRIS flag.

      -@- This interrupt is cleared by performing write operations to the input FIFO 
          until it holds 4 or more words. The input FIFO service interrupt INMIS is 
          enabled with the CRYP enable bit. Consequently, when CRYP is disabled, the 
          INMIS signal is low even if the input FIFO is empty.



   (#) CRYP_IT_OUTI  : The output FIFO service interrupt is asserted when there 
       is one or more (32-bit word) data items in the output FIFO. This interrupt 
       is associated to CRYP_FLAG_OUTRIS flag.

       -@- This interrupt is cleared by reading data from the output FIFO until there 
           is no valid (32-bit) word left (that is, the interrupt follows the state 
           of the OFNE (output FIFO not empty) flag).

 *** Managing the CRYP controller events : ***
 =============================================
 [..] The user should identify which mode will be used in his application to manage 
      the CRYP controller events: Polling mode or Interrupt mode.

   (#) In the Polling Mode it is advised to use the following functions:
       (++) CRYP_GetFlagStatus() : to check if flags events occur. 

       -@@- The CRYPT flags do not need to be cleared since they are cleared as 
            soon as the associated event are reset.   


   (#) In the Interrupt Mode it is advised to use the following functions:
       (++) CRYP_ITConfig()       : to enable or disable the interrupt source.
       (++) CRYP_GetITStatus()    : to check if Interrupt occurs.

       -@@- The CRYPT interrupts have no pending bits, the interrupt is cleared as 
             soon as the associated event is reset. 

@endverbatim
  * @{
  */ 

/**
  * @brief  Enables or disables the specified CRYP interrupts.
  * @param  CRYP_IT: specifies the CRYP interrupt source to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg CRYP_IT_INI: Input FIFO interrupt
  *            @arg CRYP_IT_OUTI: Output FIFO interrupt
  * @param  NewState: new state of the specified CRYP interrupt.
  *           This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CRYP_ITConfig(uint8_t CRYP_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_CRYP_CONFIG_IT(CRYP_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected CRYP interrupt */
    CRYP->IMSCR |= CRYP_IT;
  }
  else
  {
    /* Disable the selected CRYP interrupt */
    CRYP->IMSCR &= (uint8_t)~CRYP_IT;
  }
}

/**
  * @brief  Checks whether the specified CRYP interrupt has occurred or not.
  * @note   This function checks the status of the masked interrupt (i.e the 
  *         interrupt should be previously enabled).     
  * @param  CRYP_IT: specifies the CRYP (masked) interrupt source to check.
  *           This parameter can be one of the following values:
  *            @arg CRYP_IT_INI: Input FIFO interrupt
  *            @arg CRYP_IT_OUTI: Output FIFO interrupt
  * @retval The new state of CRYP_IT (SET or RESET).
  */
ITStatus CRYP_GetITStatus(uint8_t CRYP_IT)
{
  ITStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_CRYP_GET_IT(CRYP_IT));

  /* Check the status of the specified CRYP interrupt */
  if ((CRYP->MISR &  CRYP_IT) != (uint8_t)RESET)
  {
    /* CRYP_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* CRYP_IT is reset */
    bitstatus = RESET;
  }
  /* Return the CRYP_IT status */
  return bitstatus;
}

/**
  * @brief  Returns whether CRYP peripheral is enabled or disabled.
  * @param  none.
  * @retval Current state of the CRYP peripheral (ENABLE or DISABLE).
  */
FunctionalState CRYP_GetCmdStatus(void)
{
  FunctionalState state = DISABLE;

  if ((CRYP->CR & CRYP_CR_CRYPEN) != 0)
  {
    /* CRYPEN bit is set */
    state = ENABLE;
  }
  else
  {
    /* CRYPEN bit is reset */
    state = DISABLE;
  }
  return state;
}

/**
  * @brief  Checks whether the specified CRYP flag is set or not.
  * @param  CRYP_FLAG: specifies the CRYP flag to check.
  *          This parameter can be one of the following values:
  *            @arg CRYP_FLAG_IFEM: Input FIFO Empty flag.
  *            @arg CRYP_FLAG_IFNF: Input FIFO Not Full flag.
  *            @arg CRYP_FLAG_OFNE: Output FIFO Not Empty flag.
  *            @arg CRYP_FLAG_OFFU: Output FIFO Full flag.
  *            @arg CRYP_FLAG_BUSY: Busy flag.
  *            @arg CRYP_FLAG_OUTRIS: Output FIFO raw interrupt flag.
  *            @arg CRYP_FLAG_INRIS: Input FIFO raw interrupt flag.
  * @retval The new state of CRYP_FLAG (SET or RESET).
  */
FlagStatus CRYP_GetFlagStatus(uint8_t CRYP_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint32_t tempreg = 0;

  /* Check the parameters */
  assert_param(IS_CRYP_GET_FLAG(CRYP_FLAG));

  /* check if the FLAG is in RISR register */
  if ((CRYP_FLAG & FLAG_MASK) != 0x00) 
  {
    tempreg = CRYP->RISR;
  }
  else  /* The FLAG is in SR register */
  {
    tempreg = CRYP->SR;
  }


  /* Check the status of the specified CRYP flag */
  if ((tempreg & CRYP_FLAG ) != (uint8_t)RESET)
  {
    /* CRYP_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* CRYP_FLAG is reset */
    bitstatus = RESET;
  }

  /* Return the CRYP_FLAG status */
  return  bitstatus;
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

#endif /* CRYP */

/**
  * @}
  */ 
