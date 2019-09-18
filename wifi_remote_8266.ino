#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "Danger5"
#define STAPSK  "bakee04eee123456"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(8081);

int status[4] = {0};

void turnOn(int led) {
  digitalWrite(led, HIGH);
  status[led] = 1;  
}

void turnOff(int led) {
  digitalWrite(led, LOW);
  status[led] = 0;
}

int getStatus(int led) {
  return status[led];
}

String getStatusString(int led) {
  String lightStatus = "Off";
  if(getStatus(led) == 1) { 
    lightStatus = "On"; 
  }

  return lightStatus;
}

void handleRoot() {
  if(!server.hasArg("l")) {
    server.send(200, "text/html", "<html><head><style>ul{list-style-type:none;} a{text-decoration:none;}</style><title>WiFi Remote</title></head><body style='background-color:#CCC; font-family: tahoma; line-height:2em; font-size:1.5em;'><div style='max-width:800px; margin:10px auto; background-color:#9A9; padding:15px'><h1 style='text-align:center'>Welcome to WiFi Remote</h1><hr/><h2>Usage:</h2><h3>First Switch</h3><ul><li><a href='/?l=0'>Get Status</a></li><li><a href='/?l=0&s=1'>Turn On</a></li><li><a href='/?l=0&s=0'>Turn Off</a></li></ul><h3>Second Switch</h3><ul><li><a href='/?l=1'>Get Status</a></li><li><a href='/?l=1&s=1'>Turn On</a></li><li><a href='/?l=1&s=0'>Turn Off</a></li></ul><h3>Third Switch</h3><ul><li><a href='/?l=2'>Get Status</a></li><li><a href='/?l=2&s=1'>Turn On</a></li><li><a href='/?l=2&s=0'>Turn Off</a></li></ul><h3>Fourth Switch</h3><ul><li><a href='/?l=3'>Get Status</a></li><li><a href='/?l=3&s=1'>Turn On</a></li><li><a href='/?l=3&s=0'>Turn Off</a></li></ul></div></body></html>");
    return;
  }

  String lightStatus;
  String lightNo;
  int ledIndex;
  String lightName;

  if(server.hasArg("l") && !server.hasArg("s")) {
    lightNo = server.arg("l");        
    if(String("0") == lightNo) { 
      lightName = "first"; 
      ledIndex = 0; 
    }
    else if (String("1") == lightNo) { 
      lightName = "second"; 
      ledIndex = 1; 
    }
    else if (String("2") == lightNo) { 
      lightName = "third"; 
      ledIndex = 2; 
    }
    else if (String("3") == lightNo) { 
      lightName = "fourth"; 
      ledIndex = 3; 
    }
    else { 
      server.send(500, "text/plain", "Invalid command!");
      return; 
    }
      
    server.send(200, "text/html", "<html><head><style>ul{list-style-type:none;} a{text-decoration:none;}</style><title>WiFi Remote</title></head><body style='background-color:#CCC; font-family: tahoma; line-height:2em; font-size:1.5em;'><div style='max-width:800px; margin:10px auto; background-color:#9A9; padding:15px'><h1 style='text-align:center'>Welcome to WiFi Remote</h1><hr/><h3>Status of " + lightName + " switch is : <b>" + getStatusString(ledIndex) + "</b></h3><p><a href='/'>Home</a></div></body></html>");
    return;
  }

  if(server.hasArg("l") && server.hasArg("s")) {
    lightNo = server.arg("l");
    if(String("0") == lightNo) { 
      lightName = "First"; 
      ledIndex = 0; 
    }
    else if (String("1") == lightNo) { 
      lightName = "Second"; 
      ledIndex = 1; 
    }
    else if (String("2") == lightNo) { 
      lightName = "Third"; 
      ledIndex = 2; 
    }
    else if (String("3") == lightNo) { 
      lightName = "Fourth"; 
      ledIndex = 3; 
    }
    else { 
      server.send(500, "text/plain", "Invalid command!");
      return; 
    }

    lightStatus = server.arg("s");
    if(String("0") == lightStatus) {
      turnOff(ledIndex);      
    } else {
      turnOn(ledIndex);
    }

    server.send(200, "text/html", "<html><head><style>ul{list-style-type:none;} a{text-decoration:none;}</style><title>WiFi Remote</title></head><body style='background-color:#CCC; font-family: tahoma; line-height:2em; font-size:1.5em;'><div style='max-width:800px; margin:10px auto; background-color:#9A9; padding:15px'><h1 style='text-align:center'>Welcome to WiFi Remote</h1><hr/><h3>" + lightName + " switch is now: <b>" + getStatusString(ledIndex) + "</b></h3><a href='/'>Home</a></div></body></html>");
    return;
  }
    
  server.send(500, "text/plain", "Critical Server Error occured!");
  return; 
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setupPins() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}

void setup(void) {
  setupPins();
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}