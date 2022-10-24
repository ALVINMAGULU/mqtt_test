void onMqttConnect(bool sessionPresent ) {
  // ESP subscribed to test topic
  uint16_t packetIdSub = mqttClient.subscribe(mqttTopic1, 0);
  mqttClient.subscribe(mqttTopic2, 0);
  mqttClient.subscribe(mqttTopic3, 0);
  mqttClient.subscribe(mqttTopic4, 0);
  mqttClient.subscribe(mqttTopic5, 0);  
  
  mqttConnected = true;
  Serial.println("Connected to mqtt");
}


void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  Serial.println("Disconnected from MQTT.");
  if (WiFi.isConnected()) {
    mqttClient.connect();
  }
  mqttConnected = false;

}

void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
  String messageTemp;
  for (int i = 0; i < len; i++) {

    messageTemp += (char)payload[i];
  }
  Serial.print("  message: ");
  Serial.println(messageTemp);
  Serial.print("  topic: ");
  Serial.println(topic);
  // Check if the MQTT message was received on topic test
    if(String(topic).indexOf(mqttTopic1) >= 0) {
       digitalWrite(LIGHT1,!stringToBool(messageTemp));
       Serial.println(stringToBool(messageTemp));    
    } else if (String(topic).indexOf(mqttTopic2) >= 0) {
      digitalWrite(LIGHT2,!stringToBool(messageTemp));
    } else if (String(topic).indexOf(mqttTopic3) >= 0) {
      digitalWrite(LIGHT3,!stringToBool(messageTemp));
    } else if (String(topic).indexOf(mqttTopic4) >= 0) {
      digitalWrite(LIGHT4,!stringToBool(messageTemp));
    } else if (String(topic).indexOf(mqttTopic5) >= 0) {
      digitalWrite(LIGHT5,!stringToBool(messageTemp));
    }
  


}

void onMqttUnsubscribe(uint16_t packetId) {
  Serial.println("Unsubscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}
