void setup()
{
  pinMode(A0, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(10);
  
}

void loop()
{
  int tempSensorValue = analogRead(A0);
  Serial.println(tempSensorValue);

  digitalWrite(13, LOW);

  if(tempSensorValue > 176){
    digitalWrite(13, HIGH);
  }
}
