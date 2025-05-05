#include <stdexcept>
#include <vector>
#include <unistd.h>

#include "gtest/gtest.h"

#include "StopWatch.h"
#include "MeasurementResult.h"

namespace chrono = std::chrono;

TEST(test_MeasurementResult, test1) {
    const int input_data_size = 10;
    MeasurementReport reports[input_data_size] = {
        {"id01", 10},
        {"id02", 11},
        {"id03", 12},
        {"id04", 13},
        {"id05", 14},
        {"id06", 15},
        {"id07", 16},
        {"id08", 17},
        {"id09", 18},
        {"id10", 19}
    };

    auto mr = MeasurementResult::GetInstance();
    ASSERT_NE(nullptr, mr);
    mr->Clear();

    for (int i=0; i<input_data_size; i++)
    {
        mr->Append(reports[i]);
    }
    
    EXPECT_EQ(19.0, mr->Max());
    EXPECT_EQ(10.0, mr->Min());
    EXPECT_EQ(14.5, mr->Average());
    EXPECT_EQ(14.5, mr->Median());
    EXPECT_EQ(8.25, mr->Variance());
    EXPECT_TRUE(std::abs(2.8723 - mr->StandardDeviation()) < 0.0001);
}
