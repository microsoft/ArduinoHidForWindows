// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#include "Arduino.h"
#include "Microsoft_Potentiometer.h"

Microsoft_Potentiometer::Microsoft_Potentiometer(int pin, uint8_t readingThreshold = 10, bool invertIncreasingDirection = false) noexcept : 
    m_pin(pin), 
    m_readingThreshold(readingThreshold),
    m_currentState(0), 
    m_previousState(0), 
    m_invertIncreasingDirection(invertIncreasingDirection)
{
    pinMode(m_pin, INPUT);
}

bool Microsoft_Potentiometer::updateState() noexcept
{
    int reading = analogRead(m_pin);

    if ((reading > (m_currentState + m_readingThreshold)) || (reading < (m_currentState - m_readingThreshold)))
    {
        m_previousState = m_currentState;
        m_currentState = reading;

        return true;
    }

    return false;
}

bool Microsoft_Potentiometer::isIncreasing() noexcept
{
    return m_invertIncreasingDirection ? (m_currentState > m_previousState) : (m_currentState <= m_previousState);
}