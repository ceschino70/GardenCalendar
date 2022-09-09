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
}

void loop() 
{
  
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin) * (5.0 / 1023.0);
  //Serial.println(sensorValue);
  
  DateTime now = myRTC.now();
  
  unsigned long currentsecond = now.unixtime();
  if ((currentsecond - previousSecondMainCycle) >= MAIN_CYCLE_TIMER)
  {
    previousSecondMainCycle = currentsecond;
    
    String str = datetimeToString(now)+ " " + (String)sensorValue;
    Serial.println(str);
    Serial.println("Main cycle started!");

    File dataFile = SD.open("datalog.txt", FILE_WRITE);

    if (dataFile) 
    {
      dataFile.println(str);
      dataFile.close();
    }
    else 
    {
      Serial.println("error opening datalog.txt");
    }
  }
  delay(MILLISEC_BASE_CYCLE);
}
