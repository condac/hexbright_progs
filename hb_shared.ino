boolean serial = false;

int btnBounce = 10;
boolean btnState = false;
unsigned long btnTime;

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

int readSwitch() {
  // To be able to read the time we press the switch this function is called every loop to calculate what to do when the button is pressed
  // Once the button is released it will put out a time how long the button was pressed
  // while the button is pressed it will return 1
  pinMode(SW_PIN,INPUT);
  digitalWrite(SW_PIN,PULLUP);
  
  if (digitalRead(SW_PIN)) {
    if (btnState) {
      //The button was pressed before and is still pressed
      
      //Maybe insert power off function here?
      if (time-btnTime >POWEROFF_TIME) {
        //Power off
        sprintln("power off");
        delay(1);
        setPower(false);
      return 1;
    }
    else {
      // The button was NOT pressed before and is now being pressed
      btnState = true;
      btnTime = time;
      delay(btnBounce); // in case there is button bounching
      sprintln("Button pressed");
    }
    
  }
  else {
    if (btnState) {
      // The button was pressed and have now been released
      int out = (int) ( time-btnTime );
      sprint("Button released: ");
      sprint(""+out);
      sprintln("ms");
      return out;
    }
    else {
      // The button is not pressed
      return 0;
    }
  }
}
