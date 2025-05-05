#pragma once

#include <cstdint>
#include <string>

#include "AutoCloseable.h"
#include "MeasurementResultCollectable.h"

// GCC4環境下ではstd::chronoの精度が悪くsin関数程度では処理速度がでない（ゼロ）ため
// 時間単位はCPUクロックカウンタの値を使う。そのため、このコードはIntel CPUのみで
// 使用可能。他のCPUではGetCpuCount()を書き換える必要がある。
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

    uint64_t GetBeginEpoch();
    uint64_t GetEndEpoch();
    uint64_t GetElapsedCount();
    bool TryElapsedCount(uint64_t &count);
    bool IsAutomaticallyStopped();
    std::string GetLastMessage();

    static uint64_t GetCpuCount();

private:
    bool started_;
    bool automaticallyStopped_;
    uint64_t begin_;
    uint64_t end_;
    std::string id_;
    std::string lastError_;
};
