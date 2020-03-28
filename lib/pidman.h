#ifndef PIDMAN_h
#define PIDMAN_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "./queue.h"


#define MIN_PID     300
#define MAX_PID     5000
#define NUM_PIDS    ((MAX_PID - MIN_PID) + 1)
#define INVALID_PID -1

typedef struct 
{
	int n;
} process_t;

int init( void );


struct PidManager
{
    Queue availablePids;
    
    int numAvailablePids;
    
    pthread_mutex_t lock;
};

typedef struct PidManager PidManager;


int allocate_map(void);


void allocate_pid(int *pid);

void release_pid(int pid);

#endif /* PIDMAN_h */
