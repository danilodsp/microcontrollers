
_main:
	LDI        R27, 255
	OUT        SPL+0, R27
	LDI        R27, 0
	OUT        SPL+1, R27

;LED.c,5 :: 		void main() {
;LED.c,6 :: 		WDTCSR |= 0x40; // Desabilitando o WTD
	LDS        R27, WDTCSR+0
	SBR        R27, 64
	STS        WDTCSR+0, R27
;LED.c,7 :: 		CLKPR = 0x88;
	LDI        R27, 136
	STS        CLKPR+0, R27
;LED.c,8 :: 		DDRB = (1<<DDB0)|(1<<DDB1)|(1<<DDB2);  // IOs B como saída
	LDI        R27, 7
	OUT        DDRB+0, R27
;LED.c,9 :: 		DDRD = 0; // PORTD tudo entrada
	LDI        R27, 0
	OUT        DDRD+0, R27
;LED.c,10 :: 		SREG_I_bit = 1; // Habilita o GIE
	IN         R27, SREG_I_bit+0
	SBR        R27, 128
	OUT        SREG_I_bit+0, R27
;LED.c,12 :: 		estado = 1; // Inicia em estado 1
	LDI        R27, 1
	STS        _estado+0, R27
;LED.c,13 :: 		limite = 8; // limite de contagem
	LDI        R27, 8
	STS        _limite+0, R27
	LDI        R27, 0
	STS        _limite+1, R27
;LED.c,16 :: 		PCICR = 1<<PCIE2; // Habilitando interrupção do PORTD
	LDI        R27, 4
	STS        PCICR+0, R27
;LED.c,17 :: 		PCMSK2 = (1<<PCINT23)|(1<<PCINT22)|(1<<PCINT21); // Definindo pinos de interrupção PCINT23, 22 e 21
	LDI        R27, 224
	STS        PCMSK2+0, R27
;LED.c,20 :: 		TIMSK0 &= ~(1<<TOIE0); // Desabilitando o Timer interrupt enable
	LDS        R16, TIMSK0+0
	ANDI       R16, 254
	STS        TIMSK0+0, R16
;LED.c,21 :: 		TCCR0B = 0x05; // Prescaller 1024
	LDI        R27, 5
	OUT        TCCR0B+0, R27
;LED.c,22 :: 		while(1);
L_main0:
	JMP        L_main0
;LED.c,23 :: 		}
L_end_main:
	JMP        L_end_main
; end of _main

_interruptTimer:
	PUSH       R30
	PUSH       R31
	PUSH       R27
	IN         R27, SREG+0
	PUSH       R27

;LED.c,25 :: 		void interruptTimer() org IVT_ADDR_TIMER0_OVF {
;LED.c,26 :: 		if(count >= limite){
	LDS        R18, _count+0
	LDS        R19, _count+1
	LDS        R16, _limite+0
	LDS        R17, _limite+1
	CP         R18, R16
	CPC        R19, R17
	BRGE       L__interruptTimer22
	JMP        L_interruptTimer2
L__interruptTimer22:
;LED.c,27 :: 		PORTB0_bit = ~PORTB0_bit; // LED sendo alternado
	IN         R0, PORTB0_bit+0
	LDI        R27, 1
	EOR        R0, R27
	OUT        PORTB0_bit+0, R0
;LED.c,28 :: 		count = 0;  // Zerando contador
	LDI        R27, 0
	STS        _count+0, R27
	STS        _count+1, R27
;LED.c,29 :: 		}
	JMP        L_interruptTimer3
L_interruptTimer2:
;LED.c,31 :: 		count++;
	LDS        R16, _count+0
	LDS        R17, _count+1
	SUBI       R16, 255
	SBCI       R17, 255
	STS        _count+0, R16
	STS        _count+1, R17
;LED.c,32 :: 		}
L_interruptTimer3:
;LED.c,33 :: 		}
L_end_interruptTimer:
	POP        R27
	OUT        SREG+0, R27
	POP        R27
	POP        R31
	POP        R30
	RETI
; end of _interruptTimer

