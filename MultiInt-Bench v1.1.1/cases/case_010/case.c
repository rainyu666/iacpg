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

static inline int cib_get(cib_t *__restrict cib)
{
    if (cib_avail(cib)) {
        return (int)(cib->read_count++ & cib->mask);
    }
    return -1;
}

#define IRQ_CONNECT(irq, pri, fn, arg, flags)
void isr_mtimer(void);
IRQ_CONNECT(7, 0, isr_mtimer, 0, 0);
void isr_mtimer(void) { cib_get(&inbox); }
uint32_t foreground(void) {
    uint32_t value = cib_avail(&inbox);
    if (value != 0) {
        return 120 / value;
    }
    return 0;
}
