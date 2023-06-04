// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#pragma once

#if !defined(USBCON)

#warning "Platform does not support PluggableUSB"

#else

#include <Microsoft_HidDevice.h>

// ConsumerControl devices typically provide application-specific control of the foreground-application, where
// applications are expected to open/read from the HID directly.
// Over the years, many of these have been incorporated as system-wide settings (see descriptions for behaviour),
// or automatically-translated to WindowMessages/VirtualKeys (of the foreground-application) for developer convenience.
//
// Note: It is NOT possible to know the system-state for anything referenced below.
// Note: For any method with the prefix start*, it is expected that the corresponding stop* will also be called.
class Microsoft_HidConsumerControl : public Microsoft_HidDevice
{
public:
    // Must be constructed in global-scope to ensure descriptors are picked-up during USB initialization.
    Microsoft_HidConsumerControl();

    ~Microsoft_HidConsumerControl();

    // When 'start'ed, repeatedly increments system-volume, until 'stop'ed.
    // On Windows (today), this corresponds to a 2%-point increase every 0.5secs.
    // This behaviour is typically implemented by holding-down a button (correspond to start*), and when button is released calling stop*.
    void startIncrementVolume() noexcept;
    void stopIncrementVolume() noexcept;

    // When 'start'ed, repeatedly decrements system-volume, until 'stop'ed.
    // On Windows (today), this corresponds to a 2%-point decrease every 0.5secs.
    // This behaviour is typically implemented by holding-down a button (correspond to start*), and when button is released calling stop*.
    void startDecrementVolume() noexcept;
    void stopDecrementVolume() noexcept;

    // Increment/decrements the system-volume (APPCOMMAND_VOLUME_UP:APPCOMMAND_VOLUME_UP/APPCOMMAND_VOLUME_DOWN) by a single, fixed amount.
    // On Windows (today), this corresponds to a 2%-point increase/decrease.
    void incrementVolume() noexcept;
    void decrementVolume() noexcept;

    // Toggles mute of system-volume (VK_VOLUME_MUTE).
    void toggleMute() noexcept;

    // When 'start'ed, repeatedly increments system-screen brightess, until 'stop'ed.
    // On Windows (today), this corresponds to a 10%-point increase every 0.5secs.
    // This behaviour is typically implemented by holding-down a button (correspond to start*), and when button is released calling stop*.
    void startIncrementDisplayBrightness() noexcept;
    void stopIncrementDisplayBrightness() noexcept;

    // When 'start'ed, repeatedly decrements system-screen brightess, until 'stop'ed.
    // On Windows (today), this corresponds to a 10%-point decrease every 0.5secs.
    // This behaviour is typically implemented by holding-down a button (correspond to start*), and when button is released calling stop*.
    void startDecrementDisplayBrightness() noexcept;
    void stopDecrementDisplayBrightness() noexcept;

    // When 'start'ed, repeatedly navigates backwards (VK_BROWSER_BACK) in the foreground-application, until 'stop'ed.
    // On Windows (today), this corresponds to a navigation every 0.5secs.
    // This behaviour is typically implemented by holding-down a button (correspond to start*), and when button is released calling stop*.
    void startNavigateBackwards() noexcept;
    void stopNavigateBackwards() noexcept;

    // When 'start'ed, repeatedly navigates forwards (VK_BROWSER_FORWARD) in the foreground-application, until 'stop'ed.
    // On Windows (today), this corresponds to a navigation every 0.5secs.
    // This behaviour is typically implemented by holding-down a button (correspond to start*), and when button is released calling stop*.
    void startNavigateForwards() noexcept;
    void stopNavigateForwards() noexcept;

    // When 'start'ed, repeatedly seeks to previous-track (VK_MEDIA_PREV_TRACK) in the foreground-application, until 'stop'ed.
    // For (non-legacy) 'Windows Media Player', this corresponds to a seek every 0.5secs.
    // This behaviour is typically implemented by holding-down a button (correspond to start*), and when button is released calling stop*.
    void startScanPreviousTrack() noexcept;
    void stopScanPreviousTrack() noexcept;

    // When 'start'ed, repeatedly seeks to next-track (VK_MEDIA_NEXT_TRACK) in the foreground-application, until 'stop'ed.
    // For (non-legacy) 'Windows Media Player', this corresponds to a seek every 0.5secs.
    // This behaviour is typically implemented by holding-down a button (correspond to start*), and when button is released calling stop*.
    void startScanNextTrack() noexcept;
    void stopScanNextTrack() noexcept;

    // Starts media playing in the foreground-application by notifying the window with WM_APPCOMMAND:APPCOMMAND_MEDIA_PLAY.
    // For (non-legacy) 'Windows Media Player', this functions as a play/pause toggle.
    // For (legacy) 'Windows Media Player', this functions strictly as a play button.
    void play() noexcept;

    // Pauses media playing in the foreground-application by notifying the window with WM_APPCOMMAND:APPCOMMAND_MEDIA_PAUSE.
    // For (non-legacy) 'Windows Media Player', this functions as a play/pause toggle.
    // For (legacy) 'Windows Media Player', this functions strictly as a pause button.
    void pause() noexcept;

    // Invokes 'play/pause' (VK_MEDIA_PLAY_PAUSE) of media playing in the foreground-application.
    // For (non-legacy) 'Windows Media Player', this functions as a play/pause toggle.
    // For (legacy) 'Windows Media Player', this functions as a play/pause toggle.
    void togglePlayPause() noexcept;

    // Toggles whether system and applications have access to webcams.
    // When disabled, no application can access the camera.
    void toggleCameraAccess() noexcept;

    // Opens/closes the Gamebar.
    void toggleOpenGamebar() noexcept;

    // Starts/stops Game Recording/Capturing.
    void toggleGameRecording() noexcept;

    // Saves (up-to) the last 30secs of a game-capture.
    // Note: User must have previously enabled background-recording, via GameBar>Settings>Capturing>'Record in the background while I'm playing a game'
    void saveBackgroundGameRecordingClip() noexcept;

    // Generates+saves a screenshot of the currently playing game.
    void saveGameScreenShot() noexcept;

    // Launches a new instance of the registered email client (e.g. Outlook).
    void launchMailApplication() noexcept;

    // Launches a new instance of the in-built Calculator app.
    void launchCalculatorApplication() noexcept;

    // Launches a new instance of explorer.exe
    void launchWindowsExplorer() noexcept;

    // Launches a new instance of (legacy) Windows Media Player.
    void launchWindowsMediaPlayer() noexcept;

    // Invokes 'search' (VK_BROWSER_SEARCH) in the foreground-application.
    // When no application in the foreground, Windows Shell search invoked.
    void invokeApplicationSpecificSearch() noexcept;

    // Invokes 'home' (VK_BROWSER_HOME) in the foreground-application.
    // When no application in the foreground, Microsoft Edge browser is launched (to Home-page)
    void invokeApplicationSpecificHome() noexcept;

    // Invokes 'stop' (VK_BROWSER_STOP) in the foreground-application.
    // Microsoft Edge browser responds to this invocation.
    void invokeApplicationSpecificStop() noexcept;

    // Invokes 'refresh' (VK_BROWSER_REFRESH) in the foreground-application.
    // Microsoft Edge browser responds to this invocation.
    void invokeApplicationSpecificRefresh() noexcept;
};

#endif