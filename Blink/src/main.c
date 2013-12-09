//Main c source code

#include <stdafx.h>


int main(){	
	
	DWORD counter = 0;	
	timer_counter = counter;
	init_VIC();				//initiate vector interrupted control regs.
	init_timer();			// init timers for delays.
		
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
