#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "Timer.h"
#include "ArduinoIoTComnnection.h"
#include "EdgeDetection.h"

// I2C Addresses
#define SENSOR_TEMP_ADDRESS 0x76    // I2C Address of BME260 sensor
#define SCREEN_ADDRESS 0x3C         // I2C Address of display OLED 

#define SEALEVELPRESSURE_HPA (1011)
#define OLED_RESET -1               // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_WIDTH 128            // OLED display width, in pixels
#define SCREEN_HEIGHT 64            // OLED display height, in pixels
#define NUMBER_OF_ROWS_DISPLAIED 8  // Number of rows 

// GPIO Description 
#define GPIO_RELE D8                // Relè connected to GPIO 15
#define GPIO_RELE_FEEDBACK D7       // Relè feedback connected to GPIO 13
#define GPIO_PUSCHBUTTON D0         // Push button pin GPIO 16

// Definition of constant timers
const int MAIN_INTERVAL           = 10;     // Main timer in millisec
const int FAST_CYCLE_TIMER        = 500;    // Fast timer: check push button
const int SLOW_CYCLE_TIMER        = 2000;   // Slow timer: read & update BME280 sensor
const int RELE_CEACK_TIMER        = 2000;   // Filter commamd for relè 
const int INTERVAL                = 1000;   // Interval at which to blink (milliseconds)
const int ENABLE_COMMAND_TIMER    = 5000;   // Timer for command enable
const int RELE_ON_TIMER           = 10000;  // Relè On timer
const int RESET_ESP_TIMER         = 600000; // Number of millisec to wait before ESP reset when arduino IoT cloud connection is lost
const long UTC_OFFSET_IN_SECONDS  = 3600;   // Time zone +2h => 2h * 60min * 60sec = 7200

// Global variables
float         temp;
int           humidity;
unsigned long previousMillis = 0;                 // will store last time LED was updated
int           ledState = LOW;                     // ledState used to set the LED
bool          releChangeEnable = true;            // The onReleCommandOnChange can chenge the relè output
int           onReleCommandOnChangeCounter = 1;   // When the board connects to IoT cloud generate onReleCommandOnChange event
bool          releCommandOnPrevious = false;
bool          releFeedbackOnPrevious = false;
unsigned int  millisecOfReleOn = 0;               // Number of seconds of relè in ON state
unsigned int  deltaTimeFromLastExecution = 0;
int           disconnectionNumber;
int           counterESPReset = 0;                // Number of cycle before to ESP reset
String        dataTimeStartedModule;              // Date and Time when module is started
unsigned long currentMillis;
int           cyclesNumberOfRele;
int           releActivationTimeInSec;
bool          firstTimeNTPUpdate = true;          // Disable restart function before first connection
bool          statusButtonOld;
bool          cloudConnection;
bool          buttonStatus = false;
float         deltaTemperature = 0.4;

struct temperatureTheshold {
  float minAllarm;
  float minWorning;
  float maxWorning;
  float maxAllarm;
};

struct temperatureAcqValue {
  float temp;
  float humid;
  float press;
  String tempStr;
  String humidStr;
  String pressStr;
};

enum menuDisplay_enum {
  PageSensorsValue,
  PageSettings
};

unsigned long previousMillisMainCycle = 0;
unsigned long previousMilliscomandReleOn = 0;
unsigned long previousMillisLasExecutionProg = 0;

bool temperatureSentMax = false;
bool temperatureSentMin = false;

// Set home page
menuDisplay_enum menuDisplay = PageSensorsValue;
temperatureAcqValue acq;
temperatureTheshold tempTh;

//Temperature sensor
Adafruit_BME280 bme; // I2C

//Display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", UTC_OFFSET_IN_SECONDS);

// Timers instance
Timer timer_BlinkLed  = Timer(10, 4000);
Timer timer_cycleSlow = Timer(SLOW_CYCLE_TIMER, SLOW_CYCLE_TIMER);
Timer timer_cycleFast = Timer(FAST_CYCLE_TIMER, FAST_CYCLE_TIMER);
Timer timer_homePage  = Timer(10000,10000);

