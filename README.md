ESP32 to Nokia 3310 (DCT-3) F-Bus Bridge

Turn a cheap ESP32 into a transparent serial bridge to mod, tweak, and customize your vintage Nokia 3310 over the F-Bus protocol. No ancient PC parallel ports or legacy hardware required.

⚠️ THE OBLIGATORY DISCLAIMER

I AM NOT RESPONSIBLE FOR BRICKING YOUR PHONE.
Modifying EEPROM data, sending raw hex frames, or wiring things backward can permanently damage your phone or corrupt its software into a "Contact Service" screen of death. You are doing this at your own risk. Note: You cannot use this cable to flash ROMs or change the language pack—it is for EEPROM settings, UI unlocking, and media only.

🔌 What to Connect Where (Hardware Setup)

You can use https://www.printables.com/model/995212-mbusfbus-programming-adapter-for-nokia-3310-and-re/files

The ESP32 runs on 3.3V logic, which perfectly matches the Nokia 3310's MAD2 processor. You do not need logic level shifters, but you DO need a 1kΩ resistor on the TX line to prevent frying the phone if the ESP32 is powered while the phone is off.

Locate the 4 gold testing pads under the Nokia's battery (near the SIM card slot):

Pad 1 (Top Left / GND): Connect to ESP32 GND.

Pad 2 (Bottom Left / F-Bus TX): Connect directly to ESP32 RX2 (GPIO 16).

Pad 3 (Top Right / M-Bus): IGNORE THIS PAD. Leave it disconnected.

Pad 4 (Bottom Right / F-Bus RX): Connect to a 1kΩ Resistor, then to ESP32 TX2 (GPIO 17).<img width="296" height="439" alt="image" src="https://github.com/user-attachments/assets/5c474955-9751-4638-9305-68ba36e041f1" />


CRITICAL RULE: The Nokia MUST have a charged battery installed and be powered ON for F-Bus to work.

💻 What Apps to Use (Software Setup)

First, flash the provided esp32_fbus_bridge.ino sketch to your ESP32 using the Arduino IDE. Once flashed, your ESP32 acts as a transparent COM port at 115200 baud.

You can now use these classic Windows applications to talk to the phone:

1. Gammu (https://github.com/gammu/gammu/releases/download/1.45.1/Gammu-1.45.1-Windows.exe)

Gammu is a powerful command-line utility that lets you read and write almost everything in the phone's EEPROM.

How to set up and use Gammu:

Download Gammu for Windows and extract it to a folder.

In the same folder as gammu.exe, create a plain text file named gammurc (no extension).<img width="654" height="659" alt="image" src="https://github.com/user-attachments/assets/1951b3f8-aac3-4b3a-8f71-98caf6d7ac38" />


Open it in Notepad and paste exactly this (change COM3 to whatever port your ESP32 uses):

[gammu]
port = com3:
connection = fbus


Open Command Prompt (cmd), navigate to your Gammu folder, and test the connection by typing:
gammu identify
(If it works, Gammu will spit out your phone's IMEI, firmware version, and model).

Cool Gammu Commands to try:

gammu getbattery (Reads real-time battery voltage).

gammu netmonitor 1 (Permanently unlocks the hidden Engineering Field Test menu).

gammu getallmemory SM (Dumps your SIM card contacts).

gammu --nokiasetphonemenus Gammu will output that it is enabling the 3315 features, extra games, and hidden menus.

2. LogoManager (For Media & Customization)

LogoManager is a classic GUI app for pushing media to the phone.

Set it up: Go to Tools > Options > Connection, and set it to your ESP32's COM port using the "F-Bus cable" setting.

What you can do:

Draw a custom 72x14 Operator Logo to replace your carrier name.

Upload custom RTTTL ringtones (like the Mario theme or Interstellar) to the 7 empty slots.

Send 72x28 Picture Messages to use as custom screensavers.

