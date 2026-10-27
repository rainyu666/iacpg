/*
  planner.c - buffers movement commands and manages the acceleration profile plan
  Part of Grbl

  Copyright (c) 2011-2016 Sungeun K. Jeon for Gnea Research LLC
  Copyright (c) 2009-2011 Simen Svale Skogsrud
  Copyright (c) 2011 Jens Geisler

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#define DEBUG(...) ((void)0)
#define BLOCK_BUFFER_SIZE 8
static volatile uint8_t block_buffer_head=5,block_buffer_tail=0,block_buffer_planned=0;

uint8_t plan_get_block_buffer_available()
{
  if (block_buffer_head >= block_buffer_tail) { return((BLOCK_BUFFER_SIZE-1)-(block_buffer_head-block_buffer_tail)); }
  return((block_buffer_tail-block_buffer_head-1));
}

uint8_t plan_next_block_index(uint8_t block_index)
{
  block_index++;
  if (block_index == BLOCK_BUFFER_SIZE) { block_index = 0; }
  return(block_index);
}

void plan_discard_current_block()
{
  if (block_buffer_head != block_buffer_tail) {
    uint8_t block_index = plan_next_block_index( block_buffer_tail );
    if (block_buffer_tail == block_buffer_planned) { block_buffer_planned = block_index; }
    block_buffer_tail = block_index;
  }
}

#define ISR(vector) void vector(void)
ISR(TIMER1_COMPA_vect);
void TIMER1_COMPA_vect(void) { plan_discard_current_block(); }
static uint32_t table[3] = {17,18,19};
uint32_t foreground(void) {
    uint32_t value = plan_get_block_buffer_available();
    if (value < 3) {
        return table[value];
    }
    return 0;
}
