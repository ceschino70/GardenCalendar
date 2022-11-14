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
#define SCREEN_ADDRESS      0x3C    // I2C Address of display OLED 

#define SEALEVELPRESSURE_HPA      1011    // See level pressure
#define OLED_RESET                -1      // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_WIDTH              128     // OLED display width, in pixels
#define SCREEN_HEIGHT             64      // OLED display height, in pixels
#define NUMBER_OF_ROWS_DISPLAIED  8       // Number of rows 

// GPIO Description 
#define GPIO_RELE           D8      // Relè connected to GPIO 15
#define GPIO_RELE_FEEDBACK  D7      // Relè feedback connected to GPIO 13
#define GPIO_PUSCHBUTTON    D5      // Push button pin GPIO 16

// Constants timer 
#define MAIN_INTERVAL            10     // Main timer in millisec
#define FAST_CYCLE_TIMER         500    // Fast timer: check push button
#define SLOW_CYCLE_TIMER         2000   // Slow timer: read & update BME280 sensor
#define RELE_CEACK_TIMER         2000   // Filter commamd for relè 
#define INTERVAL                 1000   // Interval at which to blink (milliseconds)
#define ENABLE_COMMAND_TIMER     5000   // Timer for command enable
#define RELE_ON_TIMER            10000  // Relè On timer
#define RESET_ESP_TIMER          600000 // Number of millisec to wait before ESP reset when arduino IoT cloud connection is lost
#define UTC_OFFSET_IN_SECONDS    3600   // Time zone +2h => 2h * 60min * 60sec = 7200

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
unsigned long deltaTimeFunction_1 = 0;
unsigned long deltaTimeFunction_2 = 0;
int           relayStatusRead = 0;

// Theshold values
// minAllarm = Minimum allarm theshold
// minWorning = Minimum worning theshold
// maxWorning = Maximum worning theshold
// maxAllarm = Maximum allarm theshold
struct temperatureTheshold {
  float minAllarm;
  float minWorning;
  float maxWorning;
  float maxAllarm;
};

// BME260 sensor values
// temp = temperature [°C]
// humid = humitity [%]
// press = pressure [hPA]
// tempStr = value in string form
// humidStr = value in string form
// pressStr = value in string form
struct temperatureAcqValue {
  float temp;
  float humid;
  float press;
  String tempStr;
  String humidStr;
  String pressStr;
};

//  Button with interrupt
//  PIN = GPIO number
//  numberKeyPresses = number of pressed time
//  pressed = event elapsed
struct button {
    const uint8_t PIN;
    uint32_t numberKeyPresses;
    bool pressed;
};

// Pages displaied
// PageSensorsValue = sensor value page
// PageSettings = setting page
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

button button1 = {GPIO_PUSCHBUTTON, 0, false};
//variables to keep track of the timing of recent interrupts
unsigned long button_time = 0;  
unsigned long last_button_time = 0; 

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

// Display initialization
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

// Check if the temperature is inside the thresholds limits
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

  releCommandOnPrevious = CommandOn;

  return CommandOn;
}

// Check relè status
bool checkFeedbackRele()
{
  bool returnReleFeedbackOn;
  
  relayStatusRead = analogRead(GPIO_RELE_FEEDBACK);

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

  
  acq.press = bme.readPressure() / 100.0F;
  acq.pressStr = "Press. = " + (String)acq.press + " hPa";
  displayMessageSerialAndCloud_singleLine(acq.pressStr, messageTextForArduinoCloud, false, true);

  String strPre = "Approx. Altitude = " + (String)bme.readAltitude(SEALEVELPRESSURE_HPA) + " m";
  displayMessageSerialAndCloud_singleLine(strPre, messageTextForArduinoCloud, false, true);
  
  acq.humid = bme.readHumidity();
  acq.humidStr = "Humid. = " +  (String)acq.humid + " %";
  displayMessageSerialAndCloud_singleLine(acq.humidStr, messageTextForArduinoCloud, false, true);

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
  display.println("dTFun2:" + (String)deltaTimeFunction_2);
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

// Function called from interupt
void ICACHE_RAM_ATTR interruptButtonPrssed()
{
  display.println("--->Button pressed.");
  button_time = millis();
  if (button_time - last_button_time > 250)
  {
    button1.numberKeyPresses++;
    button1.pressed = true;
    last_button_time = button_time;
  }
}

