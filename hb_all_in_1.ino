#include "configuration.h"

extern boolean serial;
unsigned long time;

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
    setPower(true);
  }
  else { // if not its is turned on by connecting the usb to power to a computer or charger
    serialStart(); //Only start serial if we are connected to computer
    serial=true;
  }
  
}

void loop() {
  time = millis(); // read the time every loop
  int buttonTime = readSwitch();
  // Blink the green indicator LED now and then
  digitalWrite(GREEN_LED_PIN, (time&0x03FF)?LOW:HIGH);

  setLight(1,false);
}
  

