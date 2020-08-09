#ifndef __LINUX_ONLY_H__
#define __LINUX_ONLY_H__

#include <stdarg.h>
/*
 *  ログ情報の重要度の定義
 */
#define LOG_EMERG			0		/* シャットダウンに値するエラー */
#define LOG_ALERT			1
#define LOG_CRIT			2
#define LOG_ERROR			3		/* システムエラー */
#define LOG_WARNING			4		/* 警告メッセージ */
#define LOG_NOTICE			5
#define LOG_INFO			6
#define LOG_DEBUG			7		/* デバッグ用メッセージ */

#define LOG_MASK(prio)		(1U << (prio))
#define LOG_UPTO(prio)		((1U << ((prio) + 1)) - 1)

int syslog_msk_log(unsigned int  logmask, unsigned int lowmask);
void syslog(unsigned int prio, const char *format, ...);

#define MAILBOX_MAIN 99
#define MAILBOX_SUB1 0
#define MAILBOX_SUB2 1

#endif