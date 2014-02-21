#include "configuration.h"

// Modes
#define MODE_MOON               0
#define MODE_LOW                1
#define MODE_MED                2
#define MODE_HIGH               3
#define MODE_STROBE             4
#define MODE_BEACON             5
int maxMode           =         5;

extern boolean serial;
unsigned long time;
int mode = 0;

void setup() {
  pinMode(PWR_PIN, OUTPUT);
  digitalWrite(PWR_PIN, LOW);
  // use standard setup function from example
  pinMode(PWR_PIN,INPUT);
  digitalWrite(PWR_PIN, LOW);

  // Initialize GPIO
  pinMode(SW_PIN,INPUT);
  digitalWrite(SW_PIN,PULLUP); // pull up ?
  pinMode(LED_DRIVER_PIN, OUTPUT);
  pinMode(LED_PWM_PIN,   OUTPUT);
  digitalWrite(LED_DRIVER_PIN, LOW);
  digitalWrite(LED_PWM_PIN,   LOW);
  
  if (!digitalRead(SW_PIN)) { // If the Switch is pressed at this state the flashlight is turned on by the user, 
    setPower(true);
  }
  else { // if not its is turned on by connecting the usb to power to a computer or charger
    serialStart(); //Only start serial if we are connected to computer
    serial=true;
  }
  
}

void loop() {
  time = millis(); // read the time every loop
  
  //digitalWrite(PWR_PIN, (time&0x03FF)?LOW:HIGH );
  
  long buttonTime = readSwitch();
  if (buttonTime < 0 && buttonTime > -1000) {
    digitalWrite(GREEN_LED_PIN,HIGH);
  }
  else if (buttonTime < -(POWEROFF_TIME-500) && buttonTime > -POWEROFF_TIME) {
    digitalWrite(GREEN_LED_PIN, ((time/10)&0x000F)?LOW:HIGH );
  }
  else if (buttonTime == 0 ) { // no button is pressed
    // Blink the green indicator LED now and then
    digitalWrite(GREEN_LED_PIN, (time&0x03FF)?LOW:HIGH );
  }else {
    digitalWrite(GREEN_LED_PIN,LOW);
  }
  if (buttonTime > 1000) { //Simple cycle through modes
      mode = MODE_MOON;
  }
  else if (buttonTime > 50) { //Simple cycle through modes
    mode++;
    sprint("modechanged");
    sprintln(buttonTime);
    
    if (mode>maxMode) {
      mode = 0;
    }
  }
  

  modeCase();
}
  
void modeCase() {
  switch (mode)
  {
  case MODE_MOON:
    moon();
    break;
  case MODE_LOW:
    setLight(128,0);
    break;
  case MODE_MED:
    setLight(255,0);
    break;
  case MODE_HIGH:
    setLight(255,1);
    break;
  case MODE_STROBE:
    strobe();
    break;
  case MODE_BEACON:
    beacon();
    break;  
  }
}
