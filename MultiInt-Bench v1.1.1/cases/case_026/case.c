/*
 * Copyright (c) 2008, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#define DEBUG(...) ((void)0)
#define CC_ACCESS_NOW(type, variable) (*(volatile type *)&(variable))
struct ringbuf { uint8_t *data; uint8_t mask; volatile uint8_t put_ptr,get_ptr; };
static uint8_t storage[4]={1,2,3,4};
static struct ringbuf bytes={storage,3,1,0};

int
ringbuf_elements(struct ringbuf *r)
{
  return (r->put_ptr - r->get_ptr) & r->mask;
}

int
ringbuf_get(struct ringbuf *r)
{
  uint8_t c;
  if(((r->put_ptr - r->get_ptr) & r->mask) > 0) {
    c = CC_ACCESS_NOW(uint8_t, r->data[r->get_ptr]);
    CC_ACCESS_NOW(uint8_t, r->get_ptr) = (r->get_ptr + 1) & r->mask;
    return c;
  } else {
    return -1;
  }
}

#define ISR(vector) void vector(void)
ISR(TIMER0_COMPA_vect);
void TIMER0_COMPA_vect(void) { ringbuf_get(&bytes); }
uint32_t foreground(void) {
    uint32_t value = ringbuf_elements(&bytes);
    if (value != 0) {
        return 120 / value;
    }
    return 0;
}
