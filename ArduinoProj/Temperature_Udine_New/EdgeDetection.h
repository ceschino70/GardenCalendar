#ifndef _EDGE_DETECTION_
#define _EDGE_DETECTION_
#include <Arduino.h>

class EdgeDetection{
  private:
    bool signal;                    // Signal value
    bool signalOld;                 
    bool *signalPointer;            // Address of signal to detect
    void(*fp)(void);
    enum typeOfDetection_enum {
      TRIG_ON,
      TRIG_OFF,
      TRIG_ON_OFF
    };
    typeOfDetection_enum typeOfDetection;
     
  public:
    EdgeDetection();                // Detection class initialization 
    void run(bool *var);            // Detection start 
    void loop();                    // Main loop
    void trigOn();
    void trigOff();
    void trigOnOff();
    void cback(void(*fun)(void));   // Callback function when the edge is detect
};

#endif