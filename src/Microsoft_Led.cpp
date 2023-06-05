// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#include "Arduino.h"
#include "Microsoft_Led.h"

Microsoft_Led::Microsoft_Led(int pin) noexcept : 
    m_pin(pin)
{
    pinMode(m_pin, OUTPUT);

    off();
}

void Microsoft_Led::set(bool isOn) noexcept
{
    if (isOn)
    {
        on();
    }
    else
    {
        off();
    }
}

void Microsoft_Led::on() noexcept
{
    digitalWrite(m_pin, HIGH);
}

void Microsoft_Led::off() noexcept
{
    digitalWrite(m_pin, LOW);
}