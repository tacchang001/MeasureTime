#include <stdexcept>

#include "StopWatch.h"

StopWatch::~StopWatch()
{
    close();
}

StopWatch::StopWatch(
    bool immediately,
    std::string id,
    MeasurementResultCollectable *reporter
) {
    _started = false;
    _id = id;
    _reporter = reporter;
    _automaticallyStopped = false;
    _lastError = "";
    if (immediately)
    {
        start();
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

bool StopWatch::start()
{
    if (!_started)
    {
        _begin = std::chrono::system_clock::now();
        _end = _begin;
        _started = true;

        return true;
    }

    return false;
}

bool StopWatch::stop()
{
    if (_started)
    {
        _end = std::chrono::system_clock::now();
        _started = false;

        if (_reporter != nullptr)
        {
            MeasurementReport report(_id, getElapsedSec());
            _reporter->append(report);
        }

        return true;
    }

    return false;
}

void StopWatch::close()
{
    try {
        if (!stop())
        {
            _automaticallyStopped = true;
        }
    }
    catch(const std::exception &ex)
    {
        _lastError = ex.what();
    }
}

std::chrono::system_clock::time_point StopWatch::getBeginEpoch()
{
    return _begin;
}

std::chrono::system_clock::time_point StopWatch::getEndEpoch()
{
    return _end;
}

double StopWatch::getElapsedSec()
{
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(_end - _begin);
    return elapsed.count() / double(1000.0 * 1000.0 * 1000.0);
}

bool StopWatch::tryElapsedSec(double &c)
{
    if (!_started)
    {
        c = std::chrono::duration_cast<std::chrono::nanoseconds>(_end - _begin).count() / double(1000.0 * 1000.0 * 1000.0);

        return true;
    }

    return false;
}

bool StopWatch::isAutomaticallyStopped()
{
    return _automaticallyStopped;
}

std::string StopWatch::getLastMessage()
{
    return _lastError;
}