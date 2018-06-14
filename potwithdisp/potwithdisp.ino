#include <TimerOne.h>

///////////////////////////////////////////////////////
// Code modified / inspired by the following sources:
// https://sonsofinvention.wordpress.com/2013/05/22/arduino-compatible-mc-2100-controller-and-lathe-tachometer/
// https://www.hobbytronics.co.uk/arduino-4digit-7segment

/////////////////////////////////////////////
// LED display constants
//
#define DIGIT_1 11 //PWM Display pin 1
#define DIGIT_2 10 //PWM Display pin 2
#define DIGIT_3 2  //PWM Display pin 6
#define DIGIT_4 6  //PWM Display pin 8
#define DIGIT_ON  HIGH
#define DIGIT_OFF LOW

#define SEG_A A1 //Display pin 14
#define SEG_B 3  //Display pin 16
#define SEG_C 4  //Display pin 13
#define SEG_D 5  //Display pin 3
#define SEG_E A0 //Display pin 5
#define SEG_F 7  //Display pin 11
#define SEG_G 8  //Display pin 15
#define SEG_ON  LOW
#define SEG_OFF HIGH

// Value 1 to 5000 (1 is dim 5000 is blinding)
#define DISPLAY_BRIGHTNESS 500

/////////////////////////////////////////////
// POT/PWM constants and golbal variables
//
#define POT_READ  A3    //Pot Read Input pin
#define POT_DIFF  4     //Threshold for pot value update
#define POT_MAX   1023  //Pot Max map value 
#define MAX_DUTY  869   //PWM Max duty to map to
#define PWM_OUT   9     //PWM Output port
#define PWM_CYCLE 50.0  //PWM Output period
int gPotVal;            //Global pot value

void setup()
{
  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_G, OUTPUT);

  pinMode(DIGIT_1, OUTPUT);
  pinMode(DIGIT_2, OUTPUT);
  pinMode(DIGIT_3, OUTPUT);
  pinMode(DIGIT_4, OUTPUT);

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
  int disp = map(gPotVal, 0, POT_MAX, 0, MAX_DUTY);
  displayNumber(disp);
  Timer1.setPwmDuty(PWM_OUT, disp);
}


void updatePotValue()
{
  int potTmp = analogRead(POT_READ);
  int potChk = abs(potTmp - gPotVal);
  if (potChk >= POT_DIFF)
    gPotVal = potTmp;
}


void displayNumber(int toDisplay)
{
  long beginTime = millis();

  for (int digit = 4 ; digit > 0 ; digit--)
  {
    //Turn on a digit for a short amount of time
    switch (digit)
    {
      case 1: digitalWrite(DIGIT_1, DIGIT_ON); break;
      case 2: digitalWrite(DIGIT_2, DIGIT_ON); break;
      case 3: digitalWrite(DIGIT_3, DIGIT_ON); break;
      case 4: digitalWrite(DIGIT_4, DIGIT_ON); break;
    }

    //Turn on the right segments for this digit
    lightNumber(toDisplay % 10);
    toDisplay /= 10;

    delayMicroseconds(DISPLAY_BRIGHTNESS);
    //Display digit for fraction of a second (1us to 5000us, 500 is pretty good)

    //Turn off all segments
    lightNumber(10);

    //Turn off all digits
    digitalWrite(DIGIT_1, DIGIT_OFF);
    digitalWrite(DIGIT_2, DIGIT_OFF);
    digitalWrite(DIGIT_3, DIGIT_OFF);
    digitalWrite(DIGIT_4, DIGIT_OFF);
  }

  delay(10);
}

