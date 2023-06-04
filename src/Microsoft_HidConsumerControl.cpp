// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#include "Arduino.h"
#include "Microsoft_HidConsumerControl.h"
#include "ConsumerControlReports.h"
#include "ConsumerControlReportDescriptor.h"

Microsoft_HidConsumerControl::Microsoft_HidConsumerControl() : Microsoft_HidDevice(ConsumerControlReportDescriptor, sizeof(ConsumerControlReportDescriptor))
{
}

Microsoft_HidConsumerControl::~Microsoft_HidConsumerControl()
{
}

void Microsoft_HidConsumerControl::startIncrementVolume() noexcept
{
    VolumeIncrementReport report = {};

    report.Payload[0] = 1;
    SendInputReport(&report, sizeof(VolumeIncrementReport));
}

void Microsoft_HidConsumerControl::stopIncrementVolume() noexcept
{
    VolumeIncrementReport report = {};

    report.Payload[0] = 0;
    SendInputReport(&report, sizeof(VolumeIncrementReport));
}

void Microsoft_HidConsumerControl::startDecrementVolume() noexcept
{
    VolumeDecrementReport report = {};

    report.Payload[0] = 1;
    SendInputReport(&report, sizeof(VolumeDecrementReport));
}

void Microsoft_HidConsumerControl::stopDecrementVolume() noexcept
{
    VolumeDecrementReport report = {};

    report.Payload[0] = 0;
    SendInputReport(&report, sizeof(VolumeDecrementReport));
}

void Microsoft_HidConsumerControl::incrementVolume() noexcept
{
    VolumeReport report = {};

    // Windows-Shell has a bug where (for the Usage Volume[224]) the standard LC LogicalMin/Max of -1, +1, causes valid
    // values (-1, +1) to always be interpreted as 'some' -ve value; never +ve.
    // Solution here is to have LogicalMin/Max as -1, +2; where the device sends +2 (for -ve value) and +1 (for +ve value).
    report.Payload[0] = 1;
    SendInputReport(&report, sizeof(VolumeReport));
}

void Microsoft_HidConsumerControl::decrementVolume() noexcept
{
    VolumeReport report = {};

    // Windows-Shell has a bug where (for the Usage Volume[224]) the standard LC LogicalMin/Max of -1, +1, causes valid
    // values (-1, +1) to always be interpreted as 'some' -ve value; never +ve.
    // Solution here is to have LogicalMin/Max as -1, +2; where the device sends +2 (for -ve value) and +1 (for +ve value).
    report.Payload[0] = 2;
    SendInputReport(&report, sizeof(VolumeReport));
}

void Microsoft_HidConsumerControl::toggleMute() noexcept
{
    MuteReport report = {};

    report.Payload[0] = 1;
    SendInputReport(&report, sizeof(MuteReport));

    // Must reset state.
    report.Payload[0] = 0;
    SendInputReport(&report, sizeof(MuteReport));
}

void Microsoft_HidConsumerControl::startIncrementDisplayBrightness() noexcept
{
    DisplayBrightnessIncrementReport report = {};

    report.Payload[0] = 1;
    SendInputReport(&report, sizeof(DisplayBrightnessIncrementReport));
}

void Microsoft_HidConsumerControl::stopIncrementDisplayBrightness() noexcept
{
    DisplayBrightnessIncrementReport report = {};

    report.Payload[0] = 0;
    SendInputReport(&report, sizeof(DisplayBrightnessIncrementReport));
}

void Microsoft_HidConsumerControl::startDecrementDisplayBrightness() noexcept
{
    DisplayBrightnessDecrementReport report = {};

    report.Payload[0] = 1;
    SendInputReport(&report, sizeof(DisplayBrightnessDecrementReport));
}

void Microsoft_HidConsumerControl::stopDecrementDisplayBrightness() noexcept
{
    DisplayBrightnessDecrementReport report = {};

    report.Payload[0] = 0;
    SendInputReport(&report, sizeof(DisplayBrightnessDecrementReport));
}

void Microsoft_HidConsumerControl::startNavigateBackwards() noexcept
{
    NavigateBackwardsReport report = {};

    report.Payload[0] = 1;
    SendInputReport(&report, sizeof(NavigateBackwardsReport));
}

void Microsoft_HidConsumerControl::stopNavigateBackwards() noexcept
{
    NavigateBackwardsReport report = {};

    report.Payload[0] = 0;
    SendInputReport(&report, sizeof(NavigateBackwardsReport));
}

