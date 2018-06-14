#include <TimerOne.h>

/////////////////////////////////////////////
// POT/PWM constants and golbal variables
//
#define POT_READ  A0    //Pot Read Input pin
#define POT_DIFF  4     //Threshold for pot value update
#define POT_MAX   1023  //Pot Max map value 
#define MAX_DUTY  950   //PWM Max duty to map to
#define PWM_OUT   9     //PWM Output port
#define PWM_CYCLE 50.0  //PWM Output period
int gPotVal;            //Global pot value
int gLastPotVal;

void setup()
{
  pinMode(POT_READ, INPUT);
  pinMode(PWM_OUT, OUTPUT);
  Timer1.initialize(PWM_CYCLE*1000);
  Timer1.pwm(PWM_OUT, 0);
  //Need to delay before we start
  delay(2000);
}

void loop()
{
  updatePotValue();
  int speedset = map(gPotVal, 0, POT_MAX, 0, MAX_DUTY);
  if (gPotVal != gLastPotVal) {
    Timer1.setPwmDuty(PWM_OUT, speedset);  
  }
}


void updatePotValue()
{
  int potTmp = analogRead(POT_READ);
  int potChk = abs(potTmp - gPotVal);
  if (potChk >= POT_DIFF) {
    gLastPotVal = gPotVal;
    gPotVal = potTmp;
  }
}

