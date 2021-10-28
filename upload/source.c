#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 64
#define MAX_LINE 1024

typedef struct _person{
    char fname[MAX_STRING], lname[MAX_STRING];
    int byear;
    struct _person* next;
}person;

person* createPerson(char* fname, char* lname, int byear);
person* findEnd(person* headptr);
void insertAfter(person* prev, person* to_insert);
void prependList(person* headptr, char* fname, char* lname, int byear);
void appendList(person* headptr, char* fname, char* lname, int byear);
void printList(person* headptr);
void printNode(person* node);
person* findByLname(person* headptr, char* lname);
void deleteElement(person* headptr);
person* findBefore(person* headptr, char* lname);

//menu functions
int menu();
void printByLname(person* headptr);
void dataInput(person* headptr, void (*insert_function)(person* headptr, char* fname, char* lname, int byear));


int main(){
    person head = {.fname = "", .lname = "", .next = NULL };
    int choice;
    char to_delete[MAX_STRING];
    while(1){
        choice = menu();
        
        switch(choice){
            case 0:
                return 0;
            case 1:
                dataInput(&head, prependList);
                break;
            case 2:
                dataInput(&head, appendList);
                break;
            case 3:
                printByLname(&head);
                break;
            case 4:
                deleteElement(&head);
                break;
            case 5:
                printList(&head);
                break;
        }
    }
    return 0;
}

void prependList(person* headptr, char* fname, char* lname, int byear){
    person* to_insert = NULL;
    to_insert = createPerson(fname, lname, byear);
    if(!to_insert){
        printf("Failed to prepend list. Try again.\n");
        return;
    }
    insertAfter(headptr, to_insert);
}

void appendList(person* headptr, char* fname, char* lname, int byear){
    person* temp = headptr;
    person* to_insert = NULL;
    to_insert = createPerson(fname, lname, byear);
    if(!to_insert){
        printf("Failed to appepend list. Try again.\n");
        return;
    }
    temp = findEnd(temp);
    insertAfter(temp, to_insert);
}

void insertAfter(person* prev, person* to_insert){
    to_insert->next = prev->next;
    prev->next = to_insert;
}

person* createPerson(char* fname, char* lname, int byear){
    person* temp = NULL;

    temp = (person*)malloc(sizeof(person));
    if(!temp){
        perror("Failed to allocate memory for person in function createPerson\n");
        free(temp);
        return NULL;
    }

    strcpy(temp->fname, fname);
    strcpy(temp->lname, lname);
    temp->byear = byear;
    temp->next = NULL;

    return temp;
}

person* findEnd(person* headptr){
    person* temp = headptr;

    while(temp->next){
        temp = temp->next;
    }

    return temp;
}

void printList(person* headptr){
    if(headptr->next == NULL){
        printf("Lista je prazna.\n");
    }
    for(person* node = headptr->next; node; node = node->next){
        printNode(node);
    }
}

void printNode(person* node){
    printf("%s %s %d\n", node->fname, node->lname, node->byear);
}

person* findByLname(person* headptr, char* lname){
    for(person* node = headptr->next; node; node = node->next){
        if(!strcmp(node->lname, lname)){
            return node;
        }
    }
    return NULL;
}

void deleteElement(person* headptr){
    char lname[MAX_STRING] = {0};
    printf("Unesite prezime osobe koju zelite obrisati:\n");
    scanf(" %s", lname);
    person* before = findBefore(headptr, lname);
    if(before == NULL){
        printf("Osoba se ne nalazi na listi.\n");
        return;
    }
    person* temp = before->next;
    before->next = temp->next;
    free(temp);
}

person* findBefore(person* headptr, char* lname){
    if(headptr->next == NULL) return NULL;
    for(person* node = headptr; node->next; node = node->next){
        if(strcmp(node->next->lname, lname) == 0){
            return node;
        }
    }
    return NULL;
}

int menu(){
    int choice = 0;
    
    while(1){
        printf(
        "Izbornik:\n"
        "0 - izlaz\n"
        "1 - unos na pocetak liste\n"
        "2 - unos na kraj liste\n"
        "3 - pronadi po prezimenu\n"
        "4 - brisanje iz liste\n"
        "5 - ispis liste\n"
        );

        scanf(" %d", &choice);
        puts("");
        if(choice>=0 && choice<=5) return choice;
        
        printf("Pogresan unos. Pokusajte ponovno\n");
    }
}

void printByLname(person* headptr){
    char lname[MAX_STRING];
    person* temp = NULL;
    printf("Unesite prezime osobe koju trazite:\n");
    scanf(" %s", lname);

    temp = findByLname(headptr, lname);
    if(temp == NULL){
        printf("Osoba se ne nalazi na listi.\n");
    }
    else{
        printNode(temp);
    }
}

void dataInput(person* headptr, void (*insert_function)(person* headptr, char* fname, char* lname, int byear)){
    char fname[MAX_STRING], lname[MAX_STRING];
    int byear;
    printf("Unesite ime i prezime osobe:\n");
    scanf(" %s %s", fname, lname);
    printf("Godina rodenja: ");
    scanf(" %d", &byear);
    insert_function(headptr, fname, lname, byear);
}