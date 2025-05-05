#include "MeasurementResult.h"
#include <iterator>
#include <algorithm>
#include <vector>
#include <numeric>
#include <cmath>

MeasurementResult* MeasurementResult::instance_ = nullptr;

MeasurementResult::MeasurementResult()
    : sorted_(false)
{

}

MeasurementResult* MeasurementResult::GetInstance()
{
    if (instance_ == nullptr)
    {
        instance_ = new MeasurementResult();
    }
    
    return instance_;
}

void MeasurementResult::DestroyInstance()
{
    if (instance_ != nullptr)
    {
        delete instance_;
        instance_ = nullptr;
    }
}

void MeasurementResult::Clear()
{
    records_.clear();
}

void MeasurementResult::Append(const MeasurementReport& report)
{
    sorted_ = false;
    uint64_t key = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    records_[key] = report;
}

std::map<clock_t, MeasurementReport> MeasurementResult::GetImmutableRecords()
{
    std::map<clock_t, MeasurementReport> result;
    std::copy(records_.begin(), records_.end(), std::inserter(result, result.end()));
    return result;
}

void MeasurementResult::Sort()
{
    std::vector<double> v;
    for (const auto& pair : records_)
    {
        auto report = pair.second;
        v.push_back(report.GetElapseNanoSec());
    }

    std::sort(v.begin(), v.end());

    max_ = *std::max_element(std::begin(v), std::end(v));
    min_ = *std::min_element(std::begin(v), std::end(v));
    average_ = std::accumulate(std::begin(v), std::end(v), 0.0) / v.size();
    variance_ = std::inner_product(std::begin(v), std::end(v), std::begin(v), 0.0) / v.size() - average_ * average_;
    standard_deviation_ = std::sqrt(variance_);
    {
        auto median_index = v.size() / 2;
        median_ = (v.size()) % 2 == 0
            ? static_cast<double>(v[median_index] + v[median_index - 1]) / 2
            : v[median_index];
    }

    sorted_ = true;
}

double MeasurementResult::Max()
{
    if (!sorted_)
    {
        Sort();
    }

    return max_;
}

double MeasurementResult::Min()
{
    if (!sorted_)
    {
        Sort();
    }

    return min_;
}

double MeasurementResult::Average()
{
    if (!sorted_)
    {
        Sort();
    }

    return average_;
}

double MeasurementResult::Variance()
{
    if (!sorted_)
    {
        Sort();
    }

    return variance_;
}

double MeasurementResult::StandardDeviation()
{
    if (!sorted_)
    {
        Sort();
    }

    return standard_deviation_;
}

double MeasurementResult::Median()
{
    if (!sorted_)
    {
        Sort();
    }

    return median_;
}
