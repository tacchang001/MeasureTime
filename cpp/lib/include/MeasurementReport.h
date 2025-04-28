#pragma once

#include <string>
#include <ctime>

class MeasurementReport
{
public:
    MeasurementReport() {}
    MeasurementReport(const std::string id, clock_t elapseEpochNano);
    MeasurementReport(const MeasurementReport& rhs);

    std::string getId();
    clock_t getElapseEpochNano();

private:
    std::string _id;
    clock_t _elapseEpochNano;
};
