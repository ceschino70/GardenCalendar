#include "arduino_secrets.h"
#include "thingProperties.h"
#include "ArduinoIoTComnnection.h"

unsigned long delayTime;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);
  
  Serial.println("");
  Serial.println("Serial STARTED!");

  //Init of LCD display
  displayInit();
  
  String text_[NUMBER_OF_RAWS_DISPLAIED] = {"Initializing...", "", "", "", ""};
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
  setDebugMessageLevel(3);
  ArduinoCloud.printDebugInfo();

  bool status;

  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(SENSOR_TEMP_ADDRESS);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  Serial.println("-- Sensor communication Init OK --");
  delayTime = 2000;

  Serial.println();
  
  // Init GPIOs
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
}

void loop() 
{
  unsigned long currentMillis = millis();
  
  blinkLed();

  if ((currentMillis - previousMillisMainCycle) >= 2000)
  {
    printAndUpdateValues();
    
    previousMillisMainCycle = currentMillis;
  }
  
  delay(10);
}

void printAndUpdateValues() 
{
  ArduinoCloud.update();
    
  temp_1 = bme.readTemperature();
  String tempString = "Temper. = " + (String)temp_1 + " *C";
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
  
  Serial.println();
  
  String text__[NUMBER_OF_RAWS_DISPLAIED] = {"Sensor values:      ", "", tempString, humidityString, pressureString,"","",""};
  displayText(text__);
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
  
  if(ledState == LOW && ((currentMillis - previousMillis) >= 25))
  {
    ledState = HIGH;
    digitalWrite(LED_BUILTIN, ledState);
    previousMillis = currentMillis;
  }
}
