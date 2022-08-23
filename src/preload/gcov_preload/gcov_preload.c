#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <signal.h>
#define SIMPLE_WAY

void sighandler(int signo) 
{ 
#ifdef SIMPLE_WAY
    exit(signo); 
#else
    extern void __gcov_flush(); /* flush */
    __gcov_flush(); /* flush out gcov stats data */
    raise(signo); /* raise the signal again to crash process */ 
#endif 
} 

/**
* The code for cracking the preloaded dynamic library gcov_preload.so is as follows, where __attribute__((constructor)) is the symbol of gcc,
* The modified function will be called before the main function is executed. We use it to intercept the exception signal to our own function, and then call __gcov_flush() to output the error message
*/

__attribute__ ((constructor))

void ctor() 
{
    int sigs[] = {
        SIGILL, SIGFPE, SIGABRT, SIGBUS,
        SIGSEGV, SIGHUP, SIGINT, SIGQUIT,
        SIGTERM     
    };
    int i; 
    struct sigaction sa;
    sa.sa_handler = sighandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESETHAND;

    for(i = 0; i < sizeof(sigs)/sizeof(sigs[0]); ++i) {
        if (sigaction(sigs[i], &sa, NULL) == -1) {
            perror("Could not set signal handler");
        }
    } 
}
