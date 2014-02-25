

#include "configuration.h"

// Modes
#define MODE_MOON               0
#define MODE_LOW                1
#define MODE_MED                2
#define MODE_HIGH               3
#define MODE_STROBE             4
#define MODE_BEACON             5
#define MODE_DISCO              6
int maxMode           =         6;

unsigned long time;
int mode = 0;

void setup() {
   // If we leave the regulator's enable pin as high-impedance,
  // the regulator will power down the board about a half 
  // second after release of the button.
  pinMode(PWR_PIN,INPUT);
  digitalWrite(PWR_PIN, LOW);

  // Initialize GPIO
  pinMode(SW_PIN,INPUT);
  digitalWrite(SW_PIN,PULLUP); // pull up ?
  pinMode(LED_DRIVER_PIN, OUTPUT);
  pinMode(LED_PWM_PIN,   OUTPUT);
  digitalWrite(LED_DRIVER_PIN, LOW);
  digitalWrite(LED_PWM_PIN,   LOW);
  
  if (INVERT_SW == digitalRead(SW_PIN)) { // If the Switch is pressed at this state the flashlight is turned on by the user, 
    setPower(true);
  }
  else { // if not its is turned on by connecting the usb to power to a computer or charger
    if (DEBUG) {
      Serial.begin(9600);
      Serial.println("Connected!");
    }
  }
  startAcc();
}

void loop() {
  time = millis(); // read the time every loop
  
  //digitalWrite(PWR_PIN, (time&0x03FF)?LOW:HIGH );
  
  long buttonTime = readSwitch(); // readSwitch returns the state of the button, negative value is the current time the button is being pressed
                                  // once the button is released it returns the time it was pressed as a positive number
                                  // if not pressed it returns 0
                                  // we use the negative value to make the green light flash diffrent depending on how long the button is pressed
                                  // to give feedback so the user know when he can release the button for diffrent modes
  
  if (buttonTime < 0) {
    buttonDown(buttonTime);
  }
  else if (buttonTime == 0 ) { // no button is pressed
 
    digitalWrite(GREEN_LED_PIN, (time&0x03FF)?LOW:HIGH );   // Blink the green indicator LED now and then
  }
  
  if (buttonTime > 1000) { // If the button is pressed for more than 1s it goes to low light moon mode. 
      mode = MODE_MOON;
  }
  else if (buttonTime > 50) { //Simple cycle through modes
    mode++;
    if (DEBUG) Serial.print("modechanged");
    if (DEBUG) Serial.println(buttonTime);
    
    if (mode>maxMode) {
      mode = 0;
    }
  }
  
  loopAcc();
  modeCase(); // 
}
  
void buttonDown(long buttonTime) {
  
  if (buttonTime < 0 && buttonTime > -1000) { // the green light is on for 1s
    digitalWrite(GREEN_LED_PIN,HIGH);
  }
  else if (buttonTime < -(POWEROFF_TIME-500) && buttonTime > -POWEROFF_TIME) { // 0.5s before the light is powerd down the green light flashes rapidly
    digitalWrite(GREEN_LED_PIN, ((time/10)&0x000F)?LOW:HIGH );
  }
  else {
    digitalWrite(GREEN_LED_PIN,LOW);
  }
  
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
