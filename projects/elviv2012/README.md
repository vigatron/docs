### electro-lviv.com 2013-2015 / PCB Gerber Visualization Project

<br>

| Property          | Value                       |
|-------------------|-----------------------------|
| Started on        | Apr 2013                    |
| First published   | Nov 2013 (Demo)             |
| Stable version    | Jun 2014                    |
| Author            | Viktor Glebov (V01G04A81)   |
| Language          | PHP / JavaScripts           |

<br>

#### Gerber (RS-274X) and Excellon Parsing Libraries

The implementation supports basic interpretation of PCB manufacturing data, including:
- Aperture definitions and drawing primitives (Gerber)
- Coordinate parsing and tool handling (Excellon)
- Layer data extraction for further visualization or analysis
- Preprocessing for pseudo-3D rendering and web-based viewers

These libraries were developed as part of a web-based PCB visualization and analysis toolchain.

This repository contains PHP and JavaScript libraries for parsing and processing Gerber (RS-274X) and Excellon (drill) files.

- [View source code](https://github.com/vigatron/vigatron.github.io/tree/main/projects/elviv2012/src_gcode_part/)

<br><br>

<table>
  <tr>
    <td align="center">
      <a href="pics_web/pcb3dvis.png">
        <img src="pics_web/pcb3dvis.png" width="400"><br>
        <b>PCB 3D Visualization</b>
      </a>
    </td>
    <td align="center">
      <a href="pics_web/icsdb.png">
        <img src="pics_web/icsdb.png" width="400"><br>
        <b>BOM Manager</b>
      </a>
    </td>
  </tr>
</table>

<table>
  <tr>
    <td align="center">
      <a href="pics_web/gcode1.png">
        <img src="pics_web/gcode1.png" width="400"><br>
        <b>Gerber Files Viewer</b>
      </a>
    </td>
    <td align="center">
      <a href="pics_web/gcode2.png">
        <img src="pics_web/gcode2.png" width="400"><br>
        <b>Gerber Files Viewer (Zoom)</b>
      </a>
    </td>
  </tr>
</table>


<br><br><br>


---


### AT91Giga Board ( Own project )

| Property          | Value                       |
|-------------------|-----------------------------|
| Started on        | Aug 2013                    |
| Author            | Viktor Glebov (V01G04A81)   |


#### Multi-Architecture Emulator Board

<br>

<p>
  <a href="pics/armmcugiga.png"><img src="pics/armmcugiga.png" width="600" alt="ARMGiga Board" /></a><br>
  <em>AT91Giga Board : Year: 2012-2013 </em>
</p>

<br>

&bull; <b>Hardware Stack:</b> ARM 32-bit MCU + FPGA + HDMI Output + SD Card Storage.

&bull; <b>Emulation Targets:</b> 
<ul>
    <li><b>Planned Support:</b> Designed for emulation of <b>x86</b>, <b>MOS 6502</b>, <b>Zilog Z80</b>, and <b>ATmega</b> architectures.</li>
    <li><b>Current Implementation:</b> Partial emulation achieved for <b>x86</b> and <b>ATmega</b> cores.</li>
</ul>

&bull; <b>Technical Progress:</b> 
<ul>
    <li><b>x86 Core:</b> Instruction set is partially implemented; currently developing <b>IRQ handling</b> and system timers.</li>
    <li><b>Status:</b> Project is temporarily <b>on hold</b> due to workload and priority tasks.</li>
    <li><b>Future Goals:</b> Achieving stable BIOS POST and basic DOS compatibility.</li>
</ul>


<br>

---

<br><br><br>


## Diesel Motor Controller (HOPA Motortuning GmbH / Optimex Import Export GmbH)

| Property          | Value                       |
|-------------------|-----------------------------|
| Started on        | Dec 2013                    |
| Gerbers Completed | Feb 2014                    |
| Author            | Viktor Glebov (V01G04A81)   |


&bull; PCB layout design  
&bull; Production Test Software & QA  

<br><br><br>


<table>
  <tr>
    <td align="center">
      <a href="pics_hopa/hpc_dev.JPG">
        <img src="pics_hopa/hpc_dev.JPG" height="500" alt="Device"><br>
        <b>Device</b>
      </a>
    </td>
    <td align="center">
      <a href="pics_hopa/HPC_From_Factory.png">
        <img src="pics_hopa/HPC_From_Factory.png" height="500" alt="Serie x5"><br>
        <b>Serie x5</b>
      </a>
    </td>
  </tr>
</table>


<br><br><br>

---

<br><br><br>


## GPS Tracker (Taxi / Dubai)

| Property           | Value                       |
|--------------------|-----------------------------|
| Started on         | Sep 2014                    |
| Gerbers Completed  | Dec 2014                    |
| Embedded Software  | Feb 2015                    |
| GUI Tools & Config | Mar 2015                    |
| Tests on           | Apr 2015                    |
| Author 1           | V01G04A81                   |
| Author 2           | Sprk81                      |

<br>

&bull; Designed full hardware platform (STM32 + SD + audio subsystem)  
&bull; Integrated MP3/FM functionality (client requirement)  
&bull; Developed PC-side configuration tool (USB)  

<br>

<p>
<img src="pics_dubai/GPSTrackDevice.png" height="400" alt="Device"><br>
</p>


#### Hardware
* STM32F407
* SD-Card Interface / SPI
* UDA1334 / I2S
* FM Transmitter / I2S
* Serial Flash 16Mb
* USART / GPS
* USB Interface ( STM32-based )


#### Software
* FreeRTOS
* MP3 Decoder Library
* FatFs library
* USB device interface
* GPS / NMEA message Parser / USART
* SD Card & SPI Serial Flash drivers


#### Configuration tool

* GUI / Microsoft C# 
* System Diagnostic & Configuration
* Upload MP3 files via USB Interface
* Download GPS binary data blocks

---


<table>
  <tr>
    <td>
    <img src="pics_dubai/pcb_top.jpg" height="240" alt="Device"><br>
    </td>
    <td>
    <img src="pics_dubai/gerbv_v1p0.png" height="240" alt="Device"><br>
    </td>
    <td>
    <img src="pics_dubai/pcb_bot.jpg" height="240" alt="Device"><br>
    </td>
  </tr>
</table>


<table>
  <tr>
    <td>
      <a href="pics_dubai/scr_dubai1.png">
        <img src="pics_dubai/scr_dubai1.png" height="300"><br>
        <b>Device</b>
      </a>
    </td>
    <td>
      <a href="pics_dubai/scr_dubai2.png">
        <img src="pics_dubai/scr_dubai2.png" height="300"><br>
        <b>Serie x5</b>
      </a>
    </td>
    <td>
      <a href="pics_dubai/scr_dubai3.png">
        <img src="pics_dubai/scr_dubai3.png" height="300"><br>
        <b>3D Model</b>
      </a>
    </td>
  </tr>
</table>


<table>
  <tr>
    <td>
    <img src="pics_dubai/scr_enclosure_1.png" height="300"><br>
    </td>
    <td>
    <img src="pics_dubai/post_hk4.png" height="300"><br>
    </td>
    <td>
    <img src="pics_dubai/post_hk3.png" height="300"><br>
    </td>
  </tr>
</table>



<br><br><br>

---

<br><br><br>

## Stereo Camera (own project)

| Property           | Value                       |
|--------------------|-----------------------------|
| Started on         | Aug 2014                    |
| Author             | Viktor Glebov (V01G04A81)   |


&bull; Designed system architecture: STM32 + FPGA + SDRAM  
&bull; Dual synchronized camera interface  
&bull; HDMI output + WiFi module integration  

<p>
<img src="pics_cam/stereocam_present.png" height="1200" alt="Device">
</p>

#### Hardware

&bull; STM32F746  
&bull; XC6SLX16  
&bull; MT48LC16M16A2P-6A x2  
&bull; HDMI Output  
&bull; Micro SD-Card  
&bull; USB Interface  


#### Software

&bull; FreeRTOS  
&bull; Verilog / Testbenches  

#### Key Functionalities


&bull; <b>Traffic Sign Recognition (TSR):</b> Real-time detection and classification of road signs.  
&bull; <b>Spatial Estimation:</b> High-precision distance measurement to obstacles using stereo-vision disparity maps.  
&bull; <b>Lane Detection & Classification:</b> Identification of road markings and lane boundary types.  

<br>

#### Example

<p>
<img src="pics_cam/roadsigns.jpg" height="350" alt="Device">
</p>


<br><br><br>

---

<br><br><br>


## 3-Axis CNC Controller | Proprietary High-Performance Platform

| Property           | Value                                           |
|--------------------|-------------------------------------------------|
| Start Date         | February 2015                                   |


**Contributors:**
- **V01G04A81** — system architecture, hardware design, embedded software development  
- **Sprk81** — hardware abstraction layer (HAL) design, low-level drivers (initial implementation)  
- **GMad** — sensors integration, mechanical system consulting  

<i><b>Full-cycle hardware/firmware development with custom "Engrave Version" for client use.</b></i>

&bull; <b>System Ownership:</b> Independently developed a proprietary motion control architecture (STM32 + FPGA + L6472).  

&bull; <b>Custom Implementation:</b> Engineered a specialized "Engrave Version" tailored to specific client requirements for precision engraving.  

&bull; <b>Architectural Innovation:</b>

+ Transitioned from legacy AVR systems to a high-speed hybrid processing model (proposed Feb 2015).

+ Leveraged FPGA for hardware-level pulse generation to ensure zero-jitter motion control.

&bull; <b>Design Standards:</b> Developed based on STMicroelectronics and Avnet industrial reference designs, ensuring robust EMI/EMC performance.

    Retained full IP rights for the core hardware architecture while delivering a licensed functional module for the client's engraving equipment.


#### Hardware

&bull; STM32F407  
&bull; XC6SLX9  
&bull; MT48LC16M16A2P-75  
&bull; L6472 x3  
&bull; Extension I/O port  

<i>Status: Gerbers Sent to production 13 Apr 2015</i>

#### Software
&bull; FreeRTOS  
&bull; App core  
&bull; STM32 peripheral drivers  
&bull; L6472 drivers  
&bull; VHGUI2016 @ 800x480 port (over SPI, draft)  
&bull; Verilog / Testbenches  

#### Notes

&bull;  <b>GUI Framework Development:</b>  Iterative evolution of the proprietary interface: VHGUI (v.2004 → v.2008 → v.2012 → v.2016).
<br>

&bull; <b>Software Releases:</b>

+ <b>v1.0 "Engraver" (Jun 2015):</b> Successful deployment of the functional draft for engraving operations.
+ <b>v2.0 "CNC Pro" (Jan–Apr 2016):</b> Advanced professional version focused on complex 3-axis machining (Stable Beta).

&bull; <b>License Management:</b> Designed and deployed a dedicated <b>License Validation Server</b> (electro-lviv.com/electro-soft) to manage client-side activation (active Nov 2015 – Mar 2016).


<br><br><br>

---

<br><br><br>

## Boiler Controller (2 kW)

| Property           | Value                       |
|--------------------|-----------------------------|
| Started on         | Mar 2016                    |
| Author             | Viktor Glebov (V01G04A81)   |
| Author             | GMad                        |


&bull; Designed STM32-based control panel  
&bull; 4-digit 7-segment LED display  
&bull; Implemented user interface (buttons + LED indication)  

<br><br><br>

---

<br><br><br>

## KVM Device ( Own project ) DIY PiKVM: Remote PC Control via 100M Ethernet (HDMI In/Out)

| Property           | Value                       |
|--------------------|-----------------------------|
| Started on         | Apr 2015                    |
| Author             | Viktor Glebov (V01G04A81)   |

<br>

&bull; STM32 + ETH PHY + XC6SLX100T + SDRAM 166 Mhz + x2 HDMI  
&bull; Status: Pending.  
&bull; Finding: A reliable solution requires a more complex enterprise-grade system rather than the "simple fix" originally envisioned.  

<br>

<p>
  <a href="pics_kvm/kvm1.png"><img src="pics_kvm/kvm1.png" height="600" alt="KVM Board" /></a><br>
  <em>KVM Board ( only draft version available from archive ) : Year: 2014-2015 </em>
</p>

<br><br><br>

---

<br><br><br>

## OBD-II Multi-Protocol Diagnostic Scanner (i.MX23-based)

| Property           | Value                       |
|--------------------|-----------------------------|
| Started on         | Sep 2015                    |
| Gerbers Completed  | Dec 2015                    |
| Author             | Viktor Glebov (V01G04A81)   |

 
Designed and implemented an automotive diagnostic interface supporting CAN (ISO 15765), K-Line (ISO 9141 / KWP2000), and legacy protocols via external transceivers.

<table>
  <tr>
    <td>
    <img src="pics_obd/OBDBaseBoardTop3D.png" height="240"><br>Base board (Top)
    </td>
    <td>
    <img src="pics_obd/OBDBaseBoardBot3D.png" height="240"><br>Base board (Bottom)
    </td>
    <td>
    <img src="pics_obd/OBDMCUBoardTop3D.png" height="240"><br>iMX232 Plug (Top)
    </td>
    <td>
    <img src="pics_obd/OBDMCUBoardBot3D.png" height="240"><br>iMX232 Plug (Bottom)
    </td>
  </tr>
</table>

Developed embedded firmware for ECU communication, DTC decoding, and real-time PID data acquisition.
Implemented hardware architecture including automotive power conditioning, protection circuits, and MCU–peripheral interfacing (UART/SPI).


---
2013-2016 V01G04A81
