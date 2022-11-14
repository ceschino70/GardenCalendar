
#if !defined(ESP8266)
  #error This code is designed to run on ESP8266 and ESP8266-based boards! Please check your Tools->Board setting.
#endif

// These define's must be placed at the beginning before #include "ESP8266TimerInterrupt.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     0

// Select a Timer Clock
#define USING_TIM_DIV1                false           // for shortest and most accurate timer
#define USING_TIM_DIV16               false           // for medium time and medium accurate timer
#define USING_TIM_DIV256              true            // for longest timer but least accurate. Default

#include "ESP8266TimerInterrupt.h"

#define TIMER_INTERRUPT_DEBUG     0
#define _TIMERINTERRUPT_LOGLEVEL_ 0

#define TIMER_INTERVAL_MS         250
#define DEBOUNCING_INTERVAL_MS    80
#define LOCAL_DEBUG               1

unsigned long lastcycleTime;

// Init ESP8266 timer 1
ESP8266Timer ITimer;

void IRAM_ATTR TimerHandler()
{
  bool returnReleFeedbackOn;
  unsigned long currentMillis = millis();

  // Convert analog input to digital value
  returnReleFeedbackOn = (relayStatusRead > 100)? true : false;

  // Increase the cycle only when the relè is really on
  if (returnReleFeedbackOn == true){
    millisecOfReleOn += (int)(currentMillis - lastcycleTime); // Increase the relay timer on
    if (releFeedbackOnPrevious == false){
      cyclesNumberOfRele += 1;                      // Increase the relay counter state
      previousMilliscomandReleOn = currentMillis;   // Reset relay timer calculation
    }
  }else{
    releActivationTimeInSec = millisecOfReleOn/1000;  
  }  

  if ((currentMillis - previousMilliscomandReleOn) >= RELE_ON_TIMER){ // Check if the timer if expired
    digitalWrite(GPIO_RELE, false);                                   // Set relè OFF
    releCommandOn = false;                                            // Set the switch on arduino cloud to OFF
  }
  releFeedbackOnPrevious = returnReleFeedbackOn;
  releFeedbackOn = returnReleFeedbackOn;

  lastcycleTime = currentMillis;
}

bool timerInteruptInit()
{
  bool initReturnSuccesful = false;
  initReturnSuccesful =(ITimer.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, TimerHandler))? true: false;
  return initReturnSuccesful;
} 