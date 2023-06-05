// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#pragma once

// Describes a simple LED.
// Will configure mode of selected pin.
class Microsoft_Led
{
public:
    // Must be constructed in global-scope to ensure proper initialization.
    Microsoft_Led(int pin) noexcept;

    // Sets the LED state to that provided.
    void set(bool isOn) noexcept;

    // Turns the LED on.
    void on() noexcept;

    // Turns the LED off.
    void off() noexcept;

private:
    int m_pin;
};