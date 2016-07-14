
// Interrupt calc:
// 1/((8×10^7)/256/65535) seconds  = 0.2 seconds
// 1/(clock speed hz / prescalar / timer size)
// Note: pic32x has 1:1 between clock speed and instruction speed

sbit LED1 at LATB1_bit;
sbit LED2 at LATB2_bit;
int count = 0;
void timer1_interrupt() iv IVT_TIMER_1 ilevel 7 ics ICS_OFF
{
 //remove timer 1 inturrpt flag off
 T1IF_bit = 0;
 
 count++;
 if (count > 5) {   // slowest the timer can call an interupt is every 0.2 seconds
    LED1 = ~LED1;   // So count to 5 to make the LED flash every second
    count = 0;
 }
}

void main() 
{
  //set PORTB to digital
  ANSELB = 0;
  // set PORTB to be digital output
  TRISB = 0;
  // Turn OFF LED 1 and turn on LED2
  LED1 = 0;
  LED2 = 1;
  
  ANSELBSETbits;
  

  

  T1CON = 0;  // set timer1 settings register to 0
  TMR1 = 0;   // set timer1 count to 0
  PR1 = 0xFFFF;  // set the period register to to the full 16-bits
  
  T1CONbits.TCKPS0 = 1; // set timer prescalar
  T1CONbits.TCKPS1 = 1; // uses 2 bits, 11 = 256 prescalar
  SPI2STATbits.SPIRBF

  T1IP0_bit = 1; // set the timer interrupt priority to 7
  T1IP1_bit = 1; // takes 3 bits
  T1IP2_bit = 1; // b111 = 7
  
  EnableInterrupts();  // make sure interrupts are enabled
  T1IF_bit = 0;        // set the timer 1 interrupt flag to 0
  T1IE_bit = 1;        // set the timer 1 interrupt enabled flag to 1
  
  T1CONbits.ON = 1;    // turn the timer on
  
}