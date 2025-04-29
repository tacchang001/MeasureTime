#include <stdexcept>
#include <unistd.h>

#include "gtest/gtest.h"

#include "StopWatch.h"
#include "MeasurementResult.h"

namespace chrono = std::chrono;

TEST(test_StopWatch, test1) {
    StopWatch *sp = new StopWatch();
    EXPECT_NE(nullptr, sp);
    EXPECT_TRUE(sp->getLastMessage().empty());

    chrono::milliseconds waitTime{50};
    usleep(chrono::duration_cast<chrono::microseconds>(waitTime).count());

    {
        uint64_t nano = 0L;
        EXPECT_FALSE(sp->tryElapsedNanoSec(nano));
        EXPECT_TRUE(sp->getLastMessage().empty());
        EXPECT_TRUE(sp->stop());
        EXPECT_TRUE(sp->tryElapsedNanoSec(nano));
    }
    {
        uint64_t nano = sp->getElapsedNanoSec();
        EXPECT_TRUE(nano >= (chrono::duration_cast<chrono::nanoseconds>(waitTime).count()));
        EXPECT_TRUE(sp->getLastMessage().empty());
        EXPECT_FALSE(sp->isAutomaticallyStopped());
    }
}

TEST(test_StopWatch, test2) {
    StopWatch *sp = new StopWatch(false);
    EXPECT_NE(nullptr, sp);
    EXPECT_TRUE(sp->getLastMessage().empty());
    EXPECT_TRUE(sp->start());

    chrono::milliseconds waitTime{50};
    usleep(chrono::duration_cast<chrono::microseconds>(waitTime).count());

    {
        uint64_t nano = 0L;
        EXPECT_FALSE(sp->tryElapsedNanoSec(nano));
        EXPECT_TRUE(sp->getLastMessage().empty());
        EXPECT_TRUE(sp->stop());
        EXPECT_TRUE(sp->tryElapsedNanoSec(nano));
    }
    {
        uint64_t nano = sp->getElapsedNanoSec();
        EXPECT_TRUE(nano >= chrono::duration_cast<chrono::nanoseconds>(waitTime).count());
        EXPECT_TRUE(sp->getLastMessage().empty());
        EXPECT_FALSE(sp->isAutomaticallyStopped());
    }
}

TEST(test_StopWatch, test3) {
    MeasurementResult* reporter = MeasurementResult::get_instance();
    EXPECT_NE(nullptr, reporter);

    chrono::milliseconds waitTime{50};

    {
        StopWatch sp(true, "id01", reporter);
        EXPECT_TRUE(sp.getLastMessage().empty());

        EXPECT_EQ(0, usleep(chrono::duration_cast<chrono::microseconds>(waitTime).count()));

        uint64_t nano = 0L;
        EXPECT_FALSE(sp.tryElapsedNanoSec(nano));
        EXPECT_TRUE(sp.getLastMessage().empty());
    }

    const std::map<clock_t, MeasurementReport> records = reporter->getImmutableRecords();
    EXPECT_TRUE(records.size() == 1);
    auto item = records.begin()->second;
    double sec = item.getElapseNanoSec();
    EXPECT_TRUE(sec >= chrono::duration_cast<chrono::nanoseconds>(waitTime).count());
}
