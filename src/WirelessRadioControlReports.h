// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#pragma once

#pragma pack(push,1)

struct WirelessRadioToggleButtonReport
{
    uint8_t ReportId = 1;
    uint8_t Payload[1];
};

struct WirelessRadioSliderReport
{
    uint8_t ReportId = 2;
    uint8_t Payload[1];
};

#define WIRELESS_RADIO_LED_REPORT_ID 1
struct WirelessRadioLedReport
{
    uint8_t ReportId = WIRELESS_RADIO_LED_REPORT_ID;
    uint8_t Payload[1];
};

#pragma pack(pop)