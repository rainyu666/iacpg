/*
  ************************************************************************
  *	wiring_digital.c
  *
  *	Arduino core files for MSP430
  *		Copyright (c) 2012 Robert Wessels. All right reserved.
  *
  *
  ***********************************************************************
  Derived from:
  wiring_digital.c - digital input and output functions
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
#define LOW 0
#define HIGH 1
#define NOT_A_PORT 0
static volatile uint8_t active_pin=1;
static const uint8_t digital_pin_to_bit_mask[3]={1,2,4};
static const uint8_t digital_pin_to_port[3]={1,1,1};
static volatile uint8_t input_port=7;
static uint8_t digitalPinToBitMask(uint8_t pin) { return digital_pin_to_bit_mask[pin]; }
static uint8_t digitalPinToPort(uint8_t pin) { return digital_pin_to_port[pin]; }
static volatile uint8_t *portInputRegister(uint8_t port) { (void)port; return &input_port; }
int digitalRead(uint8_t pin)
{
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);
	volatile uint8_t *sel;
	if (port == NOT_A_PORT) return LOW;
#if (defined(P1SEL_) || defined(P1SEL))
	sel = portSel0Register(port);
	*sel &= ~bit;
#endif
#if (defined(P1SEL2_) || defined(P1SEL2))
	sel = portSel2Register(port);
	*sel &= ~bit;
#endif
#if (defined(P1SEL0_) || defined(P1SEL0))
	sel = portSel0Register(port);
	*sel &= ~bit;
#endif
#if (defined(P1SEL1_) || defined(P1SEL1))
	sel = portSel1Register(port);
	*sel &= ~bit;
#endif
	if (*portInputRegister(port) & bit) return HIGH;
	return LOW;
}
#define ISR(vector, name) void name(void)
ISR(PORT1_VECTOR, port1_isr);
void port1_isr(void) { active_pin=3; }
uint32_t foreground(void) { uint8_t pin=active_pin; if(pin<3) { return digitalRead(active_pin); } return 0; }
