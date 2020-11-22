#include "messenger.h"
#include <Wire.h>
#include "co2Sensor.h"
#include "iSensor.h"
#include "message.h"

#define BAUD 115200
#define DELAY 2000

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



CO2Sensor cO2Sensor = CO2Sensor("co2Plus");

ISensor* sensors[] = {
  &cO2Sensor
};

void onSensorData(Message data) {
  MessengerSensorHandler(data);
}

void SensorsSetup() {
  Wire.begin();
  for (uint8_t i = 0; i < sizeof(sensors) / sizeof(sensors[0]); i++) {
    sensors[i]->Setup();
    sensors[i]->SetCallback(onSensorData);
  }
  delay(DELAY);
}


void SensorsLoop() {
  for (uint8_t i = 0; i < sizeof(sensors) / sizeof(sensors[0]); i++) {
    sensors[i]->Loop();
  }
}
