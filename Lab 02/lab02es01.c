#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>

#include <limits.h>
#include <errno.h>
#include <stdarg.h>

#define MAXLENGHT 300
// Path directory di prova -> /Users/fornasierarmando/Desktop/DirectoryProvaSO

void visit_directory(const char path[], char fill[]);

int main(int argc, const char * argv[]) {
    if (argc!=2) {
        fprintf(stderr, "Error: expected prgm <pathName>\n");
        exit(1);
    }
    visit_directory(argv[1], "");
    return 0;
}


void visit_directory(const char path[], char fill[]) {
    struct stat statbuffer;
    struct dirent *dirp;
    DIR *dp;
    char new_path[MAXLENGHT];
    char new_fill[MAXLENGHT];

    if(lstat(path, &statbuffer) < 0) {
        fprintf (stderr, "Error running lstat on %s\n", path);
        exit (1);
    }

    if (!S_ISDIR(statbuffer.st_mode)) {  // FILE
        return;
    }

    if ((dp = opendir(path)) == NULL) {  // DIRECTORY
        fprintf(stderr, "Error opening directory %s\n", path);
        exit(-1);
    }

    while ((dirp = readdir(dp)) != NULL){
        sprintf(new_path, "%s%s%s", path, "/", dirp->d_name);

        if (lstat(new_path, &statbuffer) < 0) {
            fprintf(stderr, "Error running lstat on %s\n", new_path);
        }

        if (!S_ISDIR(statbuffer.st_mode)){
            printf("%sFile: %s\n", fill, dirp->d_name);
        }
        else {
            if(!strcmp(".", dirp->d_name) || !strcmp("..", dirp->d_name)){
                continue;
            }
            else {
                printf("%sDirectory: %s\n", fill, dirp->d_name);
                sprintf(new_fill, "%s%s", fill, "     ");
                visit_directory(new_path, new_fill);
            }
        }
    }
    if(closedir(dp)<0){
        fprintf(stderr, "Error closing directory %s", dirp->d_name);
        exit(-1);
    }

    return;
}
