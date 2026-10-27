/*
  serial.c - Low level functions for sending and recieving bytes via the serial port
  Part of Grbl

  Copyright (c) 2011-2016 Sungeun K. Jeon for Gnea Research LLC
  Copyright (c) 2009-2011 Simen Svale Skogsrud

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
#define RX_BUFFER_SIZE 7
#define RX_RING_BUFFER 8
static volatile uint8_t serial_rx_buffer_head=2, serial_rx_buffer_tail=0;

uint8_t serial_get_rx_buffer_count()
{
  uint8_t rtail = serial_rx_buffer_tail;
  if (serial_rx_buffer_head >= rtail) { return(serial_rx_buffer_head-rtail); }
  return (RX_BUFFER_SIZE - (rtail-serial_rx_buffer_head));
}

#define ISR(vector) void vector(void)
ISR(USART_RX_vect);
void USART_RX_vect(void) { serial_rx_buffer_head = (serial_rx_buffer_head + 1) % RX_RING_BUFFER; }
static uint32_t table[3] = {17,18,19};
uint32_t foreground(void) {
    uint32_t value = serial_get_rx_buffer_count();
    if (value < 3) {
        return table[serial_get_rx_buffer_count()];
    }
    return 0;
}
