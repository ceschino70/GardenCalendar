#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = "ac16d9bc-c2b8-48c7-9a7a-4dc5b19d16fb";
const char SSID[]               = SECRET_SSID;    // Network SSID (name)
const char PASS[]               = SECRET_PASS;    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]         = SECRET_DEVICE_KEY;    // Secret device password

// Variable send & received to Arduino Cloud
float humid_1;                    // Output
float temp_1;                     // Output
float press_1;                    // Output
bool  releCommandOn;              // Input
bool  releFeedbackOn;             // Output
int   cyclesNumber;               // Output
CloudTime releActivationTime;     // Output
String messageText;               // Output
bool programRunning;

void initProperties()
{
  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(humid_1, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(temp_1, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(press_1, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(releCommandOn, READWRITE, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(releFeedbackOn, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(cyclesNumber, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(releActivationTime, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(messageText, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(programRunning, READWRITE, 1 * SECONDS, NULL);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
