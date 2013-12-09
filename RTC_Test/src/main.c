//Main c source code

#include <stdafx.h>
#include <string.h>

static char chPinStateLow[] = "pin state low\n";
static char chPinStatehigh[] = "pin state High\n";

RTCTime local_time, current_time;

int main(){	
	
	DWORD counter = 0;	
	timer_counter = counter;
	
	init_VIC();				//initiate vector interrupted control regs.
	init_timer();			// init timers for delays.
	
	UARTInit( 9600 );		//init uart with 9600 baud rate.	
	
    /* Initialize RTC module */
    RTCInit();

    local_time.RTC_Sec = 0;
    local_time.RTC_Min = 40;
    local_time.RTC_Hour = 17;
    local_time.RTC_Mday = 12;
    local_time.RTC_Wday = 1;
    local_time.RTC_Yday = 344;		/* current date 12/09/20013 17:40:00*/
    local_time.RTC_Mon = 12;
    local_time.RTC_Year = 2013;
    RTCSetTime( local_time );		/* Set local time */
	RTCStart();
		
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
		current_time = RTCGetTime();
		printToSerial( (DWORD *)"\n" );
		printToSerial( (DWORD *)"Date : " );
		printToSerial( current_time.RTC_Mon );
		printToSerial( (DWORD *)"/" );
		printToSerial( current_time.RTC_Mon );
		printToSerial( (DWORD *)"/" );
		printToSerial( current_time.RTC_Year );
		
		printToSerial( (DWORD *)"\n\n" );
		printToSerial( (DWORD *)"Time: " );
		printToSerial( current_time.RTC_Hour );
		printToSerial( (DWORD *)":" );
		printToSerial( current_time.RTC_Min );
		printToSerial( (DWORD *)":" );
		printToSerial( current_time.RTC_Sec );
		
		printToSerial( "\n\n" );
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

void printToSerial( DWORD dWord){
	UART_DataSend( (BYTE *)dWord, strlen( dWord ) );
}
