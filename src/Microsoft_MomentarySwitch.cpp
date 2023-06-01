// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#include "Arduino.h"
#include "Microsoft_MomentarySwitch.h"

Microsoft_MomentarySwitch::Microsoft_MomentarySwitch(int pin, bool openState = LOW) noexcept : 
    m_pin(pin), 
    m_openState(openState),
    m_currentState(false), 
    m_previousState(false)
{
    pinMode(m_pin, INPUT);
}

bool Microsoft_MomentarySwitch::updateState() noexcept
{
    m_previousState = m_currentState;

    m_currentState = GetCurrentStateWithDebounce();

    return (m_currentState != m_previousState);
}

bool Microsoft_MomentarySwitch::isPressed() noexcept
{
    return m_currentState;
}

bool Microsoft_MomentarySwitch::GetCurrentStateWithDebounce() noexcept
{
    // When depressing/actuating a switch, there is often intermediate state as the switch contacts close.
    // Account for this by waiting until the reading has 'settled' to a HIGH/LOW state.

    bool previousState = digitalRead(m_pin);
    bool currentState = LOW;

    for (uint8_t i = 0; i < 10; i++)
    {
        delay(1);
        currentState = digitalRead(m_pin);
        if (currentState != previousState)
        {
            // Since the state has changed in such a small interval,
            // most likely the switch is in the middle of changing states from an actuation.
            // Wait a little-while more, until it has settled.
            i = 0;
            previousState = currentState;
        }
    }

    return (currentState != m_openState);
}