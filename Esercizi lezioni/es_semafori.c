#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>
#define L 100

struct threadData {
     pthread_t threadId;
     int id;
     FILE *fp;
     int line;
     int sum;
};

static void *readFile (void *);
sem_t sem;

int main (int argc, char *argv[]) {
     int i, nT, total, line;
     struct threadData *td;
     void *retval;
     FILE *fp;

     nT = atoi (argv[1]);
     td = (struct threadData *) malloc (nT * sizeof(struct threadData));

     fp = fopen (argv[2], "r");
     if (fp==NULL) {
          fprintf (stderr, "Error opening file.\n");
          exit (1);
     }
     sem_init (&sem, 0, 1);

     for (i=0; i<nT; i++) {
          td[i].id = i;
          td[i].fp = fp;           // same fp for all threads
          td[i].line = td[i].sum = 0;
          pthread_create (&(td[i].threadId), NULL, readFile, (void *) &td[i]);
     }

     total = line = 0;

     for (i=0; i<nT; i++) {
          pthread_join (td[i].threadId, &retval);
          total += td[i].sum;
          line += td[i].line;
     }
     fprintf (stdout, "Total: Sum=%d #Line=%d\n", total, line);
     sem_destroy (&sem);
     fclose (fp);
     return 1;
}

static void *readFile (void *arg) {
     int n, retVal;
     struct threadData *td;
     td = (struct threadData *) arg;
     do {
          sem_wait (&sem);     //protezione lettura da file
          retVal = fscanf (td->fp, "%d", &n);
          sem_post (&sem);
          if (retVal!=EOF) {
               td->line++;
               td->sum += n;
          }
          sleep(1);    // Delay Threads
     } while (retVal!=EOF);
     fprintf (stdout, "Thread: %d Sum=%d #Line=%d\n", td->id, td->sum, td->line);
     pthread_exit ((void *) 1);
}
