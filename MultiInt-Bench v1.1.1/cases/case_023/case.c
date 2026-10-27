/*
 * Copyright (c) 2004, Swedish Institute of Computer Science.
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
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#define DEBUG(...) ((void)0)
struct memb { uint16_t size, num; uint8_t *count; void *mem; };
static uint8_t slots[3]={1,0,0}, memory[3];
static struct memb pool={1,3,slots,memory};

int
memb_numfree(struct memb *m)
{
  int i;
  int num_free = 0;
  for(i = 0; i < m->num; ++i) {
    if(m->count[i] == 0) {
      ++num_free;
    }
  }
  return num_free;
}

char
memb_free(struct memb *m, void *ptr)
{
  int i;
  char *ptr2;
  ptr2 = (char *)m->mem;
  for(i = 0; i < m->num; ++i) {
    if(ptr2 == (char *)ptr) {
      if(m->count[i] > 0) {
	--(m->count[i]);
      }
      return m->count[i];
    }
    ptr2 += m->size;
  }
  return -1;
}

void clock_isr(void);
void clock_isr(void) { memb_free(&pool, &memory[0]); }
static uint32_t table[3] = {17,18,19};
uint32_t foreground(void) {
    uint32_t value = memb_numfree(&pool);
    if (value < 3) {
        return table[memb_numfree(&pool)];
    }
    return 0;
}
