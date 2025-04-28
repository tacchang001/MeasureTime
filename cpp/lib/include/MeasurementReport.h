#pragma once

#include <string>
#include <ctime>

class MeasurementReport
{
public:
    MeasurementReport() {}
    MeasurementReport(const std::string id, double elapseSec);
    MeasurementReport(const MeasurementReport& rhs);

    std::string getId();
    double getElapseSec();
    
private:
    std::string _id;
    double _elapsedSec;
};
