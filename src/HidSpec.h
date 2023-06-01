// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#pragma once

// From "Device Class Definition for Human Interface Devices 1.11"

enum class HidReportRequestKind : uint8_t
{
    GetReport = 0x01,
    GetIdle = 0x02,
    GetProtocol = 0x03,
    SetReport = 0x09,
    SetIdle = 0x0A,
    SetProtocol = 0x0B,
};

// 7.1 Standard Requests
enum class HidClassDescriptorKind : uint8_t
{
    HID = 0x21,
    Report = 0x22,
};

enum class HidReportType : uint8_t
{
    Input = 1,
    Output = 2,
    Feature = 3,
};

struct HidInterfaceDescriptor
{
    uint8_t Length;
    uint8_t DescriptorType;
    uint8_t Address;
    uint8_t VersionLowByte;
    uint8_t VersionHighByte;
    uint8_t Country;
    uint8_t HidDescriptorType;
    uint8_t HidDescriptorLengthLow;
    uint8_t HidDescriptorLengthHigh;
};

struct UsbInterfaceDescriptor
{
    InterfaceDescriptor HidClassInterface;
    HidInterfaceDescriptor HidDescriptor;
    EndpointDescriptor HidInterruptEndpoint;
};

#define D_HIDREPORT(length) { sizeof(HidInterfaceDescriptor), (uint8_t)HidClassDescriptorKind::HID, 0x01, 0x01, 0x00, 0x01, (uint8_t)HidClassDescriptorKind::Report, lowByte(length), highByte(length) }
