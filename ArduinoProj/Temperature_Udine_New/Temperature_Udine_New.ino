#include "arduino_secrets.h"
#include "thingProperties.h"

// Start function
void setup() 
{
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
  //displayText(text_);

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


  // ------------------------ Init Timers ------------------------------
  timer_BlinkLed.cback(blinkLed);
  timer_BlinkLed.isRepeating();
  timer_BlinkLed.run();

  timer_cycleSlow.cback(cycleSlow);
  timer_cycleSlow.isRepeating();
  timer_cycleSlow.run();

  timer_cycleFast.cback(cycleFast);
  timer_cycleFast.isRepeating();
  timer_cycleFast.run();

  timer_homePage.cback(timerHomePage);

  // ------------------------ Edge detection ---------------------------
  edgeDetecPushButton.cback(menuChangePage);
  edgeDetecPushButton.trigOn();
  edgeDetecPushButton.run(&buttonStatus);
  // ------------------------ Date Time Update -------------------------
  timeClient.update();
  dataTimeStartedModule = (String)timeClient.getFormattedTime();
                          
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
  
  pinMode(button1.PIN, INPUT_PULLUP);        // Initialize push button 
  attachInterrupt(button1.PIN, interruptButtonPrssed, FALLING);

  // ------------------------ Temperature theshold ---------------------
  tempTh.minAllarm  = 22.5;
  tempTh.minWorning = 22.5;
  tempTh.maxWorning = 23.5;
  tempTh.maxAllarm  = 23.5;
}

// Main loop
void loop() 
{
  currentMillis = millis();
  deltaTimeFromLastExecution = currentMillis - previousMillisLasExecutionProg;
  previousMillisLasExecutionProg = currentMillis;

  // Update all timers
  timer_BlinkLed.loop();
  timer_cycleSlow.loop();
  timer_cycleFast.loop();
  timer_homePage.loop();

  // Edge detection
  edgeDetecPushButton.loop();

  // Check relè command requeste from Cloud
  releCommandOn = checkReleRequesteOn(releCommandOn);
  // Check relè feedback from Arduino Input
  releFeedbackOn = checkFeedbackRele();

  // Update value on cloud
  cyclesNumber = cyclesNumberOfRele;
  releActivationTime = releActivationTimeInSec;
}

// Fast cycle
void cycleFast()
{
  //buttonStatus = digitalRead(GPIO_PUSCHBUTTON);

  if (button1.pressed) {
        Serial.printf("Button has been pressed %u times\n", button1.numberKeyPresses);
        button1.pressed = false;
        menuChangePage();
    }

  // Display refresh
  displayManagement();
}

// Slow cycle
void cycleSlow() 
{
  // Check cloud connection & restart board
  cloudConnection = checkConnctionAndRestart(ArduinoCloud.connected(), &messageText);
  
  // Acquisition values from BME260
  acq = temperatureAcq(&messageText);

  // Check temperature threshold
  temperatureAllarms(acq.temp, &messageText);
  
  temp_1  = acq.temp;
  humid_1 = acq.humid;
  press_1 = acq.press;
  
  ArduinoCloud.update();
}

// Blink main led function
void blinkLed()
{
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  programRunning = !programRunning;
  
  ArduinoCloud.update();
}


