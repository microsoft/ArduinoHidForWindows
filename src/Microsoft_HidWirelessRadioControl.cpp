// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#include "Arduino.h"
#include "Microsoft_HidWirelessRadioControl.h"
#include "WirelessRadioControlReports.h"
#include "WirelessRadioControlReportDescriptor.h"

Microsoft_HidWirelessRadioControl::Microsoft_HidWirelessRadioControl() : Microsoft_HidDevice(WirelessRadioControlDescriptor, sizeof(WirelessRadioControlDescriptor))
{
    m_isWirelessRadiosOnLed = false;
}

Microsoft_HidWirelessRadioControl::~Microsoft_HidWirelessRadioControl()
{
}

void Microsoft_HidWirelessRadioControl::getCurrentState(bool* isWirelessRadiosOnLed) noexcept
{
    *isWirelessRadiosOnLed = m_isWirelessRadiosOnLed;
}

void Microsoft_HidWirelessRadioControl::toggleAirplaneMode()
{
    WirelessRadioToggleButtonReport report = {};

    report.Payload[0] = 1;
    SendInputReport(&report, sizeof(WirelessRadioToggleButtonReport));
}

void Microsoft_HidWirelessRadioControl::enableAirplaneMode()
{
    WirelessRadioSliderReport report = {};

    report.Payload[0] = 1;
    SendInputReport(&report, sizeof(WirelessRadioSliderReport));
}

void Microsoft_HidWirelessRadioControl::disableAirplaneMode()
{
    WirelessRadioSliderReport report = {};

    report.Payload[0] = 0;
    SendInputReport(&report, sizeof(WirelessRadioSliderReport));
}

void Microsoft_HidWirelessRadioControl::ProcessReceivedOutputReport(uint8_t reportId, uint8_t* data, uint16_t length) noexcept
{
    switch (reportId)
    {
        case WIRELESS_RADIO_LED_REPORT_ID:
        {
            UpdateLedStateFromReport(data, length);
            break;
        }
    }
}

void Microsoft_HidWirelessRadioControl::UpdateLedStateFromReport(uint8_t* data, uint16_t length) noexcept
{
    WirelessRadioLedReport report = {};
    memcpy(&report, data, sizeof(WirelessRadioLedReport));

    if (report.ReportId == WIRELESS_RADIO_LED_REPORT_ID)
    {
        m_isWirelessRadiosOnLed = report.Payload[0];
    }
}