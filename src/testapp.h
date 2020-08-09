#ifndef __TESTAPP_H__
#define __TESTAPP_H__

#include <kernel.h>

#define MAIN_PRIORITY	5
#define MID_PRIORITY	10
#define	STACK_SIZE		4096

#define TA_TFIFO    0
#define MPF_BLKCNT 10
#define MPF_BLKSIZE 64

#define DTQ_CNT 10

void main_task(intptr_t exinf);
void sub1(intptr_t exinf);
void sub2(intptr_t exinf);

#endif