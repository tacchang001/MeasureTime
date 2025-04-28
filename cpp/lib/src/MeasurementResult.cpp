#include "MeasurementResult.h"

MeasurementResult& MeasurementResult::get_instance()
{
    if (_instance == nullptr)
    {
        _instance = new MeasurementResult();
    }
    
    return *_instance;
}

void MeasurementResult::destroy_instance()
{
    if (_instance != nullptr)
    {
        delete _instance;
        _instance = nullptr;
    }
}

void MeasurementResult::append(const MeasurementReport& report)
{
    uint64_t key = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    _records[key] = report;
}
