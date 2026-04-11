# File Format Description 'cells'

| Props | Info |
|----------------|---------------------------------|
| Автор          | Viktor Glebov (V01G04A81)       |
| File Format    | `*.cells`                       |
| File size      | 16384 bytes (16 KB)             |
| Structure      | - 256 tiles <br>- Tile size: 8x8 pixels<br>- Pixel format: HRGB2222 (8-bit) |
| Tile width     | 8 pixels = 8 bytes              |

### Pixel Format

Формат пикселя: **HRGB2222 (8 бит)**

Битовая структура (MSB → LSB):

bit 7-6 : H  (2 бита, назначение определяется аппаратной реализацией)
bit 5-4 : R  (2 бита, красный)
bit 3-2 : G  (2 бита, зелёный)
bit 1-0 : B  (2 бита, синий)

Порядок пикселей в строке тайла: слева направо (от младшего адреса к старшему).

## Описание

Файл с расширением `.cells` представляет собой бинарный дамп участка видеопамяти,
используемый в платформе CMBoards (STM32 + FPGA + SDRAM).

Файл содержит фиксированный набор из 256 тайлов,
каждый размером 8×8 пикселей с форматом 8 бит на пиксель.

Особенностью данного формата является построчная организация данных:
каждая строка всех тайлов занимает 256 × 8 = 1024 байта (0x400)

Первая строка всех 256 тайлов находится по адресу 0x0000, вторая 0x0400, третья 0x0800 ...
Смещение (offset) вычисляется по формуле:

    offset = row * 0x400 + tile_index * 8

Где:

    - row = 0..7
    - tile_index = 0..255


### Memory Layout


Row 0: [tile0][tile1][tile2] ... [tile255]
Row 1: [tile0][tile1][tile2] ... [tile255]

Примеры:

    Tile #0,  row 0: offset = 0 * 0x400 +  0 * 8
    Tile #2,  row 2: offset = 2 * 0x400 +  2 * 8
    Tile #5,  row 3: offset = 3 * 0x400 +  5 * 8
    Tile #42, row 7: offset = 7 * 0x400 + 42 * 8
    ...



## Зачем нужен этот формат?
- Оптимизирован для построчного доступа к SDRAM
- Позволяет считывать строки всех 256 тайлов за одну burst-операцию
- Идеально подходит для конвейеров рендеринга на базе FPGA


## Примеры дампов

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

## Особенности конфигурации SDRAM

Команда SDRAM ACTIVATE ROW позволяет:

- 1x SDRAM x16 — считать одну строку для 64 тайлов
- 1x SDRAM x32 — считать одну строку для 128 тайлов
- 2x SDRAM x32 — считать одну строку для всех 256 тайлов


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


### CMBoards configuration:

CMBoards — custom hardware platform based on STM32 MCU + Xilinx FPGA + external SDRAM.

* CMBoards HDM32F407HDMI : STM32F407 + XC6SLX9  + 1x SDRAM x16 + HDMI_OUT
* CMBoards HDM32F746HDMI : STM32F746 + XC6SLX9  + 1x SDRAM x32 + HDMI_OUT
* CMBoards HDM32H750HDMI : STM32F750 + XC6SLX9  + 1x DDR   x32 + HDMI_OUT
* CMBoards HDM32F746TFT7 : STM32F746 + XC6SLX16 + 2x SDRAM x32 + TFT7_800_480
* CMBoards HDM32H750TFT7 : STM32H750 + XC6SLX16 + 1x DDR   x32 + TFT7_800_480

### Ограничения

- Размер файла фиксирован: 16384 байта
- Данные хранятся без сжатия
- Выравнивание отсутствует (плотная упаковка)