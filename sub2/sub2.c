#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#ifdef ITRON
void sub2(intptr_t exinf)
#else
void *sub2(void *thdata)
#endif
{
    mail_data_u mail_data;

    while(1)
    {
        recv_mail(1, &mail_data);
        syslog(LOG_NOTICE,"fun2 recv %s\n", mail_data.mail_data.message);

        if(strcmp(mail_data.mail_data.message, "end") == 0)
        {
            break;
        }
    }
#ifdef ITRON
    return;
#else
    return NULL;
#endif
}
