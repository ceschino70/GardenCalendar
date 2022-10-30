#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

// I2C Addresses
#define SENSOR_TEMP_ADDRESS 0x76
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#define SEALEVELPRESSURE_HPA (1011)
#define OLED_RESET     -1           // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_WIDTH 128            // OLED display width, in pixels
#define SCREEN_HEIGHT 64            // OLED display height, in pixels
#define NUMBER_OF_ROWS_DISPLAIED 8  // Number of rows 
#define GPIO_RELE D8                // Relè connected to GPIO 15
#define GPIO_RELE_FEEDBACK D7       // Relè feedback connected to GPIO 13

// Definition of constant timers
const int MAIN_INTERVAL         = 10;    // Main timer in millisec
const int TEMPERATURE_ACQ_TIMER = 2000;   // Timer for read & update BME280 sensor
const int RELE_CEACK_TIMER      = 2000;   // Filter commamd for relè 
const int INTERVAL              = 1000;   // Interval at which to blink (milliseconds)
const int ENABLE_COMMAND_TIMER  = 5000;   // Timer for command enable
const int RELE_ON_TIMER         = 10000;  // Relè On timer
const int RESET_ESP_TIMER       = 600000; // Number of millisec to wait before ESP reset when arduino IoT cloud connection is lost
const long UTC_OFFSET_IN_SECONDS = 7200;  // Time zone +2h => 2h * 60min * 60sec = 7200

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

unsigned long previousMillisMainCycle = 0;
unsigned long previousMilliscomandReleOn = 0;
unsigned long previousMillisLasExecutionProg = 0;

bool temperatureSentMax = false;
bool temperatureSentMin = false;


//Temperature sensor
Adafruit_BME280 bme; // I2C

//Display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", UTC_OFFSET_IN_SECONDS);

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

void displayText (String text[])
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  //display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  
  for(int i = 0; i < NUMBER_OF_ROWS_DISPLAIED; i++)
  {
    if (i == 0)
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    else
      display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
      
    display.println(text[i]);
  }
  display.display();
}

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

void temperatureAllarms(double temperature, String *messageTextForArduinoCloud)
{  
  if (temperature > 24.8 && temperatureSentMax == false)
  {
    String txt = "Tempe. Up= " + (String)temperature + " *C";
    temperatureSentMax = true;
    displayMessageSerialAndCloud_singleLine(txt, messageTextForArduinoCloud, true, true);
  }
  else if (temperature < 24.7)
  { 
    temperatureSentMax = false;
  }

  if (temperature < 21 && temperatureSentMin == false)
  {
    String txt = "Tempe. Dw= " + (String)temperature + " *C";
    temperatureSentMin = true;
    displayMessageSerialAndCloud_singleLine(txt, messageTextForArduinoCloud, true, true);
  }
  else if (temperature > 21.3)
  { 
    temperatureSentMin = false;
  }
}

bool checkReleRequesteOn(bool CommandOn)
{
  if (CommandOn == true && CommandOn != releCommandOnPrevious){
    digitalWrite(GPIO_RELE, true);                                  // Set relè ON
    previousMilliscomandReleOn = currentMillis;                       // Reset timer
    
    Serial.println("-----------> Button pressed releStausOn = " + (String)CommandOn);
  }

  if ((currentMillis - previousMilliscomandReleOn) >= RELE_ON_TIMER){ // Check if the timer if expired
    digitalWrite(GPIO_RELE, false);                                 // Set relè OFF
    CommandOn = false;                                                // Set the switch on arduino cloud to OFF
  }
  
  releCommandOnPrevious = CommandOn;

  return CommandOn;
}

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

String checkConnctionAndRestart(bool connection, String *messageTextForArduinoCloud)
{
  String _connectionString;
  
  if (connection == 0)
  {
    Serial.println("counterESPReset = " + (String)counterESPReset);
    _connectionString = "LOST";
    ++disconnectionNumber;
    //digitalWrite(GPIO_RELE, true);

    if(counterESPReset >= RESET_ESP_TIMER)
    {
      Serial.println("Restarting!!!");
      delay(15000);
      ESP.restart();
    }
    
    counterESPReset += TEMPERATURE_ACQ_TIMER;
  }
  else
  {
    //digitalWrite(GPIO_RELE, false);
    _connectionString = "OK";
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

  return _connectionString;
}
