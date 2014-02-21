int moonCounter = 0;
boolean flipp;
void beacon() {
  if ((time&0x03FF)?0:1) {
    setLight(255,1);
  }
  else {
    setLight(0,0);
  }
}

void moon() {
  digitalWrite(LED_DRIVER_PIN,LOW);
  
  if (flipp) {
    //analogWrite(LED_PWM_PIN, 0);
    flipp=false;
  }
  else {
    analogWrite(LED_PWM_PIN, 1);
    flipp=true;
  }
    
  //digitalWrite(LED_PWM_PIN,HIGH);
  //digitalWrite(LED_PWM_PIN,LOW);
  
  //for (int i=0;i<2;i++) {
    //digitalWrite(LED_PWM_PIN,LOW);
  //}
  //analogWrite(LED_PWM_PIN, 0);
}
