#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define LINE 1024


typedef struct _polinom
{
	int broj;
	int eksponent;
	struct _polinom* next;
}polinom;

int provjera_datoteke(char* filename);

int citaj_iz_datoteke(polinom* head1, polinom* head2, char* filename);

polinom* stvori_novog(int broj, int exponent);

int unesi_sortirano(polinom* head, polinom* stvoreni);

int stvori_nakon(polinom* pronadeni, polinom* stvoreni);

int zbroji_clanove(polinom* head, polinom* prvi, polinom* stvoreni);

int mnozenje_polinoma(polinom* prvi_head, polinom* drugi_head, polinom* rezultatni_head);

int zbrajanje_polinoma(polinom* prvi_head, polinom* drugi_head, polinom* rezultatni_head);

int ispis(polinom* head);


int main()
{
	polinom head1 = { 0,0,NULL };
	polinom head2 = { 0,0,NULL };
	polinom sum_head = { 0,0,NULL };
	polinom mno_head = { 0,0,NULL };
	char* ime_datoteke = "polinom.txt";


	printf("U datoteci ima %d linija, pa ce mo imati isto toliko polinoma\n", provjera_datoteke(ime_datoteke));
	citaj_iz_datoteke(&head1, &head2, ime_datoteke);
	printf("\nPrvi polinom je oblika: \n");
	ispis(&head1);
	printf("\nDrugi polinom je oblika: \n");
	ispis(&head2);
	zbrajanje_polinoma(&head1, &head2, &sum_head);
	printf("\nKada bi se ta da polinoma zbrojili dobili bi: \n");
	ispis(&sum_head);
	printf("\nKada bi se ta da polinoma pomnozili dobili bi: \n");
	mnozenje_polinoma(&head1, &head2, &mno_head);
	ispis(&mno_head);

	return 0;
}

int ispis(polinom* head)
{
	polinom* temp = NULL;
	temp = head->next;

	puts("");

	while (temp != NULL)
	{
		printf("%dx^%d", temp->broj, temp->eksponent);
		temp = temp->next;
		if (temp != NULL)
		{
			printf(" + ");
		}
		else if (temp == NULL)
		{
			printf(" = 0\n");
		}
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

int citaj_iz_datoteke(polinom* head1, polinom* head2, char* filename)
{
	FILE* datoteka = NULL;
	polinom* temp = NULL;
	char buffer[LINE] = { 0 };
	int	temp_exponenet = 0;
	int temp_broj = 0;
	int broj_linija = 1;
	int n = 0;
	char* p = NULL;

	datoteka = fopen(filename, "r");

	if (!datoteka)
	{
		perror("\nError in file opening\n");
		return EXIT_SUCCESS;
	}


	while (!feof(datoteka))
	{
		fgets(buffer, LINE, datoteka);
		p = buffer;
		while (strlen(p)) {
			if (sscanf(p, " %d %d %n", &temp_broj, &temp_exponenet, &n) == 2)
			{
				if (broj_linija == 1)
				{
					temp = stvori_novog(temp_broj, temp_exponenet);
					unesi_sortirano(head1, temp);
				}
				else if (broj_linija == 2)
				{
					temp = stvori_novog(temp_broj, temp_exponenet);
					unesi_sortirano(head2, temp);
				}
				else
				{
					printf("Svaka cast buddy\n");
				}
			}
			else break;
			p += n;
		}
		broj_linija++;
	}

	fclose(datoteka);

	return EXIT_SUCCESS;
}

polinom* stvori_novog(int broj, int exponent)
{
	polinom* temp = NULL;									//ovdje stvaram strukturu ali zasto nebi mogao stvorit samo polinom* pokazivac na tu trukturu npr polinom* p
	temp = (polinom*)malloc(sizeof(polinom));			//prikaz memorije prilikom stvaranja novog clana?

	temp->broj = broj;
	temp->eksponent = exponent;
	temp->next = NULL;

	return temp;
}

int unesi_sortirano(polinom* head, polinom* stvoreni)
{
	polinom* hodajuci = NULL;

	hodajuci = head;

	while (hodajuci->next != NULL)
	{
		if (hodajuci->next->eksponent < stvoreni->eksponent)
		{
			break;
		}
		else if (hodajuci->next->eksponent == stvoreni->eksponent)
		{
			zbroji_clanove(head, hodajuci, stvoreni);
			return EXIT_SUCCESS;
		}
		hodajuci = hodajuci->next;								//idi mi dok ne dodes na adresu kojem je main na nulli a ne da on pokazuje na nullu
	}
	stvori_nakon(hodajuci, stvoreni);
	return EXIT_SUCCESS;
}

int stvori_nakon(polinom* pronadeni, polinom* stvoreni)
{
	stvoreni->next = pronadeni->next;
	pronadeni->next = stvoreni;

	return EXIT_SUCCESS;
}

int zbroji_clanove(polinom* head, polinom* pronadeni, polinom* stvoreni)
{
	pronadeni->next->broj += stvoreni->broj;
	free(stvoreni);
	return EXIT_SUCCESS;
}

int mnozenje_polinoma(polinom* prvi_head, polinom* drugi_head, polinom* rezultatni_head)
{
	int broj = 0;
	int exponent = 0;
	polinom* temp1 = prvi_head;
	polinom* temp2 = drugi_head;
	while (temp1->next != NULL)
	{
		temp2 = drugi_head;
		while (temp2->next != NULL)
		{
			broj = temp1->next->broj * temp2->next->broj;
			exponent = temp1->next->eksponent + temp2->next->eksponent;
			unesi_sortirano(rezultatni_head, stvori_novog(broj, exponent));

			temp2 = temp2->next;
		}
		temp1 = temp1->next;
	}
	return EXIT_SUCCESS;
}

int zbrajanje_polinoma(polinom* prvi_head, polinom* drugi_head, polinom* rezultatni_head)
{
	int broj = 0;
	int exponent = 0;
	polinom* temp1 = prvi_head->next;
	polinom* temp2 = drugi_head->next;

	while (temp1 != NULL)
	{
		unesi_sortirano(rezultatni_head, stvori_novog(temp1->broj, temp1->eksponent));
		temp1 = temp1->next;
	}

	while (temp2 != NULL)
	{
		unesi_sortirano(rezultatni_head, stvori_novog(temp2->broj, temp2->eksponent));
		temp2 = temp2->next;
	}

	return EXIT_SUCCESS;
}