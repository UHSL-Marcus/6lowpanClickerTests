/*
 * Project name:
       Motion Click
 * Copyright:
      (c) mikroElektronika, 2014.
 * Revision History:
      20140826:
      - Initial release (RD);
 * Description:
      Motion click is a simple solution for adding an infrared motion detector—sensitive only to live bodies—to your design. 
      It carries a D203B Pyroelectric motion sensor connected to a BISS0001 infrared sensor controller IC. 
      Onboard potentiometer enables you to calibrate the sensor for distance. 
      The board also features a photo resistor that enables you to set the sensor to work only at night. 
      Motion click communicates with the target board through mikroBUS IN (out) and RST lines.

      Motion click is ideal for alarm systems, light switch controllers, and similar systems where human presence needs to be detected.
      The pyroelectric motion sensor generates a voltage when exposed to infrared radiation emitted by live bodies 
      (the white plastic Flesner lens covering the sensor filters visible light). 
      The BISS001 IC processes the signal and sends an interrupt to the MCU. 
      To set up the detecting range of the sensor (up to 4 meters), use the onboard potentiometer. 
      You can also activate and deactivate the sensor through the mikroBUS™ RST pin.

      You can set up motion click to be operational only in darkness by activating the onboard Photo resistor. 
      All you have to do is resolder the zero-ohm jumper just below the photo resistor on the left side of the click board.
      
      Motion click is a motion detector sensitive only to live bodies. 
      It carries D203B, a pyroelectric sensor which generates a voltage when exposed to infrared light. 
      The signal is processed by a BIS0001 PIR sensor controller which sends an interrupt to the MCU through 
      the mikroBUS IN (out) line. An onboard potentiometer lets you adjust the detecting range of the sensor. 
      Motion click also has a night only mode—resoldering a zero-ohm jumper activates the onboard photo resistor which acts 
      as a light-sensitive switch. You can also switch the sensor ON and OFF by sending a signal from the MCU through 
      the mikroBUS RST pin.
      
      It uses a 3.3V power supply!

 * Test configuration:
     MCU:             PIC18F45K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41412F.pdf
     Dev. Board:      EasyPIC v7 Connectivity
                      http://www.mikroe.com/easypic/
     Oscillator:      HS-PLL, 8MHz Crystal, 32MHz MCU Clock
     ext. modules:    Motion Click
                      http://www.mikroe.com/click/motion/
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
      - Place Motion Click board in the mikroBUS socket 1.
      - Set development board J5 jumper according to 3.3V position!
      - Turn On SW3-2 switch for PORTB LEDs.
*/


void Tone1() {
  Sound_Play(659, 250);        // Frequency = 659Hz, duration = 250ms
}

void Tone2() {
  Sound_Play(698, 250);        // Frequency = 698Hz, duration = 250ms
}

void Tone3() {
  Sound_Play(784, 250);        // Frequency = 784Hz, duration = 250ms
}

void main() {
   ANSELB = 0;                 // Configure PortB pins as digital
   ANSELC = 0;                 // Configure PortD pins as digital
   ANSELE = 0;                 // Configure PortE pins as digital
   TRISB = 0x01;               // Configure RB0 as output
   TRISC = 0;                  // Set PortC as output
   LATB = 0x00;                // Reset PortB

   Sound_Init(&PORTC, 2);      // Initialization of sound port
   
   PORTE.B1 = 1;               // Enable Motion sensor

   while(1){
      if (PORTB.B0){           // If sensor is activated
         Tone1();              // Play tone
      }
   }
}