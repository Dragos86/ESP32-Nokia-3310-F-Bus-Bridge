# Hardware Wiring Guide

Connecting the ESP32 to the Nokia 3310 (NHM-5) is simple because both operate on 3.3V logic. No level shifters are required.

## Parts Needed
* ESP32 Development Board
* Nokia 3310 (with charged battery or power supply)
* 3 jumper wires
* 1kΩ Resistor
* Probes or pogo pins (to touch the pads under the battery without soldering)

## Pinout

Under the Nokia 3310 battery, there are 4 flat gold pads near the SIM card slot.

1. **Pad 1 (GND):** Top left pad. Connect to ESP32 `GND`.
2. **Pad 2 (F-Bus TX):** Bottom left pad. Connect to ESP32 `RX2` (GPIO 16).
3. **Pad 3 (M-Bus):** Top right pad. Leave disconnected.
4. **Pad 4 (F-Bus RX):** Bottom right pad. Connect to **1kΩ Resistor** ➔ Connect to ESP32 `TX2` (GPIO 17).

> **Warning:** Make sure the Nokia has a battery installed and is turned on before sending commands, as F-Bus only works when the baseband processor is fully booted into the OS. Never skip the 1kΩ resistor on the TX line if your ESP32 is powered via USB while the phone's battery is removed or dead, as this will force parasitic power directly into the phone's receiving UART buffer.
