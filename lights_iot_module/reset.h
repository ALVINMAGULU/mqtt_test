void IRAM_ATTR isr() {
  shouldResetBoard = true;  

}

  void resetBoard(){
  delay(3000);
  if(digitalRead(INTERRUPT_PIN)){
  runWiFiManager();

}else{
  bool formatted = SPIFFS.format();

  if(formatted){
  Serial.println("\n\nSuccess formatting");
  }else{
  Serial.println("\n\nError formatting");
  }
}
  shouldResetBoard = false;
}
