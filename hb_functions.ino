// ######################################################################################
// This file contains functions to make diffrent light modes
// ######################################################################################
extern unsigned long time;
int moonCounter = 0;
boolean flipp;
extern int mode;
int tactPrev = 0;

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
  setLight(4,0);
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
    setLightFast(255,1);
    delayMicroseconds(pulse);
    setLightFast(0,0);
  }
  if (timeWait2<time) {
    timeWait2 = time + delay2;
    //setLight(255,0);
    delayMicroseconds(pulse);
    //setLight(0,0);
  }
}

// ######################################################################################
// DISCO-mode by condac "patent pending"
// ######################################################################################

void disco() {
  extern int x;
  extern int y;
  extern int z;
  int ax = abs(x);
  int ay = abs(y);
  int az = abs(z);
      
  int totalForce;
  int intensity;
  
  totalForce = ax+ay+az; // At rest this should add up to 21.33 (but we dont have decimals of cource)
  
  intensity = (totalForce-31)*1;
  
  if (DEBUG) Serial.print("               Disco:");
  if (DEBUG) Serial.print(totalForce);
  if (DEBUG) Serial.print(" int:");
  if (DEBUG) Serial.println(intensity);
  
  if (intensity>255) {
    intensity = 255;
  }
  if (intensity <0) {
    // BlinkMode
    intensity = abs(intensity);
    if (intensity>255) {
      intensity = 255;
    }
    setLight(intensity,1);
    delay(1);
    setLight(0,1);
  }
  else {
    setLight(intensity,1);
  }
  
}

void tactical() {
  extern int y;
  int out = 512-(abs(y)* 26);
  if (out <0) {
    out = 0;
  }
  tactPrev = ( (tactPrev*2) + out )/3;
  setLight(tactPrev);
  
  if (DEBUG) Serial.print("               Tactical:");
  if (DEBUG) Serial.print(out);
  if (DEBUG) Serial.print(" prev:");
  if (DEBUG) Serial.println(tactPrev);
}
