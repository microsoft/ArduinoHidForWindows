// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#include <Microsoft_HidForWindows.h>
#include <Adafruit_NeoPixel.h>

// Utilizing dual-button components for common actions.
// https://www.seeedstudio.com/Grove-Dual-Button-p-4529.html
// Note: switch on PIN5 is unused.
const int ANSWER_CALL_MOMENTARY_SWITCH_PIN = 2;
const int HANGUP_CALL_MOMENTARY_SWITCH_PIN = 3;
const int REDIAL_CALL_MOMENTARY_SWITCH_PIN = 4;

// Utilizing a micro-switch for the hook-button.
// https://www.seeedstudio.com/Grove-Micro-Switch.html
const int HOOK_MOMENTARY_SWITCH_PIN = 7;

Microsoft_MomentarySwitch answerCallSwitch(ANSWER_CALL_MOMENTARY_SWITCH_PIN, LOW);
Microsoft_MomentarySwitch hangupCallSwitch(HANGUP_CALL_MOMENTARY_SWITCH_PIN, LOW);
Microsoft_MomentarySwitch redialSwitch(REDIAL_CALL_MOMENTARY_SWITCH_PIN, LOW);
Microsoft_MomentarySwitch hookSwitch(HOOK_MOMENTARY_SWITCH_PIN, LOW);

// Having a PIN for each LED seems a little excessive, so here using a programmable LED bar.
const int HOLD_LED = 0;
const int OFF_HOOK_LED = 1;
const int RINGING_LED = 2;
const int LINE_IN_USE_LED = 3;

// Grove - RGB LED Stick (15-WS2813 Mini)
// https://www.seeedstudio.com/Grove-RGB-LED-Stick-10-WS2813-Mini.html
const int LED_STRIP_PIN = 6;
const int LED_STRING_PIXEL_COUNT = 10;
Adafruit_NeoPixel ledStrip = Adafruit_NeoPixel(LED_STRING_PIXEL_COUNT, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);

// LED colour when 'on' is green.
uint32_t defaultLedColour = ledStrip.Color(0, 10, 0);
uint32_t offLedColour = ledStrip.Color(0, 0, 0);

Microsoft_HidTelephonyHeadset telephonyHeadset = Microsoft_HidTelephonyHeadset();

void setup()
{
    // On Arduino-Zero, PIN0/PIN1 UART is Serial1.
    // In this example, a keypad is connected to this serial-port.
    Serial1.begin(9600);

    // Initialize the NeoPixel library.
    ledStrip.begin();
    ledStrip.clear();

    ledStrip.show();
}

void loop()
{
    TelephonyHeadsetLedUpdate update;
    telephonyHeadset.getCurrentState(&update);

    if (hookSwitch.updateState())
    {
        if (hookSwitch.isPressed())
        {
            telephonyHeadset.indicateOnHook();
        }
        else
        {
            telephonyHeadset.indicateOffHook();
        }
    }

    if (answerCallSwitch.updateState())
    {
        if (answerCallSwitch.isPressed())
        {
            telephonyHeadset.answerCall();
        }
    }

    if (hangupCallSwitch.updateState())
    {
        if (hangupCallSwitch.isPressed())
        {
            telephonyHeadset.hangupCall();
        }
    }

    if (redialSwitch.updateState())
    {
        if (redialSwitch.isPressed())
        {
            telephonyHeadset.redial();
        }
    }

    bool isDigit = false;
    uint8_t pressedDigit = 0;
    char pressedSpecialty = '\0';
    if (getKeypadDigitOrSpecialty(&isDigit, &pressedDigit, &pressedSpecialty))
    {
        if (isDigit)
        {
            telephonyHeadset.enterKeypadDigit(pressedDigit);
        }
        else
        {
            telephonyHeadset.enterKeypadSpecialty(pressedSpecialty);
        }
    }

    setLedsFromUpdate(&update);
}

void setLedsFromUpdate(TelephonyHeadsetLedUpdate* update)
{
    bool needsUpdate = false;

    needsUpdate |= setLed(update->OnHold, HOLD_LED);
    needsUpdate |= setLed(update->OffHook, OFF_HOOK_LED);
    needsUpdate |= setLed(update->Ringing, RINGING_LED);
    needsUpdate |= setLed(update->LineInUse, LINE_IN_USE_LED);

    // Only call update on the NeoPixels when something has changed, show() takes a long time to execute.
    if (needsUpdate)
    {
        // Send the updated pixel color to hardware.
        ledStrip.show();
    }
}

bool setLed(bool ledState, const int ledPin)
{
    bool needsUpdate = (ledStrip.getPixelColor(ledPin) == defaultLedColour);
    if (ledState != needsUpdate)
    {
        ledStrip.setPixelColor(ledPin, ledState ? defaultLedColour : offLedColour);
        return true;
    }

    return false;
}

bool getKeypadDigitOrSpecialty(bool* isDigit, uint8_t* digit, char* specialty)
{
    char pressedChar = getKeypadKey();

    if (pressedChar == '\0')
    {
        return false;
    }

    if (pressedChar >= '1' && pressedChar <= '9')
    {
        *isDigit = true;
        *digit = (pressedChar - '1' + 1);
    }
    else if (pressedChar == '0')
    {
        *isDigit = true;
        *digit = 0;
    }
    else
    {
        *isDigit = false;
        *specialty = pressedChar;
    }

    return true;
}

char getKeypadKey()
{
    // Sorted in-order.
    // First char corresponds to 0xE1 ... last to 0xEC.
    // Mapping from https://github.com/Seeed-Studio/Seeed_Sketch_12ChKeypad/blob/master/12_Channel_Keypad.ino
    char keyPadCharacters[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '0', '#'};

    if (Serial1.available())
    {
        uint8_t data = Serial1.read();

        // Assumed input is always in valid range.
        int index = (data - 0xE1);

        return keyPadCharacters[index];
    }

    // No key pressed.
    return '\0';
}