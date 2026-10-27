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

static inline int turb_empty(const tsrb_t *rb)
{
    int retval = (rb->reads == rb->writes);
    return retval;
}

static inline uint8_t _turb_pop(tsrb_t *rb)
{
    return rb->buf[rb->reads++ & (rb->size - 1)];
}

static inline int turb_get_one(tsrb_t *rb)
{
    int retval = -1;
    if (!turb_empty(rb)) {
        retval = _turb_pop(rb);
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

int tsrb_get_one(tsrb_t *rb)
{
    unsigned irq_state = irq_disable();
    int retval = turb_get_one(rb);
    irq_restore(irq_state);
    return retval;
}
static uint8_t storage[4];
static tsrb_t shared_rb = {storage, 2, 0, 1};
int foreground(void) { return tsrb_get_one(&shared_rb); }
int timer_isr(void) { return tsrb_get_one(&shared_rb); }
