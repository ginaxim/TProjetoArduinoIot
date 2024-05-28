#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 4;
const int echoPin = 3;
const int ledPin = 5;

bool flag = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);

  Wire.begin();
  lcd.begin(16, 2);
  lcd.backlight(); 
  lcd.clear(); 

  Serial.println("Setup completo");
}

void loop() {
  long duration;
  int distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if (distance > 100) {
    digitalWrite(ledPin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Reposicao");
    lcd.setCursor(0, 1);
    lcd.print("Necessaria");
    if (!flag) {
      Serial.println("LED acesa. Enviando mensagem...");
      flag = true;
      // Aqui você pode adicionar a função para enviar a mensagem
    }
  } else {
    digitalWrite(ledPin, LOW);
    lcd.clear();
    flag = false;
  }
  delay(100); 
}