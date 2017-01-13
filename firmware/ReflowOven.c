#define    F_CPU    16000000UL
#include <avr/io.h>
#include <util/delay.h>

void init(void){	// initialize
	USART_Init(103);	// FOSC/16/BAUNDrate-1 = 16M/16/9600-1 =103.17... -> 103
}


void USART_Init( unsigned int ubrr)
{
	/* Set baud rate */
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 0stop bit */
	UCSRC = (1<<URSEL)|(0<<USBS)|(3<<UCSZ0);
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = data;
}

int main(void){
	
	init();

	char data = 'a';

	while(1){
		USART_Transmit(data);
		_delay_ms(10);
	}

	return 0;
}
