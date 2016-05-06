_timer1_interrupt:
;LEDtest.c,5 :: 		void timer1_interrupt() iv IVT_TIMER_1 ilevel 7 ics ICS_OFF
;LEDtest.c,8 :: 		T1IF_bit = 0;
LUI	R2, BitMask(T1IF_bit+0)
ORI	R2, R2, BitMask(T1IF_bit+0)
_SX	
;LEDtest.c,10 :: 		count++;
LH	R2, Offset(_count+0)(GP)
ADDIU	R2, R2, 1
SH	R2, Offset(_count+0)(GP)
;LEDtest.c,11 :: 		if (count > 5) {
SEH	R2, R2
SLTI	R2, R2, 6
BEQ	R2, R0, L__timer1_interrupt2
NOP	
J	L_timer1_interrupt0
NOP	
L__timer1_interrupt2:
;LEDtest.c,12 :: 		LED1 = ~LED1;
_LX	
EXT	R2, R2, BitPos(LATB1_bit+0), 1
XORI	R3, R2, 1
_LX	
INS	R2, R3, BitPos(LATB1_bit+0), 1
_SX	
;LEDtest.c,13 :: 		count = 0;
SH	R0, Offset(_count+0)(GP)
;LEDtest.c,14 :: 		}
L_timer1_interrupt0:
;LEDtest.c,15 :: 		}
L_end_timer1_interrupt:
ERET	
; end of _timer1_interrupt
_main:
;LEDtest.c,17 :: 		void main()
;LEDtest.c,20 :: 		ANSELB = 0;
SW	R0, Offset(ANSELB+0)(GP)
;LEDtest.c,22 :: 		TRISB = 0;
SW	R0, Offset(TRISB+0)(GP)
;LEDtest.c,24 :: 		LED1 = 0;
LUI	R2, BitMask(LATB1_bit+0)
ORI	R2, R2, BitMask(LATB1_bit+0)
_SX	
;LEDtest.c,25 :: 		LED2 = 1;
LUI	R2, BitMask(LATB2_bit+0)
ORI	R2, R2, BitMask(LATB2_bit+0)
_SX	
;LEDtest.c,27 :: 		T1CON = 0;
SW	R0, Offset(T1CON+0)(GP)
;LEDtest.c,28 :: 		TMR1 = 0;
SW	R0, Offset(TMR1+0)(GP)
;LEDtest.c,29 :: 		PR1 = 0xFFFF;
ORI	R2, R0, 65535
SW	R2, Offset(PR1+0)(GP)
;LEDtest.c,31 :: 		T1IP0_bit = 1;
LUI	R2, BitMask(T1IP0_bit+0)
ORI	R2, R2, BitMask(T1IP0_bit+0)
_SX	
;LEDtest.c,32 :: 		T1IP1_bit = 1;
LUI	R2, BitMask(T1IP1_bit+0)
ORI	R2, R2, BitMask(T1IP1_bit+0)
_SX	
;LEDtest.c,33 :: 		T1IP2_bit = 1;
LUI	R2, BitMask(T1IP2_bit+0)
ORI	R2, R2, BitMask(T1IP2_bit+0)
_SX	
;LEDtest.c,35 :: 		T1CONbits.TCKPS0 = 1;
ORI	R2, R0, 16
SW	R2, Offset(T1CONbits+8)(GP)
;LEDtest.c,36 :: 		T1CONbits.TCKPS1 = 1;
ORI	R2, R0, 32
SW	R2, Offset(T1CONbits+8)(GP)
;LEDtest.c,38 :: 		EnableInterrupts();
EI	R30
;LEDtest.c,39 :: 		T1IF_bit = 0;
LUI	R2, BitMask(T1IF_bit+0)
ORI	R2, R2, BitMask(T1IF_bit+0)
_SX	
;LEDtest.c,40 :: 		T1IE_bit = 1;
LUI	R2, BitMask(T1IE_bit+0)
ORI	R2, R2, BitMask(T1IE_bit+0)
_SX	
;LEDtest.c,42 :: 		T1CONbits.ON = 1;
ORI	R2, R0, 32768
SW	R2, Offset(T1CONbits+8)(GP)
;LEDtest.c,44 :: 		}
L_end_main:
L__main_end_loop:
J	L__main_end_loop
NOP	
; end of _main
