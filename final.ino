#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <UrlEncode.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 4;
const int echoPin = 3;
const int ledPin = 5;
const int sensorPin = 2; // Defina o pino do sensor, caso necessário

const char* ssid = "nome da rede wifi";
const char* password = "senha da rede wifi";

String phoneNumber = "+5521Numero";
String apiKey = "recebido no wpp";

bool flag = true;

void sendMessage(String message) {
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpResponseCode = http.POST("");
  if (httpResponseCode == 200) {
    Serial.println("Mensagem enviada com sucesso");
  } else {
    Serial.println("Erro no envio da mensagem");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT); // Configure o pino do sensor como entrada

  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();

  WiFi.begin(ssid, password);
  Serial.println("Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado ao WiFi neste IP ");
  Serial.println(WiFi.localIP());
}

void loop() {
  long duration;
  int distance;
  int item = digitalRead(sensorPin);

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
    if (flag) {
      sendMessage("Atenção! Reposição de estoque necessária.");
      flag = false;
    }
  } else {
    digitalWrite(ledPin, LOW);
    lcd.clear();
    flag = true;
  }
  delay(100);
}
