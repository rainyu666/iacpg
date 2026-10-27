/*
 * MIT License 
 * 
 * Copyright (c) 2020 Kirill Kotyagin
 */

#include <stm32f1xx.h>
#include "system_clock.h"
#include "system_interrupts.h"
#include "status_led.h"
#include "device_config.h"
#include "usb.h"
volatile uint32_t runtime_budget = 10U;
volatile uint32_t clock_divider = 1U;
static void update_runtime_budget(void) {
    uint32_t budget = runtime_budget;
    runtime_budget = budget + 1U;
}

static uint32_t get_base_clock(void) {
    return 72000000U / clock_divider;
}

int main() {
    system_clock_init();
    system_interrupts_init();
    device_config_init();
    status_led_init();
    usb_init();
    while (1) {
        usb_poll();
        update_runtime_budget();
        volatile uint32_t base_clock = get_base_clock();
        (void)base_clock;
    }
}
