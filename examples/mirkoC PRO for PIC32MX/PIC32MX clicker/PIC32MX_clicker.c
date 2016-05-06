/*
 * Project name:
     PIC32MX clicker (Simple 'Hello World' project)
 * Copyright:
     (c) Mikroelektronika, 2015.
 * Revision History:
     20150202:
       - initial release (FJ);
 * Description:
     This is a simple 'Hello World' project. It turns on/off LEDs connected to
     RA0 and RA1 pins depending on pressed buttons. Left button T1 changes mode
     of blinking and right button changes frequency of blinking.
 * Test configuration:
     MCU:             P32MX534F064H
                      http://ww1.microchip.com/downloads/en/DeviceDoc/61156H.pdf
     Dev.Board:       PIC32MX clicker - ac:PIC32MX_clicker
                      http://www.mikroe.com/pic32mx/clicker/
     Oscillator:      XT-PLL, 80.000MHz
     Ext. Modules:    None.
     SW:              mikroC PRO for PIC32
                      http://www.mikroe.com/mikroc/pic32/
 */

// pin definitions
sbit LD1 at LATD4_bit;
sbit LD2 at LATD1_bit;
sbit LD1_Direction at TRISD4_bit;
sbit LD2_Direction at TRISD1_bit;

sbit T1 at RB4_bit;
sbit T2 at RB0_bit;
sbit T1_Direction at TRISB4_bit;
sbit T2_Direction at TRISB0_bit;

// globals
char oldstate1 = 0, oldstate2 = 0;
char Example_State = 0;
char count;

//Timer2/3
//Prescaler 1:1; PR3 Preload = 610; PR2 Preload = 23650; Actual Interrupt Time = 500 ms
void InitTimer2_3() {
  T2CON         = 0x0;
  T3CON         = 0x0;
  TMR2          = 0;
  TMR3          = 0;
  T3IE_bit      = 1;
  T3IF_bit      = 0;
  T3IP0_bit     = 1;
  T3IP1_bit     = 1;
  T3IP2_bit     = 1;
  PR3           = 610;
  PR2           = 23650;
  T2CON         = 0x8008;
}

void Timer2_3Interrupt() iv IVT_TIMER_3 ilevel 7 ics ICS_SRS {
  char temp;

  // clear Timer Interrupt flag
  T3IF_bit = 0;
  T2CON = 0x0;
  T3CON = 0x0;

  // check T1 button state
  switch (Example_State & 0x0F){
    case 0 : LD1 = 0;                   // Both LEDs are OF
             LD2 = 0;
             break;
    
    case 1 : LD1 ^= 1;                  // Only LD1 blinks
             LD2 = 0;
             break;
    
    case 2 : LD1 = 0;                   // Only LD2 blinks
             LD2 ^= 1;
             break;
    
    case 3 : LD1 ^= 1;                  // Both LEDs blinks alternately
             LD2  = !LD1;
             break;
    
    case 4 : LD1 ^= 1;                  // Both LEDs blink simultaneously
             LD2  = LD1;             
             break;
    
    default : Example_State &= 0xF0;    // reset T1 state to zero
              break;
  }
  // check T2 button state
  switch (Example_State & 0xF0){
    case 0x00 : PR3 = 610;              // Set Timer Interrupt time to 500ms
                PR2 = 23650;
                break;
    
    case 0x10 : PR3 = 488;              // Set Timer Interrupt time to 400ms
                PR2 = 18920;
                break;
    
    case 0x20 : PR3 = 366;              // Set Timer Interrupt time to 300ms
                PR2 = 14190;
                break;
    
    case 0x30 : PR3 = 244;              // Set Timer Interrupt time to 200ms
                PR2 = 9460;
                break;
    
    case 0x40 : PR3 = 122;              // Set Timer Interrupt time to 100ms
                PR2 = 4730;
                break;
    
    default :   PR3 = 610;              // Set Timer Interrupt time to 500ms
                PR2 = 23650;
                Example_State &= 0x0F;  // reset T1 state to zero
                break;
  }
  T2CON = 0x8008;
}

// main function
void main() {
  AD1PCFG = 0xFFFF;
  JTAGEN_bit = 0;
  
  T1_Direction = 1;         // Set direction for buttons
  T2_Direction = 1;
  
  LD1_Direction = 0;        // Set direction for LEDS
  LD2_Direction = 0;
  LD1 = 0;                  // turn off leds
  LD2 = 0;
  Example_State = 0;        // set default Example state

  InitTimer2_3();           // initialize Timer
  
  EnableInterrupts();       // Enable all interrupts

  while(1){                 // Endless loop
    // check T1 button
    if (Button(&PORTB, 4, 2, 0)) {                // Detect logical zero
      oldstate1 = 1;                              // Update flag
    }
    if (oldstate1 && Button(&PORTB, 4, 2, 1)) {   // Detect zero-to-one transition
      oldstate1 = 0;                              // Update flag
      Example_State += 0x01;                      // set new Example state
      if ((Example_State & 0x0F) > 4)
        Example_State &= 0xF0;
    }
    // check T2 button
    if (Button(&PORTB, 0, 2, 0)) {                // Detect logical zero
      oldstate2 = 1;                              // Update flag
    }
    if (oldstate2 && Button(&PORTB, 0, 2, 1)) {   // Detect zero-to-one transition
      oldstate2 = 0;                              // Update flag
      Example_State += 0x10;                      // set new Example state
      if ((Example_State & 0xF0) > 0x40)
        Example_State &= 0x0F;
    }
  }
}