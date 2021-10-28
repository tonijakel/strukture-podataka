#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>


/*
-napravi datoteku
-procitaj iz nje
-spremi to u niz
-dinamicki alociraj niz zavisno o broju studenata iz niza
-svaki student je struktura koju moras napravit
-2string ili niza chara i jedan int
-niz je napravljen kao niz kojem je svaki clan struktura
-ispisi sve studente
-izracunaj aposlutni broj svakog studenta na naicn da podilimo samo njegov broj bodova sa ukupnim u nekoj livoj funkciji
-izracunaj relativni na nacin da prije ispisa zbrojis samo unos od svakoga i samo u drugoj livoj dilis sve sa tom funkciji
*/

#define LINE 200

typedef struct _student
{
	char ime[LINE];
	char prezime[LINE];
	int bodovi;
}student;


int studentcount(char* ime_datoteke);								//cita broj studenata
student* dinamickiniz(int brojstudenata, char* ime_datoteke);		//alocira niz za spremit te studente
int relativnibrojukupno(int count, student* niz);					//prebroji sve bodove svih studenata
float apsolutnibroj(int bodovi_studenta, int bodovi_ispita);		//gleda apsolutni broj studenata
float realativnoosobni(int bodovi_studenta, int relativni);			//gleda relativni broj studenata

int main()
{
	int i = NULL;
	int count = 0;
	//student* *p = NULL;
	student* s = NULL;
	//student*  q = NULL;
	int relativni_bodovi = 0;
	int bodovi_ispita = 0;
	char* filename = "vjezba1.txt";

	/*printf("Koliko bodova ima ispit: ");
	scanf("%d", &bodovi_ispita);*/

	bodovi_ispita = 100;

	count = studentcount(filename);	//prebroji studente

	s = dinamickiniz(count, filename);
	/*	*p = dinamickiniz(count, "filename");
	q = dinamickiniz(count, "filename");*/

	relativni_bodovi = relativnibrojukupno(count, s);		//izracunaj relativivni broj bodova

	for (i = 0; i < count; i++)
	{
		printf("%s %s je %d bodova. Apsolutno je imao %f%, a relatinvno je imao %f%\n\n",
			s[i].ime, s[i].prezime, s[i].bodovi, apsolutnibroj(s[i].bodovi, bodovi_ispita), realativnoosobni(s[i].bodovi, relativni_bodovi));
	}

	return 0;
}

int studentcount(char* ime_datoteke)
{
	int counter = 0;
	FILE* datoteka = NULL;
	char buffer[LINE] = { 0 };

	datoteka = fopen(ime_datoteke, "r");

	if (!datoteka)
	{
		printf("\nGreska pri otvaranju datoteke!!!!\n\n\n");
		return -1;
	}

	while (!feof(datoteka))
	{
		fgets(buffer, LINE, datoteka);
		counter++;
	}

	fclose(datoteka);

	return counter;
}

student* dinamickiniz(int brojstudenata, char* ime_datoteke)
{
	int i = 0;
	FILE* datoteka = NULL;
	student* niz_studenata = NULL;		//zasto nmg stavit student niz nego mora bit student pokazivac na niz

	niz_studenata = (student*)malloc(brojstudenata * sizeof(student));

	datoteka = fopen(ime_datoteke, "r");

	if (!datoteka)
	{
		printf("\nGreska pri otvaranju datoteke!!!!\n\n\n");
		return niz_studenata;
	}

	for (i = 0; i < brojstudenata; i++)
	{
		fscanf(datoteka, " %s %s %d", niz_studenata[i].ime, niz_studenata[i].prezime, &niz_studenata[i].bodovi);
	}

	/*
	printf("\n%lf\n", &niz_studenata);
	printf("\n%lf\n", niz_studenata);
	*/

	fclose(datoteka);

	return niz_studenata;
}

int relativnibrojukupno(int count, student* niz)
{
	int ukupni_bodovi_studenata = 0;
	int i = 0;

	for (i = 0; i < count; i++)
	{
		ukupni_bodovi_studenata += niz[i].bodovi;
	}

	return ukupni_bodovi_studenata;
}

float apsolutnibroj(int bodovi_studenta, int bodovi_ispita)
{
	return ((float)bodovi_studenta / bodovi_ispita) * 100;
}

float realativnoosobni(int bodovi_studenta, int relativni)
{
	return ((float)bodovi_studenta / relativni) * 100;
}