#include <stdexcept>
#include <unistd.h>

#include "gtest/gtest.h"

#include "StopWatch.h"

TEST(test_StopWatch, test1) {
    StopWatch *sp = new StopWatch();
    EXPECT_NE(nullptr, sp);
    EXPECT_EQ("", sp->getLastMessage());
    EXPECT_TRUE(sp->getLastMessage().empty());

    int waitMs = 50 * 1000;
    usleep(waitMs);

    clock_t nano = 0L;
    EXPECT_FALSE(sp->tryElapsedEpochNano(nano));
    EXPECT_FALSE(sp->getLastMessage().empty());
    EXPECT_TRUE(sp->stop());
    EXPECT_TRUE(sp->tryElapsedEpochNano(nano));
    EXPECT_TRUE(sp->getElapsedEpochSec() >= waitMs - 2);
    EXPECT_TRUE(sp->getLastMessage().empty());
    EXPECT_FALSE(sp->isAutomaticallyStopped());
}
