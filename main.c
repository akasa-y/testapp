#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct thdata {
    pthread_t th;
};

void *thread_func1(void *thdata)
{
    int i;
    for(i = 0; i < 10; i++)
    {
        printf("thread1 start\n");
    }
    return NULL;
}


void *thread_func2(void *thdata)
{
    int i;
    for(i = 0; i < 10; i++)
    {
        printf("thread2 start\n");
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    int ret = 0;
    int count;
    struct thdata *thdata;

    thdata = calloc(sizeof(struct thdata), 2);
    if(thdata == NULL)
    {
        perror("calloc()");
        return -1;
    }

    ret = pthread_create(&thdata[0].th, NULL, thread_func1, &thdata[0]);
    ret += pthread_create(&thdata[1].th, NULL, thread_func2, &thdata[1]);
    if(ret != 0)
    {
        perror("init pthread_create");
        return -2;
    }

    while(1)
    {
        scanf("%d", &count);
        if(count == 0)
        {
            break;
        }
    }

    free(thdata);
    return 0;
}

