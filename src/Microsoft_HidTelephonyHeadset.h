// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#pragma once

#if !defined(USBCON)

#warning "Platform does not support PluggableUSB"

#else

#include <Microsoft_HidDevice.h>

struct TelephonyHeadsetLedUpdate
{
    bool OnHold;
    bool OffHook;
    bool Ringing;
    bool LineInUse;
};

// Describes a Telephony-Headset that can be used to dial, answer and control calls on the Host.
// These Devices are utilized by the 'Phone Link' Windows UWP app.
// Note: For mute/unmute to work, the USB-Interface must also include an (optional) audio-endpoint (see mute/unmute for more details).
// Call Terminology:-
// - incoming-call -> answered -> active-call
// - active-call -> hang-up
// - outgoing-call (i.e. dialing) -> answered (by receipient) -> active-call
class Microsoft_HidTelephonyHeadset : public Microsoft_HidDevice
{
public:
    // Must be constructed in global-scope to ensure descriptors are picked-up during USB initialization.
    Microsoft_HidTelephonyHeadset();

    ~Microsoft_HidTelephonyHeadset();

    // Retrieves the current Telephony state prescribed by the Host.
    //
    // Should be called once during every loop() iteration, to retreive the current (cached) state, and state applied to 'physical' components.
    // Note: The current (cached) state is updated during USB-ISR, so calling this is O(1).
    void getCurrentState(TelephonyHeadsetLedUpdate* currentState) noexcept;

    // Indicate the Telephony-Headset is now 'on-hook'.
    // Hang-ups the currently active-call (if one is active).
    void indicateOnHook() noexcept;

    // Indicate the Telephony-Headset is now 'off-hook'
    // Answers the incoming-call (if one is active), otherwise dials the number previously entered with enterKeypad* (if one was entered).
    void indicateOffHook() noexcept;

    // Answers the incoming-call (if one is active).
    void answerCall() noexcept;

    // Hangs-up a single call.
    // If more than one-call is active, the hang-up order is:-
    //  1. outgoing-call (if currently dialing)
    //  2. active-call
    //  3. incoming-call (if currently receiving)
    void hangupCall() noexcept;

    // Hold-over from PBX-days where the hook-button (on North-American phones) could be used for auxillary-functions in conjuction
    // with the telephony-exchange.
    //      In Europe, this is commonly referred to as 'Register-Recall' and had a separate 'Recall'/'R' button.
    // A short actuation of the hook-button (<1sec) would trigger an auxillary-function (dependant on the current call-state), rather
    // than indicating the 'on-hook' condition.
    // Auxillary-Functions:-
    //  1. If has incoming-call, switch to active-call.  Previously active-call switched to onhold-call.
    //  2. If has active-call, switch to onhold-call.
    //  3. If has no active-calls, first onhold-call switched to active-call.
    //  4. If has both active-call and onhold-calls, active-call switched to onhold-call, first onhold-call switched to active-call.
    void hookFlash() noexcept;

    // (Re)dials the most recently called number.
    // It is up to the Host to maintain the list of previously-called numbers, and select the most recent.
    void redial() noexcept;

    // Mutes/unmutes the microphone audio-endpoint (on the Host) associated with this Telephony-Headset.
    // Does NOT affect the audio-source on the Device.
    // Microphone audio-endpoint MUST have the same DEVPKEY_Device_ContainerId as this Device (on the Host) to be discovered/affected.
    // This will be the case for all USB-Interface described devices.
    void mute() noexcept;
    void unmute() noexcept;

    // 0-9
    // Note: Once all keys have been entered, must invoke indicateOffHook() to begin dialing.
    void enterKeypadDigit(uint8_t digit) noexcept;

    // 'A' - 'Z'
    // Note: Once all keys have been entered, must invoke indicateOffHook() to begin dialing.
    void enterKeypadCharacter(char c) noexcept;

    // '*', '#', 'A', 'B', 'C', 'D'
    // Note: Once all keys have been entered, must invoke indicateOffHook() to begin dialing.
    void enterKeypadSpecialty(char c) noexcept;

private:
    void ProcessReceivedOutputReport(uint8_t reportId, uint8_t* data, uint16_t length) noexcept;

private:
    TelephonyHeadsetLedUpdate m_ledState;
};

#endif