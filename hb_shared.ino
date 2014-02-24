int btnBounce = 10;
boolean btnState = false;
unsigned long btnTime;
unsigned long ett = 1;

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
  pinMode(SW_PIN,INPUT);
  digitalWrite(SW_PIN,PULLUP);
  
  if (!digitalRead(SW_PIN)) {
    if (btnState) {
      //The button was pressed before and is still pressed
      
      //Maybe insert power off function here?
      if (time-btnTime >POWEROFF_TIME) {
        //Power off
        if (DEBUG) Serial.println("power off");
        delay(1);
        setPower(false);
      }
      // return the negative value of time the button is pressed while it being pressed.
      int out = btnTime - time;
      return out;
    }
    else {
      // The button was NOT pressed before and is now being pressed
      
      delay(btnBounce); // in case there is button bounching
      if (!digitalRead(SW_PIN)) {
      btnState = true;
      btnTime = millis();
      if (DEBUG) Serial.println("Button pressed");
      }
      else {
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
  return 0;
}
