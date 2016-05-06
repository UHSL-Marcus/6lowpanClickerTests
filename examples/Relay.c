/*
 * Project name:
     Relay
 * Copyright:
     (c) Mikroelektronika, 2011.
 * Revision History:
     20121212:
       - initial release (JK);
 * Description:
     This program demonstrates usage of Relay click board.
     Relay click has two Realys and user can control them with RB0, RB1, RB2 and RB3 buttons.
     Press RB0 and RB1 to toggle Relay1 and Relay2 state respectively.
     Hold RB2 and RB3 to turn on Relay1 and Relay2 respectively.
 * Test configuration:
     MCU:             PIC18F45K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41412F.pdf
     Dev.Board:       EasyPIC v7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS-PLL 32.0000 MHz, 8.0000 MHz Crystal
     Ext. Modules:    Relay click board : ac:Relay_click
                      http://www.mikroe.com/click/relay
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Place Relay click board into mikroBUS socket1.
     - Put button jumper (J17) into VCC position and pull-down PORTB0,1,2,3 (PORTB three state switch).
*/

sbit Relay1           at  LATC0_bit;
sbit Relay2           at  LATE0_bit;
sbit Relay1_Direction at TRISC0_bit;
sbit Relay2_Direction at TRISE0_bit;

char oldstate1, oldstate2;                        // Old state flag

void main() {

  ANSELB = 0;                                    // Configure PORTB pins as digital
  ANSELC = 0;                                    // Configure PORTC pins as digital
  ANSELE = 0;                                    // Configure PORTE pins as digital
  
  TRISB = 0x0F;                                  // set RB0, RB1, RB@ and RB3 pins as input
  
  Relay1_Direction = 0;                          // Set relay direction as output
  Relay2_Direction = 0;                          // Set relay direction as output
  Relay1 = 0;                                    // Turn off relay1
  Relay2 = 0;                                    // Turn off relay2
  
  oldstate1 = 0;
  oldstate2 = 0;
  
  do {
    // Relay1 toggle button
    if (Button(&PORTB, 0, 1, 1)) {               // Detect logical one
      oldstate1 = 1;                             // Update flag
    }
    if ((oldstate1 == 1) && Button(&PORTB, 0, 1, 0)) {  // Detect one-to-zero transition
      Relay1 = ~ Relay1;                         // Invert PORTC
      oldstate1 = 0;                             // Update flag
    }
    
    // Relay2 toggle button
    if (Button(&PORTB, 1, 1, 1)) {               // Detect logical one
      oldstate2 = 1;                             // Update flag
    }
    if ((oldstate2 == 1) && Button(&PORTB, 1, 1, 0)) {  // Detect one-to-zero transition
      Relay2 = ~ Relay2;                         // Invert PORTC
      oldstate2 = 0;                             // Update flag
    }
    
    // Relay1 hold button
    if (RB2_bit){                                // hold button to turn Relay1 on
      Relay1 = 1;                                // Turn on relay
      oldstate1 = 2;                             // set flag
    }
    else
      if (oldstate1 == 2)
        Relay1 = 0;                              // Turn off relay
        
    // Relay2 hold button
    if (RB3_bit){                                // hold button to turn Relay1 on
      Relay2 = 1;                                // Turn on relay
      oldstate2 = 2;                             // set flag
    }
    else
      if (oldstate2 == 2)
        Relay2 = 0;                              // Turn off relay
  } while(1);                                    // Endless loop
}