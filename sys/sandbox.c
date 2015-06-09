#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "bsp.h"

#ifdef DEBUG_CYASSL
    #include <cyassl/ssl.h>
#endif

extern void SysTick_Handler(void);

void tick_handler(int sig)
{
    SysTick_Handler();
}

#ifdef PTHREAD
#include <pthread.h>

/* Pthread virtual timer thread. 
 * Could cause some drift, but avoids performance loss due
 * to continuous SIGALRM.
 */
void *task_SysTimer(void *arg)
{
    struct timespec ts = { 0, 1000000 };
    (void)arg;
    while (1 < 2) {
        SysTick_Handler();
        nanosleep(&ts, NULL);
    }
    return NULL;
}

#endif

void BSP_Init(void)
{
    useconds_t usecs;

#ifdef PTHREAD
    pthread_t tick;
    pthread_create(&tick, NULL, task_SysTimer, NULL);
#else
    sigset(SIGALRM, tick_handler);
    usecs = 1000;
    ualarm(usecs, usecs);
#endif

#ifdef DEBUG_CYASSL
    CyaSSL_Debugging_ON();
#endif

}

#define CMDLINE_FILE "/proc/%d/cmdline"
void BSP_Reset(void)
{
    pid_t pid = getpid();
    char cmdline_file[200];
    char cmdline[1024];
    int cfd, r;
    snprintf(cmdline_file, 200, CMDLINE_FILE, pid);
    cfd = open(cmdline_file, O_RDONLY);
    if (cfd < 0) {
        printf("Reboot failed: Cannot access %s: %s\n", cmdline_file, strerror(errno));
        exit(2);
    }
    r = read(cfd, cmdline, 1024);

    if (r < 0) {
        printf("Reboot failed: Cannot read cmdline from proc file\n");
        exit(2);
    }
    printf("############ Rebooting...\n\n\n");
    sigset(SIGALRM, SIG_IGN);
    execl(cmdline, cmdline, NULL);
}

