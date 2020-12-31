#include "iSensor.h"
#include "Adafruit_PM25AQI.h"

class PMSensor : public ISensor {
  private:
    Adafruit_PM25AQI aqi = Adafruit_PM25AQI();

  public:

    void Setup() {
      if (!aqi.begin_I2C())
        Serial.println("Could not find PM 2.5 sensor!");

      else
        Serial.println("PM25 found!");
    }

    void Loop() {
      PM25_AQI_Data data;

      if (! aqi.read(&data)) {
        Serial.println("Could not read from AQI");
        delay(500);  // try again in a bit!
        return;
      }

      OnData("pm03", data.particles_03um);
      OnData("pm05", data.particles_05um);
      OnData("pm10", data.pm10_standard);
      OnData("pm25", data.pm25_standard);
      OnData("pm100", data.pm100_standard);
    }
};
