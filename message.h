#pragma once

#include "messenger.h"

struct Message {
  Message(String name, float value) {
    Name = name;
    Value = value;
  }
  String Name;
  float Value;
};
