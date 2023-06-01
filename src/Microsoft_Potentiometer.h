// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#pragma once

// Describes a simple 'potentiometer', abstracting thresholds and states.
// Will configure mode of selected pin.
class Microsoft_Potentiometer
{
public:
    // Must be constructed in global-scope to ensure proper initialization.
    Microsoft_Potentiometer(int pin, uint8_t readingThreshold, bool invertIncreasingDirection) noexcept;

    // Returns True if state has changed since previous invocation.
    // Expected to be called (only) once from within loop(), at the start of every iteration.
    bool updateState() noexcept;

    // Returns True if state is increasing (e.g. corresponding to knob being turned).
    bool isIncreasing() noexcept;

private:
    int m_pin;

    // Threshold to indicate whether the state has changed.
    // Since on an analog pin, the value will be noisy (going up/down even if potentiometer isn't changed),
    // so this helps reduce the number of 'values', so reducing noise.
    uint8_t m_readingThreshold;

    // Depending on how the underlying device is wired, an increasing voltage might mean (e.g.) turning a knob left or it could mean right.
    // This provides configuration for what increasing/decreasing voltage means.
    bool m_invertIncreasingDirection;

    int32_t m_currentState;
    int32_t m_previousState;
};