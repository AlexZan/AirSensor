#include <ArduinoJson.h>
#include "iSensor.h"
#include "SparkFun_SGP30_Arduino_Library.h"

class SGP30Sensor : public ISensor {
  private:
    SGP30 sensor;
    //    JsonObject *sensorBuffer;
  public:
    void Setup() {
      if (!sensor.begin())
        Serial.println("SGP30 sensor not detected.");
      else
        Serial.println("connected to SGP30 sensor");

        sensor.initAirQuality();
    }

    void Loop() {
      sensor.measureAirQuality();
      updateSensHumidity();
      OnData("tvoc", sensor.TVOC);
      OnData("co2b", sensor.CO2);
    }

  private:

    uint16_t updateSensHumidity() {
      float humidity = GetSensorData("humidity");
      float temperature = GetSensorData("temperature");

      double absHumidity = RHtoAbsolute(humidity, temperature);
      uint16_t sensHumidity = doubleToFixedPoint(absHumidity);

            Serial.println("---- ");
            Serial.println(humidity);
            Serial.println(temperature);
            Serial.println(absHumidity);
            Serial.println(sensHumidity);

      sensor.setHumidity(sensHumidity);
    }

    double RHtoAbsolute (float relHumidity, float tempC) {
      double eSat = 6.11 * pow(10.0, (7.5 * tempC / (237.7 + tempC)));
      double vaporPressure = (relHumidity * eSat) / 100; //millibars
      double absHumidity = 1000 * vaporPressure * 100 / ((tempC + 273) * 461.5); //Ideal gas law with unit conversions
      return absHumidity;
    }

    int16_t doubleToFixedPoint( double number) {
      int power = 1 << 8;
      double number2 = number * power;
      uint16_t value = floor(number2 + 0.5);
      return value;
    }
};
