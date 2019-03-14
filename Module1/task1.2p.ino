const int buttonPin = 2;
const int ledPin = 13;

int buttonState = 0;

void setup()
{
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(buttonPin, HIGH);
  
  attachInterrupt(0,pin_ISR, CHANGE);
  Serial.begin(10);
}

void loop()
{
  
}

void pin_ISR() {
  buttonState = digitalRead(buttonPin);
  digitalWrite(ledPin, !buttonState);
  Serial.println(buttonState);
}