// Edge detection instances
EdgeDetection edgeDetecPushButton = EdgeDetection();

void displayMessageSerialAndCloud_singleLine(String message, String *messageTextForArduinoCloud, bool enablesendingToArduinoCloud = true, bool debugString = false)
{
  String text;
  if(debugString == true)
  {
    text = "----->";
  }

  text = text + message;
  Serial.println(text);

  if (enablesendingToArduinoCloud == true)
    *messageTextForArduinoCloud = text;
}

void displayInit ()
{
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
}

void temperatureAllarms(double temperature, String *messageTextForArduinoCloud)
{  
  if (temperature > tempTh.maxAllarm && temperatureSentMax == false)
  {
    String txt = "Tempe. Up= " + (String)temperature + " *C";
    temperatureSentMax = true;
    displayMessageSerialAndCloud_singleLine(txt, messageTextForArduinoCloud, true, true);
  }
  else if (temperature < (tempTh.maxAllarm - deltaTemperature))
  { 
    temperatureSentMax = false;
  }

  if (temperature < tempTh.minAllarm && temperatureSentMin == false)
  {
    String txt = "Tempe. Dw= " + (String)temperature + " *C";
    temperatureSentMin = true;
    displayMessageSerialAndCloud_singleLine(txt, messageTextForArduinoCloud, true, true);
  }
  else if (temperature > (tempTh.minAllarm + deltaTemperature))
  { 
    temperatureSentMin = false;
  }
}

// Output manag for relè command
bool checkReleRequesteOn(bool CommandOn)
{
  if (CommandOn == true && CommandOn != releCommandOnPrevious){
    digitalWrite(GPIO_RELE, true);                                    // Set relè ON
    previousMilliscomandReleOn = currentMillis;                       // Reset timer
    
    Serial.println("-----------> Button pressed releStausOn = " + (String)CommandOn);
  }

  if ((currentMillis - previousMilliscomandReleOn) >= RELE_ON_TIMER){ // Check if the timer if expired
    digitalWrite(GPIO_RELE, false);                                   // Set relè OFF
    CommandOn = false;                                                // Set the switch on arduino cloud to OFF
  }
  
  releCommandOnPrevious = CommandOn;

  return CommandOn;
}

// Check relè status
bool checkFeedbackRele()
{
  bool returnReleFeedbackOn;
  //returnReleFeedbackOn = digitalRead(GPIO_RELE_FEEDBACK);
  int val = analogRead(GPIO_RELE_FEEDBACK);

  if(val > 100){
    returnReleFeedbackOn = true;
  }else{
    returnReleFeedbackOn = false;
  }

  // Increase the cycle only when the relè is really on
  if (returnReleFeedbackOn == true && releFeedbackOnPrevious == false){
    cyclesNumberOfRele += 1; // Increase the relè cycle counter
  }

  if(returnReleFeedbackOn == true){
    millisecOfReleOn += deltaTimeFromLastExecution; 
  }
  else{
    releActivationTimeInSec = millisecOfReleOn/1000;
  }

  releFeedbackOnPrevious = returnReleFeedbackOn;

  return returnReleFeedbackOn;
}

// Check communication with cloud and if it is lost the board will be restart
bool checkConnctionAndRestart(bool connection, String *messageTextForArduinoCloud)
{
  String _connectionString;
  bool _connectionBool = false;
  
  if (connection == 0)
  {
    Serial.println("counterESPReset = " + (String)counterESPReset);
    _connectionString = "LOST";
    _connectionBool = false;
    ++disconnectionNumber;
    //digitalWrite(GPIO_RELE, true);

    if(counterESPReset >= RESET_ESP_TIMER)
    {
      Serial.println("Restarting!!!");
      delay(15000);
      ESP.restart();
    }
    
    counterESPReset += SLOW_CYCLE_TIMER;
  }
  else
  {
    //digitalWrite(GPIO_RELE, false);
    _connectionString = "OK";
    _connectionBool = true;
    counterESPReset = 0;

    // Disable restart function before first connection
    if (firstTimeNTPUpdate)
    {
      timeClient.update();
      dataTimeStartedModule = (String)timeClient.getFormattedTime();
      String txt = "-- Main Module started: " + dataTimeStartedModule;
      displayMessageSerialAndCloud_singleLine(txt, messageTextForArduinoCloud, true, true);
      firstTimeNTPUpdate = false;
    }
  }
  return _connectionBool;
}

