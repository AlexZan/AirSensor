#pragma once

#include "message.h"

class ISensor {
  private:
    void (*onData)(Message);
  protected:
    void OnData(float value) {
      if(onData)
        onData(Message(Name, value));
    }
    String Name;
  public:
    ISensor(String name) {
      Name = name;
    }

    virtual void Setup() = 0;
    virtual void Loop() = 0;

    void SetCallback(void (*callback)(Message)) {
      onData = callback;
    }
};
