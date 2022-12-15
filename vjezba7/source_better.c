#include <stdio.h>
#include <stdlib.h>

#define LINE_MAX 1024

struct _directory;

typedef struct _directory{
    char name[256];
    struct _directory* subdirectories;
}Directory;

int main(){
    Directory root = {"root", NULL};
    return 0;
}