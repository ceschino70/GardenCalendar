#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <UnixTime.h>
#include "RTClib.h"
#include "ntpPacket.h"

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  Ethernet.init(10);  // Most Arduino shields

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) 
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start Ethernet and UDP
  if (Ethernet.begin(mac) == 0) 
  {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) 
    {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    } else if (Ethernet.linkStatus() == LinkOFF) 
    {
      Serial.println("Ethernet cable is not connected.");
    }
    // no point in carrying on, so do nothing forevermore:
    while (true) 
    {
      delay(1);
    }
  }
  Udp.begin(localPort);
}

void loop() {
  sendNTPpacket(timeServer); // send an NTP packet to a time server

  // wait to see if a reply is available
  delay(1000);
  if (Udp.parsePacket()) 
  {
    // We've received a packet, read the data from it
    Udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears;
    // print Unix time:
    Serial.println(epoch);
    stamp.getDateTime(epoch);
    DateTime now = DateTime(stamp.year,stamp.month,stamp.day,stamp.hour,stamp.minute,stamp.second);
    
    String dateTime_now = (String)now.day() + "/" + (String)now.month() + "/" + (String)now.year() + 
                            " - " + 
                          (String)now.hour() + ":" + (String)now.minute() + ":" + (String)now.second();
    Serial.println(dateTime_now);
  }
  else
  {
    Serial.println("---> No packge");
  }
  // wait ten seconds before asking for the time again
  //delay(10000);
  Ethernet.maintain();
}
