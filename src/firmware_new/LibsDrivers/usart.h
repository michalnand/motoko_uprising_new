#ifndef _USART_H_
#define _USART_H_


#include <device.h>

#define NO_CHAR       ((unsigned int)0xffff)

class Usart
{
  public:
    Usart();
    virtual ~Usart();

    void init(unsigned int baudrate = 115200, USART_TypeDef *usart = USART1);

    void put_char(char c);
    char get_char();

    unsigned int ischar();

  private:
    USART_TypeDef *usart;
};


#endif
