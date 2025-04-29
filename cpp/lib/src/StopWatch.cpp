#include <stdexcept>

#include "StopWatch.h"

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
    reporter_ = reporter;
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
        begin_ = std::chrono::system_clock::now();
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
        end_ = std::chrono::system_clock::now();
        started_ = false;

        if (reporter_ != nullptr)
        {
            MeasurementReport report(id_, GetElapsedNanoSec());
            reporter_->Append(report);
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

std::chrono::system_clock::time_point StopWatch::GetBeginEpoch()
{
    return begin_;
}

std::chrono::system_clock::time_point StopWatch::GetEndEpoch()
{
    return end_;
}

uint64_t StopWatch::GetElapsedNanoSec()
{
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end_ - begin_);
    return elapsed.count();
}

bool StopWatch::TryElapsedNanoSec(uint64_t &nano)
{
    if (!started_)
    {
        nano = std::chrono::duration_cast<std::chrono::nanoseconds>(end_ - begin_).count();

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