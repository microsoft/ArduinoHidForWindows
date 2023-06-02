// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#include <Microsoft_HidForWindows.h>

// The momentary-switch on the 'Arduino Sensor Kit' is (by default) on Digital-PIN4.
const int MOMENTARY_SWITCH_PIN = 4;

// The potentiometer on the 'Arduino Sensor Kit' is (by default) on Analog-PIN0.
const int POTENTIOMETER_PIN = 0;

Microsoft_HidConsumerControl consumerControl = Microsoft_HidConsumerControl();

Microsoft_MomentarySwitch momentarySwitch1(MOMENTARY_SWITCH_PIN, LOW);
Microsoft_Potentiometer potentiometer1(POTENTIOMETER_PIN, 10, false);

// TODO: Modify this variable to be 1, 2, 3, to invoke the appropriate sample below.
const int sample = 1;

void setup()
{
}

void loop()
{
    switch (sample)
    {
        case 1:
        {
            sample1();
            break;
        }
        case 2:
        {
            sample2();
            break;
        }
        case 3:
        {
            sample3();
            break;
        }
    }
}

void sample1()
{
    // When the potentiometer is turned to the left, system-volume is decreased.
    // When the potentiometer is turned to the right, system-volume is increased.
    // Note: It is not possible to know the system-volume before/after the decrease/increase; so in this
    // simple example it is likely that the physical position of the potentiometer will get out-of-sync with
    // the actual system-volume.
    if (potentiometer1.updateState())
    {
        if (potentiometer1.isIncreasing())
        {
            consumerControl.incrementVolume();
        }
        else
        {
            consumerControl.decrementVolume();
        }
    }
}

void sample2()
{
    // When the momentary-switch is pressed, volume will increase, and continue increasing
    // until the momentary-switch is released.
    // Note: It is not possible to know the system-volume before/after the increase.
    if (momentarySwitch1.updateState())
    {
        if (momentarySwitch1.isPressed())
        {
            consumerControl.startIncrementVolume();
        }
        else
        {
            consumerControl.stopIncrementVolume();
        }
    }
}

void sample3()
{
    // When the momentary-switch is pressed, system-mute is toggled (muted/unmuted) once.
    // To toggle again, the momentary-switch must be released, and then pressed again.
    // Note: It is not possible to know the system mute-state before/after toggling.
    if (momentarySwitch1.updateState())
    {
        if (momentarySwitch1.isPressed())
        {
            consumerControl.toggleMute();
        }
    }
}
