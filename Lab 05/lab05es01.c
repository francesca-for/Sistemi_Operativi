#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, const char* argv[]) {
     int num;

     do {
          fscanf(stdin, "%d", &num);
          if(num%2==0){
               fprintf(stdout, "%d ", num);
          }
          else {
               fprintf(stderr, "%d ", num);
          }
          sleep(1);
     }while(num!=0);

     return 0;
}
