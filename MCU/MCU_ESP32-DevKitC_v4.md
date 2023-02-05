
# ESP32 DevKitC V4
- https://docs.espressif.com/projects/esp-idf/en/latest/esp32/hw-reference/esp32/get-started-devkitc.html
- ESP32-WROOM-32D embedded, Xtensa® dual-core 32-bit LX6 microprocessor, up to 240 MHz
- Flash RAM: 320KB
- PSRAM: 4MB
- Wifi & BLE

```
; Environnement dans platform.ini
[env:pico32]
platform = espressif32
board = pico32
framework = arduino
```

ou

```
; Environnement dans platform.ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
```

[Retour]

[Retour]: ../Readme.md