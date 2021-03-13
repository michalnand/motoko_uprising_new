
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F7xx_CRC_H
#define __STM32F7xx_CRC_H

#ifdef __cplusplus
 extern "C" {
#endif

/*!< Includes ----------------------------------------------------------------*/
#include "stm32f7xx.h"

/** @addtogroup STM32F7xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup CRC
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup CRC_ReverseInputData
  * @{
  */
#define CRC_ReverseInputData_No             ((uint32_t)0x00000000) /*!< No reverse operation of Input Data */
#define CRC_ReverseInputData_8bits          CRC_CR_REV_IN_0        /*!< Reverse operation of Input Data on 8 bits */
#define CRC_ReverseInputData_16bits         CRC_CR_REV_IN_1        /*!< Reverse operation of Input Data on 16 bits */
#define CRC_ReverseInputData_32bits         CRC_CR_REV_IN          /*!< Reverse operation of Input Data on 32 bits */

#define IS_CRC_REVERSE_INPUT_DATA(DATA) (((DATA) == CRC_ReverseInputData_No)     || \
                                         ((DATA) == CRC_ReverseInputData_8bits)  || \
                                         ((DATA) == CRC_ReverseInputData_16bits) || \
                                         ((DATA) == CRC_ReverseInputData_32bits))

/**
  * @}
  */

/** @defgroup CRC_PolynomialSize
  * @{
  */
#define CRC_PolSize_7                       CRC_CR_POLYSIZE       /*!< 7-bit polynomial for CRC calculation */
#define CRC_PolSize_8                       CRC_CR_POLYSIZE_1     /*!< 8-bit polynomial for CRC calculation */
#define CRC_PolSize_16                      CRC_CR_POLYSIZE_0     /*!< 16-bit polynomial for CRC calculation */
#define CRC_PolSize_32                      ((uint32_t)0x00000000)/*!< 32-bit polynomial for CRC calculation */

#define IS_CRC_POL_SIZE(SIZE) (((SIZE) == CRC_PolSize_7)  || \
                               ((SIZE) == CRC_PolSize_8)  || \
                               ((SIZE) == CRC_PolSize_16) || \
                               ((SIZE) == CRC_PolSize_32))

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* Configuration of the CRC computation unit **********************************/
void CRC_DeInit(void);
void CRC_ResetDR(void);
void CRC_PolynomialSizeSelect(uint32_t CRC_PolSize); /* Select or Config, which one is the best */
void CRC_ReverseInputDataSelect(uint32_t CRC_ReverseInputData);
void CRC_ReverseOutputDataCmd(FunctionalState NewState);
void CRC_SetInitRegister(uint32_t CRC_InitValue); /* change the function proto to SetInitRemainder() ??? */
void CRC_SetPolynomial(uint32_t CRC_Pol);

/* CRC computation ************************************************************/
uint32_t CRC_CalcCRC(uint32_t CRC_Data);
uint32_t CRC_CalcCRC16bits(uint16_t CRC_Data);
uint32_t CRC_CalcCRC8bits(uint8_t CRC_Data);
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength);
uint32_t CRC_GetCRC(void);

/* Independent register (IDR) access (write/read) *****************************/
void CRC_SetIDRegister(uint8_t CRC_IDValue);
uint8_t CRC_GetIDRegister(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F7xx_CRC_H */

/**
  * @}
  */

/**
  * @}
  */