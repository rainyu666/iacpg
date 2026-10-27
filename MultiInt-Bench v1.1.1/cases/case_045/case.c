/*
 * Copyright (c) 2018 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#define DEBUG(...) ((void)0)
typedef unsigned k_spinlock_key_t;
static uint32_t timeout_lock;
extern k_spinlock_key_t k_spin_lock(uint32_t *);
extern void k_spin_unlock(uint32_t *, k_spinlock_key_t);
static volatile uint64_t curr_tick=UINT32_MAX;
static uint32_t elapsed(void) { return 0; }
void sys_clock_isr(void);
void sys_clock_isr(void) { curr_tick++; }
int64_t sys_clock_tick_get(void) {
    uint64_t t = 0U;
    k_spinlock_key_t key = 1;
    t = curr_tick + elapsed();
    k_spin_unlock(&timeout_lock, key);
    return t;
}
int64_t foreground(void) { return sys_clock_tick_get(); }
