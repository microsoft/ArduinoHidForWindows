// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#include "Arduino.h"
#include "Microsoft_HidLampArray.h"
#include "LampArrayReports.h"
#include "LampArrayReportDescriptor.h"

#define LAMP_UPDATE_FLAG_UPDATE_COMPLETE 1

#define MILLISECONDS_TO_MICROSECONDS(x) (x * 1000)
#define MILLIMETERS_TO_MICROMETERS(x) (x * 1000)

Microsoft_HidLampArray::Microsoft_HidLampArray(
    uint16_t lampCount, 
    uint32_t boundingBoxWidthInMillimeters, 
    uint32_t boundingBoxHeightInMillimeters, 
    uint32_t boundingBoxDepthInMillimeters, 
    uint32_t kind, 
    uint32_t minUpdateInternalInMilliseconds,
    LampAttributes* attributes) : Microsoft_HidDevice(LampArrayReportDescriptor, sizeof(LampArrayReportDescriptor))
{
    m_lampCount = lampCount;

    // TODO: throw error if m_lampCount > 65535.

    m_boundingBoxWidthInMillimeters = boundingBoxWidthInMillimeters;
    m_boundingBoxHeightInMillimeters = boundingBoxHeightInMillimeters;
    m_boundingBoxDepthInMillimeters = boundingBoxDepthInMillimeters;
    m_kind = kind;
    m_minUpdateInternalInMilliseconds = minUpdateInternalInMilliseconds;

    m_lampAttributes = (LampAttributes*)malloc(sizeof(LampAttributes) * m_lampCount);
    memcpy(m_lampAttributes, attributes, sizeof(LampAttributes) * m_lampCount);

    m_stateSize = sizeof(LampArrayColor) * m_lampCount;

    m_cachedStateWriteTo = (LampArrayColor*)malloc(m_stateSize);
    memset(m_cachedStateWriteTo, 0, m_stateSize);

    m_cachedStateReadFrom = (LampArrayColor*)malloc(m_stateSize);
    memset(m_cachedStateReadFrom, 0, m_stateSize);

    // On device start, always in AutonomousMode.
    m_isAutonomousMode = true;
}

Microsoft_HidLampArray::~Microsoft_HidLampArray()
{
    free(m_lampAttributes);
    free(m_cachedStateWriteTo);
    free(m_cachedStateReadFrom);
}

bool Microsoft_HidLampArray::getCurrentState(LampArrayColor* currentState) noexcept
{
    if (m_isAutonomousMode)
    {
        memset(currentState, 0, m_stateSize);
    }
    else
    {
        memcpy(currentState, m_cachedStateReadFrom, m_stateSize);
    }

    return m_isAutonomousMode;
}

void Microsoft_HidLampArray::ProcessReceivedGetFeatureReport(uint8_t reportId) noexcept
{
    switch (reportId)
    {
        case LAMP_ARRAY_ATTRIBUTES_REPORT_ID:
        {
            SendLampArrayAttributesReport();
            break;
        }
        case LAMP_ATTRIBUTES_RESPONSE_REPORT_ID:
        {
            SendLampAttributesReport();
            break;
        }
    }
}

void Microsoft_HidLampArray::ProcessReceivedSetFeatureReport(uint8_t reportId, uint8_t* data, uint16_t length) noexcept
{
    switch (reportId)
    {
        case LAMP_ATTRIBUTES_REQUEST_REPORT_ID:
        {
            UpdateRequestLampFromLampAttributesRequestReport(data, length);
            break;
        }
        case LAMP_MULTI_UPDATE_REPORT_ID:
        {
            UpdateLampStateCacheFromMultiUpdateReport(data, length);
            break;
        }
        case LAMP_RANGE_UPDATE_REPORT_ID:
        {
            UpdateLampStateCacheFromRangeUpdateReport(data, length);
            break;
        }
        case LAMP_ARRAY_CONTROL_REPORT_ID:
        {
            ProcessControlReport(data, length);
            break;
        }
    }
}

void Microsoft_HidLampArray::SendLampArrayAttributesReport() noexcept
{
    const LampArrayAttributesReport lampArrayAttributesReport = 
    {
        // Actual units MUST be micrometers and microseconds
        LAMP_ARRAY_ATTRIBUTES_REPORT_ID, 
        m_lampCount, 
        MILLIMETERS_TO_MICROMETERS(m_boundingBoxWidthInMillimeters), 
        MILLIMETERS_TO_MICROMETERS(m_boundingBoxHeightInMillimeters), 
        MILLIMETERS_TO_MICROMETERS(m_boundingBoxDepthInMillimeters), 
        m_kind, 
        MILLISECONDS_TO_MICROSECONDS(m_minUpdateInternalInMilliseconds)
    };

    SendFeatureReport(&lampArrayAttributesReport, sizeof(LampArrayAttributesReport));
}

