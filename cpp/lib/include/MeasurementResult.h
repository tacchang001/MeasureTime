#pragma once

#include <chrono>
#include <map>

#include "MeasurementResultCollectable.h"

class MeasurementResult final : public MeasurementResultCollectable
{
public:
    static MeasurementResult* GetInstance();
    static void DestroyInstance();

    void Append(const MeasurementReport& report) override;
    const std::map<clock_t, MeasurementReport> GetImmutableRecords();

private:
    MeasurementResult() = default;

private:
    static MeasurementResult* instance_;
    std::map<uint64_t, MeasurementReport> records_;
};
