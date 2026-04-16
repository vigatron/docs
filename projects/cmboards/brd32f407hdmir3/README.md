
# BRD32F407HDMIR3 Board

| Property          | Value                       |
|-------------------|-----------------------------|
| Designed          | Jul 2020                    |
| Device Released   | Sep 2020                    |
| Author            | Viktor Glebov (V01G04A81)   |
| Series            | Prototype / x10 units       |

Hybrid MCU+FPGA development board with real-time HDMI video output capability.

---

## Key Features

- **MCU:** STM32F407 (ARM Cortex-M4)
- **FPGA:** Xilinx XC6SLX9 (Spartan-6)
- **SDRAM:** 32 MB (Samsung K4S281632D)
- **FLASH:** 128 Mbit SPI Flash (W25Q128)
- **Storage:** SD Card (SPI/SDIO interface)
- **Extension:** 12 high-speed GPIO / expansion pins
- **Video Output:** HDMI (FPGA-based TMDS encoder, real-time video generation)
- **MCU–FPGA Interface:** high-speed parallel bus / FSMC


## Overview

The **BRD32F407HDMIR3** board is designed for applications that require tight coupling between a microcontroller (control, firmware, and peripherals) and FPGA fabric (real-time processing and video generation), with direct HDMI output driven by the FPGA.

This architecture enables separation of high-level logic and time-critical hardware tasks, allowing deterministic real-time behavior and flexible system design.

Typical use cases include:

- Real-time video signal generation (HDMI output, custom timing)
- Hardware-accelerated graphics and image processing
- Retro-style video systems and custom display controllers
- Embedded UI with FPGA-driven display pipeline
- Mixed MCU–FPGA systems with deterministic real-time behavior

The board is particularly suited for building custom video pipelines without external video controllers.

---

**PCB Layout / Top Layer**

<img src="pics/stm32f4hdm_pcblay_top.png" width="640px"/>

**Assembled Device**

<img src="pics/stm32f4dgm_photoh0.jpg" width="640px"/>

**3D Model Top View**

<img src="pics/stm32f4hdm_top3d.png" width="640px"/>

**3D Model Bottom View**

<img src="pics/stm32f4hdm_bot3d.jpg" width="640px"/>



## Documentation

- [.cells format description](https://vigatron.github.io/formats/cells) — custom tile-based format for graphics and video processing

---

2020 Viktor Glebov (V01G04A81)