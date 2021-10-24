#include "DHT.h"
#include <Arduino.h>
#include <U8x8lib.h>
#include "Seeed_BMP280.h"
#include <Wire.h>
 
#define DHTPIN 3     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 
DHT dht(DHTPIN, DHTTYPE);
 
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

BMP280 bmp280;
 
void setup(void) {
  Serial.begin(9600); 
  if (!bmp280.init()) {
        Serial.println("Device not connected or broken!");
   }
  Serial.println("DHTxx test!");
  dht.begin();
  u8x8.begin();
  u8x8.setPowerSave(0);  
  u8x8.setFlipMode(1);
}
 
void loop(void) {
 
  float temp, humi, pres;
  temp = dht.readTemperature();
  humi = dht.readHumidity();
  pres = bmp280.getPressure();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.setCursor(0, 33);
  u8x8.print("Temp:");
  u8x8.print(temp);
  u8x8.print("C");
  u8x8.setCursor(0,50);
  u8x8.print("Humidity:");
  u8x8.print(humi);
  u8x8.print("%");
  u8x8.setCursor(0,80);
  u8x8.print("AP:");
  u8x8.print(pres);
  u8x8.refreshDisplay();
  delay(200);
}
