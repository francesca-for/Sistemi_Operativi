#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void sigusr1(int sig){
    if(sig==SIGUSR1){
        fprintf(stdout, "Received SIGUSR1\n");
        fprintf(stdout, "sigurs1 sleeping...\n");
        sleep(5);
        fprintf(stdout, "...sigurs1 ended sleeping\n");
    }
    else fprintf(stderr, "Wrong signal\n");
    return;
}

static void sigusr2(int sig){
    if(sig==SIGUSR2){
        fprintf(stdout, "Received SIGUSR2\n");
        fprintf(stdout, "sigurs2 sleeping...\n");
        sleep(5);
        fprintf(stdout, "...sigurs2 ended sleeping\n");
    }
    else fprintf(stderr, "Wrong signal\n");
    return;
}

int main(int argc, const char * argv[]) {
    setbuf(stdout, 0);
    setbuf(stderr, 0);
    if(signal(SIGUSR1, sigusr1)==SIG_ERR || signal(SIGUSR2, sigusr2)==SIG_ERR){
        fprintf(stderr, "Signal Handler Error.\n");
        return -1;
    }
    while(1){
        fprintf(stdout, "Before pause <-\n");
        pause();
        fprintf(stdout, "-> After pause\n");
    }
    return 0;
}
