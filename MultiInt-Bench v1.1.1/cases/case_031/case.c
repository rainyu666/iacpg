/*
 * Copyright (C) 2020 Kaspar Schleiser <kaspar@schleiser.de>
 *               2020 Freie Universität Berlin
 *               2020 Inria
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#define DEBUG(...) ((void)0)
typedef struct { volatile uint32_t mul, div; } ztimer_convert_muldiv64_t;
static ztimer_convert_muldiv64_t converter = {2, 2};
extern unsigned irq_disable(void);
extern void irq_restore(unsigned);
static uint64_t _integer_div_ceil(uint64_t x, uint64_t y)
{
    if (x == 0) {
        return 0;
    }
    return 1 + ((x - 1) / y);
}

static uint32_t _convert_muldiv64_set(
    const ztimer_convert_muldiv64_t *ztimer_convert_muldiv64, uint32_t val)
{
    uint64_t res = val;
    if (ztimer_convert_muldiv64->mul > 1) {
        res *= ztimer_convert_muldiv64->mul;
    }
    if (ztimer_convert_muldiv64->div > 1) {
        res = _integer_div_ceil(res, ztimer_convert_muldiv64->div);
    }
    return res;
}

static uint32_t _convert_muldiv64_now(
    const ztimer_convert_muldiv64_t *ztimer_convert_muldiv64, uint32_t val)
{
    uint64_t res = val;
    if (ztimer_convert_muldiv64->div > 1) {
        res *= ztimer_convert_muldiv64->div;
    }
    if (ztimer_convert_muldiv64->mul > 1) {
        res /= ztimer_convert_muldiv64->mul;
    }
    DEBUG("_convert_muldiv64_now(%u * %u / %u == %u\n", (unsigned)val,
          (unsigned)ztimer_convert_muldiv64->div ? ztimer_convert_muldiv64->div : 1,
          (unsigned)ztimer_convert_muldiv64->mul ? ztimer_convert_muldiv64->mul : 1,
          (unsigned)res);
    return res;
}
void isr_tim2(void);
void isr_tim2(void) { converter.div = 0; }
uint32_t foreground(void) { unsigned s = irq_disable(); irq_restore(s); uint32_t r = _convert_muldiv64_set(&converter, 120); return r; }
