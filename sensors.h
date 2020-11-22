//#include <Wire.h>
//#include "co2Sensor.h"
//#include "iSensor.h"
//#include "message.h"
//
//#define DELAY 2000
//
//CO2Sensor cO2Sensor = CO2Sensor("co2Plus");
//
//void (*OnSensorData)(Message);
//
//ISensor* sensors[] = {
//  &cO2Sensor
//};
//
//void onSensorData(Message data) {
//  Serial.println(data.Name + ' ' + data.Value);
//}
//
//void SensorsSetup() {
//  Wire.begin();
//  for (uint8_t i = 0; i < sizeof(sensors) / sizeof(sensors[0]); i++) {
//    sensors[i]->Setup();
//    sensors[i]->SetCallback(OnSensorData);
//  }
//  delay(DELAY);
//}
//
//
//void SensorsLoop() {
//  for (uint8_t i = 0; i < sizeof(sensors) / sizeof(sensors[0]); i++) {
//    sensors[i]->Loop();
//  }
//}
