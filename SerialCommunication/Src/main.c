//Main c source code

#include <stdafx.h>
#include <string.h>

static char chPinStateLow[] = "pin state low\n";
static char chPinStatehigh[] = "pin state High\n";
int main(){	
	
	DWORD counter = 0;	
	timer_counter = counter;
	
	init_VIC();				//initiate vector interrupted control regs.
	init_timer();			// init timers for delays.
	
	UARTInit( 9600 );		//init uart with 9600 baud rate.
		
	/* Initialize timer for GPIO toggling timing */
	enable_timer( 0 );
	
	//set gpios direction
	IODIR0 |= (1 << 8 );	// set p0.8 pin as output.	
	IOSET0 |= ( 1 << 8 );	//set p0.8 pin as high. 3.3v
	
	while( 1 ){
		
		while( !((timer_counter - counter) == 1) );
		pinState = !pinState;
		digitalWrite( pinState );
		counter = timer_counter;
		printPinState( pinState );
		
	}
	return 0;
}

int digitalWrite( DWORD state ){
	switch( state ){
		case 0:
			IOCLR0 |= ( 1<< 8 );
		break;
		case 1:
			IOSET0 |= ( 1 << 8 );
		break;
	}
	return 0;
}

void printPinState( DWORD dState ){
	switch( dState ){
		case 0:
			UART_DataSend( (BYTE *)chPinStateLow, strlen( chPinStateLow ) );
		break;
		case 1:
			UART_DataSend( (BYTE *)chPinStatehigh, strlen( chPinStatehigh ) );
		break;
	}
	
}
