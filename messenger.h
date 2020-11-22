#pragma once

#include <ESP8266WiFi.h>
//#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <PubSubClient.h>
#include "message.h"

// WiFi parameters
#define WLAN_SSID       "DontRobMyInterWebs"
#define WLAN_PASS       "6475880652"
// Adafruit IO
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "alexzan"
#define AIO_KEY         "aio_VKDz20OwpuJbtsnw2FSA5ehY2Pn4"
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

//MQTT points
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/fanControl");
Adafruit_MQTT_Publish co2Plus = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/co2plus");

Adafruit_MQTT_Subscribe *subscription;

PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}

void wifi() {
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  delay(10);
  Serial.print(F("Connecting to "));
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("WiFi connected"));
  Serial.println(F("IP address: "));
  Serial.println(WiFi.localIP());
}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
  }
  Serial.println("MQTT Connected!");
}

void SubscriptionLoop() {
  if ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &onoffbutton) {
      Serial.print(F("Got: "));
      Serial.println((char *)onoffbutton.lastread);
    }
  }
}

void MessengerSensorHandler(Message data) {
  Serial.println(data.Name + ' ' + data.Value);
  String a = R"({})";
  //mqtt.publish("https://io.adafruit.com/alexzan/feeds/co2plus", a);
  
}


void MessengerSetup() {
  Serial.println(F("Messenger starting..."));
  wifi();
  //  connect();
  mqtt.subscribe(&onoffbutton);
}

void MessengerLoop() {
  if (! mqtt.connected())
    MQTT_connect();

  SubscriptionLoop();
}
