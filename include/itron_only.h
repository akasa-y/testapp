#ifndef __ITRON_ONLY_H__
#define __ITRON_ONLY_H__

#include <kernel.h>
#include <t_syslog.h>
#include <kernel_cfg.h>
#include "syssvc/syslog.h"

#ifndef TASK_PORTID
#define	TASK_PORTID		1			/* 文字入力するシリアルポートID */
#endif /* TASK_PORTID */

#endif