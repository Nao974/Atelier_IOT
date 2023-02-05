
# ESP32 Feather V2 de Adafruit
- https://learn.adafruit.com/adafruit-esp32-feather-v2/overview
- ESP32-PICO-MIN-02
    - https://www.espressif.com/sites/default/files/documentation/esp32-pico-mini-02_datasheet_en.pdf
    - ESP32-PICO-V3-02 embedded, Xtensa dual-core 32-bit LX6 microprocessor, up to 240 MHz
    - Flash RAM: 8 Mo
    - PSRAM: 2MB
- Wifi & BLE
- 1x LED RGB adressable NeoPixel
- 1x connecteur STEMMA QT pour l'I2C
- 1x connecteur Lipo 3,7v / 4,2v
    - Chargement de la batterie intégrée  lorsqu'il est alimenté via USB-C
    - Moniteur de batterie LiPoly avec deux diviseurs de résistance 200K 

```
; Environnement dans platform.ini
[env:adafruit_feather_esp32_v2]
platform = espressif32
board = adafruit_feather_esp32_v2
framework = arduino
```

[Retour]

[Retour]: ../Readme.md
