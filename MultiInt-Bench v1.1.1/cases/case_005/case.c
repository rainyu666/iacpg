/*
 * Copyright (c) 2021 Tokita, Hiroshi <tokita.hiroshi@gmail.com>
 * Copyright (c) 2025 Andes Technology Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#define DEBUG(...) ((void)0)
#define CSR_MISELECT 0
#define CSR_MIREG 1
#define CLIC_INTIP(irq) (irq)
#define BIT(x) (1U<<(x))
static volatile uint32_t selector=0,register_bank[2]={0,0};
static uint32_t irq_lock_word;
extern unsigned irq_lock(void);
extern void irq_unlock(unsigned);
static void csr_write(uint32_t csr,uint32_t value) { if(csr==CSR_MISELECT) { selector=value; } else { register_bank[selector]=value; } }
static void csr_set(uint32_t csr,uint32_t value) { (void)csr; register_bank[selector] |= value; }
static void micsr_set(uint32_t reg,uint32_t value) { unsigned key=irq_lock(); csr_write(CSR_MISELECT,reg); csr_set(CSR_MIREG,value); irq_unlock(key); }
#define IRQ_CONNECT(irq, pri, fn, arg, flags)
void riscv_machine_timer_irq_handler(void);
IRQ_CONNECT(7, 0, riscv_machine_timer_irq_handler, 0, 0);
void riscv_machine_timer_irq_handler(void) { csr_write(CSR_MISELECT,1); }
void riscv_clic_irq_set_pending(uint32_t irq) { csr_write(CSR_MISELECT, CLIC_INTIP(irq)); csr_set(CSR_MIREG, BIT(irq%32)); }
uint32_t foreground(void) { riscv_clic_irq_set_pending(0); return register_bank[0]; }