void Microsoft_HidLampArray::SendLampAttributesReport() noexcept
{
    // Actual units MUST be micrometers and microseconds.
    LampAttributesResponseReport lampAttributeReport = {0};
    lampAttributeReport.ReportId = LAMP_ATTRIBUTES_RESPONSE_REPORT_ID;
    lampAttributeReport.Attributes.LampId = m_lampAttributes[m_lastLampIdRequested].LampId;
    lampAttributeReport.Attributes.PositionXInMillimeters = MILLIMETERS_TO_MICROMETERS(m_lampAttributes[m_lastLampIdRequested].PositionXInMillimeters);
    lampAttributeReport.Attributes.PositionYInMillimeters = MILLIMETERS_TO_MICROMETERS(m_lampAttributes[m_lastLampIdRequested].PositionYInMillimeters);
    lampAttributeReport.Attributes.PositionZInMillimeters = MILLIMETERS_TO_MICROMETERS(m_lampAttributes[m_lastLampIdRequested].PositionZInMillimeters);
    lampAttributeReport.Attributes.UpdateLatencyInMilliseconds = MILLISECONDS_TO_MICROSECONDS(m_lampAttributes[m_lastLampIdRequested].UpdateLatencyInMilliseconds);
    lampAttributeReport.Attributes.LampPurposes = m_lampAttributes[m_lastLampIdRequested].LampPurposes;
    lampAttributeReport.Attributes.RedLevelCount = m_lampAttributes[m_lastLampIdRequested].RedLevelCount;
    lampAttributeReport.Attributes.GreenLevelCount = m_lampAttributes[m_lastLampIdRequested].GreenLevelCount;
    lampAttributeReport.Attributes.BlueLevelCount = m_lampAttributes[m_lastLampIdRequested].BlueLevelCount;
    lampAttributeReport.Attributes.IntensityLevelCount = m_lampAttributes[m_lastLampIdRequested].IntensityLevelCount;
    lampAttributeReport.Attributes.IsProgrammable = m_lampAttributes[m_lastLampIdRequested].IsProgrammable;
    lampAttributeReport.Attributes.LampKey = m_lampAttributes[m_lastLampIdRequested].LampKey;

    // LampAttributes are always fixed, send back the appropriate pre-constructed report.
    SendFeatureReport(&lampAttributeReport, sizeof(LampAttributesResponseReport));

    m_lastLampIdRequested++;

    if (m_lastLampIdRequested >= m_lampCount)
    {
        // Reset to zero
        m_lastLampIdRequested = 0;
    }
}

void Microsoft_HidLampArray::UpdateRequestLampFromLampAttributesRequestReport(uint8_t* data, uint16_t length) noexcept
{
    LampAttributesRequestReport report = {0};
    memcpy(&report, data, sizeof(LampAttributesRequestReport));

    if (report.ReportId == LAMP_ATTRIBUTES_REQUEST_REPORT_ID)
    {
        // Per HID spec, if not within bounds, always set LampId to 0.
        if (report.LampId < m_lampCount)
        {
            m_lastLampIdRequested = report.LampId;
        }
        else
        {
            m_lastLampIdRequested = 0;
        }
    }
}

void Microsoft_HidLampArray::UpdateLampStateCacheFromMultiUpdateReport(uint8_t* data, uint16_t length) noexcept
{
    LampMultiUpdateReport report = {0};
    memcpy(&report, data, sizeof(LampMultiUpdateReport));

    if (report.ReportId == LAMP_MULTI_UPDATE_REPORT_ID)
    {
        for (uint8_t i = 0; i < report.LampCount; i++)
        {
            // Ignore update if not within bounds.
            if (report.LampIds[i] < m_lampCount)
            {
                m_cachedStateWriteTo[report.LampIds[i]] = report.UpdateColors[i];
            }
        }

        // Don't want the consumer to update before the Host has completed the batch of updates.
        if (report.LampUpdateFlags & LAMP_UPDATE_FLAG_UPDATE_COMPLETE)
        {
            m_cachedStateReadFrom = m_cachedStateWriteTo;
        }
    }
}

void Microsoft_HidLampArray::UpdateLampStateCacheFromRangeUpdateReport(uint8_t* data, uint16_t length) noexcept
{
    LampRangeUpdateReport report = {0};
    memcpy(&report, data, sizeof(LampRangeUpdateReport));

    if (report.ReportId == LAMP_RANGE_UPDATE_REPORT_ID)
    {
        // Ignore update if not within bounds.
        if (report.LampIdStart >= 0 && report.LampIdStart < m_lampCount && 
            report.LampIdEnd >= 0 && report.LampIdEnd < m_lampCount && 
            report.LampIdStart <= report.LampIdEnd)
        {
            for (uint8_t i = report.LampIdStart; i <= report.LampIdEnd; i++)
            {
                m_cachedStateWriteTo[i] = report.UpdateColor;
            }

            // Don't want the consumer to update before the Host has completed the batch of updates.
            if (report.LampUpdateFlags & LAMP_UPDATE_FLAG_UPDATE_COMPLETE)
            {
                m_cachedStateReadFrom = m_cachedStateWriteTo;
            }
        }
    }
}

void Microsoft_HidLampArray::ProcessControlReport(uint8_t* data, uint16_t length) noexcept
{
    LampArrayControlReport report = {0};
    memcpy(&report, data, sizeof(LampArrayControlReport));

    if (report.ReportId == LAMP_ARRAY_CONTROL_REPORT_ID)
    {
        m_isAutonomousMode = !!report.AutonomousMode;
    }
}
