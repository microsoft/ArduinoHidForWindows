// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#pragma once

#if !defined(USBCON)

#warning "Platform does not support PluggableUSB"

#else

#include <Microsoft_HidDevice.h>

// Describes a HID 'System Control' device that acts on the system as a 'whole'.
class Microsoft_HidSystemControl : public Microsoft_HidDevice
{
public:
    // Must be constructed in global-scope to ensure descriptors are picked-up during USB initialization.
    Microsoft_HidSystemControl();

    ~Microsoft_HidSystemControl();

    // Powers-down/turns-off the connected system/Host (i.e. S5).
    void powerdown() noexcept;

    // Indicates to the connect system/Host it should 'sleep' (i.e. S3/S4).
    void sleep() noexcept;
};

#endif