
#include "../lib/pidman.h"


#define MAX_SLEEP_TIME  5

PidManager pidManager;


void* acquireAndReleasePid(void *args);


int main(int argc, const char * argv[]) {
    
    process_t p;
    p.n = init();

    int          i;
    int          status;
    pthread_t    tids[p.n];
    unsigned int sleepTimes[p.n];
    
    for (i = 0; i < p.n; i++)
    {
        sleepTimes[i] = rand() % MAX_SLEEP_TIME;
    }
    
    status = allocate_map();
    if (status != 0) return status;
    
    for (i = 0; i < p.n; i++)
    {
        status = pthread_create(&tids[i], NULL, acquireAndReleasePid,
                                (void *)&sleepTimes[i]);
        printf("%d %d\n", i, tids[i]);
        if (status != 0) return status;
    }
    
    for (i=0; i< p.n; i++)
    {
        status = pthread_join(tids[i], NULL);
        printf("%d %d\n", i, tids[i]);
        if (status != 0) return status;
    }
    
    return status;
}


void* acquireAndReleasePid(void *args)
{
    unsigned int sleepTime;
    int          pid;
    
    sleepTime = *((unsigned int *)args);
    sleep(sleepTime);
    
    allocate_pid(&pid);
    
    sleep(sleepTime);
    
    release_pid(pid);
    
    return NULL;
}
