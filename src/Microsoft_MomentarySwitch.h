// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#pragma once

// Describes a simple 'momentary-switch', abstracting debounce logic and state.
// Will configure mode of selected pin.
class Microsoft_MomentarySwitch
{
public:
    // Must be constructed in global-scope to ensure proper initialization.
    Microsoft_MomentarySwitch(int pin, bool openState) noexcept;

    // Returns True if state has changed since previous invocation.
    // Expected to be called (only) once from within loop(), at the start of every iteration.
    bool updateState() noexcept;

    // Returns True is switch is currently depressed/actuated.
    bool isPressed() noexcept;

private:
    bool GetCurrentStateWithDebounce() noexcept;

private:
    int m_pin;

    // Depending on how the underlying device is wired, the switch being open, might represent a HIGH or LOW voltage.
    // This provides configuration for what a non-actuated/open state is.
    bool m_openState;

    bool m_currentState;
    bool m_previousState;
};