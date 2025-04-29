#pragma once

#include <cstdint>
#include <string>
#include <ctime>
#include <chrono>

#include "AutoCloseable.h"
#include "MeasurementResultCollectable.h"

class StopWatch : public AutoCloseable
{
public:
    ~StopWatch();
    StopWatch();
    StopWatch(bool immediately);
    StopWatch(bool immediately, std::string id, MeasurementResultCollectable *reporter);

    bool Start();
    bool Stop();
    void Close() override;

    std::chrono::system_clock::time_point GetBeginEpoch();
    std::chrono::system_clock::time_point GetEndEpoch();
    uint64_t GetElapsedNanoSec();
    bool TryElapsedNanoSec(uint64_t &nano);
    bool IsAutomaticallyStopped();
    std::string GetLastMessage();

private:
    bool started_;
    bool automaticallyStopped_;
    std::chrono::system_clock::time_point begin_;
    std::chrono::system_clock::time_point end_;
    std::string id_;
    MeasurementResultCollectable *reporter_;
    std::string lastError_;
};
