#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef ITRON
#include "itron_only.h"
#else
#include "linux_only.h"
#endif

typedef struct {
    unsigned char send_task_id;
    unsigned char recv_task_id;
    unsigned char message_id;
    unsigned char reserved1;
} mail_header_t;

typedef struct {
    mail_header_t header;
    char message[60];
} mail_data_t;

typedef union {
    unsigned char data[32];
    mail_data_t mail_data;
} mail_data_u;

/**
 * @brief ハードウェア初期化関数
 * @return 正常時0
 * 
 * ハードウェア初期化する。LinuxとuITRONで異なった処理となる
 */
int init_hw();
int init_multi_task();
int term_multi_task();
int init_mailbox();
int term_mailbox();

int send_mail(int mailbox_id, mail_data_u *data);
int recv_mail(int mailbox_id, mail_data_u *data);

int read_line(char *line);

void main_task(intptr_t exinf);

#ifdef ITRON
void sub1(intptr_t exinf);
void sub2(intptr_t exinf);
#else
void *sub1(void *thdata);
void *sub2(void *thdata);
#endif


#endif