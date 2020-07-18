#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <unistd.h>

#include "common.h"

/* Typedef */
struct thdata {
    pthread_t th;
};

enum {
    RD = 0,
    WR = 1
};

/* RAM */
struct thdata *thdata;
int mailbox_fd[2][2];

/* ROM */
const char *mailbox_filename[2] = {"/tmp/sub1_mailbox", "/tmp/sub2_mailbox"};

int init_multi_task()
{
    int ret;

    thdata = calloc(sizeof(struct thdata), 2);
    if(thdata == NULL)
    {
        perror("calloc()");
        return -1;
    }

    ret = pthread_create(&thdata[0].th, NULL, func1_main, &thdata[0]);
    ret += pthread_create(&thdata[1].th, NULL, func2_main, &thdata[1]);
    if(ret != 0)
    {
        perror("init pthread_create");
        return -2;
    }
    return 0;
}

int term_multi_task()
{
    free(thdata);
    thdata = NULL;

    return 0;
}

int init_mailbox()
{
    int i;
    for(i = 0; i < 2; i++)
    {
        if(mkfifo(mailbox_filename[i], 0666) == -1)
        {
            perror("mkfile");
        }

        mailbox_fd[i][WR] = open(mailbox_filename[i], O_RDWR);
        mailbox_fd[i][RD] = open(mailbox_filename[i], O_RDWR);
//        if(mailbox_fd[i][WR] = open(mailbox_filename[i], O_WRONLY) == -1)
//        {
//            perror("mailbox fd WR");
//        }

//        if(mailbox_fd[i][RD] = open(mailbox_filename[i], O_RDONLY) == -1)
//        {
//           perror("mailbox fd WR");
//        }
    }
    return 0;
}

int term_mailbox()
{
    int i;
    char cmd[256];

    for(i = 0; i < 2; i++)
    {
        close(mailbox_fd[i][RD]);
        close(mailbox_fd[i][WR]);

        sprintf(cmd,"rm -f %s", mailbox_filename[i]);
        system(cmd);
    }
    return 0;
}

int send_mail(int mailbox_id, mail_data_u *data)
{
    int ret;

    ret = write(mailbox_fd[mailbox_id][WR], data, sizeof(mail_data_u));
    if(ret < 0)
    {
        printf("write err\n");
    }
    return ret;
}

int recv_mail(int mailbox_id, mail_data_u *data)
{
    int ret;

    ret = read(mailbox_fd[mailbox_id][RD], data, sizeof(mail_data_u));
    if(ret < 0)
    {
        printf("read err\n");
    }
    return ret;
}