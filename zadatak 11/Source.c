#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

#define LINE 1024
#define COUNT 10
#define VELICINA_TABLICE 11

struct _drzava;
typedef struct _drzava* position_list;

struct _grad;
typedef struct _grad* position_stablo;

typedef struct _drzava
{
	char ime[LINE];
	position_list next;
	position_stablo grad;
	int hash;								//dodano
}drzava;

typedef struct _grad
{
	char ime[LINE];
	double broj_stanovnika;
	position_stablo left;
	position_stablo right;
}grad;


bool provjera_datoteke(char* filename);

//sve za liste
bool read_make_list(position_list head, char* filename);
position_list new_in_list(char* temp_ime);
bool insert_list(position_list head, position_list new_element);
bool ispis_liste(position_list haed);

//sve za stabla
position_stablo open_file(char* filename);
position_stablo new_in_tree(char* temp_ime, int stanovnistvo);
position_stablo insert_in_tree(position_stablo current, position_stablo novi);
bool inorder(position_stablo hodajuci);
bool print2D(position_stablo current, int space);

//hash
int hash(char* ime);
bool turn_to_hash_arr(drzava* arr, position_list new_element);
position_list pop(position_list head);
bool ispisi_hash(position_list arr[]);
bool print_hash(position_list arr[]);
position_list dodaj_u_hash(position_list head, position_list new_element);


int main()
{
	position_list temp_pop = NULL;

	position_list temp_setajuci = NULL;

	position_list hash_arr[VELICINA_TABLICE] = { NULL };							//niz hash tablice sa 10 elemenata

	char* file_countries = "drzave.txt";

	drzava head = { "0",NULL,NULL };				//pokazivaci na 2 strukture

	if (provjera_datoteke(file_countries))
	{
		read_make_list(&head, file_countries);
	}

	ispis_liste(&head);

	/*
	* odi do zadnjega
	* skini ga
	* ili pametnije skini mi prvog samo da ne moras ic do zadnjeg
	* metni ga u jednu od mista hash tablice
	* ako ih ima vise samo ih lipo poredaj prema broju stanovnika
	* easy peasy (ni blizu)
	*/


	temp_setajuci = head.next;

	while (head.next != NULL)
	{
		temp_pop = pop(&head);

		//insert_list(hash_arr[temp_pop->hash], temp_pop);

		if (hash_arr[temp_pop->hash]==NULL)					//ako nema nista samo ga metni
		{
			hash_arr[temp_pop->hash] = temp_pop;			//posalji mi niz za hash i adresu head od niza
		}
		else
		{
			hash_arr[temp_pop->hash] = dodaj_u_hash(hash_arr[temp_pop->hash],temp_pop);
			//insert_list(hash_arr[temp_pop->hash],temp_pop);			//posalji mi niz za hash i adresu head od niza
		}
	}

	ispisi_hash(&hash_arr);

	return 0;
}

position_list dodaj_u_hash(position_list head, position_list new_element)
{
	position_list head_temp = head;
	position_list head_next_temp = head->next;
	position_list new_element_temp = new_element;
	position_list zamjena = NULL;

	if (strcmp(new_element_temp->ime, head_temp->ime) < 0)		//ako je prije prvoga
	{
		new_element_temp->next = head_temp;
		return new_element_temp;
	}

	while ((head_next_temp!=NULL)&&(strcmp(new_element_temp->ime, head_temp->ime) < 0))
	{
		head_temp = head_temp->next;
		head_next_temp = head_next_temp->next;
	}

	new_element->next = head_temp->next;
	head_temp->next = new_element;

	return head;
}

bool ispisi_hash(position_list arr[])
{
	puts("**********************************************************************************************************");
	puts("********************************************Ispis Hash****************************************************");
	for (int i = 0; i < VELICINA_TABLICE; i++)
	{
		printf("\nNa mjestu %d\n", i);
		if (arr[i] == NULL)
		{
			printf("Nema nista\n\n");
		}
		else
		{
			printf("Cak ima nesto\n\n");
			print_hash(arr[i]);
		}
	}
	return true;
}

bool print_hash(position_list arr_element)
{
	position_list temp = arr_element;

	while (temp!= NULL)
	{
		printf("%s\n", temp->ime);
		print2D(temp->grad, 0);
		temp = temp->next;
	}

	return true;
}


position_list pop(position_list head)
{
	position_list temp = NULL;
	temp = head->next;

	if (temp == NULL)				//ako nema nista nemoj nista ni vracat		
	{
		return EXIT_SUCCESS;
	}

	head->next = temp->next;	//povezi prvi i treci
	temp->next = NULL;

	return temp;
}

