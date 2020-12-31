#include <Wire.h>
#include <ArduinoJson.h>

#include "config.h"
#include "messenger.h"
#include "iSensor.h"
#include "co2Sensor.h"
#include "gasSensor.h"
#include "sgp30Sensor.h"
#include "pmSensor.h"



StaticJsonDocument<400> doc;
JsonObject obj = doc.to<JsonObject>();

void setup() {
  Serial.begin(BAUD);
  while (!Serial);
  delay(1000);
  MessengerSetup();
  SensorsSetup();
}

void loop() {
  SensorsLoop();
  MessengerLoop();
}

ISensor* sensors[] = {
  new CO2Sensor(), new GasSensor(), new SGP30Sensor(), new PMSensor()
};

void onSensorData(const char* name, float value) {
  doc[name] = value;
}

void SensorsSetup() {
  Wire.begin();
  for (uint8_t i = 0; i < sizeof(sensors) / sizeof(sensors[0]); i++) {
    sensors[i]->Setup();
    sensors[i]->SetCallback(onSensorData);
    sensors[i]->SetSensorBuffer(&obj);
  }
}


void SensorsLoop() {
  for (uint8_t i = 0; i < sizeof(sensors) / sizeof(sensors[0]); i++) {
    sensors[i]->Loop();
  }
  MessengerSend(doc);

  delay(DELAY);
}
