// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#pragma once

#if !defined(USBCON)

#warning "Platform does not support PluggableUSB"

#else

// Creates a distinct USB-device (off the 'main' composite USB-device).
// Multiple instances are supported; each is created as a distinct USB-device.
class Microsoft_HidDevice : public PluggableUSBModule
{
public:
    // Must be constructed in global-scope to ensure descriptors are picked-up during USB initialization.
    Microsoft_HidDevice(const uint8_t* descriptor, size_t descriptorSize);

    ~Microsoft_HidDevice();

protected:
    void SendFeatureReport(const void* reportWithId, size_t reportLength);

    void SendInputReport(const void* reportWithId, size_t reportLength);

    // Invoked when GetFeature report is received.
    // Default behaviour is to drop the report.
    virtual void ProcessReceivedGetFeatureReport(uint8_t reportId);

    // Invoked when SetFeature report is received.
    // Default behaviour is to drop the report.
    virtual void ProcessReceivedSetFeatureReport(uint8_t reportId, uint8_t* data, uint16_t length);

    //
    // PluggableUSBModule interface
    //
    int getInterface(uint8_t* interfaceCount);

    int getDescriptor(USBSetup& setup);

    bool setup(USBSetup& setup);

private:
#if __has_include("USB/PluggableUSB.h")
    uint32_t m_epType;
#else
    unsigned int m_epType;
#endif

    uint8_t m_idle;

    const uint8_t* m_descriptor;
    size_t m_descriptorSize;
};

#endif