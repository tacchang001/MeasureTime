#pragma once

#include "MeasurementReport.h"

class MeasurementResultCollectable
{
public:
    virtual void Append(const MeasurementReport& report) = 0;
};