//Given a number, turns on those segments
//If number == 10, then turn off number
void lightNumber(int numberToDisplay)
{
  switch (numberToDisplay)
  {
    case 0:
      digitalWrite(SEG_A, SEG_ON );
      digitalWrite(SEG_B, SEG_ON );
      digitalWrite(SEG_C, SEG_ON );
      digitalWrite(SEG_D, SEG_ON );
      digitalWrite(SEG_E, SEG_ON );
      digitalWrite(SEG_F, SEG_ON );
      digitalWrite(SEG_G, SEG_OFF);
      break;

    case 1:
      digitalWrite(SEG_A, SEG_OFF);
      digitalWrite(SEG_B, SEG_ON );
      digitalWrite(SEG_C, SEG_ON );
      digitalWrite(SEG_D, SEG_OFF);
      digitalWrite(SEG_E, SEG_OFF);
      digitalWrite(SEG_F, SEG_OFF);
      digitalWrite(SEG_G, SEG_OFF);
      break;

    case 2:
      digitalWrite(SEG_A, SEG_ON );
      digitalWrite(SEG_B, SEG_ON );
      digitalWrite(SEG_C, SEG_OFF);
      digitalWrite(SEG_D, SEG_ON );
      digitalWrite(SEG_E, SEG_ON );
      digitalWrite(SEG_F, SEG_OFF);
      digitalWrite(SEG_G, SEG_ON );
      break;

    case 3:
      digitalWrite(SEG_A, SEG_ON );
      digitalWrite(SEG_B, SEG_ON );
      digitalWrite(SEG_C, SEG_ON );
      digitalWrite(SEG_D, SEG_ON );
      digitalWrite(SEG_E, SEG_OFF);
      digitalWrite(SEG_F, SEG_OFF);
      digitalWrite(SEG_G, SEG_ON );
      break;

    case 4:
      digitalWrite(SEG_A, SEG_OFF);
      digitalWrite(SEG_B, SEG_ON );
      digitalWrite(SEG_C, SEG_ON );
      digitalWrite(SEG_D, SEG_OFF);
      digitalWrite(SEG_E, SEG_OFF);
      digitalWrite(SEG_F, SEG_ON );
      digitalWrite(SEG_G, SEG_ON );
      break;

    case 5:
      digitalWrite(SEG_A, SEG_ON );
      digitalWrite(SEG_B, SEG_OFF);
      digitalWrite(SEG_C, SEG_ON );
      digitalWrite(SEG_D, SEG_ON );
      digitalWrite(SEG_E, SEG_OFF);
      digitalWrite(SEG_F, SEG_ON );
      digitalWrite(SEG_G, SEG_ON );
      break;

    case 6:
      digitalWrite(SEG_A, SEG_ON );
      digitalWrite(SEG_B, SEG_OFF);
      digitalWrite(SEG_C, SEG_ON );
      digitalWrite(SEG_D, SEG_ON );
      digitalWrite(SEG_E, SEG_ON );
      digitalWrite(SEG_F, SEG_ON );
      digitalWrite(SEG_G, SEG_ON );
      break;

    case 7:
      digitalWrite(SEG_A, SEG_ON );
      digitalWrite(SEG_B, SEG_ON );
      digitalWrite(SEG_C, SEG_ON );
      digitalWrite(SEG_D, SEG_OFF);
      digitalWrite(SEG_E, SEG_OFF);
      digitalWrite(SEG_F, SEG_OFF);
      digitalWrite(SEG_G, SEG_OFF);
      break;

    case 8:
      digitalWrite(SEG_A, SEG_ON );
      digitalWrite(SEG_B, SEG_ON );
      digitalWrite(SEG_C, SEG_ON );
      digitalWrite(SEG_D, SEG_ON );
      digitalWrite(SEG_E, SEG_ON );
      digitalWrite(SEG_F, SEG_ON );
      digitalWrite(SEG_G, SEG_ON );
      break;

    case 9:
      digitalWrite(SEG_A, SEG_ON );
      digitalWrite(SEG_B, SEG_ON );
      digitalWrite(SEG_C, SEG_ON );
      digitalWrite(SEG_D, SEG_ON );
      digitalWrite(SEG_E, SEG_OFF);
      digitalWrite(SEG_F, SEG_ON );
      digitalWrite(SEG_G, SEG_ON );
      break;

    case 10:
      digitalWrite(SEG_A, SEG_OFF);
      digitalWrite(SEG_B, SEG_OFF);
      digitalWrite(SEG_C, SEG_OFF);
      digitalWrite(SEG_D, SEG_OFF);
      digitalWrite(SEG_E, SEG_OFF);
      digitalWrite(SEG_F, SEG_OFF);
      digitalWrite(SEG_G, SEG_OFF);
      break;
  }
}
