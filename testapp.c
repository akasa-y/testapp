#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

int main(int argc, char *argv[])
{
    char line[32];
    mail_data_u mail_data;

    memset(&mail_data, 0, sizeof(mail_data));
    mail_data.mail_data.header.send_task_id = 2;
    mail_data.mail_data.header.recv_task_id = 1;
    mail_data.mail_data.header.message_id = 0;
    mail_data.mail_data.message[0] = 0;

    init_hw();
    init_mailbox();
    init_multi_task();

    while(1)
    {
        read_line(line);
        memset(mail_data.mail_data.message, 0, sizeof(mail_data.mail_data.message));
        strncpy(mail_data.mail_data.message, line, strlen(line));
        send_mail(0, &mail_data);
        send_mail(1, &mail_data);
        if(strcmp(mail_data.mail_data.message, "end") == 0)
        {
            break;
        }
    }

    term_multi_task();
    term_mailbox();

    return 0;
}

