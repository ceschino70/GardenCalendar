#include "Timer.h"

/* Timer with two different cicles
 * |         fun    fun        fun    fun 
 * |----------|------|----------|------|-->t
 * 0         tm1    tm2        tm1    tm2
 *    Cycle1   Cycle2   Cycle1   Cycle2
 */

// Timer initialization
// tm = timer in millisec
Timer::Timer(unsigned long tm1, unsigned long tm2){
  timer1 = tm1;
  timer2 = tm2;
  FIRED = 0;
}

void Timer::run(){
  t = millis();
  FIRED = 0;
}

// Main loop, it checks the timers
void Timer::loop(){
  //Cycle 1
  unsigned long tx = (millis() - t);
  if ((tx>timer1) && !FIRED && Timer1Enable)
  {
    fp();
    FIRED = 1;
    if (LOOP)
    {
      FIRED = 0;
      t = millis();
    }
    Timer1Enable = !Timer1Enable; 
    Timer2Enable = !Timer2Enable;
  }
  //Cycle 2
  else if ((tx>timer2) && !FIRED && Timer2Enable)
  {
    fp();
    FIRED = 1;
    if (LOOP)
    {
      FIRED = 0;
      t = millis();
    }
    Timer1Enable = !Timer1Enable; 
    Timer2Enable = !Timer2Enable;
  }
}

// Callback of function when the time is elapsed
// fun = callback function
void Timer::cback(void(*fun)(void)){
  fp = fun;
}

void Timer::isRepeating(){
  LOOP = 1;
}
