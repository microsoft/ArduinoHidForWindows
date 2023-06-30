// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#pragma once

#pragma pack(push,1)

struct TelephonyHeadsetHookSwitchReport
{
    uint8_t ReportId = 1;
    uint8_t Payload[1];
};

struct TelephonyHeadsetPhoneMuteReport
{
    uint8_t ReportId = 2;
    uint8_t Payload[1];
};

struct TelephonyHeadsetRedialReport
{
    uint8_t ReportId = 3;
    uint8_t Payload[1];
};

struct TelephonyHeadsetFlashReport
{
    uint8_t ReportId = 4;
    uint8_t Payload[1];
};

struct TelephonyHeadsetSendReport
{
    uint8_t ReportId = 5;
    uint8_t Payload[1];
};

struct TelephonyHeadsetDropReport
{
    uint8_t ReportId = 6;
    uint8_t Payload[1];
};

struct TelephonyHeadsetKeyPadReport
{
    uint8_t ReportId = 7;
    uint8_t Payload[1];
};

#define TELEPHONY_HEADSET_HOLD_LED_REPORT_ID 1
struct TelephonyHeadsetHoldLedReport
{
    uint8_t ReportId = TELEPHONY_HEADSET_HOLD_LED_REPORT_ID;
    uint8_t Payload[1];
};

#define TELEPHONY_HEADSET_OFF_HOOK_LED_REPORT_ID 2
struct TelephonyHeadsetOffHookLedReport
{
    uint8_t ReportId = TELEPHONY_HEADSET_OFF_HOOK_LED_REPORT_ID;
    uint8_t Payload[1];
};

#define TELEPHONY_HEADSET_RING_LED_REPORT_ID 3
struct TelephonyHeadsetRingLedReport
{
    uint8_t ReportId = TELEPHONY_HEADSET_RING_LED_REPORT_ID;
    uint8_t Payload[1];
};

#define TELEPHONY_HEADSET_LINE_LED_REPORT_ID 4
struct TelephonyHeadsetLineLedReport
{
    uint8_t ReportId = TELEPHONY_HEADSET_LINE_LED_REPORT_ID;
    uint8_t Payload[1];
};

#pragma pack(pop)