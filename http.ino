#include <ESP8266WebServer.h>

ESP8266WebServer server(8081);

//const String RoomName = "South West";
//const String RoomName = "South West Varanda";
//
//const String RoomName = "South East";
//const String RoomName = "South East Varanda";
//
//const String RoomName = "East";
//
//const String RoomName = "Kitchen";
//
//const String RoomName = "Dining";
//
//const String RoomName = "North";
//
//const String RoomName = "Drawing North";
//const String RoomName = "Drawing South";
//
//const String RoomName = "North West";
//const String RoomName = "North West Varanda";
//
//const String RoomName = "Guest";
//const String RoomName = "Guest Varanda";

String getResponse(String roomName) {
  String response = "<html><head>";
  response += "<meta http-equiv='refresh' content='15'>";
  response += "<style>";
  response += ".title {text-align:center; background-color:#996633; color: #CCCCFF}";
  response += "h3 {color:#3333CC; margin-bottom:0;}";
  response += "a {text-decoration:none;}";
  response += ".container {max-width:800px; margin:10px auto; background-color:#9A9; padding:15px}";
  response += ".on-switch {background-color:#66CC33;padding: 10px 15px; color:#FFFFFF; float:left;}";
  response += ".off-switch {background-color:#CC3344;padding: 10px 15px; color:#FFFFFF; float:right;}";
  response += "hr {clear:both;}";
  response += "</style>";
  response += "<title>WiFi Remote</title></head>";
  response += "<body style='background-color:#CCC; font-family: tahoma; line-height:2em; font-size:1.5em;'>";
  response += "<div class='container'>";
  response += "<h2 class='title'><a href='/'>WiFi Remote<br/>(Room: ";
  response += roomName;
  response += ")</a></h2><hr/>";

  for(int i = 0; i < 4; i++) {   
    response += "<h3>Switch: ";
    response += (i + 1);
    response += " is now ";
    response += getStatusString(i);
    response += "</h3>";
    
    response += "<a href='/?l=";
    response += i;
    response += "&s=1' class='on-switch'>Turn On</a>";
    
    response += "<a href='/?l=";
    response += i;
    response += "&s=0' class='off-switch'>Turn Off</a>";
    
    response += "<hr/>";
  }

  response += "&copy; Md. Abdullah-Al-Bakee</div></body></html>";

  return response;
}

void handleRoot() {
  if(!server.hasArg("l")) {
    server.send(200, "text/html", getResponse(RoomName));
    return;
  }

  String lightStatus;
  String lightNo;
  int ledIndex;
  String lightName;

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

    server.sendHeader("Location", String("/"), true);
    server.send ( 302, "text/plain", "");    
    return;
  }
    
  server.send(500, "text/plain", "Critical Server Error occured!");
  return; 
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  server.send(404, "text/plain", message);
}

void http_setup() {
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
}

void http_run() {
  server.handleClient();
}