// Read temperature sonsor BME260
temperatureAcqValue temperatureAcq(String *messageTextForArduinoCloud)
{
  temperatureAcqValue acq;

  acq.temp = bme.readTemperature();
  acq.tempStr = "Tempe. = " + (String)acq.temp + " *C";
  displayMessageSerialAndCloud_singleLine(acq.tempStr, messageTextForArduinoCloud, false, true);
  //Serial.println(acq.tempStr);
  
  acq.press = bme.readPressure() / 100.0F;
  acq.pressStr = "Press. = " + (String)acq.press + " hPa";
  displayMessageSerialAndCloud_singleLine(acq.pressStr, messageTextForArduinoCloud, false, true);
  //Serial.println(acq.pressStr);
  
  //Serial.print("Approx. Altitude = ");
  //Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  //Serial.println(" m");
  String strPre = "Approx. Altitude = " + (String)bme.readAltitude(SEALEVELPRESSURE_HPA) + " m";
  displayMessageSerialAndCloud_singleLine(strPre, messageTextForArduinoCloud, false, true);
  
  acq.humid = bme.readHumidity();
  acq.humidStr = "Humid. = " +  (String)acq.humid + " %";
  displayMessageSerialAndCloud_singleLine(acq.humidStr, messageTextForArduinoCloud, false, true);
  //Serial.println(acq.humidStr);

  return acq;
}

// Page sensors designe
void PageSensorsValueFun()
{
  String tempTh;
  if (temperatureSentMax == true){
    tempTh = "Temp. Max";
  }else if(temperatureSentMin = true){
    tempTh = "Temp. Min";
  }else{
    tempTh = "Temp. OK";
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);

  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.println("Sensor values:      ");
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  display.println("");
  display.println(acq.tempStr);
  display.println(acq.humidStr);
  display.println(acq.pressStr);
  display.println("");
  display.println(tempTh);
  display.println("Time: " + (String)timeClient.getFormattedTime());


  display.display();
}

// Page setting designe
void PageSettingsFun()
{
  String connectionCloud = (cloudConnection)? "OK": "LOST";
  String releStatusString = (releFeedbackOn)? "ON": "OFF";
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);

  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.println("Settings page:      ");
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  display.println("");
  display.println("Reconn: " + dataTimeStartedModule);
  display.println("Conn. status: " + connectionCloud);
  display.println("Rele status: " + releStatusString);
  display.println("Rele time on: " + (String)releActivationTime);
  display.println("Min/Max" + (String)tempTh.minAllarm + "/" + (String)tempTh.maxAllarm);

  display.display();
}

// Call page function in order to the page selected
void displayManagement()
{
  switch (menuDisplay) 
  {
    case PageSensorsValue:
      PageSensorsValueFun();
      break;
    case PageSettings:
      PageSettingsFun();
      break;
    default:
      // statements
      break;
  }
}

// Function to change the page when the button is pressed
void menuChangePage()
{
  switch (menuDisplay) 
  {
    case PageSensorsValue:
      menuDisplay = PageSettings;
      timer_homePage.run();
      break;
    case PageSettings:
      menuDisplay = PageSensorsValue;
      break;
    default:
      menuDisplay = PageSensorsValue;
      break;
  }
}

// After x seconds move the page at home
void timerHomePage()
{
  menuDisplay = PageSettings;
  menuChangePage();
}

