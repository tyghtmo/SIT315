const int buttonPin = 2;
const int ledPin = 13;

int buttonState = 0;

void setup()
{
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(buttonPin, HIGH);
  Serial.begin(10);
}

void loop()
{
  Serial.println(buttonState);
  buttonState = digitalRead(buttonPin);
  
  
  if (buttonState == LOW){
    digitalWrite(ledPin, HIGH);
  }
  else{
    digitalWrite(ledPin, LOW);
  }
}