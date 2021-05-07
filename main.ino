#include <WiFi.h>
#include <BME280I2C.h>
#include <Wire.h>
#include "Ambient.h"

static const char *SSID = "XXXXXXXX";
static const char *PASSWORD = "XXXXXXXX";
static const unsigned int CHID = 0;
static const char *WKEY = "XXXXXXXXXXXXXXXX";

BME280I2C bme;
WiFiClient client;
Ambient ambient;

void setup() {

  Wire.begin();
  while (!bme.begin()) {
    delay(1000);
  }

  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  ambient.begin(CHID, WKEY, &client);
}

void loop() {
  float temp = 0.0;
  float hum = 0.0;
  float pres = 0.0;

  BME280::TempUnit tempUnit{BME280::TempUnit_Celsius};
  BME280::PresUnit presUnit{BME280::PresUnit_hPa};

  bme.read(pres, temp, hum, tempUnit, presUnit);

  ambient.set(1, temp);
  ambient.set(2, hum);
  ambient.set(3, pres);
  ambient.send();

  delay(15000);
}
