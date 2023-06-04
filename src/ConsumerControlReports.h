// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#pragma once

#pragma pack(push,1)

struct VolumeIncrementReport
{
    uint8_t ReportId = 1;
    uint8_t Payload[1];
};

struct VolumeDecrementReport
{
    uint8_t ReportId = 2;
    uint8_t Payload[1];
};

struct VolumeReport
{
    uint8_t ReportId = 3;
    uint8_t Payload[1];
};

struct DisplayBrightnessIncrementReport
{
    uint8_t ReportId = 4;
    uint8_t Payload[1];
};

struct DisplayBrightnessDecrementReport
{
    uint8_t ReportId = 5;
    uint8_t Payload[1];
};

struct GamebarReport
{
    enum class ConsumerArrayValues : uint8_t
    {
        Invalid = 0,
        InvokeCaptureInterface,
        StartorStopGameRecording,
        HistoricalGameCapture,
        CaptureGameScreenshot,
    };

    uint8_t ReportId = 6;
    ConsumerArrayValues ConsumerArrayItem;
};

struct ApplicationLaunchReport
{
    enum class ConsumerArrayValues : uint8_t
    {
        Invalid = 0,
        ALEmailReader,
        ALCalculator,
        ALLocalMachineBrowser,
        ALConsumerControlConfiguration,
    };

    uint8_t ReportId = 7;
    ConsumerArrayValues ConsumerArrayItem;
};

struct ApplicationControlReport
{
    enum class ConsumerArrayValues : uint8_t
    {
        Invalid = 0,
        ACSearch,
        ACHome,
        ACStop,
        ACRefresh,
    };

    uint8_t ReportId = 8;
    ConsumerArrayValues ConsumerArrayItem;
};

struct NavigateBackwardsReport
{
    uint8_t ReportId = 9;
    uint8_t Payload[1];
};

struct NavigateForwardsReport
{
    uint8_t ReportId = 10;
    uint8_t Payload[1];
};

struct ScanPreviousTrackReport
{
    uint8_t ReportId = 11;
    uint8_t Payload[1];
};

struct ScanNextTrackReport
{
    uint8_t ReportId = 12;
    uint8_t Payload[1];
};

struct PlayReport
{
    uint8_t ReportId = 13;
    uint8_t Payload[1];
};

struct PauseReport
{
    uint8_t ReportId = 14;
    uint8_t Payload[1];
};

struct PlayPauseReport
{
    uint8_t ReportId = 15;
    uint8_t Payload[1];
};

struct MuteReport
{
    uint8_t ReportId = 16;
    uint8_t Payload[1];
};

struct CameraAccessToggleReport
{
    uint8_t ReportId = 17;
    uint8_t Payload[1];
};

#pragma pack(pop)