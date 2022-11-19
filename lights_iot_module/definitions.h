#define LIGHT1 16
#define LIGHT2 17
#define LIGHT3 5
#define LIGHT4 18
#define LIGHT5 19
#define INTERRUPT_PIN 15

#define MQTTLIGHT 2
#define CONFIG_FILE "/json_config.json"

bool mqttConnected = false;
bool shouldSaveConfig = false;
int timeout = 300;
bool forceConfig = false;
bool shouldResetBoard = false;

char wifiSsid[20] = "ssid#*";
char wifiPassword[20] = "password";

String ssidString;
String pskString;
const long utcOffsetInSeconds = 10800;

char mqttTopic1[40] = "test";
char mqttTopic2[40] = "test";
char mqttTopic3[40] = "test";
char mqttTopic4[40] = "test";
char mqttTopic5[40] = "test";
char id[40] = "000";
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <AsyncMqtt_Generic.h>
#include <WiFiManager.h>
#include <FS.h>
#include <SPIFFS.h>

#define MQTT_HOST IPAddress(0,0,0,0)
#define MQTT_PORT 1883
AsyncMqttClient mqttClient;
TimerHandle_t mqttReconnectTimer;
TimerHandle_t wifiReconnectTimer;
// Interval at which to publish sensor readings

int i = 0;


#define MQTT_USERNAME "username"
#define MQTT_PASSWORD "password"
#define MQTT_PUB_TEST "test"
#define MQTT_SUB_TEST "test"

#include "functions.h"

#include "mqtt.h"
#include "wifi_functions.h"
#include "spiffs.h"
#include "wifi_manager.h"
#include "reset.h"

//bool gsm;
