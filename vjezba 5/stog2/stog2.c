#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
funkcija za unos clanova
funkcija za citanje cijelog filea u rb da pricta sve
pop vadi mi prvog
push dodaj mi prvog
dodaj na pocetak
brisi sa pocetka
*/

typedef struct _element
{
	double clan;
	struct _element* next;
} element;

int ProvjeraDatoteke(char* filename, element* head);
element* NoviElement(double broj);
int DodajNaPocetak(element* head, element* stvoreni);
int BrisiSaPocetka(element* head);
int PrintList(element* head);

int main()
{
	char* ime = "jednadzba.txt";
	element head = { .clan = 0,.next = NULL };

	ProvjeraDatoteke(ime, &head);
	PrintList(&head);

	return 0;
}



int ProvjeraDatoteke(char* filename, element* head)
{
	FILE* datoteka = NULL;
	element* jedan = NULL;
	element* dva = NULL;
	element* temp1 = NULL;
	element* temp2 = NULL;

	char buffer[1024] = { 0 };
	char* p = NULL;
	char znak;
	double broj = 0;
	int n = 0;
	int i = 0;
	int count = 0;

	temp2 = (element*)malloc(sizeof(element));

	p = buffer;
	datoteka = fopen(filename, "rb");

	if (!datoteka)
	{
		perror("Ne mogu otvorit datoteku");
		return EXIT_FAILURE;
	}

	while (!feof(datoteka))
	{
		fgets(buffer, 1024, datoteka);
		p = buffer;
		while (strlen(p))
		{

			if (sscanf(p, " %lf %n", &broj, &n) == 1)
			{
				temp1 = NoviElement(broj);
				DodajNaPocetak(head, temp1);
				count++;
			}
			else if (sscanf(p, " %c %n", &znak, &n) == 1)
			{
				PrintList(head);
				switch (znak)
				{
				case ('+'):

					jedan = head->next;
					dva = jedan->next;

					broj = jedan->clan + dva->clan;
					BrisiSaPocetka(head);
					BrisiSaPocetka(head);
					temp1 = NoviElement(broj);
					DodajNaPocetak(head, temp1);

					break;

				case ('-'):

					jedan = head->next;
					dva = head->next->next;

					broj = jedan->clan - dva->clan;
					BrisiSaPocetka(head);
					BrisiSaPocetka(head);
					temp1 = NoviElement(broj);
					DodajNaPocetak(head, temp1);

					break;

				case ('*'):

					jedan = head->next;
					dva = head->next->next;

					broj = jedan->clan * dva->clan;
					BrisiSaPocetka(head);
					BrisiSaPocetka(head);
					temp1 = NoviElement(broj);
					DodajNaPocetak(head, temp1);

					break;

				case ('/'):

					jedan = head->next;
					dva = head->next->next;
					if (dva->clan == 0)
					{
						printf("Sa nulom se ne dijeli pogresan unos");
						return EXIT_SUCCESS;
					}
					broj = jedan->clan / dva->clan;
					BrisiSaPocetka(head);
					BrisiSaPocetka(head);
					temp1 = NoviElement(broj);
					DodajNaPocetak(head, temp1);

					break;

				default:
					printf("Sto god ste napravili bravo\n");
					break;
				}
				printf("\n");
		
			}

			p += n;
		}
	}

	fclose(datoteka);

	return EXIT_SUCCESS;
}

element* NoviElement(double broj)
{
	element* p;
	p = (element*)malloc(sizeof(element));
	if (!p)
	{
		perror("Neuspješna alokacija memorije za element.\n");
		return NULL;
	}

	p->clan = broj;
	p->next = NULL;
	return p;
}

int DodajNaPocetak(element* head, element* stvoreni)
{
	stvoreni->next = head->next;
	head->next = stvoreni;

	return EXIT_SUCCESS;
}

int BrisiSaPocetka(element* head)
{
	element* temp = head->next;

	if (!temp)
		return EXIT_SUCCESS;

	head->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}

int PrintList(element* head)
{
	element* temp = NULL;
	temp = head->next;

	if (!temp)
	{
		perror("Nema elemenata");
		return EXIT_FAILURE;
	}

	while (temp != NULL)
	{
		printf(" %lf", temp->clan);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}