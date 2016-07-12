#line 1 "C:/Users/ML15AAF/Documents/GitHub/6lowpanClickerTests/LEDtest/LEDtest.c"






sbit LED1 at LATB1_bit;
sbit LED2 at LATB2_bit;
int count = 0;
void timer1_interrupt() iv IVT_TIMER_1 ilevel 7 ics ICS_OFF
{

 T1IF_bit = 0;

 count++;
 if (count > 5) {
 LED1 = ~LED1;
 count = 0;
 }
}

void main()
{

 ANSELB = 0;

 TRISB = 0;

 LED1 = 0;
 LED2 = 1;


 T1CON = 0;
 TMR1 = 0;
 PR1 = 0xFFFF;

 T1CONbits.TCKPS0 = 1;
 T1CONbits.TCKPS1 = 1;

 T1IP0_bit = 1;
 T1IP1_bit = 1;
 T1IP2_bit = 1;

 EnableInterrupts();
 T1IF_bit = 0;
 T1IE_bit = 1;

 T1CONbits.ON = 1;

}
