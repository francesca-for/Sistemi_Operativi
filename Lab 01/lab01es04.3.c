#include <stdlib.h>
#include <stdio.h>
#define BUFFER_DIM 1024

int main(int argc, const char * argv[]) {
    FILE *fps, *fpd;
    int num_elem;
    char buf[BUFFER_DIM];
    
    if(argc!=3){
        fprintf(stderr, "Error: expected 3 parameters\n");
        exit(-1);
    }
    
    if((fps=fopen(argv[1], "rb"))==NULL){
        fprintf(stderr, "Error: opening source file\n");
        exit(-1);
    }
    
    if((fpd=fopen(argv[2], "wb"))==NULL){
        fprintf(stderr, "Error: opening destination file\n");
        exit(-1);
    }
    
    while((num_elem = fread(buf, 1, BUFFER_DIM, fps)) > 0) {
        fwrite(buf, 1, num_elem, fpd);
    }
    
    fclose(fps);
    fclose(fpd);
    
    return 0;
}
