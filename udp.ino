#include <WiFiUdp.h>

#define BROADCAST_INTERVAL (20 * 1000)

WiFiUDP Udp;
IPAddress udpIp;
const unsigned int udpPort = 64101;
unsigned long lastBroadcastTime = 0;

void broadcast() {
    String message = "Room: " + RoomName + ", MAC: " + WiFi.macAddress() + ", IP: " + WiFi.localIP().toString();    
    Udp.beginPacket(udpIp, udpPort);
    Udp.write(message.c_str());
    Udp.endPacket();
    lastBroadcastTime = millis();
}

void udp_setup() {
  udpIp.fromString("192.168.8.255");  
  Udp.begin(udpPort);  
  broadcast();  
}

void udp_run() {
  if((millis() - lastBroadcastTime) > BROADCAST_INTERVAL) {    
    broadcast();
  }
}
