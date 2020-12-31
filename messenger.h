#pragma once

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi parameters
#define WLAN_SSID       "DontRobMyInterWebs"
#define WLAN_PASS       "6475880652"
// Adafruit IO
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "alexzan"
#define AIO_KEY         "aio_hsje71NhGIvjwIz8ovaEXlFBQHbK"
WiFiClient wifiClient;


PubSubClient client(wifiClient);

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}

void wifi() {
  Serial.print(F("Connecting to "));
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }

  Serial.println(F("\n WiFi connected"));
  Serial.println(F("IP address: "));
  Serial.println(WiFi.localIP());
}

void mqqtConnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    String clientId = String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), AIO_USERNAME, AIO_KEY)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void MessengerSetup() {
  Serial.println(F("Messenger starting..."));
  wifi();
  client.setServer(AIO_SERVER, AIO_SERVERPORT);
  client.setCallback(callback);
}

void MessengerLoop() {
  if (! client.connected())
    mqqtConnect();

  client.loop();

}

void MessengerSend(StaticJsonDocument<400> buffer) {

  StaticJsonDocument<400> doc;
  char output[400];
  doc["feeds"] = buffer;
  serializeJson(doc, output);


  Serial.println(output);
  
  client.publish("alexzan/groups/default/json", output);
}
