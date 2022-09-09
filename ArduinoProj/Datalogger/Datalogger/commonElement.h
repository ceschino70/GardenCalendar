
RTClib myRTC;

// Constants
const int MAIN_CYCLE_TIMER = 1; // Second of main cycle
const int MILLISEC_BASE_CYCLE = 200;
const int CHIP_SELECT = 4;

// Variables
unsigned long previousSecondMainCycle = 0;

int sensorPin = A0;
double sensorValue = 0;

//Methods
String datetimeToString (DateTime datetimeValue)
{
  String str;

  str = (String)datetimeValue.day()+"/"+(String)datetimeValue.month()+"/"+(String)datetimeValue.year()
          +"-"+
          (String)datetimeValue.hour()+":"+(String)datetimeValue.minute()+":"+(String)datetimeValue.second(); 

  return str;
}