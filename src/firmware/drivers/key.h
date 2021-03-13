#ifndef _KEY_H_
#define _KEY_H_

#include <gpio.h>
#include <thread.h>
#include <config.h>

//key input
#define KEY_GPIO                    TGPIOE
#define KEY_PIN                     3

class Key: public Thread
{
  private:
    Gpio<KEY_GPIO, KEY_PIN, GPIO_MODE_IN_PULLUP> key;  //user button
    Gpio<LED_GPIO, LED_PIN, GPIO_MODE_OUT> led;        //user led

    unsigned char led_state;
    int timer_id;

    int result;

  public:
    Key();
    ~Key();

    void init();

    int read();

    void main();

    int get_result();
};


#endif
