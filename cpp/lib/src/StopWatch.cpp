#include <stdexcept>

#include "StopWatch.h"

StopWatch::StopWatch(
    bool immediately,
    std::string id,
    MeasurementResultCollectable *reporter
) {
    _started = false;
    _endNano = 0;
    _beginNano = 0;
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

bool StopWatch::start()
{
    if (!_started)
    {
        _beginNano = clock();
        _endNano = 0;
        _started = true;

        return true;
    }

    return false;
}

bool StopWatch::stop()
{
    if (_started)
    {
        _endNano = clock();
        _started = false;
        _lastError = "";
        _automaticallyStopped = false;

        if (_reporter != nullptr)
        {
            MeasurementReport report(_id, getElapsedEpochNano());
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

clock_t StopWatch::getBeginEpochNano()
{
    return _beginNano;
}

clock_t StopWatch::getEndEpochNano()
{
    return _endNano;
}

clock_t StopWatch::getElapsedEpochNano()
{
    return _endNano - _beginNano;
}

double StopWatch::getElapsedEpochSec()
{
    return double(_endNano - _beginNano) / CLOCKS_PER_SEC;
}

bool StopWatch::tryElapsedEpochNano(clock_t &c)
{
    if (!_started)
    {
        c = _endNano - _beginNano;

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