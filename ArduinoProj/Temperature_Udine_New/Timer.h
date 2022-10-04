#ifndef _TIMER_H_
#define _TIMER_H_
#include <Arduino.h>

class Timer{
  private:
    unsigned long durata;
    unsigned long t1;
    void(*fp)(void);
    int FIRED = 0;
    int LOOP = 0;
     
  public:
    Timer(unsigned long tm);
    void run();
    void loop();
    void cback(void(*fun)(void));
    void isRepeating();
};

#endif
