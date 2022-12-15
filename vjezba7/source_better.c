#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 1024
#define NAME_MAX 256

struct _directory;

typedef struct _directory{
    char name[NAME_MAX];
    struct _directory** subdirectories;
    int subdir_count;
    int subdir_size;
}Directory;

int create_new_dir(Directory* parent, char name[NAME_MAX]);
int delete_dir(Directory* parent, char to_delete[NAME_MAX]);

int main(){
    Directory root = {"root", NULL, 0, 0};

    return 0;
}

int create_new_dir(Directory* parent, char name[NAME_MAX]){

    // check if directory with same name exists
    for(int i = 0; i < parent->subdir_count; i++){
        if(strcmp(name, parent->subdirectories[i]->name) == 0){
            printf("Failed to create directory: name already in use\n");
            return -3;
        }
    }

    if(parent->subdir_size == parent->subdir_count){ // if parent->subdirectories is full allocate more memory
        parent->subdirectories = realloc(parent->subdirectories, sizeof(Directory*) * (parent->subdir_size + 1));
        if(parent->subdirectories == NULL){ // if failed, error
            perror("create_new_dir allocation of new array");
            return -1;
        }
        else{ // if successful, add 1 to size
            parent->subdir_size += 1;
        }
    }
    

    Directory* newdir = malloc(sizeof(Directory));
    if(newdir == NULL){
        perror("create_new_dir allocation of newdir");
        return -2;
    }

    // assign and initialise starting values for newdir
    strcpy(newdir->name, name);
    newdir->subdir_count = 0;
    newdir->subdir_size = 0;
    newdir->subdirectories = NULL;

    (parent->subdirectories)[parent->subdir_count] = newdir; // place newdir to end of parent->subdirectories
    parent->subdir_count += 1;

    return 0;
}


int delete_dir(Directory* parent, char to_delete[NAME_MAX]){
    int to_delete_index = -1;

    for(int i = 0; i < parent->subdir_count; i++){

    }
}