// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#include <Microsoft_HidForWindows.h>

// The momentary-switch on the 'Arduino Sensor Kit' is (by default) on Digital-PIN4.
const int MOMENTARY_SWITCH_PIN = 4;

Microsoft_MomentarySwitch momentarySwitch1(MOMENTARY_SWITCH_PIN, LOW);

Microsoft_HidSystemControl systemControl = Microsoft_HidSystemControl();

void setup()
{
}

void loop()
{
    if (momentarySwitch1.updateState())
    {
        if (momentarySwitch1.isPressed())
        {
            systemControl.powerdown();
        }
    }
}
