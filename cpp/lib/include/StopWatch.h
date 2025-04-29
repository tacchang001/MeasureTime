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

    bool start();
    bool stop();
    void close() override;

    std::chrono::system_clock::time_point getBeginEpoch();
    std::chrono::system_clock::time_point getEndEpoch();
    uint64_t getElapsedNanoSec();
    bool tryElapsedNanoSec(uint64_t &nano);
    bool isAutomaticallyStopped();
    std::string getLastMessage();

private:
    bool _started;
    bool _automaticallyStopped;
    std::chrono::system_clock::time_point _begin;
    std::chrono::system_clock::time_point _end;
    std::string _id;
    MeasurementResultCollectable *_reporter;
    std::string _lastError;
};
