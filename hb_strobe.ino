//This function creates a Strong strobe with a overlapping slightly lover intensity strobe.

extern unsigned long time;

unsigned long delay1 = 1000/12; //12Hz
unsigned long delay2 = 1000/18; //18Hz
unsigned long timeWait1;
unsigned long timeWait2;
int pulse = 1; //how many ms long the strobe pulse is

void strobe() {
  if (timeWait1>time) {
    timeWait1 = time + delay1;
    setLight(255,1);
    delay(pulse);
    setLight(0,0);
  }
  if (timeWait2>time) {
    timeWait2 = time + delay2;
    setLight(255,0);
    delay(pulse);
    setLight(0,0);
  }
}
