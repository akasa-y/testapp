#include <string.h>
#include "gtest/gtest.h"
#include "fff.h"
DEFINE_FFF_GLOBALS;

extern "C"
{
    #include "common.h"
    #include "os_api.c"
}

FAKE_VALUE_FUNC(void*, sub1, void*);
FAKE_VALUE_FUNC(void*, sub2, void*);

class TestOsApi: public testing::Test {
    void SetUp() {
        RESET_FAKE(sub1);
        RESET_FAKE(sub2);
        FFF_RESET_HISTORY();
    }
    void TearDown() {
    }
};

TEST_F(TestOsApi, init)
{
    EXPECT_EQ(0, init_hw());
}
