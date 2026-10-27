/*
  ************************************************************************
  *	wiring.c
  *
  *	Arduino core files for MSP430
  *		Copyright (c) 2012 Robert Wessels. All right reserved.
  *
  *
  ***********************************************************************
  Derived from:
  wiring.c - Partial implementation of the Wiring API for the ATmega8.
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2005-2006 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
*/
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#define DEBUG(...) ((void)0)
extern uint16_t read_sr(void);
#define READ_SR read_sr()
extern void __dint(void);
extern void WRITE_SR(uint16_t);
static volatile uint32_t wdt_millis=UINT32_MAX;

uint32_t millis()
{
	uint32_t m;
	uint16_t oldSREG = READ_SR;
	__dint();
	m = wdt_millis;
	WRITE_SR(oldSREG);
 	return m;
}

#define ISR(vector, name) void name(void)
ISR(WDT_VECTOR, watchdog_isr);
void watchdog_isr(void) { ++wdt_millis; }
uint32_t foreground(void) {
    uint32_t value = millis();
    if (value != 0) {
        return 120 / millis();
    }
    return 0;
}
