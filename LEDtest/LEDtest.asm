_timer1_interrupt:
;LEDtest.c,10 :: 		void timer1_interrupt() iv IVT_TIMER_1 ilevel 7 ics ICS_OFF
;LEDtest.c,13 :: 		T1IF_bit = 0;
LUI	R2, BitMask(T1IF_bit+0)
ORI	R2, R2, BitMask(T1IF_bit+0)
_SX	
;LEDtest.c,15 :: 		count++;
LH	R2, Offset(_count+0)(GP)
ADDIU	R2, R2, 1
SH	R2, Offset(_count+0)(GP)
;LEDtest.c,16 :: 		if (count > 5) {   // slowest the timer can call an interupt is every 0.2 seconds
SEH	R2, R2
SLTI	R2, R2, 6
BEQ	R2, R0, L__timer1_interrupt2
NOP	
J	L_timer1_interrupt0
NOP	
L__timer1_interrupt2:
;LEDtest.c,17 :: 		LED1 = ~LED1;   // So count to 5 to make the LED flash every second
_LX	
EXT	R2, R2, BitPos(LATB1_bit+0), 1
XORI	R3, R2, 1
_LX	
INS	R2, R3, BitPos(LATB1_bit+0), 1
_SX	
;LEDtest.c,18 :: 		count = 0;
SH	R0, Offset(_count+0)(GP)
;LEDtest.c,19 :: 		}
L_timer1_interrupt0:
;LEDtest.c,20 :: 		}
L_end_timer1_interrupt:
ERET	
; end of _timer1_interrupt
_main:
;LEDtest.c,22 :: 		void main()
;LEDtest.c,25 :: 		ANSELB = 0;
SW	R0, Offset(ANSELB+0)(GP)
;LEDtest.c,27 :: 		TRISB = 0;
SW	R0, Offset(TRISB+0)(GP)
;LEDtest.c,29 :: 		LED1 = 0;
LUI	R2, BitMask(LATB1_bit+0)
ORI	R2, R2, BitMask(LATB1_bit+0)
_SX	
;LEDtest.c,30 :: 		LED2 = 1;
LUI	R2, BitMask(LATB2_bit+0)
ORI	R2, R2, BitMask(LATB2_bit+0)
_SX	
;LEDtest.c,33 :: 		T1CON = 0;  // set timer1 settings register to 0
SW	R0, Offset(T1CON+0)(GP)
;LEDtest.c,34 :: 		TMR1 = 0;   // set timer1 count to 0
SW	R0, Offset(TMR1+0)(GP)
;LEDtest.c,35 :: 		PR1 = 0xFFFF;  // set the period register to to the full 16-bits
ORI	R2, R0, 65535
SW	R2, Offset(PR1+0)(GP)
;LEDtest.c,37 :: 		T1CONbits.TCKPS0 = 1; // set timer prescalar
ORI	R2, R0, 16
SW	R2, Offset(T1CONbits+8)(GP)
;LEDtest.c,38 :: 		T1CONbits.TCKPS1 = 1; // uses 2 bits, 11 = 256 prescalar
ORI	R2, R0, 32
SW	R2, Offset(T1CONbits+8)(GP)
;LEDtest.c,40 :: 		T1IP0_bit = 1; // set the timer interrupt priority to 7
LUI	R2, BitMask(T1IP0_bit+0)
ORI	R2, R2, BitMask(T1IP0_bit+0)
_SX	
;LEDtest.c,41 :: 		T1IP1_bit = 1; // takes 3 bits
LUI	R2, BitMask(T1IP1_bit+0)
ORI	R2, R2, BitMask(T1IP1_bit+0)
_SX	
;LEDtest.c,42 :: 		T1IP2_bit = 1; // b111 = 7
LUI	R2, BitMask(T1IP2_bit+0)
ORI	R2, R2, BitMask(T1IP2_bit+0)
_SX	
;LEDtest.c,44 :: 		EnableInterrupts();  // make sure interrupts are enabled
EI	R30
;LEDtest.c,45 :: 		T1IF_bit = 0;        // set the timer 1 interrupt flag to 0
LUI	R2, BitMask(T1IF_bit+0)
ORI	R2, R2, BitMask(T1IF_bit+0)
_SX	
;LEDtest.c,46 :: 		T1IE_bit = 1;        // set the timer 1 interrupt enabled flag to 1
LUI	R2, BitMask(T1IE_bit+0)
ORI	R2, R2, BitMask(T1IE_bit+0)
_SX	
;LEDtest.c,48 :: 		T1CONbits.ON = 1;    // turn the timer on
ORI	R2, R0, 32768
SW	R2, Offset(T1CONbits+8)(GP)
;LEDtest.c,50 :: 		}
L_end_main:
L__main_end_loop:
J	L__main_end_loop
NOP	
; end of _main
