/*
 * Copyright (c) 2018 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#define DEBUG(...) ((void)0)
typedef uint64_t k_ticks_t;
typedef unsigned k_spinlock_key_t;
struct _timeout { uint32_t inactive; };
static struct _timeout event={1};
static uint32_t timeout_lock;
extern unsigned k_spin_lock(uint32_t *);
extern void k_spin_unlock(uint32_t *,unsigned);
static volatile uint64_t curr_tick=UINT32_MAX;
static int z_is_inactive_timeout(const struct _timeout *t) { return t->inactive; }
static uint64_t timeout_rem(const struct _timeout *t) { (void)t; return 0; }
#define IRQ_CONNECT(irq, pri, fn, arg, flags)
void riscv_machine_timer_irq_handler(void);
IRQ_CONNECT(7, 0, riscv_machine_timer_irq_handler, 0, 0);
void riscv_machine_timer_irq_handler(void) { curr_tick++; }
k_ticks_t z_timeout_expires(const struct _timeout *timeout) {
    k_ticks_t ticks=0;
    unsigned key=1;
    ticks = curr_tick;
    if (!z_is_inactive_timeout(timeout)) { ticks += timeout_rem(timeout); }
    k_spin_unlock(&timeout_lock,key);
    return ticks;
}
uint64_t foreground(void) { return z_timeout_expires(&event); }
