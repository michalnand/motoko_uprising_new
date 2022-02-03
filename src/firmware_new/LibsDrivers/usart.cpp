#include "usart.h"
#include "gpio.h"


Usart::Usart()
{
  
}

Usart::~Usart()
{

}

void Usart::init(unsigned int baudrate, USART_TypeDef *usart)
{
    this->usart = usart;

    if (usart == USART1)
    {
      Gpio<TGPIOA, 9, GPIO_MODE_AF>  usart_tx_pin;
      Gpio<TGPIOA, 10, GPIO_MODE_AF> usart_rx_pin;

      //Gpio<TGPIOA, 9, GPIO_MODE_AF>  usart_tx_pin;
      //Gpio<TGPIOA, 7, GPIO_MODE_AF> usart_rx_pin;

      usart_tx_pin.af_config(((uint8_t)0x07)); //AF7
      usart_rx_pin.af_config(((uint8_t)0x07)); //AF7

      RCC->APB2ENR|= RCC_APB2ENR_USART1EN;  //USART1 clock enable

      usart->CR2 = 0;  //1stop bit
      usart->CR1 = USART_CR1_RE|USART_CR1_TE;  //8bit word, no parity, RX, TX enable
      usart->CR3 = 0;

      //usart->BRR = SystemCoreClock/baudrate;
      usart->BRR = (SystemCoreClock/2)/baudrate;
      usart->CR1 |= USART_CR1_UE;    //usart enable
    } 
    else if (usart == USART2)
    {
      Gpio<TGPIOA, 2, GPIO_MODE_AF>  usart_tx_pin;
      Gpio<TGPIOA, 15, GPIO_MODE_AF> usart_rx_pin;

      usart_tx_pin.af_config(((uint8_t)0x01)); //AF1
      usart_rx_pin.af_config(((uint8_t)0x01)); //AF1

      RCC->APB1ENR|= RCC_APB1ENR_USART2EN;  //USART2 clock enable

      usart->CR2 = 0;  //1stop bit
      usart->CR1 = USART_CR1_RE|USART_CR1_TE;  //8bit word, no parity, RX, TX enable
      usart->CR3 = 0;

      usart->BRR = SystemCoreClock/baudrate;
      usart->CR1 |= USART_CR1_UE;    //usart enable
    }

} 



void Usart::put_char(char c)
{
    while (!USART_GetFlagStatus(usart, USART_FLAG_TXE))
    {

    }
    
    USART_SendData(usart, c);
}

char Usart::get_char()
{
  unsigned int c;
  while ( (c = ischar()) == NO_CHAR)
  {
    __asm("nop");
  }

  return c;
}

unsigned int Usart::ischar()
{
  if (usart->ISR & USART_ISR_RXNE)
  {
    return usart->RDR;
  }

  return NO_CHAR;
}
