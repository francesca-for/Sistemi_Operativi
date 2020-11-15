#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#define MAXLENGHT 100
// Path direcctory di prova -> /Users/fornasierarmando/Desktop/DirectoryProvaSO

void show_directory(const char path[], char fill[]);


int main(int argc, const char * argv[]) {
    if (argc!=2) {
        fprintf(stderr, "Error: expected programExe directoryPath\n");
        exit(1);
    }
    show_directory(argv[1], "");
    return 0;
}


void show_directory(const char path[], char fill[]) {
    struct stat sb;
    struct dirent *dirp;
    DIR *dp;
    char new_path[MAXLENGHT];
    char new_fill[MAXLENGHT];

    if (S_ISDIR(sb.st_mode)) {
        if ((dp = opendir(path)) == NULL){
            fprintf(stderr, "Error opening directory %s\n", path);
            exit(-1);
        }

        while ((dirp = readdir(dp)) != NULL){
            if (stat(path, &sb) < 0) {
                fprintf(stderr, "Error\n");
            }
            if (S_ISREG(sb.st_mode)){
                printf("File: %s\n", dirp->d_name);
            }
            else if (S_ISDIR(sb.st_mode)) {
                if(!strcmp("/.", dirp->d_name) || !strcmp("/..", dirp->d_name)){
                    printf("Directory: %s\n", dirp->d_name);
                }
                else {
                    printf("Directory: %s\n", dirp->d_name);
                    sprintf(new_path, "%s%s", path, dirp->d_name);
                    sprintf(new_fill, "%s%s", fill, "   ");
                    show_directory(new_path, new_fill);
                }
            }
        }
        closedir(dp);
    }

    return;
}
