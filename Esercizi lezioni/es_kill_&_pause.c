#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigUsr(int sig){
    if(sig==SIGUSR1)
        fprintf(stdout, "SIGUSR1 received\n");
    else if(sig==SIGUSR2)
        fprintf(stdout, "SIGUSR2 received\n");
    else
        fprintf(stdout, "Signal %d received\n", sig);
    return;
}


void Psx(pid_t childPid){
    fprintf(stdout, "S11\n");
    sleep(2);    //  <-----
    kill(childPid, SIGUSR1);
    fprintf(stdout, "S12\n");
    sleep(2);    //  <-----
    pause();
    fprintf(stdout, "S13\n");
    sleep(2);    //  <-----
    return;
}

void Pdx(pid_t parentPid){
    pid_t pid;
    pid = fork();
    if(pid==0){
        fprintf(stdout, "S22\n");
        sleep(2);    //  <-----
        exit(0);
    }
    else{
        fprintf(stdout, "S21\n");
        sleep(2);    //  <-----
        pause();
        fprintf(stdout, "S23\n");
        sleep(2);    //  <-----
        kill(parentPid, SIGUSR2);
        wait((int *) 0);
    }
    fprintf(stdout, "S24\n");
    sleep(2);    //  <-----
    return;
}


int main(int argc, const char * argv[]) {
    pid_t pid;
    
    if(signal(SIGUSR1, sigUsr)==SIG_ERR){
        fprintf(stderr, "Signal Handler Error\n");
        return (-2);
    }
    
    if(signal(SIGUSR2, sigUsr)==SIG_ERR){
        fprintf(stderr, "Signal Handler Error\n");
        return (-2);
    }
    
    setbuf(stdout, 0);
    
    fprintf(stdout, "S20\n");
    sleep(2);    //  <-----
    
    pid = fork();
    if(pid==0) {  // FIGLIO
        Pdx(getppid());
        exit(0);
    }
    else if(pid>0) {  // PADRE
        Psx(pid);
        wait((int *) 0);
    }
    fprintf(stdout, "S25\n");
    
    return 0;
}
