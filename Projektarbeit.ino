
/*==============================================
                Projektarbeit 
===============================================*/

/*==============================================
Titel: Projektarbeit
Description: Temperatur- und Feuchtigkeitsmessung mit LCD Display
Author: Thomas Meier & Francisco Stocker
Date: 28.01.2023
Version: V01.00.00
================================================*/

#include <DHT.h> // "DHT sensor library" by Adafruit
#include <Wire.h> // Library für LCD
#include <LiquidCrystal_I2C.h> // Library für LCD
#include "arduino_config.h" // Config-Datei mit Sensor Pinbelegung

#define DHTTYPE DHT11  // Es handelt sich um den DHT11 Sensor

DHT dht(DHTPIN, DHTTYPE); //Der Sensor wird ab jetzt mit"dth" angesprochen
LiquidCrystal_I2C lcd(0x27, 16, 2); // Pins des LCD festlegen

void setup()
{
  dht.begin(); //DHT11 Sensor starten
  lcd.init();  //LCD einschalten
  lcd.backlight(); //LCD Rücklicht einschalten
}

void loop()
{
  delay(2000); //Zwei Sekunden Vorlaufzeit (Sensor ist etwas träge)

  float Luftfeuchtigkeit = dht.readHumidity(); //Luftfeuchtigkeit auslesen
  float Temperatur = dht.readTemperature(); //Temperatur auslesen
 
  // Ausgabe auf LCD
  lcd.setCursor(0,0); //Setzt Cursor auf die 1. Zeile & die 1. Position
  lcd.print("Temp: "); //Schreibt "Temp:"
  lcd.print(Temperatur); //Zeigt die aktuelle Temperatur
  lcd.print("\337C"); // \337 = Grad(°)
  lcd.setCursor(0,1); //Setzt Cursor auf die 2. Zeile & die 1. Position
  lcd.print("Humidity: ") //Schreibt "Humidity:"
  ;lcd.print(Luftfeuchtigkeit); //Zeigt die aktuelle Luchtfeuchtigkeit
  lcd.print("%"); //Zeigt die einheit der Luftfeuchtigkeit (%)

  // Grüne LED wird eingeschalten sobald die Luftfeuchtigkeit grösser/gleich 40% ist.
  if (Luftfeuchtigkeit >= 40) {
    digitalWrite(LED_G, HIGH);
  } else {
    digitalWrite(LED_G, LOW);}

  // Gelbe LED wird eingeschalten sobald die Luftfeuchtigkeit kleiner als 40% und grösser/gleich 30% ist.
  if (Luftfeuchtigkeit < 40 and  Luftfeuchtigkeit >= 30) {
    digitalWrite(LED_Y, HIGH);
  } else {
    digitalWrite(LED_Y, LOW);}

  // Rote LED wird eingeschalten sobald die Luftfeuchtigkeit kleiner als 30% ist.
  if (Luftfeuchtigkeit < 30) {
    digitalWrite(LED_R, HIGH);
  } else {
    digitalWrite(LED_R, LOW);}
}