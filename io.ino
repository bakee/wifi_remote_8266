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

void io_setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}
