#include "MeasurementReport.h"

#include <stdexcept>

MeasurementReport::MeasurementReport(
    const std::string id, 
    uint64_t elapsed_count
) {
    id_ = id;
    elapsed_count_ = elapsed_count;
}

MeasurementReport::MeasurementReport(const MeasurementReport& rhs)
{
    id_ = rhs.id_;
    elapsed_count_ = rhs.elapsed_count_;
}

std::string MeasurementReport::GetId()
{
    return id_;
}

uint64_t MeasurementReport::GetElapseCount()
{
    return elapsed_count_;
}
