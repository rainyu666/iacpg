/*
 * SPDX-FileCopyrightText: 2017 Ken Rabold
 * SPDX-License-Identifier: LGPL-2.1-only
 */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#define DEBUG(...) ((void)0)
typedef unsigned tim_t;
typedef void (*timer_cb_t)(void *,int);
static timer_cb_t isr_cb;
static void *isr_arg;
#define mie 0
#define MIP_MTIP 1
extern void clear_csr(unsigned,unsigned);
extern void set_csr(unsigned,unsigned);
static volatile uint64_t timer_value=UINT32_MAX-15ULL, compare_value=0;
int timer_set(tim_t dev, int channel, unsigned int timeout)
{
    volatile uint64_t *mtime = &timer_value;
    volatile uint64_t *mtimecmp =
        &compare_value;
    uint64_t now = *mtime;
    uint64_t then = now + (uint64_t)timeout;
    if (dev != 0 || channel != 0) {
        return -1;
    }
    clear_csr(mie, MIP_MTIP);
    *mtimecmp = then;
    set_csr(mie, MIP_MTIP);
    return 0;
}

void timer_isr(void)
{
    volatile uint64_t *mtimecmp =
        &compare_value;
    clear_csr(mie, MIP_MTIP);
    *mtimecmp = 0xFFFFFFFFFFFFFFFF;
    if (isr_cb) {
        isr_cb(isr_arg, 0);
    }
    set_csr(mie, MIP_MTIP);
}
uint64_t foreground(void) { timer_set(0,0,32); clear_csr(mie,MIP_MTIP); uint64_t value = compare_value; set_csr(mie,MIP_MTIP); return value; }
