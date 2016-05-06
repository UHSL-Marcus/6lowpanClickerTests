#line 1 "C:/Users/ML15AAF/Documents/GitHub/ClickerTest/MotionDetectorClick/MontionDetector.c"

sbit LED1 at LATB1_bit;
sbit LED2 at LATB2_bit;
sbit toggleBtn at RB0_bit;
sbit motionOut at RD0_bit;
sbit motionEnable at LATD6_bit;

sbit LED1_dir at TRISB1_bit;
sbit LED2_dir at TRISB2_bit;
sbit toggleBtn_dir at TRISB0_bit;
sbit motionOut_dir at TRISD0_bit;
sbit motionEnable_dir at TRISD6_bit;

char toggleBtn_Oldstate;

void main()
{

 ANSELB = 0;
 ANSELD = 0;
 LED1_dir = 0;
 LED2_dir = 0;
 toggleBtn_dir = 1;
 motionOut_dir = 1;
 motionEnable_dir = 0;



 LED1 = 0;
 LED2 = 0;

 motionEnable = 0;
 toggleBtn_Oldstate = 0;

 while(1)
 {

 if (Button(&PORTB, 0, 1, 1)) {
 toggleBtn_Oldstate = 1;
 }
 if (toggleBtn_Oldstate && Button(&PORTB, 0, 1, 0)) {
 toggleBtn_Oldstate = 0;
 motionEnable = ~motionEnable;

 }



 if (motionEnable) LED1 = 1;
 else LED1 = 0;

 if(motionEnable && motionOut) LED2 = 1;
 else LED2 = 0;
 }

}
