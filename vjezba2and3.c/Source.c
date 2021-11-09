#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define LINE 1024

struct _polinom;
typedef struct _polinom* position;


typedef struct _polinom
{
	int broj;
	int eksponent;
	position next;
}polinom;

int provjera_datoteke(char* filename);

int citaj_iz_datoteke(polinom* head1, polinom* head2, char* filename);

position strvori_novog(int broj, int exponent);

int unesi_sortirano(polinom* head, position stvoreni);

int stvori_nakon(polinom* head, position prvi, position stvoreni);

int stvori_prije(polinom* head, position prvi, position stvoreni);

int zbroji_clanove(polinom* hea, position prvi, position stvoreni);

int mnozenje_polinoma(polinom* prvi_head, polinom* drugi_head, polinom* rezultatni_head);

int zbrajanje_polinoma(polinom* prvi_head, polinom* drugi_head, polinom* rezultatni_head);

int ispis(polinom* head);


int main()
{
	polinom head1 = { 0,0,NULL };
	polinom head2 = { 0,0,NULL };
	polinom rez_head = { 0,0,NULL };
	char* ime_datoteke = "polinom.txt";

	printf("U datoteci ima %d linija, pa ce mo imati isto toliko polinoma",provjera_datoteke(ime_datoteke));
	citaj_iz_datoteke(&head1, &head2, ime_datoteke);
	ispis(&head1);
	ispis(&head2);
	ispis(&rez_head);
	
	return 0;
}

int ispis(polinom* head)
{
	position temp = NULL;
	temp = (position)malloc(sizeof(polinom));
	temp = head->next;

	while (temp != NULL)
	{
		printf(" %d ^ %d",temp->broj,temp->eksponent);
	}

	return EXIT_SUCCESS;
}

int provjera_datoteke(char* filename)
{
	FILE* datoteka = NULL;
	char buffer[LINE] = { 0 };
	int count = 0;
	

	datoteka = fopen(filename, "r");

	if (!datoteka)
	{
		perror("\nError in file opening\n");
		return count;
	}

	while (!feof(datoteka))
	{
		fgets(buffer, LINE, datoteka);
		count++;
	}

	fclose(datoteka);

	return count;
}

int citaj_iz_datoteke(polinom* head1, polinom* head2,char*filename)
{
	FILE* datoteka = NULL;
	position temp = NULL;
	char buffer[LINE] = { 0 };	
	int	temp_exponenet=0;
	int temp_broj=0;
	int broj_linija = 1;

	datoteka = fopen(filename, "r");

	if (!datoteka)
	{
		perror("\nError in file opening\n");
		return EXIT_SUCCESS;
	}

	while (!feof(datoteka))
	{
		fgets(buffer, LINE, datoteka);
		if (sscanf(buffer, " %d %d %n", &temp_broj, &temp_exponenet) == 2)
		{
			if (broj_linija == 1)
			{
				temp = strvori_novog(temp_broj, temp_exponenet);
				unesi_sortirano(&head1, temp);
			}
			if (broj_linija == 2)
			{
				temp = strvori_novog(temp_broj, temp_exponenet);
				unesi_sortirano(&head2, temp);
			}
		}
		broj_linija++;
	}

	fclose(datoteka);

	return EXIT_SUCCESS;
}

position strvori_novog(int broj, int exponent)
{
	position temp = NULL;							//ovdje stvaram strukturu ali zasto nebi mogao stvorit samo position pokazivac na tu trukturu npr position p
	temp = (position)malloc(sizeof(polinom));		//prikaz memorije prilikom stvaranja novog clana?

	temp->broj = broj;
	temp->eksponent = exponent;
	temp->next = NULL;

	return temp;
}

int unesi_sortirano(polinom* head, position stvoreni)
{
	position hodajuci = NULL;

	hodajuci = &head;

	if (hodajuci->next == NULL)
	{
		stvori_nakon(&head, hodajuci, stvoreni);
	}

	while (hodajuci != NULL)
	{
		if (hodajuci->eksponent < stvoreni->eksponent)
		{
			stvori_nakon(&head, hodajuci, stvoreni);
		}

		if (hodajuci->eksponent > stvoreni->eksponent)
		{
			stvori_prije(&head, hodajuci, stvoreni);
		}

		if (hodajuci->eksponent == stvoreni->eksponent)
		{
			zbroji_clanove(&head, hodajuci, stvoreni);
		}

		hodajuci = hodajuci->next;								//idi mi dok ne dodes na adresu kojem je main na nulli a ne da on pokazuje na nullu
	}
	free(hodajuci);

	return EXIT_SUCCESS;
}

int stvori_nakon(polinom* head, position pronadeni, position stvoreni)
{
	polinom* hodajuci = NULL;							//dali da ja stvorim pokazivac na tu strukturu ili samo novu strukturu temp

	hodajuci = (polinom*)malloc(sizeof(polinom));
	hodajuci = &head;

	while (hodajuci !=NULL)
	{
		if (hodajuci == pronadeni)
		{
			stvoreni->next = pronadeni->next;
			pronadeni->next = stvoreni;
			break;
		}
		hodajuci = hodajuci->next;
	}
	return EXIT_SUCCESS;
}

int stvori_prije(polinom* head, position pronadeni, position stvoreni)
{
	position hodajuci = NULL;

	hodajuci = (position)malloc(sizeof(polinom));
	hodajuci = &head;

	while (hodajuci!=NULL)
	{
		if (hodajuci->next == pronadeni)
		{
			stvoreni->next=pronadeni;
			hodajuci->next = stvoreni;
			break;
		}
		hodajuci = hodajuci->next;
	}
	return EXIT_SUCCESS;
}

int zbroji_clanove(polinom* head, position pronadeni, position stvoreni)
{
	position hodajuci = NULL;


	hodajuci = &head;

	while (hodajuci != NULL)
	{
		if (hodajuci->next= pronadeni)
		{
			pronadeni->broj = pronadeni->broj + stvoreni->broj;
			free (stvoreni);
			break;
		}
	}
	return EXIT_SUCCESS;
}

int mnozenje_polinoma(polinom* prvi_head, polinom* drugi_head, polinom* rezultatni_head)
{
	int broj = 0;
	int exponent = 0;
	position* temp = NULL;
	temp = (position*)malloc(sizeof(polinom));
	while (prvi_head!=NULL)
	{
		while (drugi_head != NULL)
		{
			broj = prvi_head->next->broj * drugi_head->next->broj;
			exponent = prvi_head->next->eksponent * drugi_head->next->eksponent;
			drugi_head = drugi_head->next;
		}
		temp = strvori_novog(broj, exponent);
		unesi_sortirano(&rezultatni_head, temp);
		prvi_head = prvi_head->next;
	}
	return EXIT_SUCCESS;
}

int zbrajanje_polinoma(polinom* prvi_head, polinom* drugi_head, polinom* rezultatni_head)
{
	int broj = 0;
	int exponent = 0;
	position* temp = NULL;
	temp = (position*)malloc(sizeof(polinom));

	while (prvi_head != NULL)
	{
		while (drugi_head != NULL)
		{
			if (prvi_head->eksponent==drugi_head->eksponent)
			{
				broj = prvi_head->next->broj + drugi_head->next->broj;
				exponent = prvi_head->next->eksponent;
				drugi_head = drugi_head->next;
			}
		}
		temp = strvori_novog(broj, exponent);
		unesi_sortirano(&rezultatni_head, temp);
		prvi_head = prvi_head->next;
	}

	return EXIT_SUCCESS;
}