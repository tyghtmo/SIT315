//inputs
const int tiltPin = 2;
const int buttonPin = 3;

//outputs
const int gledPin = 10;
const int bledPin = 11;
const int rledPin = 12;
const int led = 13;

volatile int tiltState = 0;
volatile int buttonState = 0;

void setup()
{
  pinMode(tiltPin, INPUT);
  pinMode(buttonPin, INPUT);
  
  pinMode(gledPin, OUTPUT);
  pinMode(bledPin, OUTPUT);
  pinMode(rledPin, OUTPUT);
  pinMode(led, OUTPUT);
  
  digitalWrite(tiltPin, HIGH);
  digitalWrite(buttonPin, HIGH);
  
  attachInterrupt(digitalPinToInterrupt(tiltPin), tilt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(buttonPin), button, CHANGE);
  Serial.begin(9600);
  
}

void loop()
{
  
}


void tilt() {
  tiltState = digitalRead(tiltPin);
  digitalWrite(gledPin, !tiltState);
  Serial.print("Tilt state: ");
  Serial.println(tiltState);
}

void button() {
  buttonState = digitalRead(buttonPin);
  digitalWrite(rledPin, buttonState);
  Serial.print("Button state: ");
  Serial.println(buttonState);
}
