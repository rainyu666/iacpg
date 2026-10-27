/*
 * Copyright (c) 2017 Jean-Paul Etienne <fractalclone@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#define DEBUG(...) ((void)0)
#define ALWAYS_INLINE
#define ARG_UNUSED(x) ((void)(x))
typedef struct { volatile uint32_t val_low,val_high; } riscv_machine_timer_t;
static riscv_machine_timer_t time_registers={24,1},compare_registers;
static volatile riscv_machine_timer_t *mtime=&time_registers,*mtimecmp=&compare_registers;
static uint32_t sys_clock_hw_cycles_per_tick=100;
static uint32_t accumulated_cycle_count=100;
static uint64_t last_rtc_value=4294967280ULL;
static void _sys_clock_tick_announce(void) {}
static void riscv_machine_rearm_timer(void)
{
	uint64_t rtc;
	rtc = mtime->val_low;
	rtc |= ((uint64_t)mtime->val_high << 32);
	rtc += sys_clock_hw_cycles_per_tick;
	mtimecmp->val_low = (uint32_t)(rtc & 0xffffffff);
	mtimecmp->val_high = (uint32_t)((rtc >> 32) & 0xffffffff);
}

static void riscv_machine_timer_irq_handler(void *unused)
{
	ARG_UNUSED(unused);
	_sys_clock_tick_announce();
	riscv_machine_rearm_timer();
}

uint32_t k_cycle_get_32(void)
{
	return mtime->val_low;
}
void interrupt_entry(void) { riscv_machine_timer_irq_handler(0); }
uint32_t foreground(void) { return k_cycle_get_32(); }
