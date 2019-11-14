#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "wifi_credentials.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

void wifi_setup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void setup(void) {
  io_setup();
  wifi_setup();
  http_setup();
  udp_setup();
}

void loop(void) {
  http_run();
  udp_run();
}
