#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

void separatePathAndFileName(const char *pathFile, char *path, char *fileName) {
    const char *lastSlash = strrchr(pathFile, '/');
    
    if (lastSlash != NULL) {
        strncpy(path, pathFile, lastSlash - pathFile + 1);
        path[lastSlash - pathFile + 1] = '\0';
        strcpy(fileName, lastSlash + 1);
    } else {
        strcpy(path, "");
        strcpy(fileName, pathFile);
    }
}

char* showPath(){
    static char cwd[100];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        return cwd;
    } 
    else {
        perror("getcwd() error");
        return NULL;
    }
}
