#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	tC = atoi(argv[1]);	 // ricevo da linea di comando due valori
	tF = atoi(argv[2]);	 // che considero come interi, tempi di attesa
	//da completare
	printf(“Main: 			”);
	printf(“PID=%d; My parent PID=%d\n”, getpid(), getppid());
	//da completare
	pid = fork();

	if (pid == 0) {
		sleep(tC);
		// system call che riceve come parametro unsigned int = num secondi
 		// e mette in il processo in pausa per il tempo specificato (circa)
		printf(“Child : PIDreturned=%d	  ”, pid);
		printf(“PID=%d; My parent PID=%d\n”, getpid(), getppid()”);
	} else {
		sleep(tF);
		printf(“Father : PIDreturned=%d	  ”, pid);
		printf(“PID=%d; My parent PID=%d\n”, getpid(), getppid()”);
	}

	return 0;
}
