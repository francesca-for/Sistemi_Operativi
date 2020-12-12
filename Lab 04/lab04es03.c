#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_PRMT 50
#define LEN_PRMT 100

int main(int argc, const char *argv[]){
     //char endCmd[] = "end";
     char line[MAX_PRMT*LEN_PRMT+1], **commands;
     //char cmd[MAX_PRMT*LEN_PRMT-3];
     FILE *fp;

     if (argc!=2) {
          fprintf(stderr, "Error: 2 parametres expected\n");
          exit(-1);
     }


     /* SYSTEM */

     if((fp = fopen(argv[1], "r")) == NULL) {
          fprintf(stderr, "Error opening file %s\n", argv[1]);
          exit(1);
     }

     setbuf(stdout, 0);
     /*while (fgets(line, MAX_PRMT*LEN_PRMT+1, fp) != NULL){
          char cmd[MAX_PRMT*LEN_PRMT-3];
          strcpy(line, "ls -laR end\n");           // per debug
          fprintf(stdout, "%lu\n", strlen(line)-5);
          //strncpy(cmd, line, strlen(line)-5);
          strncpy(cmd, line, strlen(line)-5);
          strcat(cmd, "-end\n");  // per debug
          //strcat(cmd, "\0");  // per debug
          sleep(3);
          fprintf(stdout, "%s", cmd);
          system(cmd);
     }*/

     for(int i=0; i<4; i++){
          char cmd[MAX_PRMT*LEN_PRMT-3];

          if(i==0){
            strcpy(line, "ls -laR end\n");           // per debug
            fprintf(stdout, "\n%lu - ", strlen(line)-5);
            //strncpy(cmd, line, strlen(line)-5);
            strncpy(cmd, line, strlen(line)-5);
          }
          if(i==1){
            strcpy(line, "less mioFile.c end\n");           // per debug
            fprintf(stdout, "\n%lu - ", strlen(line)-5);
            //strncpy(cmd, line, strlen(line)-5);
            strncpy(cmd, line, strlen(line)-5);
          }
          if(i==2){
            strcpy(line, "mkdir tmpDir end\n");           // per debug
            fprintf(stdout, "\n%lu - ", strlen(line)-5);
            //strncpy(cmd, line, strlen(line)-5);
            strncpy(cmd, line, strlen(line)-5);
          }
          if(i==3){
            strcpy(line, "cp mioFile.c tmpDir end\n");           // per debug
            fprintf(stdout, "\n%lu - ", strlen(line)-5);
            //strncpy(cmd, line, strlen(line)-5);
            strncpy(cmd, line, strlen(line)-5);
          }

            strcat(cmd, "\n");  // per debug
          //strcat(cmd, "\0");  // per debug
            sleep(3);
            fprintf(stdout, "%s", cmd);
            system(cmd);
	}

     fclose(fp);


     /* EXEC */
/*
     if((fp = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "Error opening file %s\n", argv[1]);
		exit(1);
	}

	setbuf(stdout, 0);
	//char cmd[10];
	while (fgets(line, MAX_PRMT*LEN_PRMT+1, fp) != NULL) {
          //swhile(sscanf(const char *restrict, const char *restrict, ...)
          //commands = (char **) malloc(size_t __size)
		if(!fork()){
			char cmd[MAX_LENGTH-2];
			strncpy(cmd, line, strlen(line)-5);
			fprintf(stdout, "%s\n", strcat(cmd, "\0"));
			//sleep(1);
			execvp(const char *__file, char *const *__argv);
		}
		sleep(1);
	}

	fclose(fp);*/

	return (0);
}
