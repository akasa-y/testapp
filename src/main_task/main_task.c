/**
 * @file main_task.c
 * @brief メインタスク用の処理を記述する
 */
#include <string.h>
#include "common.h"

/**
 * @fn void main_task(intptr_t exinf)
 * @brief メインタスクのエントリー関数
 * @param[in] exinf 未使用
 * @return なし
 * 
 * この関数でハード初期化や資源確保を行う。
 * キーボードからの"end"を受けるまでキーボードの入力を他のタスクに送付する。
 */
void main_task(intptr_t exinf)
{
    char line[32];
    mail_data_u mail_data;

    memset(&mail_data, 0, sizeof(mail_data));
    mail_data.mail_data.header.send_task_id = 2;
    mail_data.mail_data.header.recv_task_id = 1;
    mail_data.mail_data.header.message_id = 0;
    mail_data.mail_data.message[0] = 0;

    init_hw();
    init_mailbox();
    init_multi_task();

    while(1)
    {
        read_line(line);
        memset(mail_data.mail_data.message, 0, sizeof(mail_data.mail_data.message));
        strncpy(mail_data.mail_data.message, line, strlen(line));
        send_mail(MAILBOX_SUB1, &mail_data);
        send_mail(MAILBOX_SUB2, &mail_data);
        if(strcmp(mail_data.mail_data.message, "end") == 0)
        {
            break;
        }
    }

    term_multi_task();
    term_mailbox();
}

