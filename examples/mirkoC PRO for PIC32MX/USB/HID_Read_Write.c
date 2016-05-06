/* 
 * Project name:
     HID_Read_Write (USB HID Read & Write Test)
 * Copyright:
     (c) Mikroelektronika, 2015.
 * Revision History:
     20150202:
       - initial release (FJ);
 * Description:
     This example establishes connection with the HID terminal that is active
     on the PC. Upon connection establishment, the HID Device Name will appear
     in the respective window. The character that user sends to PIC from the HID
     terminal will be re-sent back to user.
 * Test configuration:
     MCU:             P32MX534F064H
                      http://ww1.microchip.com/downloads/en/DeviceDoc/61156H.pdf
     Dev.Board:       PIC32MX clicker - ac:PIC32MX_clicker
                      http://www.mikroe.com/pic32mx/clicker/
     Oscillator:      XT-PLL, 80.000MHz
     Ext. Modules:    None.
     SW:              mikroC PRO for PIC32
                      http://www.mikroe.com/mikroc/pic32/
 * NOTES:  
     - None.
 */

char cnt;
char readbuff[64];
char writebuff[64];

void USB1Interrupt() iv IVT_USB_1 ilevel 7 ics ICS_SRS{
  USB_Interrupt_Proc();
}

void main(void){
  AD1PCFG = 0xFFFF;                        // Configure AN pins as digital I/O        

  USBIE_bit = 0;
  IPC11bits.USBIP = 7;
  EnableInterrupts();

  HID_Enable(&readbuff,&writebuff);

  while(1){
    while(!HID_Read())
      ;

    for(cnt=0;cnt<64;cnt++)
      writebuff[cnt]=readbuff[cnt];

    while(!HID_Write(&writebuff,64))
      ;
  }
}