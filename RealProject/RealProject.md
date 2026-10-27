# RealProject: Real Firmware Project Defect Dataset

This dataset contains **3 real firmware projects with 6 defect annotations**: 3 atomicity violations, 1 interrupt-related division by zero, and 2 multiword data races.

| Project source | Application | Platform | Defect annotations | License |
|---|---|---|---|---|
| [Blue Pill](https://github.com/r2axz/bluepill-serial-monster) | Three-port USB-to-serial firmware | STM32F103xB / Cortex-M3, 32-bit ARM | 1 atomicity violation, 1 division by zero | MIT |
| [MYND](https://github.com/teufelaudio/mynd-firmware) | Speaker firmware | STM32F072xB / Cortex-M0, 32-bit ARM | 1 atomicity violation, 1 multiword data race | MIT |
| [NanoVNA](https://github.com/ttrftech/NanoVNA) | Handheld vector network analyzer | STM32F072xB / Cortex-M0, 32-bit ARM | 1 atomicity violation, 1 multiword data race | GPL-3.0-or-later |


## Project Sources and Fault Injection Mapping

Project URLs are taken from the original source records. Licenses are based on each project's LICENSE file or source declarations; third-party components retain their own licenses.

| Case ID | Directory/source | Local license evidence | Platform |
|---|---|---|---|
| `bluepill_serial_monster` | [bluepill-serial-monster](https://github.com/r2axz/bluepill-serial-monster) → `RealProject/bluepill-serial-monster-main` | [MIT LICENSE](RealProject/bluepill-serial-monster-main/LICENSE) | Cortex-M3 / STM32F103xB, 32-bit |
| `mynd_firmware` | [mynd-firmware](https://github.com/teufelaudio/mynd-firmware) → `RealProject/mynd-firmware-main` | [MIT LICENSE](RealProject/mynd-firmware-main/LICENSE) | Cortex-M0 / STM32F072xB, 32-bit |
| `nanovna_main` | [NanoVNA](https://github.com/ttrftech/NanoVNA) → `RealProject/ttrftech__NanoVNA-main` | [main.c source declaration](RealProject/ttrftech__NanoVNA-main/main.c): GPL-3.0-or-later | Cortex-M0 / STM32F072xB, 32-bit |

