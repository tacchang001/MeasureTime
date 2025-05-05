#include <stdexcept>
#include <iostream>

#include "StopWatch.h"
#include "MeasurementResult.h"

StopWatch::~StopWatch()
{
    Close();
}

StopWatch::StopWatch(
    bool immediately,
    std::string id,
    MeasurementResultCollectable *reporter
) {
    started_ = false;
    id_ = id;
    automaticallyStopped_ = false;
    lastError_ = "";
    if (immediately)
    {
        Start();
    }
}

StopWatch::StopWatch()
    : StopWatch(true, "", nullptr)
{

}

StopWatch::StopWatch(
    bool immediately
) : StopWatch(immediately, "", nullptr)
{

}

bool StopWatch::Start()
{
    if (!started_)
    {
        begin_ = StopWatch::GetCpuCount();
        end_ = begin_;
        started_ = true;

        return true;
    }

    return false;
}

bool StopWatch::Stop()
{
    if (started_)
    {
        end_ = StopWatch::GetCpuCount();
        started_ = false;

        auto reporter = MeasurementResult::GetInstance();
        if (reporter != nullptr)
        {
            MeasurementReport report(id_, GetElapsedCount());
            reporter->Append(report);
        }

        return true;
    }

    return false;
}

void StopWatch::Close()
{
    try {
        if (!Stop())
        {
            automaticallyStopped_ = true;
        }
    }
    catch(const std::exception &ex)
    {
        lastError_ = ex.what();
    }
}

uint64_t StopWatch::GetBeginEpoch()
{
    return begin_;
}

uint64_t StopWatch::GetEndEpoch()
{
    return end_;
}

uint64_t StopWatch::GetElapsedCount()
{
    return end_ - begin_;
}

bool StopWatch::TryElapsedCount(uint64_t &count)
{
    if (!started_)
    {
        count = end_ - begin_;

        return true;
    }

    return false;
}

bool StopWatch::IsAutomaticallyStopped()
{
    return automaticallyStopped_;
}

std::string StopWatch::GetLastMessage()
{
    return lastError_;
}

// CPUクロック・カウントを取得する
__inline__ uint64_t StopWatch::GetCpuCount() {
    uint64_t a, d;
    __asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));
    return (d<<32) | a;
}
