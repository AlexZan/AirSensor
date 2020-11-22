#include "iSensor.h"
#include "SparkFun_SCD30_Arduino_Library.h"
#include "message.h"

class CO2Sensor : public ISensor {
  private:
    SCD30 sensor;

  public:
    CO2Sensor(String name) : ISensor(name) {}
    
    void Setup() {
      if (!sensor.begin())
        Serial.println("CO2 sensor not detected. Please check wiring. Freezing...");
      else
        Serial.println("connected to CO2 sensor");
    }

    void Loop() {
      if (sensor.dataAvailable())
      {
        Serial.print("co2(ppm):");
        Serial.print(sensor.getCO2());

        Serial.print(" temp(C):");
        Serial.print(sensor.getTemperature(), 1);

        Serial.print(" humidity(%):");
        Serial.println(sensor.getHumidity(), 1);

        OnData(sensor.getCO2());
      }
      else
        Serial.println("Waiting for new data");
    }
};
