// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#include <Microsoft_HidForWindows.h>
#include <FastLED.h>

//
// Adafruit NeoPixel-Shield - 40 RGB/W - https://www.adafruit.com/product/3053
//

// NeoPixel-Shield always communicates over PIN6.
// However since the shield operates at 5V, and the SAMD-board at 3.3V, a level-shifter between board-output to shield-input was introduced.
// This necessitated the remapping of PIN5 (board) to PIN6 (shield)
#define NEO_PIXEL_PIN 5

// NeoPixel-Shield has 40 neopixels
#define NEO_PIXEL_LAMP_COUNT 40

CRGB leds[NEO_PIXEL_LAMP_COUNT];

// UpdateLatency for all Lamps set to 4msec as it just seems reasonable.
#define NEO_PIXEL_LAMP_UPDATE_LATENCY (0x04)

// The Host needs to know the location of every Lamp in the LampArray (X/Y/Z position) and other metadata.
// See "26.7 LampArray Attributes and Interrogation" https://usb.org/sites/default/files/hut1_4.pdf#page=336
static LampAttributes neoPixelShieldLampAttributes[] PROGMEM = 
{
    // All positions in millimeters from upper-left corner of device.
    // All times in milliseconds.
    // Id  X     Y     Z     Latency                        Purposes           RED   GRN   BLUE  GAIN  PROGAMMBLE?           KEY
    {0x00, 0x03, 0x08, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x01, 0x0C, 0x08, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x02, 0x15, 0x08, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x03, 0x1E, 0x08, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x04, 0x27, 0x08, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x05, 0x30, 0x08, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x06, 0x39, 0x08, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x07, 0x42, 0x08, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x08, 0x03, 0x11, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x09, 0x0C, 0x11, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x0A, 0x15, 0x11, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x0B, 0x1E, 0x11, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x0C, 0x27, 0x11, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x0D, 0x30, 0x11, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x0E, 0x39, 0x11, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x0F, 0x42, 0x11, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x10, 0x03, 0x1A, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x11, 0x0C, 0x1A, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x12, 0x15, 0x1A, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x13, 0x1E, 0x1A, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x14, 0x27, 0x1A, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x15, 0x30, 0x1A, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x16, 0x39, 0x1A, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x17, 0x42, 0x1A, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x18, 0x03, 0x23, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x19, 0x0C, 0x23, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x1A, 0x15, 0x23, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x1B, 0x1E, 0x23, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x1C, 0x27, 0x23, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x1D, 0x30, 0x23, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x1E, 0x39, 0x23, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x1F, 0x42, 0x23, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x20, 0x03, 0x2C, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x21, 0x0C, 0x2C, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x22, 0x15, 0x2C, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x23, 0x1E, 0x2C, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x24, 0x27, 0x2C, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x25, 0x30, 0x2C, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x26, 0x39, 0x2C, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
    {0x27, 0x42, 0x2C, 0x00, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
};
static_assert(((sizeof(neoPixelShieldLampAttributes) / sizeof(LampAttributes)) == NEO_PIXEL_LAMP_COUNT), "neoPixelShieldLampAttributes must have NEO_PIXEL_LAMP_COUNT items.");

// All lengths in millimeters.
// All times in milliseconds.
Microsoft_HidLampArray lampArray = Microsoft_HidLampArray(NEO_PIXEL_LAMP_COUNT, 70, 55, 1, LampArrayKindPeripheral, 33, neoPixelShieldLampAttributes);

// When the LampArray is in Autonomous-Mode, displays solid blue.
#define lampArrayAutonomousColor CRGB(0, 0, 1)

void setup()
{
    // Initialize the FastLED library.
    // https://github.com/FastLED/FastLED/wiki/Chipset-reference
    FastLED.addLeds<NEOPIXEL, NEO_PIXEL_PIN>(leds, NEO_PIXEL_LAMP_COUNT);
    FastLED.clear(true);

    // Always initially in Autonomous-Mode.
    FastLED.showColor(lampArrayAutonomousColor);
}

void loop()
{
    LampArrayColor currentLampArrayState[NEO_PIXEL_LAMP_COUNT];
    bool isAutonomousMode = lampArray.getCurrentState(currentLampArrayState);

    bool update = false;

    for (uint16_t i = 0; i < NEO_PIXEL_LAMP_COUNT; i++)
    {
        // Autonomous-Mode is the Host's mechanism to indicate to the device, that the device should decide what to render.
        // The Host may do this when no application is using the LampArray, so it has nothing to render.
        // In this case, this LampArray will revert to it's default/background effect, rendering 'blue'.
        CRGB newColor = isAutonomousMode ? lampArrayAutonomousColor : CRGB(currentLampArrayState[i].RedChannel, currentLampArrayState[i].GreenChannel, currentLampArrayState[i].BlueChannel);
        if (newColor != leds[i])
        {
            leds[i] = newColor;
            update = true;
        }
    }

    // Only call update on the NeoPixels when something has changed, show() takes a long time to execute.
    if (update)
    {
        // Send the updated pixel color to hardware.
        FastLED.show();
    }
}