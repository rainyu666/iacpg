/*
 * Copyright (c) 2015, SICS Swedish ICT.
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
struct ringbufindex { volatile uint8_t mask, put_ptr, get_ptr; };
static struct ringbufindex queue={3,0,1};

int
ringbufindex_peek_get(const struct ringbufindex *r)
{
  if(((r->put_ptr - r->get_ptr) & r->mask) > 0) {
    return r->get_ptr;
  } else {
    return -1;
  }
}

int
ringbufindex_get(struct ringbufindex *r)
{
  int get_ptr;
  if(((r->put_ptr - r->get_ptr) & r->mask) > 0) {
    get_ptr = r->get_ptr;
    r->get_ptr = (r->get_ptr + 1) & r->mask;
    return get_ptr;
  } else {
    return -1;
  }
}

void uart_isr(void);
void uart_isr(void) { ringbufindex_get(&queue); ringbufindex_get(&queue); }
static uint32_t table[3] = {17,18,19};
uint32_t foreground(void) {
    uint32_t value = ringbufindex_peek_get(&queue);
    if (value < 3) {
        return table[ringbufindex_peek_get(&queue)];
    }
    return 0;
}
