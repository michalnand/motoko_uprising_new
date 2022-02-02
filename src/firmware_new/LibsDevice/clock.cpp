#include "clock.h"

extern uint32_t SystemCoreClock;


void SetSysClock216(uint32_t hse_freq)
{
  SystemCoreClock = 216000000;

  RCC_HSEConfig(RCC_HSE_ON);

  if ( RCC_WaitForHSEStartUp() != SUCCESS )
  {
    while(1);
  }

  RCC_PLLConfig(RCC_PLLSource_HSE, hse_freq, 432, 2, 9);
  RCC_PLLCmd(ENABLE);

  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
  {
    __asm("nop");
  };

  /* Activate the OverDrive to reach the 216 MHz Frequency */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  PWR_OverDriveCmd(ENABLE);

  while(PWR_GetFlagStatus(PWR_FLAG_ODRDY) == RESET )
  {
    __asm("nop");
  }

  while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET)
  {
    __asm("nop");
  }

  PWR_OverDriveSWCmd(ENABLE);

  while(PWR_GetFlagStatus(PWR_FLAG_ODSWRDY) == RESET )
  {
    __asm("nop");
  }

  FLASH_SetLatency(FLASH_Latency_7);
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

  RCC_HCLKConfig(RCC_SYSCLK_Div1);
  RCC_PCLK1Config(RCC_HCLK_Div4);
  RCC_PCLK2Config(RCC_HCLK_Div2);
}


void SetSysClock312(uint32_t hse_freq)
{
  SystemCoreClock = 320000000;
  
  RCC_HSEConfig(RCC_HSE_ON);

  if ( RCC_WaitForHSEStartUp() != SUCCESS )
  {
    while(1);
  }

  RCC_PLLConfig(RCC_PLLSource_HSE, hse_freq/4, 320, 4, 12);
  RCC_PLLCmd(ENABLE);

  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

  /* Activate the OverDrive to reach the 312 MHz Frequency */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  PWR_OverDriveCmd(ENABLE);

  while(PWR_GetFlagStatus(PWR_FLAG_ODRDY) == RESET );

  while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);

  PWR_OverDriveSWCmd(ENABLE);

  while(PWR_GetFlagStatus(PWR_FLAG_ODSWRDY) == RESET );

  FLASH_SetLatency(FLASH_Latency_7);
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

  RCC_HCLKConfig(RCC_SYSCLK_Div1);
  RCC_PCLK1Config(RCC_HCLK_Div4);
  RCC_PCLK2Config(RCC_HCLK_Div2);
}


void SetSysClock(uint32_t mode)
{
  SystemInit(); 
  if (mode == SysClok216_8HSE)
  {
    SetSysClock216(8);
  }
  else if (mode == SysClok312_8HSE)
  {
    SetSysClock312(8);
  }
  else if (mode == SysClok216_24HSE)
  {
    SetSysClock216(24);
  }
  else if (mode == SysClok312_24HSE)
  {
    SetSysClock312(24);
  }

  //SystemCoreClockUpdate();
}

