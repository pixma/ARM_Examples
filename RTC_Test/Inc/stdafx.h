

#ifndef STDAFX_H
#define STDAFX_H

#include <LPC214x.h>                        /* LPC21xx definitions */
#include <type.h>
#include <irq.h>
#include <timer.h>
#include <uart.h>
#include <rtc.h>


DWORD pinState = 0;

int main( void );
int digitalWrite( DWORD );
void printPinState( DWORD );
void printToSerial( DWORD );
#endif
