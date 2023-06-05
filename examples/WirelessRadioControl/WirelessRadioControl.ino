// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#include <Microsoft_HidForWindows.h>

// The momentary-switch on the 'Arduino Sensor Kit' is (by default) on Digital-PIN4.
const int MOMENTARY_SWITCH_PIN = 4;

// The LED on the 'Arduino Sensor Kit' is (by default) on Digital-PIN6.
const int LED_PIN = 6;

Microsoft_HidWirelessRadioControl wirelessRadioControl = Microsoft_HidWirelessRadioControl();

Microsoft_MomentarySwitch momentarySwitch1(MOMENTARY_SWITCH_PIN, LOW);
Microsoft_Led led1(LED_PIN);

void setup()
{
}

void loop()
{
    bool isWirelessRadiosOnLed = false;
    wirelessRadioControl.getCurrentState(&isWirelessRadiosOnLed);
    led1.set(isWirelessRadiosOnLed);

    if (momentarySwitch1.updateState())
    {
        if (momentarySwitch1.isPressed())
        {
            wirelessRadioControl.toggleAirplaneMode();
        }
    }
}
