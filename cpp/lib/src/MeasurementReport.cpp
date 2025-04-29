#include "MeasurementReport.h"

#include <stdexcept>

MeasurementReport::MeasurementReport(
    const std::string id, 
    uint64_t elapsed_sec
) {
    if (id.empty())
    {
        throw std::invalid_argument("ID must be specified");
    }
    id_ = id;
    elapsed_nano_sec_ = elapsed_sec;
}

MeasurementReport::MeasurementReport(const MeasurementReport& rhs)
{
    id_ = rhs.id_;
    elapsed_nano_sec_ = rhs.elapsed_nano_sec_;
}

std::string MeasurementReport::GetId()
{
    return id_;
}

uint64_t MeasurementReport::GetElapseNanoSec()
{
    return elapsed_nano_sec_;
}
