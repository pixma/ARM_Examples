

#ifndef STDAFX_H
#define STDAFX_H

#include <LPC214x.h>                        /* LPC21xx definitions */
#include <type.h>
#include <irq.h>
#include <timer.h>


DWORD pinState = 0;

int main( void );
int digitalWrite( DWORD );
#endif
