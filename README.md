# Micro-Matter-Switch
Micro Matter Switch (MMS) is a small compact switch based on ESP32 C6 Xiao<br>
<b>Note:</b> Code based on <a href="https://github.com/espressif/arduino-esp32/tree/master/libraries/Matter/examples">Espressif</a> examples but it's heavily restructured by <a href="https://github.com/adm1nsys">adm1nsys</a>.
<h1>Board</h1>
For this project I have used ESP32 C6 Xiao because it's realy tiny. This project can be compiled for another ESP32 but you have to make new case and inicialize your pins. 
<h3>Pinout of ESP 32 C6 Xiao</h3>
<img src="https://wdcdn.qpic.cn/MTY4ODg1Nzc0ODUwMjM3NA_318648_dMoXitoaQiq2N3-a_1711678067?w=1486&h=1228" alt="esp32c6 xiao pinout" width="500">
<a href="https://wiki.seeedstudio.com/xiao_esp32c6_getting_started/">ESP32 C6 Xiao WiKi</a>
<h1>Case</h1>
As a material I recomend to use PETG becouse it's easy to print, enough strong and has a lot of colours.<br>
<h3>Download Case:</h3>
<a href="https://github.com/adm1nsys/Micro-Matter-Switch/tree/main/Case">Git</a><br>
<h3>Screws:</h3>
This case was made for screws M3x12mm
<h2>Quick Start</h2>
Download <a href="https://www.arduino.cc/en/software/">Arduino IDE for MAC/Linux/Windows10/11</a> <b>NOT</b> Arduino App Lab.<br>
<h3>Setup IDE</h3>

<ol>
  <li>Open Arduino IDE</li>
  <li>Open Preferences (Above)</li>
  <li>Add in board manager URL - URL of board and click OK
      
    https://espressif.github.io/arduino-esp32/package_esp32_index.json
  <img src="https://files.seeedstudio.com/wiki/SeeedStudio-XIAO-ESP32C6/img/boards_url.png" alt="menu" width="500">
  </li>
  <li>Download the XIAO ESP32C6 board package.<br>
  <img src="https://files.seeedstudio.com/wiki/SeeedStudio-XIAO-ESP32C6/img/install_board.png" alt="board package" width="500"></li>
  <li>Choose your board as a target (above)<br>
  <img src="https://files.seeedstudio.com/wiki/SeeedStudio-XIAO-ESP32C6/img/select_xiao_c6.png" alt="choose board" width="500"></li>
  <li>Download this repo, open MMS.ino file</li>
  <li>Click on Upload or click Command(CMD) MAC / Control(Ctrl) WIN + U</li>
</ol>
