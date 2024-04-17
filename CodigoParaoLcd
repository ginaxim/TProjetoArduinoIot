#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd (0x27, 16,2 ); //configura para o display correto

void setup() {
  lcd.init(); //inicializa o display lcd

//escreve a mensagem na tela

lcd.backlight();
lcd.setCursor(0,0);
lcd.print("Ola:) esse e um ");
lcd.setCursor(0,1);
lcd.print("proj. de arduino");
}

void loop() {
}
