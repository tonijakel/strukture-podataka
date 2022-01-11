#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

#define LINE 1024
#define COUNT 10

struct _drzava;
typedef struct _drzava* position_stablo;

struct _grad;
typedef struct _grad* position_list;

typedef struct _drzava
{
	char ime[LINE];
	position_stablo left;
	position_stablo right;
	position_list grad;
}drzava;

typedef struct _grad
{
	char ime[LINE];
	double broj_stanovnika;
	position_list next;
}grad;


bool provjera_datoteke(char* filename);


position_stablo read_make_stablo(char* filename);
position_list new_in_list(char* temp_ime, int stanovnici);
position_list insert_list(position_list head, position_list new_element);
bool ispis_liste(position_list haed);


position_stablo new_in_tree(char* temp_ime);
position_list open_file(char* filename);
position_stablo new_in_tree(char* temp_ime);
position_stablo insert_in_tree(position_stablo current, position_stablo novi);
bool inorder(position_stablo hodajuci);
bool print2D(position_stablo current, int space);
position_stablo root_grad(position_stablo root);


int main()
{
	char* file_countries = "drzave.txt";

	position_stablo root = NULL;

	if (provjera_datoteke(file_countries))
	{
		root = read_make_stablo(file_countries);

		if (root == NULL)
		{
			return 0;
		}
		else  //postoji mi nesto 
			  //odi do svakog clana i stvori mu listu
		{
			root_grad(root);
		}
		print2D(root, 0);
	}

	puts("ad");
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

position_stablo read_make_stablo(char* filename)		//procitaj ime ako postoji stvori mi novi clan
{
	FILE* datoteka = NULL;
	char buffer[LINE] = { 0 };			//ovo gledas kao liniju obicnu od chara max velicine
	char* privremeni_buffer = NULL;			//ovo gledas kao pokazivac na tu liniju zato je gore u zagradama a vamo samo null jer pokazivac moze bit null
	int n = 0;
	char temp_ime[LINE] = { 0 };
	char gradic[LINE] = { 0 };
	position_stablo root = NULL;
	position_list pomocna_lista = NULL;
	int broj_drzava = 0;

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
		while (strlen(privremeni_buffer))	//ako ima ista u retku idemooooooo
		{
			if (sscanf(privremeni_buffer, " %s %n", temp_ime, &n) == 1)
			{
				if (!broj_drzava)
				{
					root = insert_in_tree(root, new_in_tree(temp_ime));
					//prvo otvorit datoteku pa onda stvaraj nove


				/*	root->grad = open_file(root->ime); */											//OVDI SU SVI TVOJI PROBLEMI RIJESI OVO I RIJESIO SI SV E
					broj_drzava++;
				}
				else
				{
					root = insert_in_tree(root, new_in_tree(temp_ime));
				}
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

	return root;
}


position_list new_in_list(char* temp_ime, int stanovnici)
{
	position_list new_element = NULL;

	new_element = (position_list)malloc(sizeof(drzava));

	strcpy(new_element->ime, temp_ime);
	new_element->broj_stanovnika = stanovnici;
	new_element->next = NULL;

	return new_element;
}

position_list insert_list(position_list head, position_list new_element)
{
	position_list temp = NULL;
	int rezultat = 0;

	temp = head;						//head je null uvik 

	if (!temp)
	{
		temp = new_element;
		return temp;
	}

	while ((temp->next != NULL) && (temp->next->broj_stanovnika > new_element->broj_stanovnika))				//idi dok nisi dosao do kraja ili dok nisi nasao manji
	{
		temp = temp->next;
	}

	new_element->next = temp->next;
	temp->next = new_element;
	//new_element->next = open_file(new_element->ime);

	return new_element;
}

/*bool ispis_liste(position_list head)
{
	position_list temp = NULL;
	position_stablo hodajuci = NULL;
	temp = head->next;
	puts("");
	while (temp)
	{
		printf("%s\n", temp->ime);
		hodajuci = temp->grad;
		print2D(hodajuci, 0);
		puts("");
		temp = temp->next;
	}
	return true;
}*/

position_list open_file(char* filename)
{
	FILE* datoteka = NULL;
	position_list temp = NULL;
	position_stablo privremeni = NULL;
	char ime_tempa[LINE] = { 0 };
	char ime_datoteke[LINE] = { 0 };
	char buffer[LINE] = { 0 };
	int n = 0;
	char* privremeni_buffer = NULL;
	char temp_ime[LINE] = { 0 };
	int broj_stanovnika = 0;



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
				temp = insert_list(temp, new_in_list(temp_ime, broj_stanovnika));
			}
			privremeni_buffer += n;
		}
		//temp->grad = privremeni;
	}

	fclose(datoteka);

	return temp;
}



position_stablo new_in_tree(char* temp_ime)
{
	position_stablo new_element = NULL;
	new_element = (position_stablo)malloc(sizeof(grad));
	strcpy(new_element->ime, temp_ime);
	new_element->left = NULL;
	new_element->right = NULL;
	new_element->grad = NULL;
	return new_element;
}

position_stablo insert_in_tree(position_stablo current, position_stablo novi)
{
	if (current == NULL)
		return novi;
	if (strcmp(current->ime, novi->ime) > 0)
		current->right = insert_in_tree(current->right, novi);
	else if (strcmp(current->ime, novi->ime) < 0)
		current->left = insert_in_tree(current->left, novi);
	else
		free(novi);
	return current;
}

/*
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
*/
bool print2D(position_stablo current, int space)
{
	if (current == NULL)
		return EXIT_SUCCESS;
	space += COUNT;

	print2D(current->left, space);

	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf(" %s", current->ime);

	print2D(current->right, space);

	return current;
}

position_stablo root_grad(position_stablo root)
{

	//pogledaj prvi ako ga ima dodaj mu listu ako ne izadi 
	//odi livo 
	//odi desno
	//vratio root radi veze i guess?
	char temp_ime[LINE] = { 0 };
	FILE* datoteka = NULL;
	position_list temp = NULL;
	char buffer[LINE] = { 0 };
	int n = 0;
	char* privremeni_buffer = NULL;
	int broj_stanovnika = 0;

	if (root != NULL)
	{
		root_grad(root->left);

		strcpy(temp_ime, root->ime);			//dodaj mi neku varijablu stalnogimena koja ce mi otvorit datoteku te drzave
		strcat(temp_ime, ".txt");
		datoteka = fopen(temp_ime, "r");

		if (!datoteka)
		{
			perror("Datoteka nije uspjesno otvorena kod lista");
			return EXIT_FAILURE;
		}
		else  //datoteka otvorena
		{
			while (!feof(datoteka))
			{
				fgets(buffer, LINE, datoteka);
				privremeni_buffer = buffer;
				while (strlen(privremeni_buffer))	//ako ima ista u retku idemooooooo
				{
					if (sscanf(privremeni_buffer, " %s %d %n", temp_ime, &broj_stanovnika, &n) == 2)			//neman vise ideja
					{
						root->grad = insert_list(root->grad, new_in_list(temp_ime, broj_stanovnika));
					}
					privremeni_buffer += n;
				}
				//temp->grad = privremeni;
			}

			fclose(datoteka);
		}
		root_grad(root->right);
	}
}
