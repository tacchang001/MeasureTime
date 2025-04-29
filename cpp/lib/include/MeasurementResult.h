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
    void Clear() override;
    std::map<clock_t, MeasurementReport> GetImmutableRecords() override;

    // 基礎統計量
    double Max();
    double Min();
    double Average();
    double Variance();
    double StandardDeviation();
    double Median();

private:
    MeasurementResult();
    void Sort();

private:
    static MeasurementResult* instance_;
    std::map<uint64_t, MeasurementReport> records_;
    bool sorted_;

    double max_;
    double min_;
    double average_;
    double variance_;
    double standard_deviation_;
    double median_;
};
