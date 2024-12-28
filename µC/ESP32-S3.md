# MicroContrôleur ESP32-S3

- Processeur simple double 32bit LX7 Xtensa à 240/160/80 Mhz
- Communication 
  - Wifi 802.11b/g/n 2.4Ghz
  - BlueTooth 5 **UNIQUEMENT** LE
  - Port USB-C natif
- Mémoire
  - 384 Kb ROM
  - 512 Kb SRAM
  - 8 kb SRAM RTC FAST Memory
  - 8 kb SRAM RTC SLOW Memory  
  - 4 kb Efuse (Eprom)
- Acceleration Cryptographique

| Mode                | Fréquence CPU | Consommation        |
|---------------------|---------------|---------------------|
| Modem-sleep         | 240 Mhz       | 66 mA               |
| Modem-sleep         | 160 Mhz       | 50 mA               |
| Modem-sleep         | 80 Mhz        | 33 mA               |
| Modem-sleep         | 40 Mhz        | 19 mA               |
| Light-sleep         | -             | 240 µA              |
| Deep-sleep          | -             | 8 µA                |
| Hibernation         | -             | 7 µA                |



DataSheet: https://cdn-shop.adafruit.com/product-files/5426/esp32-s3_datasheet_en.pdf
