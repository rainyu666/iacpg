/*
 * Copyright (c) 2015 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#define DEBUG(...) ((void)0)
typedef uint32_t ring_buf_idx_t;
struct ring_buf_index { volatile uint32_t head,tail,base; };
struct ring_buf { struct ring_buf_index put,get; uint32_t size; };
static struct ring_buf stream={{6,6,0},{0,0,0},8};

static inline uint32_t ring_buf_space_get(const struct ring_buf *buf)
{
	ring_buf_idx_t allocated = buf->put.head - buf->get.tail;
	return buf->size - allocated;
}

#define IRQ_CONNECT(irq, pri, fn, arg, flags)
void uart_sifive_isr(void);
IRQ_CONNECT(7, 0, uart_sifive_isr, 0, 0);
void uart_sifive_isr(void) { stream.get.tail++; }
static uint32_t table[3] = {17,18,19};
uint32_t foreground(void) {
    uint32_t value = ring_buf_space_get(&stream);
    if (value < 3) {
        return table[value];
    }
    return 0;
}
