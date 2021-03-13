#ifndef _BACK_LED_LIGHT_H_
#define _BACK_LED_LIGHT_H_

#include <drivers.h>

#define BL_MODE_OFF                 ((unsigned int)0)
#define BL_MODE_ON                  ((unsigned int)1)
#define BL_MODE_FLASHING            ((unsigned int)2)
#define BL_MODE_FLASHING_START      ((unsigned int)3)
#define BL_MODE_FLASHING_FAST       ((unsigned int)4)
#define BL_MODE_BREATH              ((unsigned int)5)


class BackLedLight : public Thread
{
  private:
    Gpio<TGPIOD, 13> led_back;

    unsigned int mode;
    unsigned int cnt;
    unsigned long int time_start;


  public:
    BackLedLight();
    virtual ~BackLedLight();
    void set_mode(unsigned int mode);
    void main();
};

#endif
