
#include "../lib/pidman.h"
#include "../lib/queue.h"



extern PidManager pidManager;


int 
init( void ) {

    setbuf(stdout, NULL);

    printf( "-----------PID Manager-----------\n" );

    process_t p;
    printf( "Enter Number of Threads: " );
    scanf( "%d", &p.n );

    return p.n;

}

int allocate_map(void)
{
    int status = 0;
    int i;
    
    status = construct(&pidManager.availablePids);
    if (status != 0)
    {
        return -1;
    }
    
    for (i = MIN_PID; i <= MAX_PID; i++)
    {
        pidManager.availablePids.enqueue(&pidManager.availablePids, i);
    }
    
    pidManager.numAvailablePids = NUM_PIDS;
    
    status = pthread_mutex_init(&pidManager.lock, NULL);
    if (status != 0)
        status = -1;
    
    return status;
}

int destroy_map(void)
{
    int status;
    
    if (pidManager.availablePids.queue != NULL)
        destruct(&pidManager.availablePids);
    
    status = pthread_mutex_destroy(&pidManager.lock);
    if (status != 0)
        status = -1;
    return status;
}

void allocate_pid(int *pid)
{
    int status;
    
    status = pthread_mutex_lock(&pidManager.lock);
    if (status != 0)
    {
        *pid = status;
        return;
    }
    
    if (pidManager.numAvailablePids == 0)
    {
        *pid = -1;
        return;
    }
    
    *pid = pidManager.availablePids.dequeue(&pidManager.availablePids);
    if (*pid != -1)
        pidManager.numAvailablePids--;
    
    status = pthread_mutex_unlock(&pidManager.lock);
    if (status != 0) {
        *pid = status;
    }
    
    return;
}

void release_pid(int pid)
{
    int status;
    
    if (pid < MIN_PID || pid > MAX_PID)
        return;
    
    status = pthread_mutex_lock(&pidManager.lock);
    if (status != 0)
        return;
    
    status = pidManager.availablePids.enqueue(&pidManager.availablePids, pid);
    
    if (status != -1)
        pidManager.numAvailablePids++;
    
    status = pthread_mutex_unlock(&pidManager.lock);
    
    return;
}
