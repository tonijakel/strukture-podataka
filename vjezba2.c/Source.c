#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define LINE 1024

struct _osoba;
typedef struct _osoba* position;

typedef struct _osoba
{
	char ime[LINE];
	int godina;
	position next;
}osoba;

int provjera_datoteke(char* filename);

int datoteka_u_listu(osoba* head,char* filename);

position napravi_osobu(char* ime,int godine);

int printaj(osoba* head);

position pretraga(osoba *head);

int unesi_prije(osoba *head, position trazeni);

int unesi_poslje(osoba *head, position trazeni);

int brisi(osoba* head, position trazeni);

int lista_u_datoteku(osoba* head);

int citaj_listu_iz_datoteke(char* filename);

int sort(position p);



int main()
{
	osoba head = {0,0,NULL};
	int broj_studenata_datoteke=0;
	position temp = NULL;
	char* filename = "Ucenici.txt";

	temp = (position)malloc(sizeof(osoba));

	broj_studenata_datoteke=provjera_datoteke(filename);		//za sada radi 
	//printf("%d",broj_studenata_datoteke);	

	datoteka_u_listu(&head, filename);
	printaj(&head);
	puts("Brisemo tonija");
	temp=pretraga(&head,"toni");
	unesi_prije(&head,temp);
	unesi_poslje(&head,temp);
	brisi(&head,temp);
	printaj(&head);
	lista_u_datoteku(&head);
	//sort(head.next);

	return 0;
}


int provjera_datoteke(char* filename)
{
	FILE* datoteka = NULL;
	char buffer[LINE] = {0};
	int count = 0;

	datoteka=fopen(filename,"r");	

	if (!datoteka)
	{
		perror("\nNemogu otvorit datoteku!\n");
	}
	
	while (!feof(datoteka))
	{
		fgets(buffer,LINE,datoteka);
		count++;
	}

	fclose(datoteka);

	return count;
}

int datoteka_u_listu(osoba* head, char* filename)
{
	FILE* datoteka = NULL;
	char ime[LINE] = {0};
	int godine;
	position p=NULL;

	datoteka = fopen(filename,"r");	

	while (!feof(datoteka))
	{
		fscanf(datoteka," %s %d",ime,&godine);
		p=napravi_osobu(ime,godine);
		head->next = p;
		p->next = NULL;
		head = head->next;
	}

	fclose(datoteka);

	return EXIT_SUCCESS;
}

position napravi_osobu(char* name, int age)
{
	position p=NULL;

	p = (position)malloc(sizeof(osoba));

	strcpy(p->ime,name);
	p->godina = age;

	return p;
}

int printaj(osoba *head)
{
	position p;
	p = (position)malloc(sizeof(osoba));
	
	p = head->next;							//kada bi isao printat bez p iman clan manje, zasto?
	
	puts("");
	while (head->next!=0)
	{
		p = head->next;;
		printf("%s ima %d godina\n",p->ime,p->godina);
		head = head->next;
	}
	puts("");

	return EXIT_SUCCESS;
}

position pretraga(osoba* head,char* name)
{
	position p=NULL;
	p = (position)malloc(sizeof(osoba));

	int pozicija = 0;
	
	
	while (p!=NULL)												//npr zasto vamo nije p.next nego samo p ako je p na kraju isto sto i p.next
	{	
		p = head->next;	
		if (!strcmp(p->ime, name))
		{
			pozicija++;
			printf("Trazeni clan je na %d mjestu\n",pozicija);
			return p;
		}
		pozicija++;
		head = head->next;
	}

	puts("\nTrazeni clan nije pronaden\n");

	return NULL;
}

int brisi(osoba* head,position trazeni)
{
	position setajuci=NULL;
	setajuci = (position)malloc(sizeof(osoba));

	while (setajuci != NULL)
	{
		setajuci = head->next;
		if (setajuci == trazeni)
		{
			head->next = setajuci->next;
			free(setajuci);
			break;
		}
		head = head->next;
	}
	return EXIT_SUCCESS;
}

int unesi_prije(osoba* head, position trazeni)
{
	position p=NULL;
	p = (position)malloc(sizeof(osoba));
	position temp=NULL;
	temp = (position)malloc(sizeof(osoba));

	while (head!=NULL)
	{
		p = head->next;
		if (p==trazeni)
		{
			temp=napravi_osobu("unesen prije",1);
			head->next = temp;
			temp->next = p;
			break;
		}
		head = head->next;
	}
	return EXIT_SUCCESS;
}

int unesi_poslje(osoba* head, position trazeni)
{
	position p = NULL;
	p = (position)malloc(sizeof(osoba));
	position temp = NULL;
	temp = (position)malloc(sizeof(osoba));

	while (head!=NULL)					//zasto ovako zasto ne moze !head ili !head.next
	{
		p = head->next;
		if (p == trazeni)
		{
			temp = napravi_osobu("unesen poslje", 2);
			temp->next = p->next;
			p->next = temp;
			break;
		}
		head = head->next;
	}
	return EXIT_SUCCESS;
}

int lista_u_datoteku(osoba *head)
{
	char ime[LINE] = {0};
	FILE* datoteka = NULL;
	char* ulazno[LINE] = { 0 };

	printf("\nUnesite ime datoteke: ");
	scanf(" %s",ime);

	datoteka = fopen(ime,"w");

	if (!datoteka)
	{
		perror("Ne mogu otvorit file za upis");
	}

	while (head->next != NULL)
	{
		fprintf(datoteka," %s %d",head->next->ime,head->next->godina);
		head->next = head->next->next;
	}

	fclose(datoteka);
	
	citaj_listu_iz_datoteke(ime);

	return EXIT_SUCCESS;
}

int citaj_listu_iz_datoteke(char *filename)
{
	FILE* datoteka = NULL;
	char buffer[LINE] = {0};
	char ime[LINE] = { 0 };
	int godine = 0;

	datoteka = fopen(filename,"r");
	while (!feof(datoteka))
	{
		strcpy(buffer,"");
		fgets(buffer,LINE,datoteka);
		if (sscanf(datoteka, " %s %d",ime,&godine) == 2)
		{
			fprintf(datoteka," %s %d");
		}
	}

	fclose(datoteka);

	return EXIT_SUCCESS;
}

int sort(position p)								//kopirano sa prezentacija sa predavanja
{
	position j, prev_j, temp,end;
	prev_j = (position)malloc(sizeof(osoba));
	temp = (position)malloc(sizeof(osoba));
	j = (position)malloc(sizeof(osoba));
	end = (position)malloc(sizeof(osoba));
	
 	while (p->next != end)
	{
		prev_j = p;
		j = p->next;
		while (j->next != end)
		{
			if (j->godina > j->next->godina)
			{
				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}
			prev_j = j;
			j = j->next;
		}
		end = j;
	}
	return EXIT_SUCCESS;
}
