#pragma once

#include <chrono>
#include <map>

#include "MeasurementResultCollectable.h"

class MeasurementResult final : public MeasurementResultCollectable
{
public:
    static MeasurementResult* get_instance();
    static void destroy_instance();

    void append(const MeasurementReport& report) override;
    const std::map<clock_t, MeasurementReport> getImmutableRecords();

private:
    MeasurementResult() = default;

private:
    static MeasurementResult* _instance;
    std::map<uint64_t, MeasurementReport> _records;
};
