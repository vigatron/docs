# Project VideoCARD 2008

| Property          | Value                       |
|-------------------|-----------------------------|
| Device Released   | Feb 2008                    |
| Author            | Viktor Glebov (V01G04A81)   |
| Series            | Small Series (x3) Prototype |


## Embedded Videocard

| Component            | Specification / Notes          |
|----------------------|--------------------------------|
| MCU                  | AT91SAM7X256                   |
| CPLD (x2)            | XC95144XL                      |
| SRAM (x2)            | 512K, 10 ns each               |
| Storage              | SD-CARD Interface              |
| Video Output         | VGA Interface                  |
| Optional Video Out   | PAL / NTSC                     |
| Connectivity         | USB Interface                  |
| Infrared             | IrDA Receiver                  |



## Video-Mode

* (A) Resolution: 640 x 480, 8-bit color
* (B) Resolution: 320 x 240, 8-bit color


### PCB Layout

<a href="pics/Video2008_PCB.JPG"><img src="pics/Video2008_PCB.JPG" /></a>
<em>PCB Layout</em>

### PCB Layout 3D

<a href="pics/Video2008_PCB3D.JPG"><img src="pics/Video2008_PCB3D.JPG" /></a>
<em>PCB 3D Viewer</em>

### Assembly

<a href="pics/Video2008_DVC.JPG"><img src="pics/Video2008_DVC.JPG" /></a>
<em>After Soldering Process </em>


---
### Уточнение по видеокарте

"Проект экспериментальный, CPLD использовались для упрощённой графики, полноценного GPU не было."

##### Вопрос ( от ИИ для уточнения )
> Какая именно модель FPGA использовалась в проекте «Автонавигатор» 2007 года?
    В тексте упомянута XC95144XL (это CPLD), а в задачах — VHDL и отрисовка графики,
    что для такой маленькой CPLD является нетривиальной задачей без внешнего контроллера.
    Был ли там полноценный графический чип?

##### Ответ
> на плате установлено 2 CPLD чипа - один отрисовывает текущее окно,
    второй чип получает команды от процессора - буффер, потом оба CPLD синхронизируют содержимое.


##### Вопрос
> Как была реализована передача данных между CPLD? Использовалась общая шина данных к SRAM,
    или CPLD #1 передавала инструкции напрямую в CPLD #2 через выделенные линии синхронизации?

##### Ответ
> у каждой CPLD - свой SRAM банк. Второй CPLD регулярно отрисовывает картинку на выходе ( VGA ),
    первый - принимает содержание от MCU. В момент синхронизации - первый CPLD дублирует
    содержимое через параллельную шину в CPLD #2

---

<table>
  <tr>
    <td align="center">
      <a href="pics/Video2008_ALL.jpg">
        <img src="pics/Video2008_ALL.jpg" />
      </a><br><em>Demo Screens</em>
    </td>
    <td align="center">
      <a href="pics/Video2008_UnderTests.jpg">
        <img src="pics/Video2008_UnderTests.jpg" width="80%" />
      </a><br><em>Device under tests</em>
    </td>
  </tr>
</table>

---

Related Links :

[Avtonavi 2008 Board Details](https://github.com/vigatron/docs/tree/main/projects/autonavi2008)


---
2008 Viktor Glebov V01G04A81
