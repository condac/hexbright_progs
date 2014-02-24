
int btnBounce = 10; // the minimum pressed time on the button in ms
boolean btnState = false;
unsigned long btnTime;
unsigned long ett = 1;

void setLight(int pwm, boolean high) {
  // Set the output for the light
  // The light can adjust brightness in 2 ways
  // 1st is PWM on the output signal. making fades posible
  // 2nd is a high or low on the led driver giving it high or low currents
  // Maximum brightnes:
  // 500 Lumens PWM 255 Driver 1
  // 175 Lumens PWM 255 Driver 0
  // 50  Lumens PWM 64  Driver 0
  
  if (high) { 
    digitalWrite(LED_DRIVER_PIN, HIGH);
  }
  else {
    digitalWrite(LED_DRIVER_PIN, LOW);
  }
  analogWrite(LED_PWM_PIN, pwm);  
}

void setPower(boolean in) { //takes true or false and power up or down the flashlight
  // Not tested
  if (in) {
    pinMode(PWR_PIN, OUTPUT);
    digitalWrite(PWR_PIN, HIGH);
  }
  else {
    digitalWrite(PWR_PIN, LOW);
  }
  
}

void heatProtection() {
  
  if (analogRead(TEMP_PIN)>OVERTEMP) {
    if (DEBUG) Serial.println("Overheat!");
    setLight(0,false);
  }
  
}


int readSwitch() {
  // To be able to read the time we press the switch this function is called every loop to calculate what to do when the button is pressed
  // Once the button is released it will put out a time how long the button was pressed
  // while the button is pressed it will return 1
  
  pinMode(SW_PIN,INPUT);  //Make sure the switch is set as input
  digitalWrite(SW_PIN,PULLUP); // Set the pull up resistor to desired value
  
  if (INVERT_SW == digitalRead(SW_PIN)) {
    if (btnState) {
      //The button was pressed before and is still pressed
      
      //Maybe insert power off function here?
      if (time-btnTime >POWEROFF_TIME) {
        //Power off
        if (DEBUG) Serial.println("power off");
        delay(1); // power off delay, not realy needed as for now, might be needed if we implement save functions later. 
        setPower(false); // Power off the device
      }
      // return the negative value of time the button is pressed while it being pressed.
      int out = btnTime - time;
      return out;
    }
    else {  // The button was NOT pressed before and is now being pressed
      
      delay(btnBounce); // in case there is button bounching
      if (INVERT_SW == digitalRead(SW_PIN)) { // After delay check again if the button is still presseed
        btnState = true; // Set state to true
        btnTime = millis(); // Start button timer
        if (DEBUG) Serial.println("Button pressed");
      }
      else { // If the button was pressed for a super short time we ignore it
        if (DEBUG) Serial.println("Button bounce");
      
      }
    }
    
  }
  else {
    if (btnState) {
      // The button was pressed and have now been released
      unsigned long out = time-btnTime ;
      if (DEBUG) Serial.print("Button released: ");
      if (DEBUG) Serial.print(out);
      if (DEBUG) Serial.println("ms");
      btnState = false;
      return out;
    }
    else {
      // The button is not pressed
      return 0;
    }
  }
  return 0; // unreachable if everything is right. 
}
