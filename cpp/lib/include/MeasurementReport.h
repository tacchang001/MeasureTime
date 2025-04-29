#pragma once

#include <cstdint>
#include <string>
#include <ctime>

class MeasurementReport
{
public:
    MeasurementReport() {}
    MeasurementReport(const std::string id, uint64_t elapse_nano_sec);
    MeasurementReport(const MeasurementReport& rhs);

    std::string GetId();
    uint64_t GetElapseNanoSec();
    
private:
    std::string id_;
    uint64_t elapsed_nano_sec_;
};
