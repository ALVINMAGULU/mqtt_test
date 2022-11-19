#include <WiFi.h>
#include <WiFiClient.h>
void wifiConnect() {
  
  Serial.print("Connecting to wifi");
  Serial.println(wifiSsid);
  Serial.println(wifiPassword);
  WiFi.begin(wifiSsid,wifiPassword);
  int t = 0;
  
  while (WiFi.status() != WL_CONNECTED) {
   
    Serial.print(".");
    t ++;
    if (t >= 10) {
      break;
    }
      delay(1000);
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("wifi connected");
     mqttClient.connect();
  }
   
}
