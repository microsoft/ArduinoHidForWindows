# Background
A 'Wireless Radio Control' device allows enabling/disable all wireless radios (e.g. WIFI, Bluetooth, Celluar) on a system.

[Wireless Radio Controls HID Usages](https://usb.org/sites/default/files/hut1_4.pdf#page=53) describe the underlying interaction between Host and Device.  This interaction is implemented by `Microsoft_HidWirelessRadioControl`

# Building Sample Device
This section describes the hardware components (constituting the end-device) used for this sample.  Other configurations may require changes to the sample code to integrate with alternate switches/LEDs or development-platform.

<img src="./docs/ArduinoWithSensorKit.jpg" alt="Wireless Radio Control assembled" width="427"/>

## Design
Arduino (with Seeed Studio) has released a collection of simple IO and sensor devices (as a shield), packaged as the [Arduino Sensor Kit](https://store.arduino.cc/products/arduino-sensor-kit-base).  Of concern here are the:-
- Momentary switch (Digital PIN4)
- LED (Digital PIN6)

There are many other sources and methods to attach these components, but require additional components (e.g. resistors), so for simplicitly of this sample, this shield was chosen.

An Arduino Zero is chosen because of it's native USB support (via Atmel SAMD21 microcontroller) and friendly EDBG for source-debugging.

*Note: The Arduino Sensor Kit has 2 voltage options:- 3.3v & 5v (adjustable via a switch next to A0 port.  For Arduino Zero, this must be set to 3.3v*.

## Components
- [Arduino Zero](https://store-usa.arduino.cc/products/arduino-zero?selectedStore=us)
- [Arduino Zero Case](https://store-usa.arduino.cc/products/arduino-zero-case?variant=40735839748303)
- [Arduino Sensor Kit](https://store.arduino.cc/products/arduino-sensor-kit-base)

# Troubleshooting
- Validate connected to a Windows 10/11 system (untested on non-Windows systems (e.g. macOS, Linux, etc…))
- Validated with latest (1.8.13) [SAMD Arduino Core](https://github.com/arduino/ArduinoCore-samd), earlier versions may not have required USBCore fixes.
- Sample does not work with Adafruit SAMD21 boards as the [Adafruit fork](https://github.com/adafruit/ArduinoCore-samd) of the [SAMD Arduino Core](https://github.com/arduino/ArduinoCore-samd) isn't aligned with the official, which now contains several important fixes in USBCore regarding control-transfers and max-descriptor size.
- If using an Arduino Zero, ensure the 'Arduino Sensor Kit' shield is switched to 3.3v.