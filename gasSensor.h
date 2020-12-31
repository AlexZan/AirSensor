#include "iSensor.h"

#define gasSesnsorAnalogPin A0

class GasSensor : public ISensor {
  public:
    void Setup() {
      Serial.print("started gas sensor");
    }

    void Loop() {
      int reading = analogRead(gasSesnsorAnalogPin);
      OnData("gas", reading);
    }
};
