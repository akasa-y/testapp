//#include <stdio.h>
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
        memset(&mail_data, 0, sizeof(mail_data));
        recv_mail(MAILBOX_SUB1, &mail_data);
        syslog(LOG_NOTICE,"fun1 recv %s\n", mail_data.mail_data.message);

        if(strcmp(mail_data.mail_data.message, "end") == 0)
        {
            break;
        }
        mail_data.mail_data.header.send_task_id = 0;
        mail_data.mail_data.header.recv_task_id = 1;
        mail_data.mail_data.header.message_id = 0;
        
        syslog(LOG_NOTICE,"fun1 send %s\n", mail_data.mail_data.message);
        send_mail(MAILBOX_SUB2, &mail_data);
    }
#ifdef ITRON
    return;
#else
    return NULL;
#endif
}

