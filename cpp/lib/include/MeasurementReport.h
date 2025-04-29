#pragma once

#include <cstdint>
#include <string>
#include <ctime>

class MeasurementReport
{
public:
    MeasurementReport() {}
    MeasurementReport(const std::string id, uint64_t elapseNanoSec);
    MeasurementReport(const MeasurementReport& rhs);

    std::string getId();
    uint64_t getElapseNanoSec();
    
private:
    std::string _id;
    uint64_t _elapsedNanoSec;
};
