#include <string.h>
#include "gtest/gtest.h"
#include "fff.h"
DEFINE_FFF_GLOBALS;

extern "C"
{
    #include "common.h"
    #include "main_task/main_task.c"
}

int test_init();

FAKE_VALUE_FUNC(int, read_line, char*);
FAKE_VALUE_FUNC(int, send_mail, int, mail_data_u*);
FAKE_VALUE_FUNC(int, init_multi_task);
FAKE_VALUE_FUNC(int, term_multi_task);
FAKE_VALUE_FUNC(int, init_hw);
FAKE_VALUE_FUNC(int, init_mailbox);
FAKE_VALUE_FUNC(int, term_mailbox);

class TestMainTask: public testing::Test {
    void SetUp() {
        RESET_FAKE(read_line);
        RESET_FAKE(send_mail);
        RESET_FAKE(init_multi_task);
        RESET_FAKE(term_multi_task);
        RESET_FAKE(init_hw);
        RESET_FAKE(init_mailbox);
        RESET_FAKE(term_mailbox);
        FFF_RESET_HISTORY();
        test_init();
    }
    void TearDown() {
        test_init();
    }
};

static int num;
static int read_num;
static char *strings[16] = {NULL};

int test_init()
{
    unsigned int i;
    for(i = 0; i < sizeof(strings)/sizeof(char*); i++ ){
        free(strings[i]);
        strings[i] = NULL;
    }
    num = 0;
    read_num = 0;

    return 0;
}

int test_read_add(const char *str)
{
    strings[num] = (char*)malloc(strlen(str));
    strcpy(strings[num], str);
    num++;
    return 0;
}

int test_read_line(char *line)
{
    if(read_num < num) {
        strcpy(line, strings[read_num]);
        read_num++;
        return 0;
    } else {
        return -1;
    }
}


TEST_F(TestMainTask, test1)
{
    test_read_add("end");
    read_line_fake.custom_fake = test_read_line;
    main_task((intptr_t)NULL);
    EXPECT_EQ(read_line_fake.call_count, 1);
}

TEST_F(TestMainTask, test2)
{
    test_read_add("start");
    test_read_add("end");
    read_line_fake.custom_fake = test_read_line;
    main_task((intptr_t)NULL);
    EXPECT_EQ(read_line_fake.call_count, 2);
}
