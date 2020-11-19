#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <limits.h>
#include <errno.h>
#include <stdarg.h>

#define MAXLENGHT 300
#define BUF_DIM 2048
// Path directory di prova -> /Users/fornasierarmando/Desktop/DirectoryProvaSO

void visit_and_copy_dir(char *source_path, char *dest_path);
void copy_element(char *source_path, char *dest_path, mode_t mode);

int main(int argc, const char * argv[]) {
    if (argc!=3) {
        fprintf(stderr, "Error, expected: prgm <source_pathName> <dest_pathName>\n");
        exit(1);
    }
    visit_and_copy_dir(argv[1], argv[2]);
    
    return 0;
}


void visit_and_copy_dir(char *source_path, char *dest_path) {
    struct stat statbuffer;
    struct dirent *dirp;
    DIR *dp;
    char new_source_path[MAXLENGHT];
    char new_dest_path[MAXLENGHT];
    
    if(lstat(source_path, &statbuffer) < 0) {
        fprintf (stderr, "Error running lstat on %s\n", source_path);
        exit (1);
    }
    
    /* FILE */
    if (S_ISDIR(statbuffer.st_mode)==0) {  // se source_path è un file lo copio
        copy_element(source_path, dest_path, statbuffer.st_mode);
        return;
    }
    
    /* DIRECTORY */
    if ((dp = opendir(source_path)) == NULL) {  // se è un direttorio lo apro
        fprintf(stderr, "Error opening directory %s\n", source_path);
        exit(-1);
    }
    
    if(mkdir(dest_path, statbuffer.st_mode)!=0){   // creo un direttorio gemello in dest_path
        fprintf(stderr, "Error creating new directory %s\n", dest_path);
        exit(-1);
    }
    
    while ((dirp = readdir(dp)) != NULL){
        sprintf(new_source_path, "%s/%s", source_path, dirp->d_name);  // creo path dell'elemento corrente
        sprintf(new_dest_path, "%s/%s", dest_path, dirp->d_name);  // creo path destinazione per l'elemento corrente
        
        if (lstat(new_source_path, &statbuffer) < 0) {
            fprintf(stderr, "Error running lstat on %s\n", new_source_path);
            exit(1);
        }
        
        if (!S_ISDIR(statbuffer.st_mode)){
            copy_element(new_source_path, new_dest_path, statbuffer.st_mode);  // se l'elemento è un file lo copio
        }
        else {
            if(!strcmp(".", dirp->d_name) || !strcmp("..", dirp->d_name)){  // ignoro ./ e ../
                continue;
            }
            visit_and_copy_dir(new_source_path, new_dest_path);
        }
    }
    if(closedir(dp)<0){
        fprintf(stderr, "Error closing directory %s", dirp->d_name);
        exit(-1);
    }
    
    return;
}



void copy_element(char *source_path, char *dest_path, mode_t mode) {
    int fdR, fdW, num_r, num_w;
    char buffer[BUF_DIM];
    
    if((fdR = open(source_path, O_RDONLY)) == -1){
        fprintf(stderr, "Error opening file in read mode - %s\n", source_path);
        exit(1);
    }
    if((fdW = open(dest_path, mode | O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1){
        fprintf(stderr, "Error opening file in write mode - %s\n", dest_path);
        exit(1);
    }
    
    while((num_r = (int)read(fdR, buffer, BUF_DIM)) > 0) {
        if((num_w = (int)write(fdW, buffer, num_r)) != num_r) {
            fprintf(stderr, "Error: read %d, written %d bytes\n", num_r, num_w);
            exit(-1);
        }
    }
    
    if(close(fdR)!=0 || close(fdW)!=0){
        fprintf(stderr, "Error closing a file\n");
    }
    
    return;
}
