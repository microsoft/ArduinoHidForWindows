// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#pragma once

#define LAMP_ARRAY_ATTRIBUTES_REPORT_ID 1
struct __attribute__ ((__packed__)) LampArrayAttributesReport
{
    uint8_t  ReportId;
    uint16_t LampCount;
    uint32_t BoundingBoxWidthInMillimeters;
    uint32_t BoundingBoxHeightInMillimeters;
    uint32_t BoundingBoxDepthInMillimeters;
    uint32_t LampArrayKind;
    uint32_t MinUpdateIntervalInMicroseconds;
};

#define LAMP_ATTRIBUTES_REQUEST_REPORT_ID 2
struct __attribute__ ((__packed__)) LampAttributesRequestReport
{
    uint8_t ReportId;
    uint16_t LampId;
};

#define LAMP_ATTRIBUTES_RESPONSE_REPORT_ID 3
struct __attribute__ ((__packed__)) LampAttributesResponseReport
{
    uint8_t ReportId;
    LampAttributes Attributes;
};

#define LAMP_MULTI_UPDATE_REPORT_ID 4
#define LAMP_MULTI_UPDATE_LAMP_COUNT 8
struct __attribute__ ((__packed__)) LampMultiUpdateReport
{
    uint8_t ReportId;
    uint8_t LampCount;
    uint8_t LampUpdateFlags;
    uint16_t LampIds[LAMP_MULTI_UPDATE_LAMP_COUNT];
    LampArrayColor UpdateColors[LAMP_MULTI_UPDATE_LAMP_COUNT];
};

#define LAMP_RANGE_UPDATE_REPORT_ID 5
struct __attribute__ ((__packed__)) LampRangeUpdateReport
{
    uint8_t ReportId;
    uint8_t LampUpdateFlags;
    uint16_t LampIdStart;
    uint16_t LampIdEnd;
    LampArrayColor UpdateColor;
};

#define LAMP_ARRAY_CONTROL_REPORT_ID 6
struct __attribute__ ((__packed__)) LampArrayControlReport
{
    uint8_t ReportId;
    uint8_t AutonomousMode;
};