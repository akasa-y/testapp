#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

void *func1_main(void *thdata)
{
    mail_data_u mail_data;

    while(1)
    {
        recv_mail(0, &mail_data);
        printf("fun1 recv %s\n", mail_data.mail_data.message);

        if(strcmp(mail_data.mail_data.message, "end") == 0)
        {
            break;
        }
        mail_data.mail_data.header.send_task_id = 0;
        mail_data.mail_data.header.recv_task_id = 1;
        mail_data.mail_data.header.message_id = 0;

        strcat(mail_data.mail_data.message, " from1");
        send_mail(1, &mail_data);
    }

    return NULL;
}