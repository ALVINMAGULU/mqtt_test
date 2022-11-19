
#include "definitions.h"

void setup() {
  Serial.begin(115200);

  pinMode(LIGHT1, OUTPUT);
  pinMode(LIGHT2, OUTPUT);
  pinMode(LIGHT3, OUTPUT);
  pinMode(LIGHT4, OUTPUT);
  pinMode(LIGHT5, OUTPUT);

  digitalWrite(LIGHT1,HIGH);
  digitalWrite(LIGHT2,HIGH);
  digitalWrite(LIGHT3,HIGH);
  digitalWrite(LIGHT4,HIGH);
  digitalWrite(LIGHT5,HIGH);

  pinMode(MQTTLIGHT, OUTPUT);

  // setting up mqtt functions
  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);



  WiFi.mode(WIFI_STA);

  bool spiffsSetup = loadConfigFile();
  if (!spiffsSetup) {
    Serial.println(F("Forcing config mode as there is no saved config"));
    forceConfig = true;
  }


  attachInterrupt(INTERRUPT_PIN, isr, FALLING);

  if (forceConfig) {
    runWiFiManager();
  }
}


void loop() {
  if (WiFi.status() != WL_CONNECTED && wifiSsid != "ssid#*") {
    wifiConnect();
  }

  if (shouldResetBoard == true) {
    resetBoard();
  }

  digitalWrite(MQTTLIGHT, !mqttConnected);
}
