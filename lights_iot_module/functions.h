bool stringToBool(String string){
  if(string == "on"){
    return true;
  }else{
     return false;
  }
}

void addId (char mqttTopic[]){
  String string  = String(id) + "/" + String(mqttTopic);
  string.toCharArray(mqttTopic, string.length()+1);
}
