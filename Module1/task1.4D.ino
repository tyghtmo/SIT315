#include <avr/interrupt.h>
//inputs
const int tiltPin = 2;
const int buttonPin = 3;
const int tempPin = A0;

//outputs
const int gledPin = 10;
const int bledPin = 11;
const int rledPin = 12;
const int led = 13;

volatile int tiltState = 0;
volatile int buttonState = 0;

void setup()
{
  pinMode(tempPin, INPUT);
  
  pinMode(gledPin, OUTPUT);
  pinMode(bledPin, OUTPUT);
  pinMode(rledPin, OUTPUT);
  pinMode(led, OUTPUT);
  
  digitalWrite(tiltPin, HIGH);
  digitalWrite(buttonPin, HIGH);
  
  attachInterrupt(digitalPinToInterrupt(tiltPin), tilt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(buttonPin), button, CHANGE);
  Serial.begin(100);
  
  //timer interrupt setup
  cli(); //disable interrupts
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();
}

void loop()
{
  //Temperature loop
  int tempSensorValue = analogRead(tempPin);
  //Serial.println(tempSensorValue);
  
  if(tempSensorValue > 176){
    digitalWrite(bledPin, HIGH);
  } else {
    digitalWrite(bledPin, LOW);
  }
  
}

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  Serial.println(digitalRead(led));
  if(digitalRead(led) == HIGH){
    digitalWrite(led, LOW);
  } else {
    digitalWrite(led, HIGH);
  }
}

void tilt() {
  tiltState = digitalRead(tiltPin);
  digitalWrite(gledPin, !tiltState);
  Serial.println(tiltState);
}

void button() {
  buttonState = digitalRead(buttonPin);
  digitalWrite(rledPin, buttonState);
  Serial.println(buttonState);
}
