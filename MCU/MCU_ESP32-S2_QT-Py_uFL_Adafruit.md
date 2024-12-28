
# ESP32-S2 QT Py de Adafruit µFL

https://learn.adafruit.com/adafruit-qt-py-esp32-s2/overview

- ESP32-S2F
  - https://www.espressif.com/sites/default/files/documentation/esp32-s2_datasheet_en.pdf
  - Processeur simple coeur 32bit LX7 Xtensa à 240/160/80 Mhz
  - Communication 
    - Wifi 802.11b/g/n 2.4Ghz
    - **PAS** de BlueTooth 
    - Antenne µFL
  - Mémoire µC
    - 384 Kb ROM
    - 512 Kb SRAM
    - 8 kb SRAM RTC FAST Memory
    - 8 kb SRAM RTC SLOW Memory  
    - 4 kb Efuse (Eprom)
  - Acceleration Cryptographique
- Mémoire Carte
  - 4 Mb FLASH
  - 2 Mb PSRAM  
- 1x LED RGB adressable NeoPixel
- 1x connecteur STEMMA QT pour l'I2C
- USB natif
- Pads d'entrée de batterie jusqu'à 6 V
- Consommation carte
  - Deep Sleep = 70µA

## Functional_Block_Diagram
<p >
    <img src="assets/ESP32-S2_Functional_Block_Diagram.png"  width="75%" alt="Functional_Block_Diagram">
</p>

## Power_Consumption of ESP32-S2F
<p >
    <img src="assets/ESP32-S2_Power_Consumption.png"  width="75%" alt="Power_Consumption">
</p>

```
; Environnement dans platform.ini
[env:adafruit_qtpy_esp32s2]
platform = espressif32
board = adafruit_qtpy_esp32s2
framework = arduino
```

[Retour]

[Retour]: ../Readme.md

