#include "arduino_secrets.h"
#include "thingProperties.h"
#include "ArduinoIoTComnnection.h"

unsigned long currentMillis;

bool enable = false;
bool temperatureSentMax = false;
bool temperatureSentMin = false;

bool firstTimeNTPUpdate = true;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);
  
  Serial.println("");
  Serial.println("-- Serial STARTED! --");

  timeClient.begin();
  delay(1500);
  Serial.println("-- NTPClient STARTED! --");

  //Init of LCD display
  displayInit();
  
  String text_[NUMBER_OF_ROWS_DISPLAIED] = {"Initializing...", "", "", "", ""};
  displayText(text_);

  Serial.println("-- Display Init OK --");

  // Init the connection with Arduino IoT Cloud
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(4);
  ArduinoCloud.printDebugInfo();

  bool status;

  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(SENSOR_TEMP_ADDRESS);
  if (!status) 
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  Serial.println("-- Sensor communication Init OK --");

  Serial.println();

  // Set the switch on arduino cloud to OFF
  releCommandOn = false;
  
  // Set counter to 0
  millisecOfReleOn = 0;

  // ------------------------ Date Time Update -------------------------
  timeClient.update();
  dataTimeStartedModule = (String)timeClient.getHours()+":"+(String)timeClient.getMinutes()+":"+(String)timeClient.getSeconds();
  Serial.println("-- Module started: " + dataTimeStartedModule);
  
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  
  // ------------------------ Init GPIOs -------------------------------
  pinMode(LED_BUILTIN, OUTPUT);       // Initialize the LED_BUILTIN pin as an output
  pinMode(GPIO_RELE, OUTPUT);         // Initialize relè output
  pinMode(GPIO_RELE_FEEDBACK, INPUT); // Initialize relè feedback
}

void loop() 
{
  currentMillis = millis();

  deltaTimeFromLastExecution = currentMillis - previousMillisLasExecutionProg;
  previousMillisLasExecutionProg = currentMillis;
  
  blinkLed();

  if ((currentMillis - previousMillisMainCycle) >= TEMPERATURE_ACQ_TIMER)
  {
    printAndUpdateValues();
    
    previousMillisMainCycle = currentMillis; 
  }

  checkReleCommandOn();
  
  checkFeedbackRele();

  
  delay(MAIN_INTERVAL);

}

void checkReleCommandOn()
{
  if (releCommandOn == true && releCommandOn != releCommandOnPrevious)
  {
    // ----- TEST CONNECTION -----------
    //digitalWrite(GPIO_RELE, true);                                  // Set relè ON
    previousMilliscomandReleOn = currentMillis;                       // Reset timer
    
    Serial.println("-----------> Button pressed releStausOn = " + (String)releFeedbackOn);
  }

  if ((currentMillis - previousMilliscomandReleOn) >= RELE_ON_TIMER)  // Check if the timer if expired
  {
    // ----- TEST CONNECTION -----------
    //digitalWrite(GPIO_RELE, false);                                 // Set relè OFF
    releCommandOn = false;                                            // Set the switch on arduino cloud to OFF
  }
  
  releCommandOnPrevious = releCommandOn;
}

void checkFeedbackRele()
{
  releFeedbackOn = digitalRead(GPIO_RELE_FEEDBACK);

  // Increase the cycle only when the relè is really on
  if (releFeedbackOn == true && releFeedbackOnPrevious == false)
  {
    cyclesNumber += 1; // Increase the relè cycle counter
  }

  if(releFeedbackOn == true)
  {
    millisecOfReleOn += deltaTimeFromLastExecution; 
  }
  else
  {
    releActivationTime = millisecOfReleOn/1000;
  }

  releFeedbackOnPrevious = releFeedbackOn;
}

void printAndUpdateValues() 
{
  String connectionString;
  
  if (ArduinoCloud.connected() == 0)
  {
    Serial.println("counterESPReset = " + (String)counterESPReset);
    connectionString = "LOST";
    ++disconnectionNumber;
    digitalWrite(GPIO_RELE, true);

    if(counterESPReset >= RESET_ESP_TIMER)
    {
      Serial.println("Restarting!!!");
      delay(10000);
      ESP.restart();
    }
    
    counterESPReset += TEMPERATURE_ACQ_TIMER;
  }
  else
  {
    digitalWrite(GPIO_RELE, false);
    connectionString = "OK";
    counterESPReset = 0;

    if (firstTimeNTPUpdate)
      {
        timeClient.update();
        dataTimeStartedModule = (String)timeClient.getHours()+":"+(String)timeClient.getMinutes()+":"+(String)timeClient.getSeconds();
        String txt = "-- Main Module started: " + dataTimeStartedModule;
        displayMessageSerialAndCloud_singleLine(txt, &messageText, true, true);
        firstTimeNTPUpdate = false;
      }
  }
    
  temp_1 = bme.readTemperature();
  String tempString = "Tempe. = " + (String)temp_1 + " *C";
  Serial.println(tempString);
  
  press_1 = bme.readPressure() / 100.0F;
  String pressureString = "Press. = " + (String)press_1 + " hPa";
  Serial.println(pressureString);
  
  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");
  
  humid_1 = bme.readHumidity();
  String humidityString = "Humid. = " +  (String)humid_1 + " %";
  Serial.println(humidityString);
  
  String str = "Disc:" + (String)disconnectionNumber + "; " + (String)connectionString;
  Serial.println(str);

  temperatureAllarms(temp_1);

  String text__[NUMBER_OF_ROWS_DISPLAIED] = {"Sensor values:      ", "", tempString, humidityString, pressureString,"" ,dataTimeStartedModule ,str};
  displayText(text__);

  Serial.println();
  
  ArduinoCloud.update();
}

void blinkLed()
{
  unsigned long currentMillis = millis();
  if (ledState == HIGH && ((currentMillis - previousMillis) >= 2000)) 
  {
    ledState = LOW;
    digitalWrite(LED_BUILTIN, ledState);
    previousMillis = currentMillis;
  }
  
  if(ledState == LOW && ((currentMillis - previousMillis) >= 10))
  {
    ledState = HIGH;
    digitalWrite(LED_BUILTIN, ledState);
    previousMillis = currentMillis;
  }
}

void onReleCommandOnChange()  
{
  String txt = "Button pressed releStausOn = " + (String)releFeedbackOn;
  displayMessageSerialAndCloud_singleLine(txt, &messageText, false, true);
}

void temperatureAllarms(double temperature)
{
  if (temperature > 23 && temperatureSentMax == false)
  {
    String txt = "Tempe. Up= " + (String)temperature + " *C";
    temperatureSentMax = true;
    displayMessageSerialAndCloud_singleLine(txt, &messageText, true, true);
  }
  else if (temperature < 22.7)
  { 
    temperatureSentMax = false;
  }

  if (temperature < 21 && temperatureSentMin == false)
  {
    String txt = "Tempe. Dw= " + (String)temperature + " *C";
    temperatureSentMin = true;
    displayMessageSerialAndCloud_singleLine(txt, &messageText, true, true);
  }
  else if (temperature > 21.3)
  { 
    temperatureSentMin = false;
  }
}