void Microsoft_HidConsumerControl::startNavigateForwards() noexcept
{
    NavigateForwardsReport report = {};

    report.Payload[0] = 1;
    SendInputReport(&report, sizeof(NavigateForwardsReport));
}

void Microsoft_HidConsumerControl::stopNavigateForwards() noexcept
{
    NavigateForwardsReport report = {};

    report.Payload[0] = 0;
    SendInputReport(&report, sizeof(NavigateForwardsReport));
}

void Microsoft_HidConsumerControl::startScanPreviousTrack() noexcept
{
    ScanPreviousTrackReport report = {};

    report.Payload[0] = 1;
    SendInputReport(&report, sizeof(ScanPreviousTrackReport));
}

void Microsoft_HidConsumerControl::stopScanPreviousTrack() noexcept
{
    ScanPreviousTrackReport report = {};

    report.Payload[0] = 0;
    SendInputReport(&report, sizeof(ScanPreviousTrackReport));
}

void Microsoft_HidConsumerControl::startScanNextTrack() noexcept
{
    ScanNextTrackReport report = {};

    report.Payload[0] = 1;
    SendInputReport(&report, sizeof(ScanNextTrackReport));
}

void Microsoft_HidConsumerControl::stopScanNextTrack() noexcept
{
    ScanNextTrackReport report = {};

    report.Payload[0] = 0;
    SendInputReport(&report, sizeof(ScanNextTrackReport));
}

void Microsoft_HidConsumerControl::play() noexcept
{
    PlayReport report = {};

    report.Payload[0] = 1;
    SendInputReport(&report, sizeof(PlayReport));

    // Must reset state.
    report.Payload[0] = 0;
    SendInputReport(&report, sizeof(PlayReport));
}

void Microsoft_HidConsumerControl::pause() noexcept
{
    PauseReport report = {};

    report.Payload[0] = 1;
    SendInputReport(&report, sizeof(PauseReport));

    // Must reset state.
    report.Payload[0] = 0;
    SendInputReport(&report, sizeof(PauseReport));
}

void Microsoft_HidConsumerControl::togglePlayPause() noexcept
{
    PlayPauseReport report = {};

    report.Payload[0] = 1;
    SendInputReport(&report, sizeof(PlayPauseReport));

    // Must reset state.
    report.Payload[0] = 0;
    SendInputReport(&report, sizeof(PlayPauseReport));
}

void Microsoft_HidConsumerControl::toggleCameraAccess() noexcept
{
    CameraAccessToggleReport report = {};

    report.Payload[0] = 1;
    SendInputReport(&report, sizeof(CameraAccessToggleReport));

    // Must reset state.
    report.Payload[0] = 0;
    SendInputReport(&report, sizeof(CameraAccessToggleReport));
}

void Microsoft_HidConsumerControl::toggleOpenGamebar() noexcept
{
    GamebarReport report = {};

    report.ConsumerArrayItem = GamebarReport::ConsumerArrayValues::InvokeCaptureInterface;
    SendInputReport(&report, sizeof(GamebarReport));

    // Must reset state.
    report.ConsumerArrayItem = GamebarReport::ConsumerArrayValues::Invalid;
    SendInputReport(&report, sizeof(GamebarReport));
}

void Microsoft_HidConsumerControl::toggleGameRecording() noexcept
{
    GamebarReport report = {};

    report.ConsumerArrayItem = GamebarReport::ConsumerArrayValues::StartorStopGameRecording;
    SendInputReport(&report, sizeof(GamebarReport));

    // Must reset state.
    report.ConsumerArrayItem = GamebarReport::ConsumerArrayValues::Invalid;
    SendInputReport(&report, sizeof(GamebarReport));
}

void Microsoft_HidConsumerControl::saveBackgroundGameRecordingClip() noexcept
{
    GamebarReport report = {};

    report.ConsumerArrayItem = GamebarReport::ConsumerArrayValues::HistoricalGameCapture;
    SendInputReport(&report, sizeof(GamebarReport));

    // Must reset state.
    report.ConsumerArrayItem = GamebarReport::ConsumerArrayValues::Invalid;
    SendInputReport(&report, sizeof(GamebarReport));
}

