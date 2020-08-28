#include <string.h>
#include "gtest/gtest.h"
#include "fff.h"
DEFINE_FFF_GLOBALS;

extern "C"
{
    #include "common.h"
    #include "linux/os_api.c"
}

FAKE_VALUE_FUNC(void*, sub1, void*);
FAKE_VALUE_FUNC(void*, sub2, void*);
FAKE_VALUE_FUNC(void*, calloc, size_t, size_t);
FAKE_VALUE_FUNC(int, pthread_join, pthread_t, void**);
FAKE_VALUE_FUNC(int, mkfifo, const char *, mode_t);
FAKE_VALUE_FUNC(ssize_t, write, int, const void*, size_t);

class TestOsApi: public testing::Test {
    void SetUp() {
        RESET_FAKE(sub1);
        RESET_FAKE(sub2);
        RESET_FAKE(calloc);
        RESET_FAKE(write);
        FFF_RESET_HISTORY();
    }
    void TearDown() {
    }
};

TEST_F(TestOsApi, init)
{
    printf("TestOsAPI init\n");
    EXPECT_EQ(0, init_hw());
}

TEST_F(TestOsApi, initMultiTaskCalloc)
{
    calloc_fake.return_val = NULL;
    EXPECT_EQ(-1, init_multi_task());
}

#if 0
int test_join(pthread_t th, void **aaa)
{
    printf("test\n");
    return 0;
}

TEST_F(TestOsApi, termMultiTaskPthreadJoin)
{
    thdata = (struct thdata*)calloc(sizeof(struct thdata), 2);
    pthread_join_fake.custom_fake = test_join;
    EXPECT_EQ(0, term_multi_task());
}
#endif

TEST_F(TestOsApi, initMailbox)
{
    EXPECT_EQ(0, init_mailbox());
}

TEST_F(TestOsApi, termMailbox)
{
    EXPECT_EQ(0, term_mailbox());
}

TEST_F(TestOsApi, sendMail)
{
    mail_data_u data;
    write_fake.return_val = 10;
    EXPECT_EQ(10, send_mail(1, &data));
}

TEST_F(TestOsApi, sendMailWriteErr)
{
    mail_data_u data;
    write_fake.return_val = -1;
    EXPECT_EQ(-1, send_mail(1, &data));
}