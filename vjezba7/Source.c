#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <string.h>

#define LINE 1024

struct _element;
typedef struct _element* position;

typedef struct _element
{
	char ime[LINE];
	position sibling;
	position child;
}element;

struct _element_stoga;
typedef struct _element_stoga* position_stog;

typedef struct _element_stoga
{
	position podatak_stablo;
	position_stog next;
}element_stoga;

//stog
int push(position_stog head, position_stog stvoreni, position ulazni);
position pop(position_stog head);
position_stog stvori_novog_stog();
int printaj(position_stog head);
position_stog trazi_element(position_stog head);

//stablo
position stvori_novog();
position insert(position current, position ne);

//ispisi odabira
int meni();
int odabir();

int main()
{
	char naredba[LINE] = { 0 };
	element majka = { "C:",NULL,NULL };
	position ne = NULL;
	position parent = &majka;
	position_stog roditelj = NULL;
	position_stog temp = NULL;
	element_stoga head = { NULL,NULL };
	//majka = (position)malloc(sizeof(element));

	meni();
	odabir();
	scanf(" %s", naredba);

	do
	{
		if (strcmp(naredba, "meni") == 0)
		{
			meni();
			odabir();
			scanf(" %s", naredba);
		}
		else if (strcmp(naredba, "md") == 0)
		{
			//temp = insert(parent->child, stvori_novog());
			parent->child = insert(parent->child, stvori_novog());
			//push(&head, stvori_novog_stog(),temp);
			odabir();
			scanf(" %s", naredba);
		}
		else if (strcmp(naredba, "cd..") == 0)
		{
			position result = pop(&head);
			if (result != NULL)
			{
				parent = result;
			}
			odabir();
			scanf(" %s", naredba);
		}
		else if (strcmp(naredba, "cd_dir") == 0)
		{
			temp = trazi_element(&head);
			if (temp == EXIT_SUCCESS)
			{
				printf("\nNazalost taj direktorij ne postoji ili je naziv krivo unesen\n");
			}
			else
			{
				roditelj = trazi_element(&head);
			}
			odabir();
			scanf(" %s", naredba);
		}
		else if (strcmp(naredba, "dir") == 0)
		{
			printaj(&head);
			odabir();
			scanf(" %s", naredba);
		}
		/*
		switch (*naredba)
		{
		case 'meni':
		{
			meni();
			break;
		}
		case 'md':
		{
			ne = stvori_novog();
			parent->child = insert(parent->child,ne);
			break;
		}
		case 'cd dir':
		{

			break;
		}
		case 'cd..':
		{

			break;
		}
		case 'dir':
		{

			break;
		}
			default:
				break;
		}*/
	} while (strcmp(naredba, "izlaz") != 0);
	return 0;
}

int meni()
{
	printf("\nZa sada su realizirane naredbe\n\n");
	printf("meni\n");
	printf("md\n");
	printf("cd dir\n");
	printf("cd..\n");
	printf("dir\n");
	printf("izlaz\n");
	return EXIT_SUCCESS;
}

position stvori_novog()
{
	position novi;
	novi = (position)malloc(sizeof(element));
	char naziv[LINE] = { 0 };
	printf("\nUnesite ime structure: ");
	scanf(" %s", naziv);
	strcpy(novi->ime, naziv);
	novi->child = NULL;
	novi->sibling = NULL;
	return novi;
}

position insert(position current, position ne)
{
	if (!current)
	{
		return ne;
	}
	if (strcmp(current->ime, ne->ime) > 0)
	{
		current->sibling = insert(current->sibling, ne);
	}
	else if (strcmp(current->ime, ne->ime) < 0)
	{
		ne->sibling = current;
		return ne;
	}
	return current;
}

position_stog stvori_novog_stog()
{
	position_stog novi = NULL;
	novi = (position_stog)malloc(sizeof(element_stoga));
	novi->podatak_stablo = NULL;
	novi->next = NULL;
	return novi;
}

int push(position_stog head, position_stog stvoreni, position ulazni)
{
	stvoreni->next = head->next;
	stvoreni->podatak_stablo = ulazni;
	head->next = stvoreni;				//zasto ako su jedan i drugi deklarirani kao element_stoga*

	return EXIT_SUCCESS;
}

position pop(position_stog head)
{
	position_stog temp = NULL;
	position result = NULL;

	temp = head->next;

	if (temp != NULL)
	{
		head->next = temp->next;
		result = temp->podatak_stablo;
		free(temp);
	}
	return result;
}

int printaj(position_stog head)
{
	position_stog temp = NULL;
	//element_stoga* temp2 = NULL;
	temp = head->next;
	//temp2 = head->next;

	if (!temp)
	{
		perror("\nNema elemenata!!\n");
	}

	while (temp != NULL)
	{
		printf("/%s", temp->podatak_stablo->ime);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

position_stog trazi_element(position_stog head)
{
	position_stog temp = NULL;
	char ime[LINE] = { 0 };
	printf("\nU koji direktorij idemo: ");
	scanf(" %s", ime);
	temp = head->next;

	if (!temp)
		return EXIT_SUCCESS;

	while (temp != NULL)
	{
		if (strcmp(temp->podatak_stablo->ime, ime))
			return temp;
	}
	return EXIT_SUCCESS;
}

int odabir()
{
	puts("\nVas odabir je:");
}