void Microsoft_HidConsumerControl::saveGameScreenShot() noexcept
{
    GamebarReport report = {};

    report.ConsumerArrayItem = GamebarReport::ConsumerArrayValues::CaptureGameScreenshot;
    SendInputReport(&report, sizeof(GamebarReport));

    // Must reset state.
    report.ConsumerArrayItem = GamebarReport::ConsumerArrayValues::Invalid;
    SendInputReport(&report, sizeof(GamebarReport));
}

void Microsoft_HidConsumerControl::launchMailApplication() noexcept
{
    ApplicationLaunchReport report = {};

    report.ConsumerArrayItem = ApplicationLaunchReport::ConsumerArrayValues::ALEmailReader;
    SendInputReport(&report, sizeof(ApplicationLaunchReport));

    // Must reset state.
    report.ConsumerArrayItem = ApplicationLaunchReport::ConsumerArrayValues::Invalid;
    SendInputReport(&report, sizeof(ApplicationLaunchReport));
}

void Microsoft_HidConsumerControl::launchCalculatorApplication() noexcept
{
    ApplicationLaunchReport report = {};

    report.ConsumerArrayItem = ApplicationLaunchReport::ConsumerArrayValues::ALCalculator;
    SendInputReport(&report, sizeof(ApplicationLaunchReport));

    // Must reset state.
    report.ConsumerArrayItem = ApplicationLaunchReport::ConsumerArrayValues::Invalid;
    SendInputReport(&report, sizeof(ApplicationLaunchReport));
}

void Microsoft_HidConsumerControl::launchWindowsExplorer() noexcept
{
    ApplicationLaunchReport report = {};

    report.ConsumerArrayItem = ApplicationLaunchReport::ConsumerArrayValues::ALLocalMachineBrowser;
    SendInputReport(&report, sizeof(ApplicationLaunchReport));

    // Must reset state.
    report.ConsumerArrayItem = ApplicationLaunchReport::ConsumerArrayValues::Invalid;
    SendInputReport(&report, sizeof(ApplicationLaunchReport));
}

void Microsoft_HidConsumerControl::launchWindowsMediaPlayer() noexcept
{
    ApplicationLaunchReport report = {};

    report.ConsumerArrayItem = ApplicationLaunchReport::ConsumerArrayValues::ALConsumerControlConfiguration;
    SendInputReport(&report, sizeof(ApplicationLaunchReport));

    // Must reset state.
    report.ConsumerArrayItem = ApplicationLaunchReport::ConsumerArrayValues::Invalid;
    SendInputReport(&report, sizeof(ApplicationLaunchReport));
}

void Microsoft_HidConsumerControl::invokeApplicationSpecificSearch() noexcept
{
    ApplicationControlReport report = {};

    report.ConsumerArrayItem = ApplicationControlReport::ConsumerArrayValues::ACSearch;
    SendInputReport(&report, sizeof(ApplicationControlReport));

    // Must reset state.
    report.ConsumerArrayItem = ApplicationControlReport::ConsumerArrayValues::Invalid;
    SendInputReport(&report, sizeof(ApplicationControlReport));
}

void Microsoft_HidConsumerControl::invokeApplicationSpecificHome() noexcept
{
    ApplicationControlReport report = {};

    report.ConsumerArrayItem = ApplicationControlReport::ConsumerArrayValues::ACHome;
    SendInputReport(&report, sizeof(ApplicationControlReport));

    // Must reset state.
    report.ConsumerArrayItem = ApplicationControlReport::ConsumerArrayValues::Invalid;
    SendInputReport(&report, sizeof(ApplicationControlReport));
}

void Microsoft_HidConsumerControl::invokeApplicationSpecificStop() noexcept
{
    ApplicationControlReport report = {};

    report.ConsumerArrayItem = ApplicationControlReport::ConsumerArrayValues::ACStop;
    SendInputReport(&report, sizeof(ApplicationControlReport));

    // Must reset state.
    report.ConsumerArrayItem = ApplicationControlReport::ConsumerArrayValues::Invalid;
    SendInputReport(&report, sizeof(ApplicationControlReport));
}

void Microsoft_HidConsumerControl::invokeApplicationSpecificRefresh() noexcept
{
    ApplicationControlReport report = {};

    report.ConsumerArrayItem = ApplicationControlReport::ConsumerArrayValues::ACRefresh;
    SendInputReport(&report, sizeof(ApplicationControlReport));

    // Must reset state.
    report.ConsumerArrayItem = ApplicationControlReport::ConsumerArrayValues::Invalid;
    SendInputReport(&report, sizeof(ApplicationControlReport));
}
