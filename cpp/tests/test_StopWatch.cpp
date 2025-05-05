#include <stdexcept>
#include <unistd.h>

#include "gtest/gtest.h"

#include "StopWatch.h"
#include "MeasurementResult.h"

namespace chrono = std::chrono;

TEST(test_StopWatch, test1) {
    StopWatch *sp = new StopWatch();
    EXPECT_NE(nullptr, sp);
    EXPECT_TRUE(sp->GetLastMessage().empty());

    chrono::milliseconds waitTime{50};
    usleep(chrono::duration_cast<chrono::microseconds>(waitTime).count());

    {
        uint64_t nano = 0L;
        EXPECT_FALSE(sp->TryElapsedCount(nano));
        EXPECT_TRUE(sp->GetLastMessage().empty());
        EXPECT_TRUE(sp->Stop());
        EXPECT_TRUE(sp->TryElapsedCount(nano));
    }
    {
        uint64_t nano = sp->GetElapsedCount();
        EXPECT_TRUE(nano >= (chrono::duration_cast<chrono::nanoseconds>(waitTime).count()));
        EXPECT_TRUE(sp->GetLastMessage().empty());
        EXPECT_FALSE(sp->IsAutomaticallyStopped());
    }
}

TEST(test_StopWatch, test2) {
    StopWatch *sp = new StopWatch(false);
    EXPECT_NE(nullptr, sp);
    EXPECT_TRUE(sp->GetLastMessage().empty());
    EXPECT_TRUE(sp->Start());

    chrono::milliseconds waitTime{50};
    usleep(chrono::duration_cast<chrono::microseconds>(waitTime).count());

    {
        uint64_t nano = 0L;
        EXPECT_FALSE(sp->TryElapsedCount(nano));
        EXPECT_TRUE(sp->GetLastMessage().empty());
        EXPECT_TRUE(sp->Stop());
        EXPECT_TRUE(sp->TryElapsedCount(nano));
    }
    {
        uint64_t nano = sp->GetElapsedCount();
        EXPECT_TRUE(nano >= chrono::duration_cast<chrono::nanoseconds>(waitTime).count());
        EXPECT_TRUE(sp->GetLastMessage().empty());
        EXPECT_FALSE(sp->IsAutomaticallyStopped());
    }
}

TEST(test_StopWatch, test3) {
    MeasurementResult* reporter = MeasurementResult::GetInstance();
    EXPECT_NE(nullptr, reporter);
    reporter->Clear();

    chrono::milliseconds waitTime{50};

    {
        StopWatch sp(true, "id01", reporter);
        EXPECT_TRUE(sp.GetLastMessage().empty());

        EXPECT_EQ(0, usleep(chrono::duration_cast<chrono::microseconds>(waitTime).count()));

        uint64_t nano = 0L;
        EXPECT_FALSE(sp.TryElapsedCount(nano));
        EXPECT_TRUE(sp.GetLastMessage().empty());
    }

    const std::map<clock_t, MeasurementReport> records = reporter->GetImmutableRecords();
    EXPECT_TRUE(records.size() == 1);
    auto item = records.begin()->second;
    uint64_t nano = item.GetElapseCount();
    EXPECT_TRUE(nano >= chrono::duration_cast<chrono::nanoseconds>(waitTime).count());
}
