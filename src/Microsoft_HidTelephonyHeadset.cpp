// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#include "Arduino.h"
#include "Microsoft_HidTelephonyHeadset.h"
#include "TelephonyHeadsetReports.h"
#include "TelephonyHeadsetReportDescriptor.h"

Microsoft_HidTelephonyHeadset::Microsoft_HidTelephonyHeadset() : Microsoft_HidDevice(TelephonyHeadsetDescriptor, sizeof(TelephonyHeadsetDescriptor))
{
    m_ledState = {0};
}

Microsoft_HidTelephonyHeadset::~Microsoft_HidTelephonyHeadset()
{
}

void Microsoft_HidTelephonyHeadset::getCurrentState(TelephonyHeadsetLedUpdate* currentState) noexcept
{
    memcpy(currentState, &m_ledState, sizeof(TelephonyHeadsetLedUpdate));
}

void Microsoft_HidTelephonyHeadset::indicateOnHook() noexcept
{
    TelephonyHeadsetHookSwitchReport report = {};

    report.Payload[0] = 0;
    SendInputReport(&report, sizeof(TelephonyHeadsetHookSwitchReport));
}

void Microsoft_HidTelephonyHeadset::indicateOffHook() noexcept
{
    TelephonyHeadsetHookSwitchReport report = {};

    report.Payload[0] = 1;
    SendInputReport(&report, sizeof(TelephonyHeadsetHookSwitchReport));
}

void Microsoft_HidTelephonyHeadset::answerCall() noexcept
{
    TelephonyHeadsetSendReport report = {};

    report.Payload[0] = 1;
    SendInputReport(&report, sizeof(TelephonyHeadsetSendReport));

    // Must reset state.
    report.Payload[0] = 0;
    SendInputReport(&report, sizeof(TelephonyHeadsetSendReport));
}

void Microsoft_HidTelephonyHeadset::hangupCall() noexcept
{
    TelephonyHeadsetDropReport report = {};

    report.Payload[0] = 1;
    SendInputReport(&report, sizeof(TelephonyHeadsetDropReport));

    // Must reset state.
    report.Payload[0] = 0;
    SendInputReport(&report, sizeof(TelephonyHeadsetDropReport));
}

void Microsoft_HidTelephonyHeadset::hookFlash() noexcept
{
    TelephonyHeadsetFlashReport report = {};

    report.Payload[0] = 1;
    SendInputReport(&report, sizeof(TelephonyHeadsetFlashReport));

    // Must reset state.
    report.Payload[0] = 0;
    SendInputReport(&report, sizeof(TelephonyHeadsetFlashReport));
}

void Microsoft_HidTelephonyHeadset::redial() noexcept
{
    TelephonyHeadsetRedialReport report = {};

    report.Payload[0] = 1;
    SendInputReport(&report, sizeof(TelephonyHeadsetRedialReport));

    // Must reset state.
    report.Payload[0] = 0;
    SendInputReport(&report, sizeof(TelephonyHeadsetRedialReport));
}

void Microsoft_HidTelephonyHeadset::mute() noexcept
{
    TelephonyHeadsetPhoneMuteReport report = {};

    report.Payload[0] = 1;
    SendInputReport(&report, sizeof(TelephonyHeadsetPhoneMuteReport));
}

void Microsoft_HidTelephonyHeadset::unmute() noexcept
{
    TelephonyHeadsetPhoneMuteReport report = {};

    report.Payload[0] = 0;
    SendInputReport(&report, sizeof(TelephonyHeadsetPhoneMuteReport));
}

void Microsoft_HidTelephonyHeadset::enterKeypadDigit(uint8_t digit) noexcept
{
    if (digit > 9)
    {
        // Invalid digit, ignore.
        return;
    }

    TelephonyHeadsetKeyPadReport report = {};

    report.Payload[0] = digit + 1; // Offset starts at 1
    SendInputReport(&report, sizeof(TelephonyHeadsetKeyPadReport));
}

