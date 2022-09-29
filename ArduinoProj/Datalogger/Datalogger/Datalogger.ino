#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <DS3231.h>

#include "commonElement.h"

void setup() 
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) 
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(CHIP_SELECT)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("card initialized.");

  Wire.begin();
  
  int ii = ((MAIN_CYCLE_TIMER *1000)/MILLISEC_BASE_CYCLE);
  
  Serial.println("---> Number of base cycle " + (String)ii);

  arrayIndexSaved = 0;
}

void loop() 
{
  
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin) * (5.0 / 1023.0);
  //Serial.println(sensorValue);
  
  DateTime now = myRTC.now();

  _sensorValues[arrayIndexSaved] = sensorValue;
  
  if(arrayIndexSaved < ARRAY_DIMENSION)
  {
    ++arrayIndexSaved;
  }
  
  unsigned long currentsecond = now.unixtime();
  if ((currentsecond - previousSecondMainCycle) >= MAIN_CYCLE_TIMER)
  {
    Serial.println("---> arrayIndexSaved = " + (String)arrayIndexSaved);
    String str1 = convertArrayToString(_sensorValues, arrayIndexSaved -1);
    
    previousSecondMainCycle = currentsecond;
    
    String str = datetimeToString(now);
    Serial.println(str + " " + str1);
    //Serial.println("Main cycle started!");

    File dataFile = SD.open("datalog.txt", FILE_WRITE);

    if (dataFile) 
    {
      dataFile.print(str);
      
      for (int i = 0; i < arrayIndexSaved; i++)
      { 
        dataFile.print(";");
        dataFile.println((String)_sensorValues[i]);
        //dataFile.println(";");
      }
      
      dataFile.close();
    }
    else 
    {
      Serial.println("error opening datalog.txt");
    }
    arrayIndexSaved = 0;
  }
  
  delay(MILLISEC_BASE_CYCLE);
}
