//This function creates a Strong strobe with a overlapping slightly lover intensity strobe.

extern unsigned long time;

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
