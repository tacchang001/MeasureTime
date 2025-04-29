#include "MeasurementResult.h"

MeasurementResult* MeasurementResult::instance_ = nullptr;

MeasurementResult* MeasurementResult::GetInstance()
{
    if (instance_ == nullptr)
    {
        instance_ = new MeasurementResult();
    }
    
    return instance_;
}

void MeasurementResult::DestroyInstance()
{
    if (instance_ != nullptr)
    {
        delete instance_;
        instance_ = nullptr;
    }
}

void MeasurementResult::Append(const MeasurementReport& report)
{
    uint64_t key = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    records_[key] = report;
}

const std::map<clock_t, MeasurementReport> MeasurementResult::GetImmutableRecords()
{
    std::map<clock_t, MeasurementReport> result;
    std::copy(records_.begin(), records_.end(), std::inserter(result, result.end()));
    return result;
}
