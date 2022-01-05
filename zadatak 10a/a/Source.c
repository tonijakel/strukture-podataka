#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

#define LINE 1024
#define COUNT 10

struct _drzava;
typedef struct _drzava* position_list;

struct _grad;
typedef struct _grad* position_stablo;

typedef struct _drzava
{
	char ime[LINE];
	position_list next;
	position_stablo grad;
}drzava;

typedef struct _grad
{
	char ime[LINE];
	double broj_stanovnika;
	position_stablo left;
	position_stablo right;
}grad;


bool provjera_datoteke(char *filename);

//sve za liste
bool read_make_list(position_list head,char *filename);
position_list new_in_list(char* temp_ime);
bool insert_list(position_list head, position_list new_element);
bool ispis_liste(position_list haed);

//sve za stabla
position_stablo new_in_tree(char* temp_ime);
position_stablo open_file(char* filename);
position_stablo new_in_tree(char* temp_ime, int stanovnistvo);
position_stablo insert_in_tree(position_stablo current, position_stablo novi);
bool inorder(position_stablo hodajuci);
bool print2D(position_stablo current, int space);


int main()
{
	char* file_countries = "drzave.txt";

	drzava head = {"0",NULL,NULL};				//pokazivaci na 2 strukture

	if (provjera_datoteke(file_countries))
	{
		read_make_list(&head,file_countries);
	}

		ispis_liste(&head);

	return 0;
}


bool provjera_datoteke(char* filename)
{
	FILE* datoteka = NULL;
	datoteka = fopen(filename, "r");

	if (!datoteka)
	{
		perror("\nNemogu otvorit datoteku!\n");
		return false;
	}

	puts("\nDatoteka uspjesno otvorena :)\n");

	fclose(datoteka);

	return true;
}

bool read_make_list(position_list head,char* filename)		//procitaj ime ako postoji stvori mi novi clan
{
	FILE* datoteka = NULL;
	char buffer[LINE] = {0};			//ovo gledas kao liniju obicnu od chara max velicine
	char* privremeni_buffer = NULL;			//ovo gledas kao pokazivac na tu liniju zato je gore u zagradama a vamo samo null jer pokazivac moze bit null
	int n=0;
	char temp_ime[LINE] = {0};
	char gradic[LINE] = { 0 };

	datoteka = fopen(filename,"r");
	
	if (!datoteka)
	{
		perror("\nDatoteka nije otvorena\n");
		return false;
	}

	while (!feof(datoteka))
	{
		fgets(buffer, LINE, datoteka);
		privremeni_buffer = buffer;
		while (strlen(privremeni_buffer))	//ako ima ista u retku idemooooooo
		{
			if (sscanf(privremeni_buffer," %s %n",temp_ime,&n)==1)
			{				
				insert_list(head,new_in_list(temp_ime));
				//open_file(temp_ime);
			}
			privremeni_buffer += n;
		}
	}	

	fclose(datoteka);

	//vrlo vjerojatno moze lakse i pametnije ali da

	/*
	datoteka = fopen(filename, "r");

	while (!feof(datoteka))
	{
		fgets(buffer, LINE, datoteka);
		privremeni_buffer = buffer;
		while (strlen(privremeni_buffer))	//ako ima ista u retku idemooooooo
		{
			if (sscanf(privremeni_buffer, " %s %n", temp_ime, &n) == 1)
			{
				//otvori datoteku pod tim imenom 
				//nadi tog istog imena 
				//na njegov grad povezi prvi grad sta pise
				//napravi binarno stablo
				//easy peasy lemon squezy
				open_file(head);
			}
			privremeni_buffer += n;
		}
	}
	
	fclose(datoteka);*/

	return true;
}

position_list new_in_list( char *temp_ime)
{
	position_list new_element=NULL;

	new_element = (position_list)malloc(sizeof(drzava));

	strcpy(new_element->ime,temp_ime);
	new_element->grad = NULL;
	new_element->next = NULL;

	return new_element;
}

bool insert_list(position_list head, position_list new_element)
{
	position_list temp=NULL;
	int rezultat = 0;

	temp = head;

	while((temp->next != NULL) && (strcmp(temp->next->ime, new_element->ime) < 0))				//idi dok nisi dosao do kraja ili dok nisi nasao manji
	{
		temp = temp->next;
	}

	new_element->next = temp->next;
	temp->next = new_element;
	new_element->grad=open_file(new_element->ime);

	return true;
}

bool ispis_liste(position_list head)
{
	position_list temp=NULL;
	position_stablo hodajuci=NULL;
	temp = head->next;

	puts("");

	while (temp)
	{
		printf("%s\n",temp->ime);
		hodajuci = temp->grad;
		print2D(hodajuci,0);
		puts("");
		temp = temp->next;
	}

	return true;
}

position_stablo open_file(char *filename)
{
	FILE* datoteka = NULL;
	position_list temp=NULL;
	position_stablo privremeni = NULL;
	char ime_tempa[LINE] = { 0 };
	char ime_datoteke[LINE] = { 0 };
	char buffer[LINE] = { 0 };
	char* privremeni_buffer = NULL;
	char temp_ime[LINE] = { 0 };
	int broj_stanovnika = 0;
	int n = 0;

	
	//temp = head->next;
	strcpy(ime_datoteke,filename);
	strcat(ime_datoteke,".txt");
	

	datoteka = fopen(ime_datoteke,"r");
	
	if (!datoteka)
	{
		perror("datoteka se nije otvorila");
		return false;
	}

	//otvoria si datoteku dobru 
	//procitaj sve iz nje
	while (!feof(datoteka))
	{
		fgets(buffer, LINE, datoteka);
		privremeni_buffer = buffer;
		while (strlen(privremeni_buffer))	//ako ima ista u retku idemooooooo
		{
			if (sscanf(privremeni_buffer, " %s %d %n", temp_ime,&broj_stanovnika, &n) == 2)
			{
				privremeni= insert_in_tree(privremeni, new_in_tree(temp_ime,broj_stanovnika));
			}
			privremeni_buffer += n;
		}
		//temp->grad = privremeni;
	}

	fclose(datoteka);

	return privremeni;
}

position_stablo new_in_tree(char* temp_ime,int stanovnistvo)
{
	position_stablo new_element = NULL;
	new_element = (position_stablo)malloc(sizeof(grad));
	new_element->broj_stanovnika = stanovnistvo;
	strcpy(new_element->ime, temp_ime);
	new_element->left = NULL;
	new_element->right = NULL;
	return new_element;
}

position_stablo insert_in_tree(position_stablo current, position_stablo novi)
{
	if (current == NULL)
		return novi;
	if ((current->broj_stanovnika) > (novi->broj_stanovnika))
		current->right = insert_in_tree(current->right,novi);
	else if ((current->broj_stanovnika) < (novi->broj_stanovnika))
		current->left = insert_in_tree(current->left, novi);

	return current;
}

bool inorder(position_stablo hodajuci)
{
	if (hodajuci!=NULL)
	{
		inorder(hodajuci->left);
		printf("%s %0.lf ",hodajuci->ime,hodajuci->broj_stanovnika);					//zasto samo odjednom MORA lf umisto d
		inorder(hodajuci->right);
	}
	return true;
}

bool print2D(position_stablo current, int space)
{
	if (current == NULL)
		return EXIT_SUCCESS;
	space += COUNT;

	print2D(current->left, space);

	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf(" %s-%0.lf\n", current->ime, current->broj_stanovnika);

	print2D(current->right, space);

	return current;
}