bool turn_to_hash_arr(drzava* arr[], position_list new_element)			//2 pokazivaca jer jednom da pretvoris u position drugi put da prebacis arr
{
	if (arr[new_element->hash] == NULL)			//ako nema nista na tome mistu odlicno samo sibi
	{
		arr[new_element->hash] = new_element;
	}
	else  //nesto vec ima na tom mistu 
	{
		insert_list(arr[new_element->hash], new_element);
	}
	return true;
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

bool read_make_list(position_list head, char* filename)		//procitaj ime ako postoji stvori mi novi clan
{
	FILE* datoteka = NULL;
	char buffer[LINE] = { 0 };			//ovo gledas kao liniju obicnu od chara max velicine
	char* privremeni_buffer = NULL;			//ovo gledas kao pokazivac na tu liniju zato je gore u zagradama a vamo samo null jer pokazivac moze bit null
	int n = 0;
	char temp_ime[LINE] = { 0 };
	char gradic[LINE] = { 0 };

	datoteka = fopen(filename, "r");

	if (!datoteka)
	{
		perror("\nDatoteka nije otvorena\n");
		return false;
	}

	while (!feof(datoteka))
	{
		fgets(buffer, LINE, datoteka);
		privremeni_buffer = buffer;
		while (strlen(privremeni_buffer))						//ako ima ista u retku idemooooooo
		{
			if (sscanf(privremeni_buffer, " %s %n", temp_ime, &n) == 1)
			{
				insert_list(head, new_in_list(temp_ime));
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

position_list new_in_list(char* temp_ime)
{
	position_list new_element = NULL;

	new_element = (position_list)malloc(sizeof(drzava));

	strcpy(new_element->ime, temp_ime);

	new_element->hash = hash(new_element->ime);

	new_element->grad = NULL;
	new_element->next = NULL;

	return new_element;
}

int hash(char* ime)
{
	int HashV = 0;

	for (int i = 0; i < 5; i++)
	{
		HashV += *ime++;
	}

	return HashV % VELICINA_TABLICE;
}

bool insert_list(position_list head, position_list new_element)
{
	position_list temp = NULL;
	int rezultat = 0;

	temp = head;

	//za hash prob mi treba neki key 
	//kad nades element koji ima isti key dodaj ga na to misto

	while ((temp->next != NULL) && (strcmp(temp->next->ime, new_element->ime) < 0))				//idi dok nisi dosao do kraja ili dok nisi nasao manji
	{
		temp = temp->next;
	}

	new_element->next = temp->next;
	temp->next = new_element;
	new_element->grad = open_file(new_element->ime);

	return true;
}

bool ispis_liste(position_list head)
{
	position_list temp = NULL;
	position_stablo hodajuci = NULL;
	temp = head->next;

	puts("");

	while (temp)
	{
		printf("%s ima hash: %d", temp->ime, temp->hash);
		hodajuci = temp->grad;
		print2D(hodajuci, 0);
		puts("");
		temp = temp->next;
	}

	return true;
}

position_stablo open_file(char* filename)
{
	FILE* datoteka = NULL;
	position_list temp = NULL;
	position_stablo privremeni = NULL;
	char ime_tempa[LINE] = { 0 };
	char ime_datoteke[LINE] = { 0 };
	char buffer[LINE] = { 0 };
	char* privremeni_buffer = NULL;
	char temp_ime[LINE] = { 0 };
	int broj_stanovnika = 0;
	int n = 0;


	//temp = head->next;
	strcpy(ime_datoteke, filename);
	strcat(ime_datoteke, ".txt");


	datoteka = fopen(ime_datoteke, "r");

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
			if (sscanf(privremeni_buffer, " %s %d %n", temp_ime, &broj_stanovnika, &n) == 2)
			{
				privremeni = insert_in_tree(privremeni, new_in_tree(temp_ime, broj_stanovnika));
			}
			privremeni_buffer += n;
		}
		//temp->grad = privremeni;
	}

	fclose(datoteka);

	return privremeni;
}

position_stablo new_in_tree(char* temp_ime, int stanovnistvo)
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
		current->right = insert_in_tree(current->right, novi);
	else if ((current->broj_stanovnika) < (novi->broj_stanovnika))
		current->left = insert_in_tree(current->left, novi);

	return current;
}

bool inorder(position_stablo hodajuci)
{
	if (hodajuci != NULL)
	{
		inorder(hodajuci->left);
		printf("%s %0.lf ", hodajuci->ime, hodajuci->broj_stanovnika);					//zasto samo odjednom MORA lf umisto d
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
	printf(" %s->%0.lf\n", current->ime, current->broj_stanovnika);

	print2D(current->right, space);

	return current;
}