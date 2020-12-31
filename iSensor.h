#pragma once
#include <ArduinoJson.h>

class ISensor {
  private:
    JsonObject *sensorBuffer;
  protected:
    void (*OnData)(const char* name, float value);
    float GetSensorData(const char* name) {
      return (*sensorBuffer)[name];
    }
  public:

    virtual void Setup() = 0;
    virtual void Setup(JsonObject *sensorBuffer) {
      Setup();
    }
    virtual void Loop() = 0;

    void SetSensorBuffer(JsonObject *buffer) {
      sensorBuffer = buffer;
    }
    void SetCallback(void (*callback)(const char* name, float value)) {
      OnData = callback;
    }
};
