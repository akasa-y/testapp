#include <stdio.h>
#include <stdlib.h>
#include "common.h"

void *func1_main(void *thdata)
{
    int i;
    for(i = 0; i < 10; i++)
    {
        printf("thread1 start\n");
    }
    return NULL;
}