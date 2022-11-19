void saveConfigFile() {
  Serial.println(F("Saving configuration..."));
  StaticJsonDocument<600> json;
  json["mqtt1"] = mqttTopic1;
  json["mqtt2"] = mqttTopic2;
  json["mqtt3"] = mqttTopic3;
  json["mqtt4"] = mqttTopic4;
  json["mqtt5"] = mqttTopic5;
  json["ssid"] = ssidString;
  json["password"] = pskString;
  
  File configFile = SPIFFS.open(CONFIG_FILE, "w");
  if (!configFile) {
    // Error, file did not open
    Serial.println("failed to open config file for writing");
  }
  if (serializeJson(json, configFile) == 0) {
    // Error writing file
    Serial.println(F("Failed to write to file"));
  }
  // Close file
  configFile.close();
}

bool loadConfigFile()
// Load existing configuration file
{
  // Uncomment if we need to format filesystem
  // SPIFFS.format();

  // Read configuration from FS json
  Serial.println("Mounting File System...");

  // May need to make it begin(true) first time you are using SPIFFS
  if (SPIFFS.begin(false) || SPIFFS.begin(true)) {
    Serial.println("mounted file system");
    if (SPIFFS.exists(CONFIG_FILE)) {
      // The file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open(CONFIG_FILE, "r");
      if (configFile) {
        Serial.println("Opened configuration file");
        StaticJsonDocument<1024> json;
        DeserializationError error = deserializeJson(json, configFile);
        serializeJsonPretty(json, Serial);
        if (!error) {
          Serial.println("Parsing JSON");

          strcpy(mqttTopic1, json["mqtt1"]);
          strcpy(mqttTopic2, json["mqtt2"]);
          strcpy(mqttTopic3, json["mqtt3"]);
          strcpy(mqttTopic4, json["mqtt4"]);
          strcpy(mqttTopic5, json["mqtt5"]);
         
         String str3 = json["ssid"].as<String>();
       
          String str4 = json["password"].as<String>();
          //wifiPassword = string2.c_str();
          str3.toCharArray(wifiSsid, str3.length()+1);
          str4.toCharArray(wifiPassword, str4.length()+1);
          
          return true;
        } else {
          // Error loading JSON data
          Serial.println("Failed to load json config");
        }
      }
    }
  } else {
    // Error mounting file system
    Serial.println("Failed to mount FS");
  }

  return false;
}

void saveConfigCallback()
// Callback notifying us of the need to save configuration
{
  Serial.println("Should save config");
  shouldSaveConfig = true;
  forceConfig = false;
}
