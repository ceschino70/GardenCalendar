#include "EdgeDetection.h"

/* Edge Detection
*   This function detect trige on, trig off and both edges.
*
*      ^         ____________
*      |        /            \
*      |       /              \
*      |______/                \________
*      ----------------------------------->t    
*              ^             ^
*/

EdgeDetection::EdgeDetection()
{
}

void EdgeDetection::run(bool *var)
{
  signalPointer = var;
}

void EdgeDetection::loop()
{
  signal =  *signalPointer;
  switch (typeOfDetection) 
  {
    case TRIG_ON:
      if((signal == true) && (signalOld == false))
      {
        fp();
      }
          
      break;
    case TRIG_OFF:
      if((signal == true) && (signalOld == false))
      {
        fp();
      }
      break;
    case TRIG_ON_OFF:
      if(signal != signalOld)
      {
        fp();
      }
      break;
    default:
      break;
  }
  signalOld = signal;
}

void EdgeDetection::trigOn()
{
  typeOfDetection = TRIG_ON;
}

void EdgeDetection::trigOff()
{
  typeOfDetection = TRIG_OFF;
}

void EdgeDetection::trigOnOff()
{
  typeOfDetection = TRIG_ON_OFF;
}

void EdgeDetection::cback(void(*fun)(void))
{
  fp = fun;
}

