# File Format Description 'cells'

| Props | Info |
|----------------|---------------------------------|
| Автор          | Viktor Glebov (V01G04A81)       |
| File Format    | `*.cells`                       |
| File size      | 16384 bytes (16 KB)             |
| Structure      | - 256 tiles <br>- Tile size: 8x8 pixels<br>- Pixel format: HRGB2222 (8-bit) |
| Tile size      | 8x8 pixels                      |
| Bytes/Tile row | 8 bytes                         |

---

## Описание


Файл с расширением `.cells` представляет собой бинарное представление видеоданных,
организованное в специализированном построчном layout,
производном от содержимого видеопамяти и используемом в платформе CMBoards (STM32 + FPGA + SDRAM).
 

Файл содержит фиксированный набор из 256 тайлов,
каждый размером 8×8 пикселей с форматом 8 бит на пиксель.


Особенностью данного формата является построчная организация данных:
каждая строка (scanline) всех 256 тайлов содержит 256 × 8 пикселей = 2048 байт (0x800)

---

## Видео - Демонстрация 

[![Смотреть видео](https://img.youtube.com/vi/6Itho-f9JyU/0.jpg)](https://www.youtube.com/watch?v=6Itho-f9JyU)

---

## Зачем нужен этот формат?
- Оптимизирован для построчного доступа к SDRAM
- Позволяет считывать строки всех 256 тайлов за одну burst-операцию
- Идеально подходит для конвейеров рендеринга на базе FPGA

---

## Примеры

<table>
  <tr>
    <td align="center">
      <a href="example1.png">
        <img src="example1.png" alt="cells example 1" width="512"/>
      </a><br><em>Пример #1<br>256 cells 8x8</em>
    </td>
    <td align="center">
      <a href="example2.png">
        <img src="example2.png" alt="cells example 2" width="512"/>
      </a><br><em>Пример #2<br>256 cells 8x8</em>
    </td>

  </tr>
</table>

---

### Pixel Format

Формат пикселя: **HRGB2222 (8 бит)**

Битовая структура (MSB → LSB):

bit 7-6 : H  (2 бита, назначение определяется аппаратной реализацией)  
bit 5-4 : R  (2 бита, красный)  
bit 3-2 : G  (2 бита, зелёный)  
bit 1-0 : B  (2 бита, синий)  

Порядок пикселей в строке тайла: слева направо (от младшего адреса к старшему).

Биты H (bit 7-6) используются как модификатор цвета.
При преобразовании в RGB они формируют XOR-маску (COLXOR),
которая применяется к значениям каналов R, G и B после их расширения до 4 бит
и перед финальным расширением до 8 бит.


---

### Color Conversion

Преобразование 8-бит uint8_t в 24-бит RGB 8:8:8 - CLR32RGB(V) 

**vhcolors.hpp**

```cpp
#pragma once

#include <stdint.h>

#define COL2B(X, SHL)   ( ( (X) >> SHL ) & 3 )
#define COLDBL(C2B)     ( ( (C2B) << 2 ) | (C2B) )
#define COLQRT(C4B)     ( ( (C4B) << 4 ) | (C4B) )
#define COLXOR(X)       ( ( ( (X) >> 5) & 4 ) | ( ( (X) >> 5) & 2) )
#define COLF8(X,N)      COLQRT( ( COLDBL( COL2B(X,N) )  ^ COLXOR(X) ) )
#define CLRR8(X)        COLF8((X), 4)
#define CLRG8(X)        COLF8((X), 2)
#define CLRB8(X)        COLF8((X), 0)
#define CLRSH(X,N)      ((X)<<N)
#define CLR32RGB(X)     (CLRSH(CLRR8(X),  0) | CLRSH(CLRG8(X), 8) | CLRSH(CLRB8(X), 16))
#define CLR32BGR(X)     (CLRSH(CLRR8(X), 16) | CLRSH(CLRG8(X), 8) | CLRSH(CLRB8(X),  0))
#define SWAPRB(X)       ( ( ( X & 0xFF ) << 16) | ( X & 0xFF00) | ( (X>>16) & 0xFF ) )
```

---
### Memory Layout


Row 0: [tile0][tile1][tile2] ... [tile255]
Row 1: [tile0][tile1][tile2] ... [tile255]

Примеры:

    Tile #0,  row 0: offset = 0 * 0x800 +  0 * 8
    Tile #2,  row 2: offset = 2 * 0x800 +  2 * 8
    Tile #5,  row 3: offset = 3 * 0x800 +  5 * 8
    Tile #42, row 7: offset = 7 * 0x800 + 42 * 8
    ...

Первая строка всех 256 тайлов находится по адресу 0x0000, вторая 0x0800, третья 0x1000 ...

Смещение (offset) вычисляется по формуле:

    offset = row * 0x800 + tile_index * 8

Где:

    - row = 0..7
    - tile_index = 0..255


---

## Особенности конфигурации SDRAM

Формат оптимизирован для последовательного burst-доступа SDRAM.
После активации строки (ACTIVATE) данные могут считываться непрерывно,
при этом количество одновременно считываемых тайлов зависит от ширины шины памяти :

- 1x SDRAM x16 — за непрерывный burst покрывается до 64 тайлов
- 1x SDRAM x32 — до 128 тайлов
- 2x SDRAM x32 — до 256 тайлов


<table>
  <tr>
    <td align="center">
      <a href="sdram16s_pins.png">
        <img src="sdram16s_pins.png" alt="SDRAM 16-bit pinout" width="620"/>
      </a><br><em>SDRAM 16-bit</em>
    </td>
    <td align="center">
      <a href="sdram32s_pins.png">
        <img src="sdram32s_pins.png" alt="SDRAM 32-bit pinout" width="410"/>
      </a><br><em>SDRAM 32-bit</em>
    </td>
  </tr>
</table>

<table>
  <tr>
    <td align="center">
      <a href="sdram_io.png">
        <img src="sdram_io.png" alt="SDRAM read/write diagram" width="1060"/>
      </a><br><em>SDRAM Read / Write</em>
    </td>
  </tr>
</table>


---

### CMBoards configuration:

CMBoards — custom hardware platform based on STM32 MCU + Xilinx FPGA + external SDRAM.

* CMBoards HDM32F407HDMI : STM32F407 + XC6SLX9  + 1x SDRAM x16 + HDMI_OUT
* CMBoards HDM32F746HDMI : STM32F746 + XC6SLX9  + 1x SDRAM x32 + HDMI_OUT
* CMBoards HDM32H750HDMI : STM32F750 + XC6SLX9  + 1x DDR   x32 + HDMI_OUT
* CMBoards HDM32F746TFT7 : STM32F746 + XC6SLX16 + 2x SDRAM x32 + TFT7_800_480
* CMBoards HDM32H750TFT7 : STM32H750 + XC6SLX16 + 1x DDR   x32 + TFT7_800_480

---


### Ограничения

- Размер файла фиксирован: 16384 байта
- Данные хранятся без сжатия

---
Links : 

[BRD32F407HDMIR3 Board Details](https://vigatron.github.io/projects/cmboards/brd32f407hdmir3/)


---


##### Tags

> Streaming-optimized tile layout for SDRAM-based rendering pipelines

- FPGA
- SDRAM
- Tile-based rendering
- Tile graphics format
- 2D graphics pipeline
- Embedded graphics
- Memory-efficient layout
- Cache-friendly layout
- Burst-friendly data layout
- Low-latency rendering
- Scanline-oriented layout
- Row-interleaved tiles
- Hardware-friendly format
- Zero-seek renderer
- Predictable latency pipeline
- Real-time rendering systems

---
2020-2026 Viktor Glebov (V01G04A81)