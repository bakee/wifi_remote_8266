int status[4] = {0};

void turnOn(int pin) {  
  digitalWrite(pin, HIGH);
  status[pin] = 1;  
}

void turnOff(int pin) { 
  digitalWrite(pin, LOW);
  status[pin] = 0;
}

int getStatus(int pin) {
  return status[pin];
}

String getStatusString(int pin) {
  String lightStatus = "Off";
  if(getStatus(pin) == 1) { 
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