_interruptButton:
	PUSH       R30
	PUSH       R31
	PUSH       R27
	IN         R27, SREG+0
	PUSH       R27
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 2
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;LED.c,35 :: 		void interruptButton() org IVT_ADDR_PCINT2 {
;LED.c,36 :: 		int DEBOUNCE = 5;
	LDI        R27, 5
	STD        Y+0, R27
	LDI        R27, 0
	STD        Y+1, R27
;LED.c,38 :: 		do{
L_interruptButton4:
;LED.c,39 :: 		DEBOUNCE--;
	LDD        R16, Y+0
	LDD        R17, Y+1
	SUBI       R16, 1
	SBCI       R17, 0
	STD        Y+0, R16
	STD        Y+1, R17
;LED.c,40 :: 		}while((PIND5_bit|PIND6_bit|PIND7_bit)&&(DEBOUNCE>0));
	IN         R1, PIND5_bit+0
	IN         R0, PIND6_bit+0
	SBR        R20, 1
	SBRS       R1, 5
	SBRC       R0, 6
	RJMP       L__interruptButton29
	CBR        R20, 1
L__interruptButton29:
	IN         R0, PIND7_bit+0
	SET
	SBRS       R20, 0
	SBRC       R0, 7
	RJMP       L__interruptButton33
	CLT
L__interruptButton33:
	BLD        R20, 0
	SBRS       R20, 0
	JMP        L__interruptButton19
	LDD        R18, Y+0
	LDD        R19, Y+1
	LDI        R16, 0
	LDI        R17, 0
	CP         R16, R18
	CPC        R17, R19
	BRLT       L__interruptButton34
	JMP        L__interruptButton18
L__interruptButton34:
	JMP        L_interruptButton4
L__interruptButton19:
L__interruptButton18:
;LED.c,42 :: 		if(DEBOUNCE==0){
	LDD        R16, Y+0
	LDD        R17, Y+1
	CPI        R17, 0
	BRNE       L__interruptButton35
	CPI        R16, 0
L__interruptButton35:
	BREQ       L__interruptButton36
	JMP        L_interruptButton9
L__interruptButton36:
;LED.c,43 :: 		if(PIND5_bit == 1){
	IN         R27, PIND5_bit+0
	SBRS       R27, 5
	JMP        L_interruptButton10
;LED.c,44 :: 		if(estado!=3){
	LDS        R16, _estado+0
	CPI        R16, 3
	BRNE       L__interruptButton37
	JMP        L_interruptButton11
L__interruptButton37:
;LED.c,45 :: 		estado = 1;
	LDI        R27, 1
	STS        _estado+0, R27
;LED.c,46 :: 		TIMSK0 = 0;
	LDI        R27, 0
	STS        TIMSK0+0, R27
;LED.c,47 :: 		PORTB0_bit = 0;
	IN         R27, PORTB0_bit+0
	CBR        R27, 1
	OUT        PORTB0_bit+0, R27
;LED.c,48 :: 		PORTB1_bit = 1;
	IN         R27, PORTB1_bit+0
	SBR        R27, 2
	OUT        PORTB1_bit+0, R27
;LED.c,49 :: 		PORTB2_bit = 0;
	IN         R27, PORTB2_bit+0
	CBR        R27, 4
	OUT        PORTB2_bit+0, R27
;LED.c,50 :: 		}
L_interruptButton11:
;LED.c,51 :: 		}
	JMP        L_interruptButton12
L_interruptButton10:
;LED.c,52 :: 		else if(PIND6_bit == 1){
	IN         R27, PIND6_bit+0
	SBRS       R27, 6
	JMP        L_interruptButton13
;LED.c,53 :: 		estado = 2;
	LDI        R27, 2
	STS        _estado+0, R27
;LED.c,54 :: 		TIMSK0 = (1<<TOIE0);
	LDI        R27, 1
	STS        TIMSK0+0, R27
;LED.c,55 :: 		limite = 4;
	LDI        R27, 4
	STS        _limite+0, R27
	LDI        R27, 0
	STS        _limite+1, R27
;LED.c,56 :: 		PORTB1_bit = 0;
	IN         R27, PORTB1_bit+0
	CBR        R27, 2
	OUT        PORTB1_bit+0, R27
;LED.c,57 :: 		PORTB2_bit = 1;
	IN         R27, PORTB2_bit+0
	SBR        R27, 4
	OUT        PORTB2_bit+0, R27
;LED.c,58 :: 		}
	JMP        L_interruptButton14
L_interruptButton13:
;LED.c,59 :: 		else if(PIND7_bit == 1){
	IN         R27, PIND7_bit+0
	SBRS       R27, 7
	JMP        L_interruptButton15
;LED.c,60 :: 		if(estado!=1){
	LDS        R16, _estado+0
	CPI        R16, 1
	BRNE       L__interruptButton38
	JMP        L_interruptButton16
L__interruptButton38:
;LED.c,61 :: 		estado = 3;
	LDI        R27, 3
	STS        _estado+0, R27
;LED.c,62 :: 		TIMSK0 = (1<<TOIE0);
	LDI        R27, 1
	STS        TIMSK0+0, R27
;LED.c,63 :: 		limite = 1;
	LDI        R27, 1
	STS        _limite+0, R27
	LDI        R27, 0
	STS        _limite+1, R27
;LED.c,64 :: 		PORTB1_bit = 1;
	IN         R27, PORTB1_bit+0
	SBR        R27, 2
	OUT        PORTB1_bit+0, R27
;LED.c,65 :: 		PORTB2_bit = 1;
	IN         R27, PORTB2_bit+0
	SBR        R27, 4
	OUT        PORTB2_bit+0, R27
;LED.c,66 :: 		}
L_interruptButton16:
;LED.c,67 :: 		}}
L_interruptButton15:
L_interruptButton14:
L_interruptButton12:
L_interruptButton9:
;LED.c,68 :: 		PIND = 0;
	LDI        R27, 0
	OUT        PIND+0, R27
;LED.c,69 :: 		}
L_end_interruptButton:
	ADIW       R28, 1
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	POP        R27
	OUT        SREG+0, R27
	POP        R27
	POP        R31
	POP        R30
	RETI
; end of _interruptButton
