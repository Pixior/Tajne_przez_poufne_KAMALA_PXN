#include "derivative.h"
#include "uart.h"


/**************************
 * Defines
 **************************/
#define UARTX UART0
#if UARTX == UART0
	#define UARTX_CLOCK_EN_FLAG (SIM_SCGC4_UART0_MASK)
	#define UARTX_BDL (UART0_BDL)
	#define UARTX_BDH (UART0_BDH)
	#define UARTX_C2 (UART0_C2)
	#define UARTX_S1 (UART0_S1)
	#define UARTX_D (UART0_D)
	#define INT_UARTX (INT_UART0)
	#define UARTX_IRQHandler UART0_IRQHandler
#endif

#define BIT(x)	(1 << (x))
//#define TIMER_STATUS	BIT(22)	example
#define UART2_C2_TIE_MASK	0x80
#define UART2_C2_RIE_MASK	0x20
#define UART2_S1_TDRE_MASK	0x80
#define UART2_S1_RDRF_MASK	0x20
#define BUFFER_LENGTH		256

/**************************
 * Variables definitions
 **************************/
static volatile uint8_t byteReceived;
static volatile uint8_t readyToTransmit = 1;
static volatile uint8_t flagIsReceived;
static volatile uint8_t bufferTransmit[BUFFER_LENGTH];

static volatile uint8_t queueHead = 0;
static volatile uint8_t queueTail;



/***********************************************************************
 * 
 * Function:	initUART2
 * 
 * Description: Initialize the serial port UART2.
 * 				
 *
 * Notes: 		It works with openSDA com port.
 * 				Just open putty and debug without any additional uart/usb converter.
 * 				It requires bus clock to have 24Mhz.
 * 				It work at 9600 baud rate. 
 * 				It has 4x oversampling.
 * 				Sorry for a mess ;)
 * 
 * Returns:		None. 
 * 
 ***********************************************************************/
void initUARTX(void) {

	SIM_SCGC4 |= UARTX_CLOCK_EN_FLAG;	
#if UARTX == UART0
	/*	Set UART GPIO */	
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;						
	// set UART0 pins
	PORTA_PCR1  = PORT_PCR_MUX(2);// | PORT_PCR_DSE_MASK;		// RX
	PORTA_PCR2  = PORT_PCR_MUX(2);		// TX
#endif
	UART0_C1 = 0x00U; 
	UART0_C2 = 0x00U; 
	UART0_C3 = 0x00U;
	UART0_C4 = 0;
	UART0_S2 = 0x00U;  
	
	/*	Enable UART clock */
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1); 
	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK; /* Select PLL as a clock source for various peripherals */
	
	/*	Set UART baud rate
	 * 	The baud rate equals (UART Module Clock) / (SBR[12:0] x 4)
	 * 	Module Clock equals bus clock. Bus clock is set in mcg.c for 24 MHz.
	 * 	(SBR[12:0] = (UART Module Clock) / ((baud rate) x 4)
	 * 	SBR[12:0] = 13
	 * 	24000000/((9600)*4) = 625 => 113 DL & 2 DH
	 */
	UARTX_BDL = UART_BDL_SBR(113);//56);//226);	// 156 - 9600 bps
	UARTX_BDH = UART_BDH_SBR(2);//1);//4);
	
	UART0_C4 = 3;
	
	UART0_C5 |= 1<<1;
	
	/*	Set Hardware interrupt requested when TDRE flag is 1 */
	//UART2_C2 |= UART2_C2_TIE_MASK;
	
	/*	Receiver Interrupt Enable for RDRF
	 * 		1 Hardware interrupt requested when RDRF flag is 1.
	 */
	UARTX_C2 |= UART_C2_RIE_MASK;
	
	/* Set the ICPR and ISER registers accordingly */
	NVIC_ICPR = 1 << ((INT_UARTX -16)%32);
	NVIC_ISER = 1 << ((INT_UARTX -16)%32);

	/*	Enable Transmitter */
	UARTX_C2 |= UART_C2_TE_MASK;
	
	/*	Enable Receiver */
	UARTX_C2 |= UART_C2_RE_MASK;
	
}

/***********************************************************************
 * 
 * Function:	transmitByte 
 * 
 * Description: Send a byte via the serial port.
 * 
 * Notes: 		Firstly, the function checks if the serial port
 * 				is ready to transmit. If so, ready to transmit flag
 * 				is cleared, transmitter interrupt is set and the given 
 * 				byte is send to the data register. If the readyToTransmit
 * 				flag is cleared at the beginning of a function, it will
 * 				skip the transmitting.
 * 
 * Returns:		None. 
 * 
 ***********************************************************************/ 
void transmitByte(uint8_t byte) {
	if (isReadyToTransmit) {
		readyToTransmit = 0;
		//UART0_C2 |= UART0_C2_TIE_MASK;
		UART0_D = byte;
		while(!(UARTX_S1 & UART_S1_TDRE_MASK));
	}		
}

/***********************************************************************
 * 
 * Function:	isReadyToTransmit 
 * 
 * Description: API function.
 * 
 * Notes: 		
 * 
 * Returns:		1 - if the data register is ready to get a new data
 * 				0 - if the data register isn't ready to get a new data 
 * 
 ***********************************************************************/
int isReadyToTransmit(void) {
	return readyToTransmit;
}

/***********************************************************************
 * 
 * Function:	isReceived
 * 
 * Description: Check if there is a new received byte.
 * 
 * Notes: 		API function.
 * 
 * Returns:		1 - 
 * 				0 - 
 * 
 ***********************************************************************/
int isReceived(void) {
	return flagIsReceived;
}

/***********************************************************************
 * 
 * Function:	getReceived
 * 
 * Description: Writes last received byte to a given variable
 * 
 * Notes: 		API function.
 * 
 * Returns:		Last received byte. 
 * 
 ***********************************************************************/
char getReceived(void) {	
	flagIsReceived = 0;
	return byteReceived;
}

/***********************************************************************
 * 
 * Function:	printt
 * 
 * Description:	
 * 
 * Notes:		
 * 
 * Returns:		
 ***********************************************************************/
void printt(char buffer[]) {
	
	/* Count the number of chars */ 
	int length = 0;
	while (buffer[length] != 0) {
		bufferTransmit[(queueTail + length) % BUFFER_LENGTH] = buffer[length];
		length++;
	}

	/* Compute a new queueTail value */
	queueTail = ((queueTail + length) % BUFFER_LENGTH);
		
	/* Enable interrupts for TDRE*/
	UARTX_C2 |= UART_C2_TIE_MASK;
}

/***********************************************************************
 * 
 * Function:	UART2_IRQHandler
 * 
 * Description: UART interrupt hander.
 * 
 * Notes: 		
 * 
 * Returns:		None. 
 * 
 ***********************************************************************/
void UARTX_IRQHandler() {
	
	/* Interrupt from RX pin */
	if (UARTX_S1 & UART_S1_RDRF_MASK) {
		byteReceived = UARTX_D;
		flagIsReceived = 1;
	}
	/* Interrupt from Transmit Data Register Empty Flag */
	else if (UARTX_S1 & UART_S1_TDRE_MASK) {				
		
		/* Disable interrupts if everything sent */
		if (queueTail == queueHead) {
			UARTX_C2 &= ~(UART_C2_TIE_MASK);
		}
		else {
			UARTX_D = bufferTransmit[queueHead];
			queueHead = ((queueHead + 1) % BUFFER_LENGTH);
		}
	}
}

