#pragma once

#include <cstdint>
#include <string>
#include <ctime>

class MeasurementReport
{
public:
    MeasurementReport() {}
    MeasurementReport(const std::string id, uint64_t elapse_count);
    MeasurementReport(const MeasurementReport& rhs);

    std::string GetId();
    uint64_t GetElapseCount();
    
private:
    std::string id_;
    uint64_t elapsed_count_;
};
