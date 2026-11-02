ESP32 Nokia 3310 (DCT-3) F-Bus Bridge & Modding Guide
A modern hardware bridge and toolset to interface with the Nokia 3310 over the F-Bus protocol using an ESP32. This repository allows you to unlock hidden 3315 features, upload custom media, and read hardware telemetry without requiring legacy PC serial hardware.
⚠️ Hardware Limitations
This F-Bus bridge CANNOT flash ROMs. You cannot use this to change the firmware language (PPM), upload custom games, or install 3330 animated screensavers. ROM flashing requires a synchronous hardware Dejan Flasher connected to a PC parallel port. This bridge is strictly for EEPROM modification and serial AT/F-Bus commands.
Exact Wiring Diagram (F-Bus)
Connect the ESP32 directly to the 4 gold testing pads located under the Nokia 3310 battery. No level shifters are required because the ESP32 operates at the 3.3V logic expected by the Nokia MAD2 processor.
Pad 1 (Top Left): Ground GND ➔ Connect to ESP32 GND
Pad 2 (Bottom Left): F-Bus TX ➔ Connect to ESP32 RX2 (GPIO 16)
Pad 3 (Top Right): M-Bus ➔ LEAVE DISCONNECTED
Pad 4 (Bottom Right): F-Bus RX ➔ Connect to 1kΩ Resistor ➔ Connect to ESP32 TX2 (GPIO 17)
(Note: The Nokia must have a battery installed and be powered on. F-Bus only communicates when the baseband processor is fully booted into the operating system).
Software Setup
Flash firmware/esp32_fbus_bridge.ino to your ESP32.
Install Python dependencies: pip install -r requirements.txt
Guide: The 3310 to 3315 Conversion
The Nokia 3310 and 3315 share the exact same firmware (V 06.07). The 3315 features are simply hidden behind an EEPROM product profile switch.
Using this ESP32 bridge as your COM port interface, open Gammu or Nokia Tool by Rollis to edit the EEPROM:
Connect the software to your ESP32's COM port at 115200 baud.
Read the phone's EEPROM.
Locate the Product Profile block.
Enable the bits for Automatic Keyguard, Picture Editor, and Timed Profiles.
Write the changes back to the phone and restart it. The new menus will appear immediately.
Guide: Customization (Ringtones, Logos, Screensavers)
With the ESP32 bridge running, use LogoManager to push custom media directly to the phone's EEPROM:
Ringtones: Convert melodies to RTTTL (Ring Tone Text Transfer Language) format, paste them into LogoManager, and send them to the 7 custom slots. (Note: Only monophonic, non-overlapping notes are supported).
Operator Logos: Upload a 72x14 monochrome bitmap to permanently replace the carrier name (e.g., Orange, Moldcell) on the home screen.
Screensavers: Upload a 72x28 monochrome bitmap as a Picture Message. On the phone, navigate to Menu > Settings > Phone settings > Screen saver and select the uploaded picture to display when the phone sleeps.
