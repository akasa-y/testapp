#ifndef __COMMON_H__
#define __COMMON_H__

typedef struct {
    unsigned char send_task_id;
    unsigned char recv_task_id;
    unsigned char message_id;
    unsigned char reserved1;
} mail_header_t;

typedef struct {
    mail_header_t header;
    char message[28];
} mail_data_t;

typedef union {
    unsigned char data[32];
    mail_data_t mail_data;
} mail_data_u;

int init_multi_task();
int term_multi_task();
int init_mailbox();
int term_mailbox();

int send_mail(int mailbox_id, mail_data_u *data);
int recv_mail(int mailbox_id, mail_data_u *data);

void *func1_main(void *thdata);
void *func2_main(void *thdata);

#endif