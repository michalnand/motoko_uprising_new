#include <clock.h>


void SetSysClock216(void)
{
  RCC_HSEConfig(RCC_HSE_ON);

  if ( RCC_WaitForHSEStartUp() != SUCCESS )
  {
    while(1);
  }

  RCC_PLLConfig(RCC_PLLSource_HSE, 8, 432, 2, 9);
  RCC_PLLCmd(ENABLE);

  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

  /* Activate the OverDrive to reach the 216 MHz Frequency */
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

  SystemCoreClockUpdate();
}

void core_SystemClock_Config_216()
{
    SystemInit();
    SetSysClock216();
    SystemCoreClockUpdate();
}




void SetSysClock312(void)
{
  RCC_HSEConfig(RCC_HSE_ON);

  if ( RCC_WaitForHSEStartUp() != SUCCESS )
  {
    while(1);
  }

  RCC_PLLConfig(RCC_PLLSource_HSE, 4, 312, 2, 13);
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

  SystemCoreClockUpdate();
}

void core_SystemClock_Config_312()
{
    SystemInit();
    SetSysClock216();
    SystemCoreClockUpdate();
}
