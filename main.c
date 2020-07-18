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

    init_mailbox();
    init_multi_task();

    while(1)
    {
        fgets(line, 32, stdin);
        if(strlen(line) == 1)
        {
            break;
        }
        strcpy(mail_data.mail_data.message, line);
        send_mail(1, &mail_data);
    }

    term_multi_task();
    term_mailbox();

    return 0;
}

