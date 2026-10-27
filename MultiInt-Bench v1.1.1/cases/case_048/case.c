/*
 * SPDX-FileCopyrightText: 2016 Kaspar Schleiser <kaspar@schleiser.de>
 * SPDX-FileCopyrightText: 2013 Freie Universität Berlin
 * SPDX-License-Identifier: LGPL-2.1-only
 */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#define DEBUG(...) ((void)0)
typedef struct { volatile uint32_t read_count,write_count,mask; } cib_t;
static cib_t inbox={0,1,3};

static inline unsigned int cib_avail(const cib_t *cib)
{
    return cib->write_count - cib->read_count;
}

static inline int cib_peek_at_unsafe(const cib_t *__restrict cib, unsigned offset)
{
    return (cib->read_count + offset) & cib->mask;
}

static inline int cib_peek_at(const cib_t *__restrict cib, unsigned offset)
{
    if (offset < cib_avail(cib)) {
        return cib_peek_at_unsafe(cib, offset);
    }
    return -1;
}

static inline int cib_peek(const cib_t *__restrict cib)
{
    return cib_peek_at(cib, 0);
}

static inline int cib_get(cib_t *__restrict cib)
{
    if (cib_avail(cib)) {
        return (int)(cib->read_count++ & cib->mask);
    }
    return -1;
}

#define IRQ_CONNECT(irq, pri, fn, arg, flags)
void isr_uart0(void);
IRQ_CONNECT(7, 0, isr_uart0, 0, 0);
void isr_uart0(void) { cib_get(&inbox); }
static uint32_t table[4] = {17,18,19,20};
extern unsigned irq_disable(void);
extern void irq_restore(unsigned);
static int inbox_peek(void) { unsigned s=irq_disable(); int value=cib_peek(&inbox); irq_restore(s); return value; }
uint32_t foreground(void) {
    uint32_t value = inbox_peek();
    if (value < 4) {
        return table[value];
    }
    return 0;
}
