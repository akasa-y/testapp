#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#ifdef ITRON
void sub1(intptr_t exinf)
#else
void *sub1(void *thdata)
#endif
{
    mail_data_u mail_data;

    while(1)
    {
        recv_mail(0, &mail_data);
        syslog(LOG_NOTICE,"fun1 recv %s\n", mail_data.mail_data.message);

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
#ifdef ITRON
    return;
#else
    return NULL;
#endif
}