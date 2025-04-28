#pragma once

#include "MeasurementReport.h"

class MeasurementResultCollectable
{
public:
    virtual void append(const MeasurementReport& report) = 0;
};
