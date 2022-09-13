#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = "ac16d9bc-c2b8-48c7-9a7a-4dc5b19d16fb";
const char SSID[]               = SECRET_SSID;    // Network SSID (name)
const char PASS[]               = SECRET_PASS;    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]         = SECRET_DEVICE_KEY;    // Secret device password

// Variable send & received to Arduino Cloud
float humid_1;
float temp_1;
float press_1;
bool  releCommandOn;
bool  releFeedbackOn;
int   cyclesNumber;
bool  comandEnable;

void onReleCommandOnChange();
void onComandEnableChange();

void initProperties()
{
  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(humid_1, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(temp_1, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(press_1, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(releCommandOn, READWRITE, ON_CHANGE, onReleCommandOnChange);
  ArduinoCloud.addProperty(comandEnable, READWRITE, ON_CHANGE, onComandEnableChange);
  ArduinoCloud.addProperty(releFeedbackOn, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(cyclesNumber, READ, ON_CHANGE, NULL);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
