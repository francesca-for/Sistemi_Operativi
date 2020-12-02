#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main () {
  char str[100];
  int i;

  setbuf(stdout,0);
  fork();
  for (i=0; i<2; i++){
    if (fork()!=0) {
      sprintf (str, "echo system with i=%d, %d", i, getpid());
      //sleep(8);
      system (str);
    } else {
      sprintf (str, "exec with i=%d, %d", i, getpid());
      //sleep(5+5*i);
      execlp ("echo", "myPgrm", str, NULL);
    }
  }
  return (0);
}
