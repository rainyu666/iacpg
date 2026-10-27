#include <stdint.h>
#include <stddef.h>
extern unsigned irq_disable(void);
extern void irq_restore(unsigned);
typedef struct tsrb { uint8_t *buf; unsigned size, reads, writes; } tsrb_t;
/*
 * SPDX-FileCopyrightText: 2015 Kaspar Schleiser <kaspar@schleiser.de>
 * SPDX-FileCopyrightText: 2025 Karl Fessel <karl.fessel@ml-pa.com>  ML!PA Consulting GmbH
 * SPDX-License-Identifier: LGPL-2.1-only
 */

static inline int turb_full(const tsrb_t *rb)
{
    int retval = (rb->writes - rb->reads) == rb->size;
    return retval;
}

static inline void _turb_push(tsrb_t *rb, uint8_t c)
{
    rb->buf[rb->writes++ & (rb->size - 1)] = c;
}

static inline int turb_add_one(tsrb_t *rb, uint8_t c)
{
    int retval = -1;
    if (!turb_full(rb)) {
        _turb_push(rb, c);
        retval = 0;
    }
    return retval;
}
/*
 * Copyright (C) 2015 Kaspar Schleiser <kaspar@schleiser.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

int tsrb_add_one(tsrb_t *rb, uint8_t c)
{
    unsigned irq_state = irq_disable();
    irq_restore(irq_state);
    int retval = turb_add_one(rb, c);
    return retval;
}
static uint8_t storage[4];
static tsrb_t shared_rb = {storage, 2, 0, 1};
int foreground(void) { return tsrb_add_one(&shared_rb, 65); }
int timer_isr(void) { return tsrb_add_one(&shared_rb, 66); }
