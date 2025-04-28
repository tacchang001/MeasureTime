#include <stdexcept>
#include <unistd.h>

#include "gtest/gtest.h"

#include "StopWatch.h"
#include "MeasurementResult.h"

TEST(test_StopWatch, test1) {
    StopWatch *sp = new StopWatch();
    EXPECT_NE(nullptr, sp);
    EXPECT_TRUE(sp->getLastMessage().empty());

    std::cout << std::chrono::system_clock::now().time_since_epoch().count() << std::endl;
    int waitMs = 50;
    usleep(waitMs * 1000);
    std::cout << std::chrono::system_clock::now().time_since_epoch().count() << std::endl;

    double nano = 0L;
    EXPECT_FALSE(sp->tryElapsedSec(nano));
    EXPECT_TRUE(sp->getLastMessage().empty());
    EXPECT_TRUE(sp->stop());
    EXPECT_TRUE(sp->tryElapsedSec(nano));
    double sec = sp->getElapsedSec();
    EXPECT_TRUE(sec >= (waitMs / 1000.0));
    EXPECT_TRUE(sp->getLastMessage().empty());
    EXPECT_FALSE(sp->isAutomaticallyStopped());
}

TEST(test_StopWatch, test2) {
    StopWatch *sp = new StopWatch(false);
    EXPECT_NE(nullptr, sp);
    EXPECT_TRUE(sp->getLastMessage().empty());
    EXPECT_TRUE(sp->start());

    int waitMs = 50;
    usleep(waitMs * 1000);

    double nano = 0L;
    EXPECT_FALSE(sp->tryElapsedSec(nano));
    EXPECT_TRUE(sp->getLastMessage().empty());
    EXPECT_TRUE(sp->stop());
    EXPECT_TRUE(sp->tryElapsedSec(nano));
    double sec = sp->getElapsedSec();
    EXPECT_TRUE(sec >= (waitMs / 1000.0));
    EXPECT_TRUE(sp->getLastMessage().empty());
    EXPECT_FALSE(sp->isAutomaticallyStopped());
}

TEST(test_StopWatch, test3) {
    MeasurementResult* reporter = MeasurementResult::get_instance();
    EXPECT_NE(nullptr, reporter);

    const int waitMs = 50;
    {
        StopWatch sp(true, "id01", reporter);
        EXPECT_TRUE(sp.getLastMessage().empty());

        EXPECT_EQ(0, usleep(waitMs * 1000));

        double nano = 0L;
        EXPECT_FALSE(sp.tryElapsedSec(nano));
        EXPECT_TRUE(sp.getLastMessage().empty());
    }

    const std::map<clock_t, MeasurementReport> records = reporter->getImmutableRecords();
    EXPECT_TRUE(records.size() == 1);
    auto item = records.begin()->second;
    double sec = item.getElapseSec();
    EXPECT_TRUE(sec >= (waitMs / 1000.0));    // 秒で比較
}
