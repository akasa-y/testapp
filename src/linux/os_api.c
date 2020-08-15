#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

#include "common.h"

/* Typedef */
//! スレッド用の構造体
struct thdata {
    pthread_t th; //!< スレッドIDを記録する
};

//! メールボックス(mailbox_fd)にアクセスするために使用する
enum {
    RD = 0, //!< READ用の配列アクセス
    WR = 1  //!< WRITE用の配列アクセス
};

/* RAM */
struct thdata *thdata;  //!< (RAM)スレッド記録用
int mailbox_fd[2][2];   //!< (RAM)スレッド間IFに使用するメールボックスfd

/* ROM */
const char *mailbox_filename[2] = {"/tmp/sub1_mailbox", "/tmp/sub2_mailbox"}; //!< (ROM)FIFOアクセス用ファイル

/**
 * @brief Linux用ハードウェア初期化関数
 * @return 常に0
 * 
 * Linuxではハードウェア初期化はないため何もせず0を返す
 */
int init_hw()
{
    return 0;
}

int init_multi_task()
{
    int ret;

    thdata = (struct thdata*)calloc(sizeof(struct thdata), 2);
    if(thdata == NULL)
    {
        perror("calloc()");
        ret = -1;
        goto err1;
    }

    if(pthread_create(&thdata[0].th, NULL, sub1, &thdata[0]) != 0)
    {
        perror("pthread_create0");
        ret = -2;
        goto err2;
    }

    if(pthread_create(&thdata[1].th, NULL, sub2, &thdata[1]) != 0)
    {
        perror("pthread_create1");
        ret = -3;
        goto err3;
    }

    return 0;

err3:
    pthread_cancel(thdata[0].th);
    pthread_join(thdata[0].th, NULL);
err2:
    free(thdata);
    thdata = NULL;
err1:
    return ret;
}

int term_multi_task()
{
    int i;
    int ret = 0;
    for(i = 0; i < 2; i++)
    {
        if(pthread_join(thdata[i].th, NULL) != 0)
        {
            printf("join err %d\n", i);
            ret = -1;
        }
    }

    free(thdata);
    thdata = NULL;

    return ret;
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

int read_line(char *line)
{
    char *c;
    fgets(line, 32, stdin);

    c = strchr(line, '\n');
    if(c)
    {
        *c = 0;
    }
    return strlen(line);
}

int syslog_msk_log(unsigned int  logmask, unsigned int lowmask)
{
    return 0;
}

void syslog(unsigned int prio, const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);
}
