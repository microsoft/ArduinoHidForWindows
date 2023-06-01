// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#include "Arduino.h"

#if __has_include("USB/PluggableUSB.h")
    #include "USB/PluggableUSB.h"
#else
    #include "api/PluggableUSB.h"
#endif

#include "Microsoft_HidDevice.h"
#include "HidSpec.h"

#define USB_ENDPOINT_MAX_PACKET_SIZE 0x40

#define INTERFACE_COUNT 0x01
#define ENDPOINT_COUNT 0x01

extern USBDeviceClass USBDevice;

Microsoft_HidDevice::Microsoft_HidDevice(const uint8_t* descriptor, size_t descriptorSize) : PluggableUSBModule(ENDPOINT_COUNT, INTERFACE_COUNT, &m_epType)
{
    m_descriptor = descriptor;
    m_descriptorSize = descriptorSize;

    m_idle = 1;

    m_epType = USB_ENDPOINT_TYPE_INTERRUPT | USB_ENDPOINT_IN(0);

    PluggableUSB().plug(this);
}

Microsoft_HidDevice::~Microsoft_HidDevice()
{
}

int Microsoft_HidDevice::getInterface(uint8_t* interfaceCount)
{
    *interfaceCount += INTERFACE_COUNT;
    UsbInterfaceDescriptor interface =
    {
        D_INTERFACE(pluggedInterface, ENDPOINT_COUNT, USB_DEVICE_CLASS_HUMAN_INTERFACE, 0, 0),
        D_HIDREPORT(m_descriptorSize),
        D_ENDPOINT((uint8_t)USB_ENDPOINT_IN(pluggedEndpoint), USB_ENDPOINT_TYPE_INTERRUPT, USB_ENDPOINT_MAX_PACKET_SIZE, 0x01)
    };

    return USBDevice.sendControl(&interface, sizeof(interface));
}

int Microsoft_HidDevice::getDescriptor(USBSetup& setup)
{
    if (setup.bmRequestType != REQUEST_DEVICETOHOST_STANDARD_INTERFACE)
    {
        return 0;
    }

    if (setup.wValueH != (uint8_t)HidClassDescriptorKind::Report)
    {
        return 0;
    }

    if (setup.wIndex != pluggedInterface)
    {
        return 0;
    }

    int status = USBDevice.sendControl(m_descriptor, m_descriptorSize);

    return status;
}

bool Microsoft_HidDevice::setup(USBSetup& setup)
{
    if (pluggedInterface != setup.wIndex)
    {
        return false;
    }

    uint8_t requestType = setup.bmRequestType;
    HidReportRequestKind request = (HidReportRequestKind)setup.bRequest;

    switch (requestType)
    {
        case REQUEST_DEVICETOHOST_CLASS_INTERFACE:
        {
            switch (request)
            {
                case HidReportRequestKind::GetReport:
                {
                    uint8_t reportId = setup.wValueL;
                    HidReportType reportType = (HidReportType)setup.wValueH;
                    switch (reportType)
                    {
                        case HidReportType::Feature:
                        {
                            ProcessReceivedGetFeatureReport(reportId);
                        }
                    }

                    return true;
                }
                case HidReportRequestKind::GetProtocol:
                {
                    return true;
                }
                case HidReportRequestKind::GetIdle:
                {
                    USBDevice.armSend(0, &m_idle, 1);

                    return true;
                }
            }

            break;
        }
        case REQUEST_HOSTTODEVICE_CLASS_INTERFACE:
        {
            switch (request)
            {
                case HidReportRequestKind::SetProtocol:
                {
                    return true;
                }
                case HidReportRequestKind::SetIdle:
                {
                    m_idle = setup.wValueL;

                    return true;
                }
                case HidReportRequestKind::SetReport:
                {
                    uint16_t reportlength = setup.wLength;
                    uint8_t reportId = setup.wValueL;
                    uint8_t* report = (uint8_t*)malloc(reportlength);

                    USBDevice.recvControl(report, reportlength);

                    HidReportType reportType = (HidReportType)setup.wValueH;
                    switch (reportType)
                    {
                        case HidReportType::Feature:
                        {
                            ProcessReceivedSetFeatureReport(reportId, report, reportlength);

                            // Upon receipt of a Feature-Report, (during DATA transaction phase of SETUP/DATA/STATUS),
                            // IN-buffer must be set to zero-length, so 0 bytes are sent back for DATA1 packet.
                            // See Pg771 of the Atmel SAMD data sheet (Management of IN Transactions)
                            USBDevice.sendZlp(0);
                        }
                    }

                    free(report);

                    return true;
                }
            }

            break;
        }
    }

    return false;
}

void Microsoft_HidDevice::SendFeatureReport(const void* reportWithId, size_t reportLength)
{
    USBDevice.sendControl(reportWithId, reportLength);
}

void Microsoft_HidDevice::SendInputReport(const void* reportWithId, size_t reportLength)
{
    USBDevice.send(pluggedEndpoint, reportWithId, reportLength);
}

void Microsoft_HidDevice::ProcessReceivedGetFeatureReport(uint8_t reportId) noexcept
{
}

void Microsoft_HidDevice::ProcessReceivedSetFeatureReport(uint8_t reportId, uint8_t* data, uint16_t length) noexcept
{
}