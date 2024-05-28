int trig = 4;
int echo = 5;
long micro, cm;

void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
    
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
    
  digitalWrite(trig, LOW);
  
  micro = pulseIn(echo, HIGH);
  
  cm = micro / 58;
  
  Serial.println(cm);
 
  delay(100);
}
