#include "iSensor.h"
#include "SparkFun_SCD30_Arduino_Library.h"

class CO2Sensor : public ISensor {
  private:
    SCD30 sensor;

  public:
    
    void Setup() {
      if (!sensor.begin())
        Serial.println("CO2 sensor not detected.");
      else
        Serial.println("connected to CO2 sensor");
    }

    void Loop() {
      if (sensor.dataAvailable())
      {
        OnData("co2", sensor.getCO2());
        OnData("temperature", sensor.getTemperature());
        OnData("humidity", sensor.getHumidity());
      }
      else
        Serial.println("Waiting for new data");
    }
};
