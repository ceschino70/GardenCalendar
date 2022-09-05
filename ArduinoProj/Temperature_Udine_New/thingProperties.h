#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// I2C Addresses
#define SENSOR_TEMP_ADDRESS 0x76
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#define SEALEVELPRESSURE_HPA (1011)
#define OLED_RESET     -1           // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_WIDTH 128            // OLED display width, in pixels
#define SCREEN_HEIGHT 64            // OLED display height, in pixels
#define NUMBER_OF_RAWS_DISPLAIED 8
#define GPIO_RELE D8                // Relè connecte to GPIO 15

//const int LEDPIN =  2;// the number of the LED pin

// Definition of constant timers
const int MAIN_INTERVAL         = 10;     // Main timer
const int TEMPERATURE_ACQ_TIMER = 2000;   // Timer for read & update BME280 sensor
const int RELE_CEACK_TIMER      = 2000;   // Filter commamd for relè 
const int INTERVAL              = 1000;   // interval at which to blink (milliseconds)

float         temp;
int           humidity;
unsigned long previousMillis = 0;         // will store last time LED was updated
int           ledState = LOW;             // ledState used to set the LED
bool          releStausOn = false;        // Status of output (false = relè OFF, true = relè ON)
bool          releStausOn_Old = false;    // OLD Status of output (false = relè OFF, true = relè ON)
bool          releChangeEnable = true;    // The onReleCommandOnChange can chenge the relè output
int           onReleCommandOnChangeCounter = 1; // When the board connects to IoT cloud generate onReleCommandOnChange event
int           ciclyReleOn = 0;

unsigned long previousMillisMainCycle = 0;
unsigned long previousMillisRelecheck = 0;


//Temperature sensor
Adafruit_BME280 bme; // I2C

//Display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void displayInit ()
{
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
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
  
  for(int i = 0; i < NUMBER_OF_RAWS_DISPLAIED; i++)
  {
    if (i == 0)
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    else
      display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
      
    display.println(text[i]);
  }
  display.display();
}
