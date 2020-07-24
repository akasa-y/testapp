#include <kernel.h>
#include <kernel_cfg.h>
#include <t_syslog.h>
#include <string.h>
#include "syssvc/syslog.h"

#include "common.h"

/* Typedef */

/* RAM */

/* ROM */

int init_multi_task()
{
    if(act_tsk(SUB1) != E_OK)
    {
        syslog(LOG_ERROR, "sub1 start err");
    }

    if(act_tsk(SUB2) != E_OK)
    {
        syslog(LOG_ERROR, "sub2 start err");
    }

    return 0;
}

int term_multi_task()
{
    if(ter_tsk(SUB1) != E_OK)
    {
        syslog(LOG_ERROR, "sub1 term err");
    }

    if(ter_tsk(SUB2) != E_OK)
    {
        syslog(LOG_ERROR, "sub2 term err");
    }

    return 0;
}

int init_mailbox()
{
    return 0;
}

int term_mailbox()
{
    return 0;
}

int send_mail(int mailbox_id, mail_data_u *data)
{
    mail_data_u *mpf = NULL;

    get_mpf(MPF_DTQ, (void**)&mpf);
    memcpy(mpf, data, sizeof(mail_data_u));
    snd_dtq(mailbox_id, (intptr_t)mpf);

    return 0;
}

int recv_mail(int mailbox_id, mail_data_u *data)
{
    mail_data_u *mpf = NULL;

    rcv_dtq(mailbox_id, (intptr_t*)&mpf);
    memcpy(data, mpf, sizeof(mail_data_u));
    rel_mpf(MPF_DTQ, mpf);

    return 0;
}
