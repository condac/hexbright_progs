// ######################################################################################
// This file contains common used functions.
// ######################################################################################

#include <Wire.h>

extern unsigned long time;
int btnBounce = 10; // the minimum pressed time on the button in ms
boolean btnState = false;
unsigned long btnTime;
unsigned long accTime;
extern int mode;
int x;
int y;
int z;

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

void setLightFast(int pwm, boolean high) { // The digitalWrite function is by design very slow compared to what it is posible in the hardware. 
                                           // This is a attempt to manipulate the ports directly. 
  if (high) { 
    PORTB |= (1 << 1); // Set 1 on DRIVER pin
  }
  else {
    PORTB &= ~(1 << 1); // Set 0 on DRIVER pin
  }
  OCR1B = pwm;
}

void setPWM(int pwm) { // Set only PWM don't bother with the driver
  OCR1B = pwm;
}

void setPower(boolean in) { //takes true or false and power up or down the flashlight
  // Not tested
  if (in) {
    pinMode(PWR_PIN, OUTPUT);
    digitalWrite(PWR_PIN, HIGH);
  }
  else {
    pinMode(PWR_PIN, OUTPUT);
    digitalWrite(PWR_PIN, LOW);
  }
}

void heatProtection() {
  int temp = analogRead(TEMP_PIN);
  if (temp>OVERTEMP) {
    if (DEBUG) Serial.println("Overheat!");
    setLight(0,false);
    mode = 0;
    for (int i=100;i>0;i--) { // not often you see a for loop with i--
      setLight(i,false);
    }
  }
  if (DEBUG) Serial.print("temp: ");
  if (DEBUG) Serial.println(temp);
}

void checkCharge() {
  // Copy from factory example
  // Check the state of the charge controller
  int chargeState = analogRead(CHARGE_PIN);
  if (chargeState < 128)  // Low - charging
  {
    digitalWrite(GREEN_LED_PIN, (time&0x0100)?LOW:HIGH);
  }
  else if (chargeState > 768) // High - charged
  {
    digitalWrite(GREEN_LED_PIN, HIGH);
  }
  else // Hi-Z - shutdown
  {
    digitalWrite(GREEN_LED_PIN, LOW);    
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

void loopAcc() { // Read the accelerometer once at 120hz
  if (accTime<time) {
    accTime = time + 9;
    readAccXYZ();
  }
}

void readAccXYZ() { // TODO: read the accelerometer
  
  byte val[3];
  int count = 0;
  val[0] = val[1] = val[2] = 64;
  
  Wire.requestFrom((int)MMA7660_ADDRESS, 3);
  
  while(Wire.available()) {
    if(count < 3) {
      while(val[count] > 63) {
        val[count] = Wire.read();
      }
      count++;
    }
  }
  
  // Shift the values left 2 is the same as x*2*2 and divide by 4 seems to get the same results
  // BUT! the value returned by the accelerometer is a signed 6-bit value, and the 5th bit is the positive/negative bit
  // We move the signed bit up to the 8th bit and create a valid signed 8-bit number, then we divide it by 4.
  x = (val[0]<<2)/4; 
  y = (val[1]<<2)/4;
  z = (val[2]<<2)/4;
  // The resulting x y z values are from -32 to +31 where 21.33 is 1g 
}

void startAcc() {
  Wire.beginTransmission(MMA7660_ADDRESS); // transmit to device
  Wire.write((byte)0x00);                // try to send data

  if(Wire.endTransmission() == 0) { // If the device responds and is present
    sendCommand(MMA7660_MODE, 0x00); // Set device to standby mode (temporarly)
    sendCommand(MMA7660_SR, 0x00);   // Set the sample rate to 120hz and tap detection mode
    sendCommand(MMA7660_MODE, 0x01); // Set the device to active mode.
  }
}

void sendCommand(byte op, byte com) {
  Wire.beginTransmission(MMA7660_ADDRESS);
  Wire.write((byte)op);   
  Wire.write((byte)com);

  Wire.endTransmission();
}
