# Interrupt Concurrency Defect Dataset

This dataset covers foreground–interrupt interleavings in embedded software, including atomicity violations, interrupt-related division by zero, interrupt-related array out-of-bounds accesses, and multiword data races.

## MultiInt-Bench

The dataset contains **34 pairs comprising 68 C programs** across ARM, AVR, MSP430, and RV32 platforms. Each pair contains a defective sample and a control/fixed sample.

| Platform | Sample pairs | Programs | Atomicity violations | Interrupt-related division by zero | Interrupt-related array out-of-bounds accesses | Multiword data races |
|---|---:|---:|---:|---:|---:|---:|
| ARM | 9 | 18 | 7 | 2 | 2 | 2 |
| AVR | 9 | 18 | 7 | 2 | 2 | 4 |
| MSP430 | 8 | 16 | 6 | 2 | 2 | 2 |
| RV32 | 8 | 16 | 6 | 2 | 2 | 3 |
| Total | 34 | 68 | 26 | 8 | 8 | 11 |

Counts indicate the number of programs containing each defect category. A program may contain multiple categories, giving 53 category annotations in total. Platform parameters are recorded in `profile.json`, and defect annotations in `LABEL.yml`. Source code and third-party components retain their respective licenses.

Samples are derived from queue, buffer, timer, counter, and interrupt-control code in the following open-source projects:

