#include "arduino_secrets.h"
#include "thingProperties.h"
#include "ArduinoIoTComnnection.h"

unsigned long delayTime;
unsigned long currentMillis;

bool enable = false;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);
  
  Serial.println("");
  Serial.println("Serial STARTED!");

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

  // Set the switch on arduino cloud to OFF
  releCommandOn = false;
  
  // ------------------------ Init GPIOs -------------------------------
  pinMode(LED_BUILTIN, OUTPUT);       // Initialize the LED_BUILTIN pin as an output
  pinMode(GPIO_RELE, OUTPUT);         // Initialize relè output
  pinMode(GPIO_RELE_FEEDBACK, INPUT); // Initialize relè feedback
}

void loop() 
{
  currentMillis = millis();
  
  blinkLed();

  if ((currentMillis - previousMillisMainCycle) >= TEMPERATURE_ACQ_TIMER)
  {
    printAndUpdateValues();
    
    previousMillisMainCycle = currentMillis;

    unsigned long deltaT = (currentMillis - previousMilliscomandEnable);
    //Serial.println("-----------> deltaT = " + (String)deltaT);
    if (deltaT >= ENABLE_COMMAND_TIMER && enable == true)
    {
      //Serial.println("-----------> deltaT >= ENABLE_COMMAND_TIMER");
      enable = false;
    }
  }

  if ((releStausOn_Old != releStausOn) &&
      (currentMillis - previousMillisRelecheck) >= RELE_CEACK_TIMER)
  {
    releChangeEnable = true;
  }

  cyclesNumber = ciclyReleOn;
  releStausOn_Old = releStausOn;
  releFeedbackOn = releStausOn;

  checkReleCommandOn();
  
  checkFeedbackRele();

  delay(MAIN_INTERVAL);
}

void checkReleCommandOn()
{
  if (releCommandOn == true && releCommandOn != releCommandOnPrevious)
  {
    
    digitalWrite(GPIO_RELE, true);                                    // Set relè ON
    previousMilliscomandReleOn = currentMillis;                       // Reset timer
    
    Serial.println("-----------> Button pressed releStausOn = " + (String)releStausOn);
  }

  if ((currentMillis - previousMilliscomandReleOn) >= RELE_ON_TIMER)  // Check if the timer if expired
  {
    digitalWrite(GPIO_RELE, false);                                   // Set relè OFF
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
    ciclyReleOn += 1; // Increase the relè cycle counter
  }
  releFeedbackOnPrevious = releFeedbackOn;
  
  Serial.println("-----------> releFeedbackOn = " + (String)releFeedbackOn);
}

void printAndUpdateValues() 
{
  ArduinoCloud.update();
    
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
  
  String str = "ciclyReleOn = " + (String)ciclyReleOn;
  Serial.println(str);
  
  Serial.println();
  
  String text__[NUMBER_OF_ROWS_DISPLAIED] = {"Sensor values:      ", "", tempString, humidityString, pressureString,"","",str};
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
  
  if(ledState == LOW && ((currentMillis - previousMillis) >= 10))
  {
    ledState = HIGH;
    digitalWrite(LED_BUILTIN, ledState);
    previousMillis = currentMillis;
  }
}

void onReleCommandOnChange()  
{
  /*
  if (releChangeEnable == true && onReleCommandOnChangeCounter <= 0)
  {    
    releChangeEnable = false;
    releStausOn =! releStausOn;
    
    digitalWrite(GPIO_RELE, releStausOn);
    
    Serial.println("-----------> Button pressed releStausOn = " + (String)releStausOn);
  }
  onReleCommandOnChangeCounter = 0;
  */
  Serial.println("-----------> Button pressed releStausOn = " + (String)releStausOn);
}

void onComandEnableChange()  
{
  previousMilliscomandEnable = currentMillis;
  Serial.println("-----------> previousMilliscomandEnable = " + (String)previousMilliscomandEnable);
  
  enable = true;
}
