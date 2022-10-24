void runWiFiManager() {

  WiFiManager wm;
  // WiFiManagerParameter mqtt_topic1("ssid", "Wifi ssid", "wifi name", 40);
  WiFiManagerParameter Id("id", "ID", "", 40);
  WiFiManagerParameter mqtt_topic1("output1", "light1", "test", 40);
  WiFiManagerParameter mqtt_topic2("output2", "light2", "test", 40);
  WiFiManagerParameter mqtt_topic3("output3", "light3", "test", 40);
  WiFiManagerParameter mqtt_topic4("output4", "light4", "test", 40);
  WiFiManagerParameter mqtt_topic5("output5", "light5", "test", 40);
  wm.setSaveConfigCallback(saveConfigCallback);
  wm.setClass("invert");


  //wm.resetSettings();
  wm.addParameter(&Id);
  wm.addParameter(&mqtt_topic1);
  wm.addParameter(&mqtt_topic2);
  wm.addParameter(&mqtt_topic3);
  wm.addParameter(&mqtt_topic4);
  wm.addParameter(&mqtt_topic5);
  // set configportal timeout
  wm.setConfigPortalTimeout(timeout);

  if (!wm.startConfigPortal("EchoYange lights") || forceConfig) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.restart();
    delay(5000);
  }

  strncpy(mqttTopic1, mqtt_topic1.getValue(), sizeof(mqttTopic1));
  strncpy(mqttTopic2, mqtt_topic2.getValue(), sizeof(mqttTopic2));
  strncpy(mqttTopic3, mqtt_topic3.getValue(), sizeof(mqttTopic3));
  strncpy(mqttTopic4, mqtt_topic4.getValue(), sizeof(mqttTopic4));
  strncpy(mqttTopic5, mqtt_topic5.getValue(), sizeof(mqttTopic5));
  strncpy(id, Id.getValue(), sizeof(id));
  addId(mqttTopic1);
  addId(mqttTopic2);
  addId(mqttTopic3);
  addId(mqttTopic4);
  addId(mqttTopic5);
  
   String str1 = wm.getWiFiPass(true);
   String str2 = WiFi.SSID();
 
   str1.toCharArray(wifiPassword, sizeof(str1));
   str2.toCharArray(wifiSsid, sizeof(str2));
  
  //if you get here you have connected to the WiFi
  if (shouldSaveConfig) {

    saveConfigFile();
    loadConfigFile();
  }
  mqttClient.connect();
}