| Source project | Main components | License |
|---|---|---|
| [RIOT](https://github.com/RIOT-OS/RIOT/tree/46fac72c1fb9417632664236349c670e65541d24) | CIB, TSRB, timers | LGPL-2.1-only |
| [Contiki](https://github.com/contiki-os/contiki/tree/32b5b17f674232867c22916bb2e2534c8e9a92ff) | Ring buffers, memory pools, clocks | BSD-3-Clause |
| [Grbl](https://github.com/gnea/grbl/tree/bfb67f0c7963fe3ce4aaf8a97f9009ea5a8db36e) | Serial buffers, motion planner | GPL-3.0-or-later |
| [Energia](https://github.com/energia/Energia/tree/7afdf1ebfeaa06cd0dfee7d4539f076e007ab4e4) | Clocks, digital I/O | LGPL-2.1-or-later |
| [Zephyr](https://github.com/zephyrproject-rtos/zephyr/tree/23bf240be49e06a003d0c49cc462f73580c1a118) | Timeouts, ring buffers, RISC-V timers and interrupt control | Apache-2.0 |

## Source Mapping

The following sections document the sources, pinned commits, upstream functions, and adaptations for each sample pair.

### Upstream Source Snapshots

| Project/snapshot | Commit | Path | License |
|---|---|---|---|
| RIOT | `46fac72c1fb9417632664236349c670e65541d24` | [core/lib/include/cib.h](https://raw.githubusercontent.com/RIOT-OS/RIOT/46fac72c1fb9417632664236349c670e65541d24/core/lib/include/cib.h) | LGPL-2.1-only |
| RIOT | `46fac72c1fb9417632664236349c670e65541d24` | [sys/include/turb.h](https://raw.githubusercontent.com/RIOT-OS/RIOT/46fac72c1fb9417632664236349c670e65541d24/sys/include/turb.h) | LGPL-2.1-only |
| RIOT | `46fac72c1fb9417632664236349c670e65541d24` | [sys/tsrb/tsrb.c](https://raw.githubusercontent.com/RIOT-OS/RIOT/46fac72c1fb9417632664236349c670e65541d24/sys/tsrb/tsrb.c) | LGPL-2.1-only |
| RIOT | `46fac72c1fb9417632664236349c670e65541d24` | [sys/ztimer/convert_muldiv64.c](https://raw.githubusercontent.com/RIOT-OS/RIOT/46fac72c1fb9417632664236349c670e65541d24/sys/ztimer/convert_muldiv64.c) | LGPL-2.1-only |
| RIOT | `46fac72c1fb9417632664236349c670e65541d24` | [cpu/riscv_common/periph/coretimer.c](https://raw.githubusercontent.com/RIOT-OS/RIOT/46fac72c1fb9417632664236349c670e65541d24/cpu/riscv_common/periph/coretimer.c) | LGPL-2.1-only |
| RIOT | `46fac72c1fb9417632664236349c670e65541d24` | [sys/include/xtimer/implementation.h](https://raw.githubusercontent.com/RIOT-OS/RIOT/46fac72c1fb9417632664236349c670e65541d24/sys/include/xtimer/implementation.h) | LGPL-2.1-only |
| contiki | `32b5b17f674232867c22916bb2e2534c8e9a92ff` | [core/lib/ringbuf.c](https://raw.githubusercontent.com/contiki-os/contiki/32b5b17f674232867c22916bb2e2534c8e9a92ff/core/lib/ringbuf.c) | BSD-3-Clause |
| contiki | `32b5b17f674232867c22916bb2e2534c8e9a92ff` | [core/lib/ringbufindex.c](https://raw.githubusercontent.com/contiki-os/contiki/32b5b17f674232867c22916bb2e2534c8e9a92ff/core/lib/ringbufindex.c) | BSD-3-Clause |
| contiki | `32b5b17f674232867c22916bb2e2534c8e9a92ff` | [core/lib/memb.c](https://raw.githubusercontent.com/contiki-os/contiki/32b5b17f674232867c22916bb2e2534c8e9a92ff/core/lib/memb.c) | BSD-3-Clause |
| contiki | `32b5b17f674232867c22916bb2e2534c8e9a92ff` | [core/sys/timer.c](https://raw.githubusercontent.com/contiki-os/contiki/32b5b17f674232867c22916bb2e2534c8e9a92ff/core/sys/timer.c) | BSD-3-Clause |
| contiki | `32b5b17f674232867c22916bb2e2534c8e9a92ff` | [cpu/msp430/f1xxx/clock.c](https://raw.githubusercontent.com/contiki-os/contiki/32b5b17f674232867c22916bb2e2534c8e9a92ff/cpu/msp430/f1xxx/clock.c) | BSD-3-Clause |
| contiki | `32b5b17f674232867c22916bb2e2534c8e9a92ff` | [cpu/avr/dev/clock.c](https://raw.githubusercontent.com/contiki-os/contiki/32b5b17f674232867c22916bb2e2534c8e9a92ff/cpu/avr/dev/clock.c) | BSD-3-Clause |
| grbl | `bfb67f0c7963fe3ce4aaf8a97f9009ea5a8db36e` | [grbl/serial.c](https://raw.githubusercontent.com/gnea/grbl/bfb67f0c7963fe3ce4aaf8a97f9009ea5a8db36e/grbl/serial.c) | GPL-3.0-or-later |
| grbl | `bfb67f0c7963fe3ce4aaf8a97f9009ea5a8db36e` | [grbl/planner.c](https://raw.githubusercontent.com/gnea/grbl/bfb67f0c7963fe3ce4aaf8a97f9009ea5a8db36e/grbl/planner.c) | GPL-3.0-or-later |
| Energia | `7afdf1ebfeaa06cd0dfee7d4539f076e007ab4e4` | [hardware/msp430/cores/msp430/wiring.c](https://raw.githubusercontent.com/energia/Energia/7afdf1ebfeaa06cd0dfee7d4539f076e007ab4e4/hardware/msp430/cores/msp430/wiring.c) | LGPL-2.1-or-later |
| Energia | `7afdf1ebfeaa06cd0dfee7d4539f076e007ab4e4` | [hardware/msp430/cores/msp430/wiring_digital.c](https://raw.githubusercontent.com/energia/Energia/7afdf1ebfeaa06cd0dfee7d4539f076e007ab4e4/hardware/msp430/cores/msp430/wiring_digital.c) | LGPL-2.1-or-later |
| zephyr | `23bf240be49e06a003d0c49cc462f73580c1a118` | [kernel/timeout.c](https://raw.githubusercontent.com/zephyrproject-rtos/zephyr/23bf240be49e06a003d0c49cc462f73580c1a118/kernel/timeout.c) | Apache-2.0 |
| zephyr | `23bf240be49e06a003d0c49cc462f73580c1a118` | [include/zephyr/sys/ring_buffer.h](https://raw.githubusercontent.com/zephyrproject-rtos/zephyr/23bf240be49e06a003d0c49cc462f73580c1a118/include/zephyr/sys/ring_buffer.h) | Apache-2.0 |
| zephyr | `23bf240be49e06a003d0c49cc462f73580c1a118` | [drivers/interrupt_controller/intc_clic.c](https://raw.githubusercontent.com/zephyrproject-rtos/zephyr/23bf240be49e06a003d0c49cc462f73580c1a118/drivers/interrupt_controller/intc_clic.c) | Apache-2.0 |
| zephyr_clock_pre | `be856d4b134c0807870c48f2c9d34fc997fb73f2` | [drivers/timer/riscv_machine_timer.c](https://raw.githubusercontent.com/zephyrproject-rtos/zephyr/be856d4b134c0807870c48f2c9d34fc997fb73f2/drivers/timer/riscv_machine_timer.c) | Apache-2.0 |
| zephyr_clock_post | `97d76cad669a856b4a0b986eb58cc62fff749a90` | [drivers/timer/riscv_machine_timer.c](https://raw.githubusercontent.com/zephyrproject-rtos/zephyr/97d76cad669a856b4a0b986eb58cc62fff749a90/drivers/timer/riscv_machine_timer.c) | Apache-2.0 |
| zephyr_clic_pre | `037b8fe971bd4a11689b0b1304e66cd4c9cfb39c` | [drivers/interrupt_controller/intc_clic.c](https://raw.githubusercontent.com/zephyrproject-rtos/zephyr/037b8fe971bd4a11689b0b1304e66cd4c9cfb39c/drivers/interrupt_controller/intc_clic.c) | Apache-2.0 |

### Sample Numbers and Source Identifiers

Each row lists the defective sample followed by the control sample.

| Defective/control samples | Source pair ID | Platform |
|---|---|---|
| [case_001](MultiInt-Bench%20v1.1.1/cases/case_001/case.c) / [case_002](MultiInt-Bench%20v1.1.1/cases/case_002/case.c) | `g5f9e910ba24d` | arm |
| [case_003](MultiInt-Bench%20v1.1.1/cases/case_003/case.c) / [case_004](MultiInt-Bench%20v1.1.1/cases/case_004/case.c) | `gfbfc9c714998` | msp430 |
| [case_005](MultiInt-Bench%20v1.1.1/cases/case_005/case.c) / [case_006](MultiInt-Bench%20v1.1.1/cases/case_006/case.c) | `g8858cebce50a` | riscv |
| [case_007](MultiInt-Bench%20v1.1.1/cases/case_007/case.c) / [case_008](MultiInt-Bench%20v1.1.1/cases/case_008/case.c) | `g81493af59b56` | riscv |
| [case_009](MultiInt-Bench%20v1.1.1/cases/case_009/case.c) / [case_010](MultiInt-Bench%20v1.1.1/cases/case_010/case.c) | `g7677ee9477ea` | riscv |
| [case_011](MultiInt-Bench%20v1.1.1/cases/case_011/case.c) / [case_012](MultiInt-Bench%20v1.1.1/cases/case_012/case.c) | `g4cb65a232aa1` | riscv |
| [case_013](MultiInt-Bench%20v1.1.1/cases/case_013/case.c) / [case_014](MultiInt-Bench%20v1.1.1/cases/case_014/case.c) | `g269307add0f1` | msp430 |
| [case_015](MultiInt-Bench%20v1.1.1/cases/case_015/case.c) / [case_016](MultiInt-Bench%20v1.1.1/cases/case_016/case.c) | `ga552032e8c7b` | msp430 |
| [case_017](MultiInt-Bench%20v1.1.1/cases/case_017/case.c) / [case_018](MultiInt-Bench%20v1.1.1/cases/case_018/case.c) | `g2672acd4b78a` | riscv |
| [case_019](MultiInt-Bench%20v1.1.1/cases/case_019/case.c) / [case_020](MultiInt-Bench%20v1.1.1/cases/case_020/case.c) | `gd2c4191bb5bd` | arm |
| [case_021](MultiInt-Bench%20v1.1.1/cases/case_021/case.c) / [case_022](MultiInt-Bench%20v1.1.1/cases/case_022/case.c) | `g8e5dc48f9996` | msp430 |
| [case_023](MultiInt-Bench%20v1.1.1/cases/case_023/case.c) / [case_024](MultiInt-Bench%20v1.1.1/cases/case_024/case.c) | `g0234e259a4b9` | arm |
| [case_025](MultiInt-Bench%20v1.1.1/cases/case_025/case.c) / [case_026](MultiInt-Bench%20v1.1.1/cases/case_026/case.c) | `g717d792307b6` | avr |
| [case_027](MultiInt-Bench%20v1.1.1/cases/case_027/case.c) / [case_028](MultiInt-Bench%20v1.1.1/cases/case_028/case.c) | `g4fc635532174` | avr |
| [case_029](MultiInt-Bench%20v1.1.1/cases/case_029/case.c) / [case_030](MultiInt-Bench%20v1.1.1/cases/case_030/case.c) | `gbfb7ab9fd384` | msp430 |
| [case_031](MultiInt-Bench%20v1.1.1/cases/case_031/case.c) / [case_032](MultiInt-Bench%20v1.1.1/cases/case_032/case.c) | `g318422b3284b` | arm |
| [case_033](MultiInt-Bench%20v1.1.1/cases/case_033/case.c) / [case_034](MultiInt-Bench%20v1.1.1/cases/case_034/case.c) | `g1be2ac847508` | msp430 |
| [case_035](MultiInt-Bench%20v1.1.1/cases/case_035/case.c) / [case_036](MultiInt-Bench%20v1.1.1/cases/case_036/case.c) | `g8d938409c3f5` | avr |
| [case_037](MultiInt-Bench%20v1.1.1/cases/case_037/case.c) / [case_038](MultiInt-Bench%20v1.1.1/cases/case_038/case.c) | `g4dd4c499c9b6` | riscv |
| [case_039](MultiInt-Bench%20v1.1.1/cases/case_039/case.c) / [case_040](MultiInt-Bench%20v1.1.1/cases/case_040/case.c) | `gb9f8dfbf047e` | riscv |
| [case_041](MultiInt-Bench%20v1.1.1/cases/case_041/case.c) / [case_042](MultiInt-Bench%20v1.1.1/cases/case_042/case.c) | `ged01b9a22810` | msp430 |
| [case_043](MultiInt-Bench%20v1.1.1/cases/case_043/case.c) / [case_044](MultiInt-Bench%20v1.1.1/cases/case_044/case.c) | `gcc7f3c840813` | arm |
| [case_045](MultiInt-Bench%20v1.1.1/cases/case_045/case.c) / [case_046](MultiInt-Bench%20v1.1.1/cases/case_046/case.c) | `g616e696028a7` | arm |
| [case_047](MultiInt-Bench%20v1.1.1/cases/case_047/case.c) / [case_048](MultiInt-Bench%20v1.1.1/cases/case_048/case.c) | `g3867b620520c` | riscv |
| [case_049](MultiInt-Bench%20v1.1.1/cases/case_049/case.c) / [case_050](MultiInt-Bench%20v1.1.1/cases/case_050/case.c) | `g53f7266e0619` | avr |
| [case_051](MultiInt-Bench%20v1.1.1/cases/case_051/case.c) / [case_052](MultiInt-Bench%20v1.1.1/cases/case_052/case.c) | `g3ae33e04434a` | msp430 |
| [case_053](MultiInt-Bench%20v1.1.1/cases/case_053/case.c) / [case_054](MultiInt-Bench%20v1.1.1/cases/case_054/case.c) | `contiki_clock_seconds_avr` | avr |
| [case_055](MultiInt-Bench%20v1.1.1/cases/case_055/case.c) / [case_056](MultiInt-Bench%20v1.1.1/cases/case_056/case.c) | `contiki_ringbuf_publish_avr` | avr |
| [case_057](MultiInt-Bench%20v1.1.1/cases/case_057/case.c) / [case_058](MultiInt-Bench%20v1.1.1/cases/case_058/case.c) | `riot_tsrb_add_avr` | avr |
| [case_059](MultiInt-Bench%20v1.1.1/cases/case_059/case.c) / [case_060](MultiInt-Bench%20v1.1.1/cases/case_060/case.c) | `riot_tsrb_get_avr` | avr |
| [case_061](MultiInt-Bench%20v1.1.1/cases/case_061/case.c) / [case_062](MultiInt-Bench%20v1.1.1/cases/case_062/case.c) | `riot_tsrb_add_arm` | arm |
| [case_063](MultiInt-Bench%20v1.1.1/cases/case_063/case.c) / [case_064](MultiInt-Bench%20v1.1.1/cases/case_064/case.c) | `contiki_clock_time_avr` | avr |
| [case_065](MultiInt-Bench%20v1.1.1/cases/case_065/case.c) / [case_066](MultiInt-Bench%20v1.1.1/cases/case_066/case.c) | `contiki_ringbuf_publish_arm` | arm |
| [case_067](MultiInt-Bench%20v1.1.1/cases/case_067/case.c) / [case_068](MultiInt-Bench%20v1.1.1/cases/case_068/case.c) | `riot_tsrb_get_arm` | arm |

### Sources and Adaptations by Pair

The original adaptation notes, pinned commits, and upstream line numbers are retained. For line numbers within the dataset, refer to `LABEL.yml`.

#### case_001 / case_002 — contiki_cc2538_queue_peek

Source pair: `g5f9e910ba24d`; Architecture: `arm`; Source category: `source_derived_counterfactual`.

Native index-buffer functions; one interrupt drains two queued elements. The application status table covers indices 0..2. Added application observation sink; control uses checked local snapshot, exposed variant rereads live state at the sink. This is not an upstream-reported defect.

- [`ringbufindex_peek_get`](https://github.com/contiki-os/contiki/blob/32b5b17f674232867c22916bb2e2534c8e9a92ff/core/lib/ringbufindex.c#L114): `core/lib/ringbufindex.c`, upstream line 114; License `BSD-3-Clause`.
- [`ringbufindex_get`](https://github.com/contiki-os/contiki/blob/32b5b17f674232867c22916bb2e2534c8e9a92ff/core/lib/ringbufindex.c#L89): `core/lib/ringbufindex.c`, upstream line 89; License `BSD-3-Clause`.

#### case_003 / case_004 — energia_msp430_gpio_dispatch

Source pair: `gfbfc9c714998`; Architecture: `msp430`; Source category: `source_derived_counterfactual`.

Native digitalRead body and pin-map macros expressed as C helpers; three-pin board subset. An added port event changes the selected application pin; only the exposed caller rereads it after validation.

- [`digitalRead`](https://github.com/energia/Energia/blob/7afdf1ebfeaa06cd0dfee7d4539f076e007ab4e4/hardware/msp430/cores/msp430/wiring_digital.c#L183): `hardware/msp430/cores/msp430/wiring_digital.c`, upstream line 183; License `LGPL-2.1-or-later`.

#### case_005 / case_006 — zephyr_rv32_clic_indirect

Source pair: `g8858cebce50a`; Architecture: `riscv`; Source category: `real_fix_reproducer`.

Patch-grounded reduced reproducer of Zephyr 23bf240. Select the SMCSRIND branch; model MISELECT and MIREG with a two-register volatile bank and the micsr IRQ lock. ISR changes the indirect selector, as described by the upstream fix. Device model, wrapper and IRQ caller are explicit reproducer adaptations, not unchanged full firmware.

Upstream fix: [23bf240be49e06a003d0c49cc462f73580c1a118](https://github.com/zephyrproject-rtos/zephyr/commit/23bf240be49e06a003d0c49cc462f73580c1a118); Pre-fix commit: `037b8fe971bd4a11689b0b1304e66cd4c9cfb39c`.

- [`riscv_clic_irq_set_pending`](https://github.com/zephyrproject-rtos/zephyr/blob/037b8fe971bd4a11689b0b1304e66cd4c9cfb39c/drivers/interrupt_controller/intc_clic.c#L248): `drivers/interrupt_controller/intc_clic.c`, upstream line 248; License `Apache-2.0`.
- [`riscv_clic_irq_set_pending`](https://github.com/zephyrproject-rtos/zephyr/blob/23bf240be49e06a003d0c49cc462f73580c1a118/drivers/interrupt_controller/intc_clic.c#L259): `drivers/interrupt_controller/intc_clic.c`, upstream line 259; License `Apache-2.0`.

#### case_007 / case_008 — zephyr_rv32_stream_ratio

Source pair: `g81493af59b56`; Architecture: `riscv`; Source category: `source_derived_counterfactual`.

Native ring size query; IRQ drains the last byte using the documented get-head ownership. Added application ratio. Added application observation sink; control uses checked local snapshot, exposed variant rereads live state at the sink. This is not an upstream-reported defect.

- [`ring_buf_size_get`](https://github.com/zephyrproject-rtos/zephyr/blob/23bf240be49e06a003d0c49cc462f73580c1a118/include/zephyr/sys/ring_buffer.h#L273): `include/zephyr/sys/ring_buffer.h`, upstream line 273; License `Apache-2.0`.

#### case_009 / case_010 — riot_rv32_message_count_ratio

Source pair: `g7677ee9477ea`; Architecture: `riscv`; Source category: `source_derived_counterfactual`.

Native CIB API in a single consumer-IRQ scenario; count ratio caller is added. This bounded scenario does not claim the original caller API was interrupt-safe. Added application observation sink; control uses checked local snapshot, exposed variant rereads live state at the sink. This is not an upstream-reported defect.

- [`cib_avail`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/core/lib/include/cib.h#L98): `core/lib/include/cib.h`, upstream line 98; License `LGPL-2.1-only`.
- [`cib_get`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/core/lib/include/cib.h#L129): `core/lib/include/cib.h`, upstream line 129; License `LGPL-2.1-only`.

#### case_011 / case_012 — zephyr_rv32_timeout_timestamp

Source pair: `g4cb65a232aa1`; Architecture: `riscv`; Source category: `source_derived_counterfactual`.

Native timeout-expiry API with explicit single-core lock expansion and an inactive timeout. Mutation removes lock acquisition. This shares the Zephyr timeout source family with the ARM getter and is not claimed as an independent project.

- [`z_timeout_expires`](https://github.com/zephyrproject-rtos/zephyr/blob/23bf240be49e06a003d0c49cc462f73580c1a118/kernel/timeout.c#L196): `kernel/timeout.c`, upstream line 196; License `Apache-2.0`.

#### case_013 / case_014 — energia_msp430_tick_capture

Source pair: `g269307add0f1`; Architecture: `msp430`; Source category: `source_derived_counterfactual`.

Native millis getter, uint32_t ABI spelling, watchdog one-millisecond effect. Mutation removes only the interrupt disable, retaining saved-state restore.

- [`millis`](https://github.com/energia/Energia/blob/7afdf1ebfeaa06cd0dfee7d4539f076e007ab4e4/hardware/msp430/cores/msp430/wiring.c#L480): `hardware/msp430/cores/msp430/wiring.c`, upstream line 480; License `LGPL-2.1-or-later`.

#### case_015 / case_016 — contiki_msp430_timer_publication

Source pair: `ga552032e8c7b`; Architecture: `msp430`; Source category: `source_derived_counterfactual`.

Native timer_set and remaining-time functions. Added ISR observer requires interval and start to be published together; control masks the update, mutation removes lock acquisition. Clock is held at 100 during this call.

- [`timer_set`](https://github.com/contiki-os/contiki/blob/32b5b17f674232867c22916bb2e2534c8e9a92ff/core/sys/timer.c#L63): `core/sys/timer.c`, upstream line 63; License `BSD-3-Clause`.
- [`timer_remaining`](https://github.com/contiki-os/contiki/blob/32b5b17f674232867c22916bb2e2534c8e9a92ff/core/sys/timer.c#L141): `core/sys/timer.c`, upstream line 141; License `BSD-3-Clause`.

#### case_017 / case_018 — zephyr_rv32_cycle_snapshot

Source pair: `g2672acd4b78a`; Architecture: `riscv`; Source category: `real_fix_reproducer`.

Reduced reproducer of Zephyr ZEP-1546: explicit MMIO cells replace hardware addresses while preserving clock access, timer rearming, and the ISR body. The clock advances at interrupt boundaries to expose inconsistencies between the accumulated value and the baseline. This sample includes both an atomicity violation and a multiword data race: the 64-bit baseline read can tear, and truncating the return value to 32 bits does not eliminate the multiword nature of the access.

Upstream fix: [97d76cad669a856b4a0b986eb58cc62fff749a90](https://github.com/zephyrproject-rtos/zephyr/commit/97d76cad669a856b4a0b986eb58cc62fff749a90); Pre-fix commit: `be856d4b134c0807870c48f2c9d34fc997fb73f2`.

- [`riscv_machine_rearm_timer`](https://github.com/zephyrproject-rtos/zephyr/blob/be856d4b134c0807870c48f2c9d34fc997fb73f2/drivers/timer/riscv_machine_timer.c#L33): `drivers/timer/riscv_machine_timer.c`, upstream line 33; License `Apache-2.0`.
- [`riscv_machine_timer_irq_handler`](https://github.com/zephyrproject-rtos/zephyr/blob/be856d4b134c0807870c48f2c9d34fc997fb73f2/drivers/timer/riscv_machine_timer.c#L58): `drivers/timer/riscv_machine_timer.c`, upstream line 58; License `Apache-2.0`.
- [`k_cycle_get_32`](https://github.com/zephyrproject-rtos/zephyr/blob/be856d4b134c0807870c48f2c9d34fc997fb73f2/drivers/timer/riscv_machine_timer.c#L98): `drivers/timer/riscv_machine_timer.c`, upstream line 98; License `Apache-2.0`.
- [`riscv_machine_rearm_timer`](https://github.com/zephyrproject-rtos/zephyr/blob/97d76cad669a856b4a0b986eb58cc62fff749a90/drivers/timer/riscv_machine_timer.c#L30): `drivers/timer/riscv_machine_timer.c`, upstream line 30; License `Apache-2.0`.
- [`riscv_machine_timer_irq_handler`](https://github.com/zephyrproject-rtos/zephyr/blob/97d76cad669a856b4a0b986eb58cc62fff749a90/drivers/timer/riscv_machine_timer.c#L54): `drivers/timer/riscv_machine_timer.c`, upstream line 54; License `Apache-2.0`.
- [`k_cycle_get_32`](https://github.com/zephyrproject-rtos/zephyr/blob/97d76cad669a856b4a0b986eb58cc62fff749a90/drivers/timer/riscv_machine_timer.c#L92): `drivers/timer/riscv_machine_timer.c`, upstream line 92; License `Apache-2.0`.

#### case_019 / case_020 — riot_stm32_xtimer_return

Source pair: `gd2c4191bb5bd`; Architecture: `arm`; Source category: `source_derived_counterfactual`.

The original return reads shared uint64_t after restoring IRQs. Control captures that return value inside the existing critical section. Hardware low timer is held fixed for this bounded return-transfer scenario; ISR time-accounting effect is one increment. This is a source-derived candidate with constructed control, not an upstream-confirmed bug.

- [`_xtimer_now64`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/sys/include/xtimer/implementation.h#L104): `sys/include/xtimer/implementation.h`, upstream line 104; License `LGPL-2.1-only`.

#### case_021 / case_022 — energia_msp430_millis_wrap_ratio

Source pair: `g8e5dc48f9996`; Architecture: `msp430`; Source category: `source_derived_counterfactual`.

Fixed-width uint32_t preserves the native MSP430 unsigned-long ABI. Watchdog accounting effect is projected to a one-millisecond increment. IRQ-protected getter is unchanged; the added caller tests and rereads it. Added application observation sink; control uses checked local snapshot, exposed variant rereads live state at the sink. This is not an upstream-reported defect.

- [`millis`](https://github.com/energia/Energia/blob/7afdf1ebfeaa06cd0dfee7d4539f076e007ab4e4/hardware/msp430/cores/msp430/wiring.c#L480): `hardware/msp430/cores/msp430/wiring.c`, upstream line 480; License `LGPL-2.1-or-later`.

#### case_023 / case_024 — contiki_cc2538_pool_availability

Source pair: `g0234e259a4b9`; Architecture: `arm`; Source category: `source_derived_counterfactual`.

Native block-pool functions; IRQ releases a valid allocated block. Analysis application uses free-count as a small status-table selector. Added application observation sink; control uses checked local snapshot, exposed variant rereads live state at the sink. This is not an upstream-reported defect.

- [`memb_numfree`](https://github.com/contiki-os/contiki/blob/32b5b17f674232867c22916bb2e2534c8e9a92ff/core/lib/memb.c#L110): `core/lib/memb.c`, upstream line 110; License `BSD-3-Clause`.
- [`memb_free`](https://github.com/contiki-os/contiki/blob/32b5b17f674232867c22916bb2e2534c8e9a92ff/core/lib/memb.c#L78): `core/lib/memb.c`, upstream line 78; License `BSD-3-Clause`.

#### case_025 / case_026 — contiki_avr_queue_ratio

Source pair: `g717d792307b6`; Architecture: `avr`; Source category: `source_derived_counterfactual`.

Native occupancy calculation and consumer; added foreground ratio application. ISR adapter is one valid buffer consumption, not a transplanted platform template. Added application observation sink; control uses checked local snapshot, exposed variant rereads live state at the sink. This is not an upstream-reported defect.

- [`ringbuf_elements`](https://github.com/contiki-os/contiki/blob/32b5b17f674232867c22916bb2e2534c8e9a92ff/core/lib/ringbuf.c#L118): `core/lib/ringbuf.c`, upstream line 118; License `BSD-3-Clause`.
- [`ringbuf_get`](https://github.com/contiki-os/contiki/blob/32b5b17f674232867c22916bb2e2534c8e9a92ff/core/lib/ringbuf.c#L79): `core/lib/ringbuf.c`, upstream line 79; License `BSD-3-Clause`.

#### case_027 / case_028 — grbl_avr_motion_capacity_lookup

Source pair: `g4fc635532174`; Architecture: `avr`; Source category: `source_derived_counterfactual`.

Native planner helpers; stepper ISR discards one executed block. Reduced ring size and external status lookup are declared adapters. Added application observation sink; control uses checked local snapshot, exposed variant rereads live state at the sink. This is not an upstream-reported defect.

- [`plan_get_block_buffer_available`](https://github.com/gnea/grbl/blob/bfb67f0c7963fe3ce4aaf8a97f9009ea5a8db36e/grbl/planner.c#L498): `grbl/planner.c`, upstream line 498; License `GPL-3.0-or-later`.
- [`plan_next_block_index`](https://github.com/gnea/grbl/blob/bfb67f0c7963fe3ce4aaf8a97f9009ea5a8db36e/grbl/planner.c#L44): `grbl/planner.c`, upstream line 44; License `GPL-3.0-or-later`.
- [`plan_discard_current_block`](https://github.com/gnea/grbl/blob/bfb67f0c7963fe3ce4aaf8a97f9009ea5a8db36e/grbl/planner.c#L215): `grbl/planner.c`, upstream line 215; License `GPL-3.0-or-later`.

#### case_029 / case_030 — contiki_msp430_tick_wrap_ratio

Source pair: `gbfb7ab9fd384`; Architecture: `msp430`; Source category: `source_derived_counterfactual`.

Native timer accessor; timer tick wraps the uint16_t counter. Ratio is an added application sink at the natural rollover boundary. Added application observation sink; control uses checked local snapshot, exposed variant rereads live state at the sink. This is not an upstream-reported defect.

- [`clock_time`](https://github.com/contiki-os/contiki/blob/32b5b17f674232867c22916bb2e2534c8e9a92ff/cpu/msp430/f1xxx/clock.c#L113): `cpu/msp430/f1xxx/clock.c`, upstream line 113; License `BSD-3-Clause`.

#### case_031 / case_032 — riot_stm32_conversion_set

Source pair: `g318422b3284b`; Architecture: `arm`; Source category: `source_derived_counterfactual`.

Concurrent runtime converter reconfiguration is an added context. The native mul/div functions are retained; the protected control masks the update and the mutation restores IRQs before the call.

- [`_integer_div_ceil`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/sys/ztimer/convert_muldiv64.c#L34): `sys/ztimer/convert_muldiv64.c`, upstream line 34; License `LGPL-2.1-only`.
- [`_convert_muldiv64_set`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/sys/ztimer/convert_muldiv64.c#L43): `sys/ztimer/convert_muldiv64.c`, upstream line 43; License `LGPL-2.1-only`.
- [`_convert_muldiv64_now`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/sys/ztimer/convert_muldiv64.c#L58): `sys/ztimer/convert_muldiv64.c`, upstream line 58; License `LGPL-2.1-only`.

#### case_033 / case_034 — contiki_msp430_seconds_snapshot

Source pair: `g1be2ac847508`; Architecture: `msp430`; Source category: `source_derived_counterfactual`.

Native MSP430 32-bit seconds accessor with its retry protocol; fixed-width spelling preserves ABI. Exposed variant removes the validation loop. Timer effects outside incrementing seconds are projected out under the stated one-ISR bound.

- [`clock_seconds`](https://github.com/contiki-os/contiki/blob/32b5b17f674232867c22916bb2e2534c8e9a92ff/cpu/msp430/f1xxx/clock.c#L220): `cpu/msp430/f1xxx/clock.c`, upstream line 220; License `BSD-3-Clause`.

#### case_035 / case_036 — grbl_avr_rx_capacity_ratio

Source pair: `g8d938409c3f5`; Architecture: `avr`; Source category: `source_derived_counterfactual`.

Native capacity calculation with reduced ring capacity. UART byte reception advances the producer by one; payload IO is projected out. Added application observation sink; control uses checked local snapshot, exposed variant rereads live state at the sink. This is not an upstream-reported defect.

- [`serial_get_rx_buffer_available`](https://github.com/gnea/grbl/blob/bfb67f0c7963fe3ce4aaf8a97f9009ea5a8db36e/grbl/serial.c#L37): `grbl/serial.c`, upstream line 37; License `GPL-3.0-or-later`.

#### case_037 / case_038 — riot_rv32_compare_programming

Source pair: `g4dd4c499c9b6`; Architecture: `riscv`; Source category: `source_derived_counterfactual`.

MMIO register addresses are replaced by explicit volatile uint64_t register cells; the native 64-bit store and timer ISR reset are retained. Mutation postpones disabling MTIP until after the split-width compare store. Hardware evolution and callbacks are inactive in this bounded configuration. The added 64-bit observation read is protected in both samples; only the native compare-store protection differs.

- [`timer_set`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/cpu/riscv_common/periph/coretimer.c#L74): `cpu/riscv_common/periph/coretimer.c`, upstream line 74; License `LGPL-2.1-only`.
- [`timer_isr`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/cpu/riscv_common/periph/coretimer.c#L168): `cpu/riscv_common/periph/coretimer.c`, upstream line 168; License `LGPL-2.1-only`.

#### case_039 / case_040 — zephyr_rv32_stream_capacity_lookup

Source pair: `gb9f8dfbf047e`; Architecture: `riscv`; Source category: `source_derived_counterfactual`.

Native free-space query; completing one IRQ-side read increases free capacity from 2 to 3. External table lookup is an added application scenario. Added application observation sink; control uses checked local snapshot, exposed variant rereads live state at the sink. This is not an upstream-reported defect.

- [`ring_buf_space_get`](https://github.com/zephyrproject-rtos/zephyr/blob/23bf240be49e06a003d0c49cc462f73580c1a118/include/zephyr/sys/ring_buffer.h#L235): `include/zephyr/sys/ring_buffer.h`, upstream line 235; License `Apache-2.0`.

#### case_041 / case_042 — contiki_msp430_uart_queue_lookup

Source pair: `ged01b9a22810`; Architecture: `msp430`; Source category: `source_derived_counterfactual`.

Native index-buffer API and valid one-byte receive effect; added application table. Queue storage capacity remains 8 while application lookup accepts values below 3. Added application observation sink; control uses checked local snapshot, exposed variant rereads live state at the sink. This is not an upstream-reported defect.

- [`ringbufindex_elements`](https://github.com/contiki-os/contiki/blob/32b5b17f674232867c22916bb2e2534c8e9a92ff/core/lib/ringbufindex.c#L133): `core/lib/ringbufindex.c`, upstream line 133; License `BSD-3-Clause`.
- [`ringbufindex_put`](https://github.com/contiki-os/contiki/blob/32b5b17f674232867c22916bb2e2534c8e9a92ff/core/lib/ringbufindex.c#L57): `core/lib/ringbufindex.c`, upstream line 57; License `BSD-3-Clause`.

#### case_043 / case_044 — riot_stm32_conversion_now

Source pair: `gcc7f3c840813`; Architecture: `arm`; Source category: `source_derived_counterfactual`.

Concurrent runtime converter reconfiguration is an added context. The native mul/div functions are retained; the protected control masks the update and the mutation restores IRQs before the call.

- [`_integer_div_ceil`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/sys/ztimer/convert_muldiv64.c#L34): `sys/ztimer/convert_muldiv64.c`, upstream line 34; License `LGPL-2.1-only`.
- [`_convert_muldiv64_set`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/sys/ztimer/convert_muldiv64.c#L43): `sys/ztimer/convert_muldiv64.c`, upstream line 43; License `LGPL-2.1-only`.
- [`_convert_muldiv64_now`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/sys/ztimer/convert_muldiv64.c#L58): `sys/ztimer/convert_muldiv64.c`, upstream line 58; License `LGPL-2.1-only`.

#### case_045 / case_046 — zephyr_arm_kernel_tick

Source pair: `g616e696028a7`; Architecture: `arm`; Source category: `source_derived_counterfactual`.

Expand native K_SPINLOCK into its single-core IRQ-save lock/unlock calls; elapsed() is zero in this idle configuration. Exposed variant removes lock acquisition. Timer announce is projected to its one-tick counter effect.

- [`sys_clock_tick_get`](https://github.com/zephyrproject-rtos/zephyr/blob/23bf240be49e06a003d0c49cc462f73580c1a118/kernel/timeout.c#L272): `kernel/timeout.c`, upstream line 272; License `Apache-2.0`.

#### case_047 / case_048 — riot_rv32_pending_slot_lookup

Source pair: `g3867b620520c`; Architecture: `riscv`; Source category: `source_derived_counterfactual`.

Native non-consuming CIB peek returns -1 on empty; IRQ consumes the sole valid entry. The status caller preserves or discards the checked snapshot depending on variant. Added application observation sink; control uses checked local snapshot, exposed variant rereads live state at the sink. This is not an upstream-reported defect. Both samples call the native non-thread-safe CIB peek through an IRQ-save snapshot adapter, honoring the original API exclusivity contract. The exposed caller still rereads that snapshot after checking, whereas the control uses its checked local.

- [`cib_avail`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/core/lib/include/cib.h#L98): `core/lib/include/cib.h`, upstream line 98; License `LGPL-2.1-only`.
- [`cib_peek_at_unsafe`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/core/lib/include/cib.h#L158): `core/lib/include/cib.h`, upstream line 158; License `LGPL-2.1-only`.
- [`cib_peek_at`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/core/lib/include/cib.h#L179): `core/lib/include/cib.h`, upstream line 179; License `LGPL-2.1-only`.
- [`cib_peek`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/core/lib/include/cib.h#L218): `core/lib/include/cib.h`, upstream line 218; License `LGPL-2.1-only`.
- [`cib_get`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/core/lib/include/cib.h#L129): `core/lib/include/cib.h`, upstream line 129; License `LGPL-2.1-only`.

#### case_049 / case_050 — grbl_avr_rx_status_lookup

Source pair: `g53f7266e0619`; Architecture: `avr`; Source category: `source_derived_counterfactual`.

Native occupancy calculation; reduced UART model retains one-byte producer effect. Status-table application is added. Added application observation sink; control uses checked local snapshot, exposed variant rereads live state at the sink. This is not an upstream-reported defect.

- [`serial_get_rx_buffer_count`](https://github.com/gnea/grbl/blob/bfb67f0c7963fe3ce4aaf8a97f9009ea5a8db36e/grbl/serial.c#L47): `grbl/serial.c`, upstream line 47; License `GPL-3.0-or-later`.

#### case_051 / case_052 — contiki_msp430_pool_claim

Source pair: `g3ae33e04434a`; Architecture: `msp430`; Source category: `source_derived_counterfactual`.

Native allocation body with a newly declared two-context caller contract. Control protects the full claim; the mutation drops acquisition so foreground and ISR can claim the same slot. No upstream concurrency guarantee or reported bug is claimed.

- [`memb_alloc`](https://github.com/contiki-os/contiki/blob/32b5b17f674232867c22916bb2e2534c8e9a92ff/core/lib/memb.c#L58): `core/lib/memb.c`, upstream line 58; License `BSD-3-Clause`.

#### case_053 / case_054 — contiki_clock_seconds_avr

Source pair: `contiki_clock_seconds_avr`; Architecture: `avr`; Source category: `retained_source_derived_pair`.

remove the stable-snapshot retry around a multi-byte volatile read

- [`clock_seconds`](https://github.com/contiki-os/contiki/blob/32b5b17f674232867c22916bb2e2534c8e9a92ff/cpu/avr/dev/clock.c#L143): `cpu/avr/dev/clock.c`, upstream line 143; License `BSD-3-Clause`.

#### case_055 / case_056 — contiki_ringbuf_publish_avr

Source pair: `contiki_ringbuf_publish_avr`; Architecture: `avr`; Source category: `retained_source_derived_pair`.

publish the producer index before storing the payload, preserving sequential behavior

- [`ringbuf_init`](https://github.com/contiki-os/contiki/blob/32b5b17f674232867c22916bb2e2534c8e9a92ff/core/lib/ringbuf.c#L43): `core/lib/ringbuf.c`, upstream line 43; License `BSD-3-Clause`.
- [`ringbuf_put`](https://github.com/contiki-os/contiki/blob/32b5b17f674232867c22916bb2e2534c8e9a92ff/core/lib/ringbuf.c#L52): `core/lib/ringbuf.c`, upstream line 52; License `BSD-3-Clause`.
- [`ringbuf_get`](https://github.com/contiki-os/contiki/blob/32b5b17f674232867c22916bb2e2534c8e9a92ff/core/lib/ringbuf.c#L79): `core/lib/ringbuf.c`, upstream line 79; License `BSD-3-Clause`.

#### case_057 / case_058 — riot_tsrb_add_avr

Source pair: `riot_tsrb_add_avr`; Architecture: `avr`; Source category: `retained_source_derived_pair`.

move irq_restore before the protected cross-function buffer operation

- [`turb_full`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/sys/include/turb.h#L71): `sys/include/turb.h`, upstream line 71; License `LGPL-2.1-only`.
- [`_turb_push`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/sys/include/turb.h#L91): `sys/include/turb.h`, upstream line 91; License `LGPL-2.1-only`.
- [`turb_add_one`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/sys/include/turb.h#L200): `sys/include/turb.h`, upstream line 200; License `LGPL-2.1-only`.
- [`tsrb_add_one`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/sys/tsrb/tsrb.c#L64): `sys/tsrb/tsrb.c`, upstream line 64; License `LGPL-2.1-only`.

#### case_059 / case_060 — riot_tsrb_get_avr

Source pair: `riot_tsrb_get_avr`; Architecture: `avr`; Source category: `retained_source_derived_pair`.

move irq_restore before the protected cross-function buffer operation

- [`turb_empty`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/sys/include/turb.h#L46): `sys/include/turb.h`, upstream line 46; License `LGPL-2.1-only`.
- [`_turb_pop`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/sys/include/turb.h#L96): `sys/include/turb.h`, upstream line 96; License `LGPL-2.1-only`.
- [`turb_get_one`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/sys/include/turb.h#L114): `sys/include/turb.h`, upstream line 114; License `LGPL-2.1-only`.
- [`tsrb_get_one`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/sys/tsrb/tsrb.c#L24): `sys/tsrb/tsrb.c`, upstream line 24; License `LGPL-2.1-only`.

#### case_061 / case_062 — riot_tsrb_add_arm

Source pair: `riot_tsrb_add_arm`; Architecture: `arm`; Source category: `retained_source_derived_pair`.

move irq_restore before the protected cross-function buffer operation

- [`turb_full`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/sys/include/turb.h#L71): `sys/include/turb.h`, upstream line 71; License `LGPL-2.1-only`.
- [`_turb_push`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/sys/include/turb.h#L91): `sys/include/turb.h`, upstream line 91; License `LGPL-2.1-only`.
- [`turb_add_one`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/sys/include/turb.h#L200): `sys/include/turb.h`, upstream line 200; License `LGPL-2.1-only`.
- [`tsrb_add_one`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/sys/tsrb/tsrb.c#L64): `sys/tsrb/tsrb.c`, upstream line 64; License `LGPL-2.1-only`.

#### case_063 / case_064 — contiki_clock_time_avr

Source pair: `contiki_clock_time_avr`; Architecture: `avr`; Source category: `retained_source_derived_pair`.

remove the stable-snapshot retry around a multi-byte volatile read

- [`clock_time`](https://github.com/contiki-os/contiki/blob/32b5b17f674232867c22916bb2e2534c8e9a92ff/cpu/avr/dev/clock.c#L128): `cpu/avr/dev/clock.c`, upstream line 128; License `BSD-3-Clause`.

#### case_065 / case_066 — contiki_ringbuf_publish_arm

Source pair: `contiki_ringbuf_publish_arm`; Architecture: `arm`; Source category: `retained_source_derived_pair`.

publish the producer index before storing the payload, preserving sequential behavior

- [`ringbuf_init`](https://github.com/contiki-os/contiki/blob/32b5b17f674232867c22916bb2e2534c8e9a92ff/core/lib/ringbuf.c#L43): `core/lib/ringbuf.c`, upstream line 43; License `BSD-3-Clause`.
- [`ringbuf_put`](https://github.com/contiki-os/contiki/blob/32b5b17f674232867c22916bb2e2534c8e9a92ff/core/lib/ringbuf.c#L52): `core/lib/ringbuf.c`, upstream line 52; License `BSD-3-Clause`.
- [`ringbuf_get`](https://github.com/contiki-os/contiki/blob/32b5b17f674232867c22916bb2e2534c8e9a92ff/core/lib/ringbuf.c#L79): `core/lib/ringbuf.c`, upstream line 79; License `BSD-3-Clause`.

#### case_067 / case_068 — riot_tsrb_get_arm

Source pair: `riot_tsrb_get_arm`; Architecture: `arm`; Source category: `retained_source_derived_pair`.

move irq_restore before the protected cross-function buffer operation

- [`turb_empty`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/sys/include/turb.h#L46): `sys/include/turb.h`, upstream line 46; License `LGPL-2.1-only`.
- [`_turb_pop`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/sys/include/turb.h#L96): `sys/include/turb.h`, upstream line 96; License `LGPL-2.1-only`.
- [`turb_get_one`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/sys/include/turb.h#L114): `sys/include/turb.h`, upstream line 114; License `LGPL-2.1-only`.
- [`tsrb_get_one`](https://github.com/RIOT-OS/RIOT/blob/46fac72c1fb9417632664236349c670e65541d24/sys/tsrb/tsrb.c#L24): `sys/tsrb/tsrb.c`, upstream line 24; License `LGPL-2.1-only`.
