#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

void *func2_main(void *thdata)
{
    mail_data_u mail_data;

    while(1)
    {
        recv_mail(1, &mail_data);
        printf("fun2 recv %s\n", mail_data.mail_data.message);

        if(strcmp(mail_data.mail_data.message, "end") == 0)
        {
            break;
        }
    }

    return NULL;
}
