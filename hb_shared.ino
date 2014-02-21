boolean serial = false;


void setLight(int pwm, boolean high) {
  //Set the output for the light
  //The light can adjust brightness in 2 ways
  // 1st is PWM on the output signal. making fades posible
  // 2nd is a high or low on the led driver giving it high or low currents
  if (high) { 
    digitalWrite(LED_DRIVER_PIN, HIGH);
  }
  else {
    digitalWrite(LED_DRIVER_PIN, LOW);
  }
  analogWrite(LED_PWM_PIN, pwm);  
}

void setPower(boolean in) { //takes true or false and power up or down the flashlight
  
  
}

void heatProtection() {
  if (analogRead(TEMP_PIN)>OVERTEMP) {
    sprintln("Overheat!");
    setLight(0,false);
  }
  
}
void sprintln(String in) {
  if (serial) {
    Serial.println(in);
  }
}
void sprint(String in) {
  if (serial) {
    Serial.print(in);
  }
}
void serialStart() { //Only start serial if we are connected to computer
  Serial.begin(9600);
    serial = true;
    Serial.println("Connected!");
}
