#include <WiFiUdp.h>

#define BROADCAST_INTERVAL (20000)

WiFiUDP Udp;
IPAddress udpIp;
const unsigned int udpPort = 64101;
unsigned long timeStamp = 0;

void SendUdpPacket() {
    String message = "Room: " + RoomName + ", IP: " + WiFi.localIP().toString();    
    Udp.beginPacket(udpIp, udpPort);
    Udp.write(message.c_str());
    Udp.endPacket();
}

void udp_setup() {
  udpIp.fromString("192.168.8.255");
  timeStamp = millis();
  Udp.begin(udpPort);
}

void udp_run() {
    if(millis() - timeStamp > BROADCAST_INTERVAL) {
    timeStamp = millis();
    SendUdpPacket();
  }
}
