#include "configuration.h"

extern boolean serial;

void setup() {
  // use standard setup function from example
  pinMode(PWR_PIN,INPUT);
  digitalWrite(PWR_PIN, LOW);

  // Initialize GPIO
  pinMode(SW_PIN,  INPUT);
  pinMode(LED_DRIVER_PIN, OUTPUT);
  pinMode(LED_PWM_PIN,   OUTPUT);
  digitalWrite(LED_DRIVER_PIN, LOW);
  digitalWrite(LED_PWM_PIN,   LOW);
  
  if (digitalRead(SW_PIN)) { // If the Switch is pressed at this state the flashlight is turned on by the user, 

  }
  else { // if not its is turned on by connecting the usb to power to a computer or charger
    serialStart(); //Only start serial if we are connected to computer
    serial=true;
  }
}

void loop() {
    
  setLight(1,false);
}
  
