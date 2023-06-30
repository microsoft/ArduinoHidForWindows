// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

#pragma once

#pragma pack(push,1)

struct SystemControlPowerReport
{
    uint8_t ReportId = 1;
    uint8_t Payload[1];
};

#pragma pack(pop)