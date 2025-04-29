#include "MeasurementReport.h"

#include <stdexcept>

MeasurementReport::MeasurementReport(
    const std::string id, 
    uint64_t elapsedSec
) {
    if (id.empty())
    {
        throw std::invalid_argument("ID must be specified");
    }
    _id = id;
    _elapsedNanoSec = elapsedSec;
}

MeasurementReport::MeasurementReport(const MeasurementReport& rhs)
{
    _id = rhs._id;
    _elapsedNanoSec = rhs._elapsedNanoSec;
}

std::string MeasurementReport::getId()
{
    return _id;
}

uint64_t MeasurementReport::getElapseNanoSec()
{
    return _elapsedNanoSec;
}
