_main:
;MontionDetector.c,16 :: 		void main()
;MontionDetector.c,19 :: 		ANSELB = 0;                   // set PORTB to digital
SW	R0, Offset(ANSELB+0)(GP)
;MontionDetector.c,20 :: 		ANSELD = 0;                   // set PORTD to digital
SW	R0, Offset(ANSELD+0)(GP)
;MontionDetector.c,21 :: 		LED1_dir = 0;                 // set LED1 and 2 to output
LUI	R2, BitMask(TRISB1_bit+0)
ORI	R2, R2, BitMask(TRISB1_bit+0)
_SX	
;MontionDetector.c,22 :: 		LED2_dir = 0;
LUI	R2, BitMask(TRISB2_bit+0)
ORI	R2, R2, BitMask(TRISB2_bit+0)
_SX	
;MontionDetector.c,23 :: 		toggleBtn_dir = 1;            // Set Button (T2) to input
LUI	R2, BitMask(TRISB0_bit+0)
ORI	R2, R2, BitMask(TRISB0_bit+0)
_SX	
;MontionDetector.c,24 :: 		motionOut_dir = 1;            // Set motion detection input pin to input
LUI	R2, BitMask(TRISD0_bit+0)
ORI	R2, R2, BitMask(TRISD0_bit+0)
_SX	
;MontionDetector.c,25 :: 		motionEnable_dir = 0;         // set motion detection enable pin to output
LUI	R2, BitMask(TRISD6_bit+0)
ORI	R2, R2, BitMask(TRISD6_bit+0)
_SX	
;MontionDetector.c,29 :: 		LED1 = 0;
LUI	R2, BitMask(LATB1_bit+0)
ORI	R2, R2, BitMask(LATB1_bit+0)
_SX	
;MontionDetector.c,30 :: 		LED2 = 0;
LUI	R2, BitMask(LATB2_bit+0)
ORI	R2, R2, BitMask(LATB2_bit+0)
_SX	
;MontionDetector.c,32 :: 		motionEnable = 0;             // disable motion detection
LUI	R2, BitMask(LATD6_bit+0)
ORI	R2, R2, BitMask(LATD6_bit+0)
_SX	
;MontionDetector.c,33 :: 		toggleBtn_Oldstate = 0;           // default Button state to unpressed
SB	R0, Offset(_toggleBtn_Oldstate+0)(GP)
;MontionDetector.c,35 :: 		while(1)
L_main0:
;MontionDetector.c,38 :: 		if (Button(&PORTB, 0, 1, 1)) {
ORI	R28, R0, 1
ORI	R27, R0, 1
MOVZ	R26, R0, R0
LUI	R25, hi_addr(PORTB+0)
ORI	R25, R25, lo_addr(PORTB+0)
JAL	_Button+0
NOP	
BNE	R2, R0, L__main20
NOP	
J	L_main2
NOP	
L__main20:
;MontionDetector.c,39 :: 		toggleBtn_Oldstate = 1;
ORI	R2, R0, 1
SB	R2, Offset(_toggleBtn_Oldstate+0)(GP)
;MontionDetector.c,40 :: 		}
L_main2:
;MontionDetector.c,41 :: 		if (toggleBtn_Oldstate && Button(&PORTB, 0, 1, 0)) { // detect a 1 to 0 transition
LBU	R2, Offset(_toggleBtn_Oldstate+0)(GP)
BNE	R2, R0, L__main22
NOP	
J	L__main15
NOP	
L__main22:
MOVZ	R28, R0, R0
ORI	R27, R0, 1
MOVZ	R26, R0, R0
LUI	R25, hi_addr(PORTB+0)
ORI	R25, R25, lo_addr(PORTB+0)
JAL	_Button+0
NOP	
BNE	R2, R0, L__main24
NOP	
J	L__main14
NOP	
L__main24:
L__main13:
;MontionDetector.c,42 :: 		toggleBtn_Oldstate = 0;
SB	R0, Offset(_toggleBtn_Oldstate+0)(GP)
;MontionDetector.c,43 :: 		motionEnable = ~motionEnable;
_LX	
EXT	R2, R2, BitPos(LATD6_bit+0), 1
XORI	R3, R2, 1
_LX	
INS	R2, R3, BitPos(LATD6_bit+0), 1
_SX	
;MontionDetector.c,41 :: 		if (toggleBtn_Oldstate && Button(&PORTB, 0, 1, 0)) { // detect a 1 to 0 transition
L__main15:
L__main14:
;MontionDetector.c,49 :: 		if (motionEnable) LED1 = 1;// when enabled, turn on LED1
_LX	
EXT	R2, R2, BitPos(LATD6_bit+0), 1
BNE	R2, R0, L__main26
NOP	
J	L_main6
NOP	
L__main26:
LUI	R2, BitMask(LATB1_bit+0)
ORI	R2, R2, BitMask(LATB1_bit+0)
_SX	
J	L_main7
NOP	
L_main6:
;MontionDetector.c,50 :: 		else LED1 = 0;
LUI	R2, BitMask(LATB1_bit+0)
ORI	R2, R2, BitMask(LATB1_bit+0)
_SX	
L_main7:
;MontionDetector.c,52 :: 		if(motionEnable && motionOut) LED2 = 1;  // read RD0, the motion click sets this to 1 when motion is detected
_LX	
EXT	R2, R2, BitPos(LATD6_bit+0), 1
BNE	R2, R0, L__main28
NOP	
J	L__main17
NOP	
L__main28:
_LX	
EXT	R2, R2, BitPos(RD0_bit+0), 1
BNE	R2, R0, L__main30
NOP	
J	L__main16
NOP	
L__main30:
L__main12:
LUI	R2, BitMask(LATB2_bit+0)
ORI	R2, R2, BitMask(LATB2_bit+0)
_SX	
J	L_main11
NOP	
L__main17:
L__main16:
;MontionDetector.c,53 :: 		else LED2 = 0;
LUI	R2, BitMask(LATB2_bit+0)
ORI	R2, R2, BitMask(LATB2_bit+0)
_SX	
L_main11:
;MontionDetector.c,54 :: 		}
J	L_main0
NOP	
;MontionDetector.c,56 :: 		}
L_end_main:
L__main_end_loop:
J	L__main_end_loop
NOP	
; end of _main
