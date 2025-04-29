#pragma once

#include <map>
#include "MeasurementReport.h"

class MeasurementResultCollectable
{
public:
    virtual void Append(const MeasurementReport& report) = 0;
    virtual void Clear() = 0;
    virtual std::map<clock_t, MeasurementReport> GetImmutableRecords() = 0;
};
