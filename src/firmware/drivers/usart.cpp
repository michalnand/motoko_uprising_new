#include <usart.h>
#include <gpio.h>

#include <config.h>
#include <stm32f7xx.h>
#include <stm32f7xx_hal.h>


//use usart1, on pins PA9 and PA10
#define USART      USART1
#define    USART_BAUD            115200


Usart::Usart()
{

}


void Usart::init(unsigned int baudrate)
{
    Gpio<TGPIOA, 9, GPIO_MODE_AF>  usart_tx_pin;
    Gpio<TGPIOA, 10, GPIO_MODE_AF> usart_rx_pin;

    usart_tx_pin.af_config(((uint8_t)0x07)); //AF7
    usart_rx_pin.af_config(((uint8_t)0x07)); //AF7

    RCC->APB2ENR|= RCC_APB2ENR_USART1EN;  //USART1 clock enable

    USART1->CR2 = 0;  //1stop bit
    USART1->CR1 = USART_CR1_RE|USART_CR1_TE;  //8bit word, no parity, RX, TX enable
    USART1->CR3 = 0;

    USART1->BRR = F_CPU/(2*baudrate);
    USART1->CR1 |= USART_CR1_UE;    //usart enable

}

Usart::~Usart()
{


}

void Usart::put_char(char c)
{

    while (!USART_GetFlagStatus(USART1, USART_FLAG_TXE))
    {
    }
    USART_SendData(USART1, c);
}

char Usart::get_char()
{
  unsigned int c;
  while ( (c = ischar()) == NO_CHAR)
    __asm("nop");

  return c;
}

unsigned int Usart::ischar()
{
  if (USART->ISR & USART_ISR_RXNE)
  {
    return USART->RDR;
  }

  return NO_CHAR;
}
