// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#include "Arduino.h"
#include "Microsoft_HidSystemControl.h"
#include "SystemControlReports.h"
#include "SystemControlReportDescriptor.h"

Microsoft_HidSystemControl::Microsoft_HidSystemControl() : Microsoft_HidDevice(SystemControlDescriptor, sizeof(SystemControlDescriptor))
{
}

Microsoft_HidSystemControl::~Microsoft_HidSystemControl()
{
}

void Microsoft_HidSystemControl::powerdown() noexcept
{
    SystemControlPowerReport report = {};

    report.Payload[0] = 0b00000001;
    SendInputReport(&report, sizeof(SystemControlPowerReport));
}

void Microsoft_HidSystemControl::sleep() noexcept
{
    SystemControlPowerReport report = {};

    report.Payload[0] = 0b00000010;
    SendInputReport(&report, sizeof(SystemControlPowerReport));
}
