#include <kernel.h>
#include <kernel_cfg.h>
#include <t_syslog.h>
#include <string.h>
#include "syssvc/syslog.h"
#include "syssvc/serial.h"

#include "common.h"

/* Typedef */

/* RAM */

/* ROM */

Inline void
svc_perror(const char *file, int_t line, const char *expr, ER ercd)
{
	if (ercd < 0) {
		t_perror(LOG_ERROR, file, line, expr, ercd);
	}
}

#define	SVC_PERROR(expr)	svc_perror(__FILE__, __LINE__, #expr, (expr))

static int init_serial()
{
    ER_UINT	ercd;
	ercd = serial_opn_por(TASK_PORTID);
	if (ercd < 0 && MERCD(ercd) != E_OBJ) {
		syslog(LOG_ERROR, "%s (%d) reported by `serial_opn_por'.",
									itron_strerror(ercd), SERCD(ercd));
	}
	SVC_PERROR(serial_ctl_por(TASK_PORTID,
							(IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV)));
    return 0;
}

int init_hw()
{
    return init_serial();
}

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

int read_line(char *line)
{
    int i = 0;
    char c;

    while(i < 256)
    {
//        syslog(LOG_NOTICE, "in read_line");
        serial_rea_dat(TASK_PORTID, &c, 1);
//        syslog(LOG_NOTICE, "read_line get %x", c, c);
        if(c == 0xd)
        {
            line[i] = 0;
            break;
        }
        else
        {
            line[i++] = c;
        }
    }
//    syslog(LOG_NOTICE, "read_line done %s, %d", line, i);
    return i;
}