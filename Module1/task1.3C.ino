//inputs
const int tiltPin = 2;
const int buttonPin = 3;

//outputs
const int gledPin = 10;
const int bledPin = 11;
const int rledPin = 12;

volatile int tiltState = 0;
int buttonState = 0;

void setup()
{
  pinMode(tiltPin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(A0, INPUT);
  
  pinMode(gledPin, OUTPUT);
  pinMode(bledPin, OUTPUT);
  pinMode(rledPin, OUTPUT);
  
  digitalWrite(tiltPin, HIGH);
  digitalWrite(buttonPin, HIGH);
  
  attachInterrupt(digitalPinToInterrupt(2), pin_ISR, CHANGE);
  Serial.begin(100);
}

void loop()
{
  //Temperature loop
  int tempSensorValue = analogRead(A0);
  Serial.println(tempSensorValue);
    
  if(tempSensorValue > 176){
    digitalWrite(bledPin, HIGH);
  } else {
    digitalWrite(bledPin, LOW);
  }
  
    
  //Button loop
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  
  if(buttonState == HIGH){
    digitalWrite(rledPin, HIGH);
  } else {
    digitalWrite(rledPin, LOW);
  }
  
  
}

void pin_ISR() {
  tiltState = digitalRead(tiltPin);
  digitalWrite(gledPin, !tiltState);
  Serial.println(tiltState);
}