void Microsoft_HidTelephonyHeadset::enterKeypadCharacter(char c) noexcept
{
    TelephonyHeadsetKeyPadReport report = {};

    switch (c)
    {
        case 'A':
        case 'B':
        case 'C':
        {
            report.Payload[0] = 3;
            break;
        }
        case 'D':
        case 'E':
        case 'F':
        {
            report.Payload[0] = 4;
            break;
        }
        case 'G':
        case 'H':
        case 'I':
        {
            report.Payload[0] = 5;
            break;
        }
        case 'J':
        case 'K':
        case 'L':
        {
            report.Payload[0] = 6;
            break;
        }
        case 'M':
        case 'N':
        case 'O':
        {
            report.Payload[0] = 7;
            break;
        }
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        {
            report.Payload[0] = 8;
            break;
        }
        case 'T':
        case 'U':
        case 'V':
        {
            report.Payload[0] = 9;
            break;
        }
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
        {
            report.Payload[0] = 10;
            break;
        }
        default:
        {
            // Invalid char, ignore.
        }
    }

    SendInputReport(&report, sizeof(TelephonyHeadsetKeyPadReport));
}

void Microsoft_HidTelephonyHeadset::enterKeypadSpecialty(char c) noexcept
{
    TelephonyHeadsetKeyPadReport report = {};

    switch (c)
    {
        case '*':
        {
            report.Payload[0] = 11;
            break;
        }
        case '#':
        {
            report.Payload[0] = 12;
            break;
        }
        case 'A':
        {
            report.Payload[0] = 13;
            break;
        }
        case 'B':
        {
            report.Payload[0] = 14;
            break;
        }
        case 'C':
        {
            report.Payload[0] = 15;
            break;
        }
        case 'D':
        {
            report.Payload[0] = 16;
            break;
        }
        default:
        {
            // Invalid char, ignore.
        }
    }

    SendInputReport(&report, sizeof(TelephonyHeadsetKeyPadReport));
}

void Microsoft_HidTelephonyHeadset::ProcessReceivedOutputReport(uint8_t reportId, uint8_t* data, uint16_t length) noexcept
{
    switch (reportId)
    {
        case TELEPHONY_HEADSET_HOLD_LED_REPORT_ID:
        {
            TelephonyHeadsetHoldLedReport report = {};
            memcpy(&report, data, sizeof(TelephonyHeadsetHoldLedReport));

            if (report.ReportId == TELEPHONY_HEADSET_HOLD_LED_REPORT_ID)
            {
                m_ledState.OnHold = report.Payload[0];
            }

            break;
        }
        case TELEPHONY_HEADSET_OFF_HOOK_LED_REPORT_ID:
        {
            TelephonyHeadsetOffHookLedReport report = {};
            memcpy(&report, data, sizeof(TelephonyHeadsetOffHookLedReport));

            if (report.ReportId == TELEPHONY_HEADSET_OFF_HOOK_LED_REPORT_ID)
            {
                m_ledState.OffHook = report.Payload[0];
            }

            break;
        }
        case TELEPHONY_HEADSET_RING_LED_REPORT_ID:
        {
            TelephonyHeadsetRingLedReport report = {};
            memcpy(&report, data, sizeof(TelephonyHeadsetRingLedReport));

            if (report.ReportId == TELEPHONY_HEADSET_RING_LED_REPORT_ID)
            {
                m_ledState.Ringing = report.Payload[0];
            }

            break;
        }
        case TELEPHONY_HEADSET_LINE_LED_REPORT_ID:
        {
            TelephonyHeadsetLineLedReport report = {};
            memcpy(&report, data, sizeof(TelephonyHeadsetLineLedReport));

            if (report.ReportId == TELEPHONY_HEADSET_LINE_LED_REPORT_ID)
            {
                m_ledState.LineInUse = report.Payload[0];
            }

            break;
        }
    }
}
