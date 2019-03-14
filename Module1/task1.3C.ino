//inputs
const int tiltPin = 2;
const int buttonPin = 3;

//outputs
const int gledPin = 10;
const int bledPin = 11;
const int rledPin = 12;

volatile int tiltState = 0;
volatile int buttonState = 0;

void setup()
{
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(tiltPin, HIGH);
  
  attachInterrupt(digitalPinToInterrupt(2), pin_tilt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), pin_button, CHANGE);
  Serial.begin(10);
}

void loop()
{
  int tempSensorValue = analogRead(A0);
  //Serial.println(tempSensorValue);

  digitalWrite(bledPin, LOW);

  if(tempSensorValue > 176){
    digitalWrite(bledPin, HIGH);
  }
  
  
}

void pin_tilt() {
  tiltState = digitalRead(tiltPin);
  digitalWrite(gledPin, !tiltState);
  //Serial.println(tiltState);
}

void pin_button(){
  buttonState = digitalRead(buttonPin);
  digitalWrite(rledPin, !buttonState);
  Serial.println(buttonState);
}
