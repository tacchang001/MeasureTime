#include "MeasurementReport.h"

#include <stdexcept>

MeasurementReport::MeasurementReport(
    const std::string id, 
    clock_t elapseEpochNano
) {
    if (id.empty())
    {
        throw std::invalid_argument("ID must be specified");
    }
    _id = id;
    _elapseEpochNano = elapseEpochNano;
}

MeasurementReport::MeasurementReport(const MeasurementReport& rhs)
{
    _id = rhs._id;
    _elapseEpochNano = rhs._elapseEpochNano;
}

std::string MeasurementReport::getId()
{
    return _id;
}

clock_t MeasurementReport::getElapseEpochNano()
{
    return _elapseEpochNano;
}
