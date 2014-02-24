// ######################################################################################
// This file contains functions to make diffrent light modes
// ######################################################################################
extern unsigned long time;
int moonCounter = 0;
boolean flipp;
extern int mode;

void beacon() { // creates a light pulse every second
  if ((time&0x03FF)?0:1) {
    setLight(255,1);
  }
  else {
    setLight(0,0);
  }
}

void moon() {
  
  // atempt to make light even more weak than 1 pwm
  digitalWrite(LED_DRIVER_PIN,LOW);
  
  if (flipp) {
    //analogWrite(LED_PWM_PIN, 0);
    flipp=false;
  }
  else {
    analogWrite(LED_PWM_PIN, 1);
    flipp=true;
  }
}

// ######################################################################################
//This function creates a Strong strobe with a overlapping slightly lover intensity strobe.
// ######################################################################################
unsigned long delay1 = 1000/10; // Hz
unsigned long delay2 = 999/10; // Hz
unsigned long timeWait1;
unsigned long timeWait2;
int pulse = 10000; //how many ms long the strobe pulse is

void strobe() {
  if (timeWait1<time) {
    timeWait1 = time + delay1;
    setLight(255,1);
    delayMicroseconds(pulse);
    setLight(0,0);
  }
  if (timeWait2<time) {
    timeWait2 = time + delay2;
    //setLight(255,0);
    delayMicroseconds(pulse);
    //setLight(0,0);
  }
}
