# wifi_remote_8266
ESP01 Board to control 4 relays/ssrs via WiFi webserver. This code uses 4 relay since, the very low cost ESP01 board has only 4 usable pins.

# Pre-requisite

- Arduino IDE
- ESP 8266 board installed [(Instruction)](http://arduino.esp8266.com/Arduino/versions/2.0.0/doc/installing.html)

# Steps

- Update [wifi_credentials.h](wifi_credentials.h) file according to your wifi network
- Make sure the esp 8266 board is selected as the current board
- Upload program to the board
- ESP board will aquire an IP address from the router. To know this IP address:
 - Get it by accessing your router control panel
 - or
 - ESP board will broadcast it's ip address at port 64101, so by listening to this port with any UDP listener this ip address can be known
 - Use any browser and go to that ip address using port 8081. For example, if the ip address of ESP board is `192.168.8.5`, then type `https://192.168.8.5:8081/` in the address bar.
 - Control ESP pins from the web interface
