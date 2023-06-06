// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#pragma once

#if !defined(USBCON)

#warning "Platform does not support PluggableUSB"

#else

#include <Microsoft_HidDevice.h>

#define LAMP_NOT_PROGRAMMABLE 0x00
#define LAMP_IS_PROGRAMMABLE 0x01

enum LampPurposeKind
{
    LampPurposeControl = 1,
    LampPurposeAccent = 2,
    LampPurposeBranding = 4,
    LampPurposeStatus = 8,
    LampPurposeIllumination = 16,
    LampPurposePresentation = 32,
};

enum LampArrayKind
{
    LampArrayKindKeyboard = 1,
    LampArrayKindMouse = 2,
    LampArrayKindGameController = 3,
    LampArrayKindPeripheral = 4,
    LampArrayKindScene = 5,
    LampArrayKindNotification = 6,
    LampArrayKindChassis = 7,
    LampArrayKindWearable = 8,
    LampArrayKindFurniture = 9,
    LampArrayKindArt = 10,
};

struct __attribute__ ((__packed__)) LampArrayColor
{
    uint8_t RedChannel;
    uint8_t GreenChannel;
    uint8_t BlueChannel;
    uint8_t IntensityChannel;
};

struct __attribute__ ((__packed__)) LampAttributes
{
    uint16_t LampId;
    uint32_t PositionXInMillimeters;
    uint32_t PositionYInMillimeters;
    uint32_t PositionZInMillimeters;
    uint32_t UpdateLatencyInMilliseconds;
    uint32_t LampPurposes;
    uint8_t RedLevelCount;
    uint8_t GreenLevelCount;
    uint8_t BlueLevelCount;
    uint8_t IntensityLevelCount;
    uint8_t IsProgrammable;
    uint8_t LampKey;
};

// LampArray devices exposes an array-of-Lamps (e.g. LEDs), that the system or foreground-application may manipulate.
// These will likely be part of a composite device (e.g. Keyboard), where the LampArray allows manipulation of the RGB-LEDs behind keyboard-keys.
// All static data MUST be accurately described, including supported colors, geometric positions and intended purposes for each Lamp.
class Microsoft_HidLampArray : public Microsoft_HidDevice
{
public:
    // Must be constructed in global-scope to ensure descriptors are picked-up during USB initialization.
    Microsoft_HidLampArray(
        uint16_t lampCount,
        uint32_t boundingBoxWidthInMillimeters, 
        uint32_t boundingBoxHeightInMillimeters, 
        uint32_t boundingBoxDepthInMillimeters, 
        uint32_t kind, 
        uint32_t minUpdateInternalInMilliseconds,
        LampAttributes* attributes);

    ~Microsoft_HidLampArray();

    // Fills the supplied LampArrayColor array with the current state prescribed by the Host.
    // Note: Supplied array must be the same size as the attributes array passed to the constructor.
    // Note: When in 'Autonomous-Mode', the supplied array is zero'd.
    // Returns 'true' if the Host prescribes the Device to be in 'Autonomous-Mode', where it does not get
    // Lamp state, and it is up to the Device to decide what to render.
    //
    // Should be called once during every loop() iteration, to retreive the current (cached) state, and state applied to 'physical' Lamps.
    // Note: The current (cached) state is updated during USB-ISR, so calling this is O(1).
    bool getCurrentState(LampArrayColor* currentState) noexcept;

private:
    void ProcessReceivedGetFeatureReport(uint8_t reportId) noexcept;

    void ProcessReceivedSetFeatureReport(uint8_t reportId, uint8_t* data, uint16_t length) noexcept;

    void SendLampArrayAttributesReport() noexcept;

    void SendLampAttributesReport() noexcept;

    void UpdateRequestLampFromLampAttributesRequestReport(uint8_t* data, uint16_t length) noexcept;

    void UpdateLampStateCacheFromMultiUpdateReport(uint8_t* data, uint16_t length) noexcept;

    void UpdateLampStateCacheFromRangeUpdateReport(uint8_t* data, uint16_t length) noexcept;

    void ProcessControlReport(uint8_t* data, uint16_t length) noexcept;

private:
    uint16_t m_lampCount;

    uint32_t m_boundingBoxWidthInMillimeters;
    uint32_t m_boundingBoxHeightInMillimeters;
    uint32_t m_boundingBoxDepthInMillimeters;

    uint32_t m_kind;

    uint32_t m_minUpdateInternalInMilliseconds;

    LampAttributes* m_lampAttributes;

    // Last LampId of the corresponding LampAttributes requested by the Host.
    uint16_t m_lastLampIdRequested;

    uint32_t m_stateSize;

    LampArrayColor* m_cachedStateWriteTo;

    LampArrayColor* m_cachedStateReadFrom;

    // Indicates if Device should be in automonous-mode.
    // Host will put the Device in automonous-mode when doesn't have exclusive lock.
    bool m_isAutonomousMode;
};

#endif