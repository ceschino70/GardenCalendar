#include "Timer.h"

// Timer initialization
// tm = timer in millisec
Timer::Timer(unsigned long tm1, unsigned long tm2){
  timer1 = tm1;
  timer2 = tm2;
  FIRED = 0;
  Timer1Enable = 1;
  Timer2Enable = 0;
}

void Timer::run(){
  t = millis();
  FIRED = 0;
}

//
void Timer::loop(){
  unsigned long tx = (millis() - t);
  if ((tx>timer1) && !FIRED && Timer1Enable){
    fp();
    FIRED = 0;
    if (LOOP){
      FIRED = 0;
      t = millis();
    }
    Timer1Enable = !Timer1Enable; 
    Timer2Enable = !Timer2Enable;
  }
  if ((tx>timer2) && !FIRED && Timer2Enable){
    fp();
    FIRED = 0;
    if (LOOP){
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
