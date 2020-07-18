#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

void *func2_main(void *thdata)
{
    int ret;
    mail_data_u mail_data;

    while(1)
    {
        ret = recv_mail(1, &mail_data);
        printf("recv %s\n", mail_data.mail_data.message);

        if(strcmp(mail_data.mail_data.message, "end\n") == 0)
        {
            printf("done\n");
            break;
        }
    }

    return NULL;
}
