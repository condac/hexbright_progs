#define DEBUG                   1 // Debug controlls serial output

#define PULLUP                  1  //do we need pull up resistor on the switch???
#define INVERT_SW               0  // Is the switch inverted or not
#define OVERTEMP                340 
#define POWEROFF_TIME           4000 // 4s press of the button will power off
// Digital Pins
                                //0 serial tx pin
                                //1 serial rx pin
#define RED_LED_PIN             2
#define SW_PIN                  2
                                //3 unknown
                                //4 unknown
#define GREEN_LED_PIN           5
                                //6 unknown
                                //7 unknown
#define PWR_PIN                 13 //8
#define LED_DRIVER_PIN          9
#define LED_PWM_PIN             10
                                //11 unknown
                                //12 unknown
                                //13 unknown

// Analog Pins
#define TEMP_PIN                0
                                //A1 unknown
                                //A2 unknown
#define CHARGE_PIN              3


// Accelerometer

#define MMA7660_ADDRESS   0x4c // Default is 0x4c
#define MMA7660_X     0x00
#define MMA7660_Y     0x01
#define MMA7660_Z     0x02
#define MMA7660_TILT  0x03
#define MMA7660_SRST  0x04
#define MMA7660_SPCNT 0x05
#define MMA7660_INTSU 0x06
#define MMA7660_MODE  0x07
#define MMA7660_SR    0x08 // Sample rate register
#define MMA7660_PDET  0x09
#define MMA7660_PD    0x0A


