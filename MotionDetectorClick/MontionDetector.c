
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

  ANSELB = 0;                   // set PORTB to digital
  ANSELD = 0;                   // set PORTD to digital
  LED1_dir = 0;                 // set LED1 and 2 to output
  LED2_dir = 0;
  toggleBtn_dir = 1;            // Set Button (T2) to input
  motionOut_dir = 1;            // Set motion detection input pin to input
  motionEnable_dir = 0;         // set motion detection enable pin to output


  // Turn OFF LED1 and LED2
  LED1 = 0;
  LED2 = 0;
  
  motionEnable = 0;             // disable motion detection
  toggleBtn_Oldstate = 0;       // default Button state to unpressed
  
  while(1)
  {
    //Button press
    if (Button(&PORTB, 0, 1, 1)) {
       toggleBtn_Oldstate = 1;
    }
    if (toggleBtn_Oldstate && Button(&PORTB, 0, 1, 0)) { // detect a 1 to 0 transition
       toggleBtn_Oldstate = 0;
       motionEnable = ~motionEnable;
       //LED1 = ~LED1;
    }

  
    // Motion detection
    if (motionEnable) LED1 = 1;// when enabled, turn on LED1
    else LED1 = 0;
    
    if(motionEnable && motionOut) LED2 = 1;  // read RD0, the motion click sets this to 1 when motion is detected
    else LED2 = 0;
  }

}