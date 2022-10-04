#include "Timer.h"

Timer::Timer(unsigned long tm){
  durata = tm;
  FIRED = 0;
}

void Timer::run(){
  t1 = millis();
  FIRED = 0;
  
}

void Timer::loop(){
  unsigned long tx = (millis() - t1);
  if ((tx>durata) && !FIRED){
    fp();
    FIRED = 0;
    if (LOOP){
      FIRED = 0;
      t1 = millis();
    }
  }
}

void Timer::cback(void(*fun)(void)){
  fp = fun;
}

void Timer::isRepeating(){
  LOOP = 1;
}
