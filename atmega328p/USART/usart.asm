
_main:
	LDI        R27, 255
	OUT        SPL+0, R27
	LDI        R27, 0
	OUT        SPL+1, R27

;usart.c,3 :: 		void main() {
;usart.c,4 :: 		WDTCSR |= 0x40; // Desabilitando o WTD
	LDS        R27, WDTCSR+0
	SBR        R27, 64
	STS        WDTCSR+0, R27
;usart.c,5 :: 		DDRB = (1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3);  // IOs B como saída
	LDI        R27, 15
	OUT        DDRB+0, R27
;usart.c,6 :: 		SREG_I_bit = 1; // Habilita o GIE
	IN         R27, SREG_I_bit+0
	SBR        R27, 128
	OUT        SREG_I_bit+0, R27
;usart.c,8 :: 		estado = 0;  // Estado inicial
	LDI        R27, 0
	STS        _estado+0, R27
	STS        _estado+1, R27
;usart.c,11 :: 		PCICR = 1<<PCIE2; // Habilitando interrupção do PORTD
	LDI        R27, 4
	STS        PCICR+0, R27
;usart.c,12 :: 		PCMSK2 = (1<<PCINT23)|(1<<PCINT22); // Definindo pinos de interrupção PCINT23, 22 e 21
	LDI        R27, 192
	STS        PCMSK2+0, R27
;usart.c,15 :: 		UART1_Init(9600); // Inicializando a UART
	LDI        R27, 51
	STS        UBRR0L+0, R27
	LDI        R27, 0
	STS        UBRR0H+0, R27
	CALL       _UART1_Init+0
;usart.c,18 :: 		while(1);
L_main0:
	JMP        L_main0
;usart.c,19 :: 		}
L_end_main:
	JMP        L_end_main
; end of _main

_interrupt_rx:
	PUSH       R30
	PUSH       R31
	PUSH       R27
	IN         R27, SREG+0
	PUSH       R27

;usart.c,21 :: 		void interrupt_rx() org IVT_ADDR_USART__RX{
;usart.c,22 :: 		estado = UART1_Read();
	CALL       _UART1_Read+0
	STS        _estado+0, R16
	LDI        R27, 0
	STS        _estado+1, R27
;usart.c,23 :: 		PORTB  = estado;
	LDS        R16, _estado+0
	OUT        PORTB+0, R16
;usart.c,24 :: 		}
L_end_interrupt_rx:
	POP        R27
	OUT        SREG+0, R27
	POP        R27
	POP        R31
	POP        R30
	RETI
; end of _interrupt_rx

_interruptButton:
	PUSH       R30
	PUSH       R31
	PUSH       R27
	IN         R27, SREG+0
	PUSH       R27

;usart.c,26 :: 		void interruptButton() org IVT_ADDR_PCINT2{
;usart.c,27 :: 		if(PIND6_bit == 1){
	PUSH       R2
	IN         R27, PIND6_bit+0
	SBRS       R27, 6
	JMP        L_interruptButton2
;usart.c,28 :: 		estado++;
	LDS        R16, _estado+0
	LDS        R17, _estado+1
	MOVW       R18, R16
	SUBI       R18, 255
	SBCI       R19, 255
	STS        _estado+0, R18
	STS        _estado+1, R19
;usart.c,29 :: 		if(estado>15){
	LDI        R16, 15
	LDI        R17, 0
	CP         R16, R18
	CPC        R17, R19
	BRLT       L__interruptButton8
	JMP        L_interruptButton3
L__interruptButton8:
;usart.c,30 :: 		estado=0;
	LDI        R27, 0
	STS        _estado+0, R27
	STS        _estado+1, R27
;usart.c,31 :: 		}
L_interruptButton3:
;usart.c,32 :: 		PORTB = estado;
	LDS        R16, _estado+0
	OUT        PORTB+0, R16
;usart.c,33 :: 		}
L_interruptButton2:
;usart.c,34 :: 		if(PIND7_bit == 1){
	IN         R27, PIND7_bit+0
	SBRS       R27, 7
	JMP        L_interruptButton4
;usart.c,35 :: 		UART1_Write(estado);
	LDS        R2, _estado+0
	CALL       _UART1_Write+0
;usart.c,36 :: 		}
L_interruptButton4:
;usart.c,37 :: 		PIND = 0;
	LDI        R27, 0
	OUT        PIND+0, R27
;usart.c,38 :: 		}
L_end_interruptButton:
	POP        R2
	POP        R27
	OUT        SREG+0, R27
	POP        R27
	POP        R31
	POP        R30
	RETI
; end of _interruptButton
