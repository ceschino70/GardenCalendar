/**********************************************
 * Catalin Batrinu bcatalin@gmail.com 
 * Read temperature and pressure from BMP280
 * and send it to thingspeaks.com
**********************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <ESP8266WiFi.h>

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11 
#define BMP_CS 10

Adafruit_BMP280 bme; // I2C
// replace with your channel’s thingspeak API key,
String apiKey = "YOUR-API-KEY";
const char* ssid = "FrancescoWiFi";
const char* password = "121111119";
const char* server = "api.thingspeak.com";
WiFiClient client;


/**************************  
 *   S E T U P
 **************************/
void setup() {
  Serial.begin(9600);
  Serial.println(F("BMP280 test"));
  
  if (!bme.begin()) {  
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
  WiFi.begin(ssid, password);
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
}

  /**************************  
 *  L O O P
 **************************/
void loop() {
    Serial.print("T=");
    Serial.print(bme.readTemperature());
    Serial.print(" *C");
    
    Serial.print(" P=");
    Serial.print(bme.readPressure());
    Serial.print(" Pa");

    Serial.print(" A= ");
    Serial.print(bme.readAltitude(1013.25)); // this should be adjusted to your local forcase
    Serial.println(" m");

 /*   if (client.connect(server,80))  // "184.106.153.149" or api.thingspeak.com
    {
        String postStr = apiKey;
        postStr +="&field1=";
        postStr += String(bme.readTemperature());
        postStr +="&field2=";
        postStr += String(bme.readPressure());
        postStr += "\r\n\r\n";
        
        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(postStr.length());
        client.print("\n\n");
        client.print(postStr);    
    }
    client.stop(); */
    //every 20 sec   
    delay(20000);
}
