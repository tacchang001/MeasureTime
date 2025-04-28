#include "MeasurementReport.h"

#include <stdexcept>

MeasurementReport::MeasurementReport(
    const std::string id, 
    double elapsedSec
) {
    if (id.empty())
    {
        throw std::invalid_argument("ID must be specified");
    }
    _id = id;
    _elapsedSec = elapsedSec;
}

MeasurementReport::MeasurementReport(const MeasurementReport& rhs)
{
    _id = rhs._id;
    _elapsedSec = rhs._elapsedSec;
}

std::string MeasurementReport::getId()
{
    return _id;
}

double MeasurementReport::getElapseSec()
{
    return _elapsedSec;
}
