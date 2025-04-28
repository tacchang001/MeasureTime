#pragma once

#include <string>
#include <ctime>

#include "AutoCloseable.h"
#include "MeasurementResultCollectable.h"

class StopWatch : public AutoCloseable
{
public:
    StopWatch();
    StopWatch(bool immediately, std::string id, MeasurementResultCollectable *reporter);

    bool start();
    bool stop();
    void close() override;

    clock_t getBeginEpochNano();
    clock_t getEndEpochNano();
    clock_t getElapsedEpochNano();
    double getElapsedEpochSec();
    bool tryElapsedEpochNano(clock_t &c);
    bool isAutomaticallyStopped();
    std::string getLastMessage();

private:
    bool _started;
    bool _automaticallyStopped;
    clock_t _beginNano;
    clock_t _endNano;
    std::string _id;
    MeasurementResultCollectable *_reporter;
    std::string _lastError;
};
