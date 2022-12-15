#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 1024
#define NAME_MAX 256
#define OVERHEAD_MAX 5

struct _directory;

typedef struct _directory{
    char name[NAME_MAX];
    struct _directory** subdirectories;
    int subdir_count;
    int subdir_size;
}Directory;

int create_new_dir(Directory* parent, char name[NAME_MAX]);
int find_and_delete_dir(Directory* parent, char to_delete[NAME_MAX]);

int main(){
    Directory root = {"root", NULL, 0, 0};
    root.subdirectories = malloc(sizeof(Directory*));
    if(root.subdirectories == NULL){
        perror("Brate kako ti je pa prvi malloc smh my head");
        return -1;
    }
    root.subdir_count = 1;
    root.subdir_size = 1;
    root.subdirectories[0] = &root; // every directory has its parent at index 0, root is its own parent

    return 0;
}

int create_new_dir(Directory* parent, char name[NAME_MAX]){

    //check if name is empty
    if(strcmp(name, "") == 0){
        printf("Directory name can not be empty.\n");
        return 0;
    }

    // check if directory with same name exists
    for(int i = 0; i < parent->subdir_count; i++){
        if(strcmp(name, parent->subdirectories[i]->name) == 0){
            printf("Failed to create directory: name already in use\n");
            return 0;
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
    newdir->subdir_count = 1;
    newdir->subdir_size = 1;
    newdir->subdirectories = malloc(sizeof(Directory*));
    newdir->subdirectories[0] = parent; // place parent of every dir at index 0, for purposes of cd ..

    (parent->subdirectories)[parent->subdir_count] = newdir; // place newdir to end of parent->subdirectories
    parent->subdir_count += 1;

    return 0;
}


int find_and_delete_dir(Directory* parent, char to_delete[NAME_MAX]){
    Directory* to_delete_ptr = NULL;
    int i, j;


    // find the to_delete directory index
    for(i = 1; i < parent->subdir_count; i++){ // start at index 1 because 0 is reserved for parent
        if(strcmp(to_delete, parent->subdirectories[i]->name) == 0){
            to_delete_ptr = parent->subdirectories[i];
            break;
        }
    }

    if(to_delete_ptr == NULL){
        printf("Directory does not exist.\n");
        return 0;
    }

    //if found delete dir and its contents
    delete_dir(to_delete_ptr);

    for(j = i + 1; j < parent->subdir_count; j++){ // shift all directories that were behind the deleted directory one place down
        parent->subdirectories[j - 1] = parent->subdirectories[j];
    }
    parent->subdir_count -= 1;

    // if parent->subdir_size is OVERHEAD_MAX larger that subdir_count, reallocate to save memory
    if(parent->subdir_size > parent->subdir_count + OVERHEAD_MAX){
        parent->subdirectories = realloc(parent->subdirectories, parent->subdir_count * sizeof(Directory*));
        if(parent->subdirectories == NULL){ // *IN THEORY* never fails
            perror("realloc in find_and_delete_dir");
            return -1;
        }
        parent->subdir_size = parent->subdir_count;
    }

    return 0;    
}

int delete_dir(Directory* to_delete_ptr){
    for(int i = 1; i < to_delete_ptr->subdir_count; i++){
        delete_dir(to_delete_ptr->subdirectories[i]);
    }

    free(to_delete_ptr);

    return 0;
}