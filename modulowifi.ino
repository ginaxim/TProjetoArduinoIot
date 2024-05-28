//file > preferences > addicional boards manager urls: https://espressif.github.io/arduino-esp32/package_esp32_index.json
//boards manager > search: esp32 by espressif systems

//bot whatsapp (call me bot) - 34 621 33 17 09
//istalar a biblioteca no arduino: UrlEncode by masayuki sugahara, httpClient e wifi

//código:



#include <WiFi.h>
#include <HTTPClient.h>
#include <UrlEncode.h>

const char* ssid = "nome da rede wifi";
const char* password = "senha da rede wifi";

#define Sensor 36
bool flag = 1;

// +international_country_code + phone number
// Brasil +55, example: +5511988888888
String phoneNumber = "+5521Numero";
String apiKey = "recebido no wpp";

void sendMessage(String message) {

  // Data to send with HTTP POST
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  HTTPClient http;
  http.begin(url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200) {
    Serial.print("Mensagem enviada com sucesso");
  } else {
    Serial.println("Erro no envio da mensagem");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}

void setup() {
  Serial.begin(115200);

  pinMode(Sensor, INPUT);

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

  int item = digitalRead(Sensor);


  if (item == 1) {
    
    if (flag) {
      sendMessage("Atenção! Reposição de estoque necessária.");
      flag = 0;
    }
  } else {
    
    flag = 1;
  }
}