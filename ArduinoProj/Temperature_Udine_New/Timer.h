#ifndef _TIMER_H_
#define _TIMER_H_
#include <Arduino.h>

class Timer{
  private:
    unsigned long timer1;
    unsigned long timer2;
    unsigned long t;
    void(*fp)(void);
    int FIRED = 0;
    int LOOP = 0;
    bool Timer1Enable = 1;
    bool Timer2Enable = 0;
     
  public:
    Timer(unsigned long tm1, unsigned long tm2);        // Timer initialization 
    void run();                     // Timer start 
    void loop();                    // Main loop where it check if the time is finish
    void isRepeating();             // If you whnt creat a recursive timer
    void cback(void(*fun)(void));   // Callback of function when the time is elapsed
};

#endif
