/*
 * SPDX-FileCopyrightText: 2015 Kaspar Schleiser <kaspar@schleiser.de>
 * SPDX-FileCopyrightText: 2016 Eistec AB
 * SPDX-FileCopyrightText: 2018 Josua Arndt
 * SPDX-License-Identifier: LGPL-2.1-only
 */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#define DEBUG(...) ((void)0)
extern unsigned irq_disable(void);
extern void irq_restore(unsigned);
static volatile uint64_t _xtimer_current_time=UINT32_MAX;
static uint32_t _xtimer_lltimer_now(void) { return UINT32_MAX; }
void isr_tim2(void);
void isr_tim2(void) { _xtimer_current_time++; }
static inline uint64_t _xtimer_now64(void)
{
    uint32_t now, elapsed;
    unsigned state = irq_disable();
    now = _xtimer_lltimer_now();
    elapsed = now - ((uint32_t)_xtimer_current_time & 0xFFFFFFFF);
    _xtimer_current_time += (uint64_t)elapsed;

    uint64_t result = _xtimer_current_time;
    irq_restore(state);
    return result;
}
uint64_t foreground(void) { return _xtimer_now64(); }
