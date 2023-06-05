// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#pragma once

#if !defined(USBCON)

#warning "Platform does not support PluggableUSB"

#else

#include <Microsoft_HidDevice.h>

// Describes a HID 'Wireless Radio Control' device, to control the behaviour 
// of the system's wireless radios (e.g. WIFI, Bluetooth, Celluar)
class Microsoft_HidWirelessRadioControl : public Microsoft_HidDevice
{
public:
    // Must be constructed in global-scope to ensure descriptors are picked-up during USB initialization.
    Microsoft_HidWirelessRadioControl();

    ~Microsoft_HidWirelessRadioControl();

    // Retrieves the current WirelessRadioControl state prescribed by the Host.
    //
    // Should be called once during every loop() iteration, to retreive the current (cached) state, and state applied to 'physical' components.
    // Note: The current (cached) state is updated during USB-ISR, so calling this is O(1).
    void getCurrentState(bool* isWirelessRadiosOnLed) noexcept;

    // Toggles airplane-mode to be enabled/disabled.
    // When airplane-mode is enabled, all wireless radios (e.g. WIFI, Bluetooth, Celluar) are turned-off.
    // When airplane-mode is disabled, all wireless radios (e.g. WIFI, Bluetooth, Celluar) are turned-on.
    // Note: It is NOT possible to know the state of airplane-mode before/after toggling.
    void toggleAirplaneMode() noexcept;

    // Enables/disables (explicitly) airplane-mode.
    // When airplane-mode is enabled, all wireless radios (e.g. WIFI, Bluetooth, Celluar) are turned-off.
    // When airplane-mode is disabled, all wireless radios (e.g. WIFI, Bluetooth, Celluar) are turned-on.
    // Note: It is NOT guaranteed that after airplane-mode is enabled/disabled that it will remain so,
    // as there is a shell-affordance (quick-settings button) to also toggle airplane-mode.
    void enableAirplaneMode() noexcept;
    void disableAirplaneMode() noexcept;

private:
    void ProcessReceivedOutputReport(uint8_t reportId, uint8_t* data, uint16_t length) noexcept;

    void UpdateLedStateFromReport(uint8_t* data, uint16_t length) noexcept;

private:
    // LED indicating whether wireless radios are on/off (i.e. airplane-mode is disabled/enabled).
    // Note: This can be set independantly of whether airplane-mode button was toggled (e.g. via toggleAirplaneMode()), as
    // there is a shell-affordance (quick-settings button) to also toggle airplane-mode.
    bool m_isWirelessRadiosOnLed;
};

#endif