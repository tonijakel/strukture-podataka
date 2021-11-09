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

int datoteka_u_listu(osoba* head, char* filename);

position napravi_osobu(char* ime, int godine);

int printaj(osoba* head);

position pretraga(osoba* head,int funkcija);

int unesi_prije(osoba* head, position trazeni);

int unesi_poslje(osoba* head, position trazeni);

int brisi(osoba* head, position trazeni);

char* lista_u_datoteku(osoba* head,char *ime);

int citaj_listu_iz_datoteke(char* filename);

int brisi_sve(osoba* head);

//int sort(position p);

//int unesit_sortirano(osoba* head);

int menu();

int odluka();

int imena_datoteka(char* filename1, char* filename2, char* filename3);

int main()
{
	osoba head = { 0,0,NULL };
	position temp = NULL;
	position temp_napravljene_osobe = NULL;
	position hodajuca = NULL;
	char* datoteka1 = "Ucenici.txt";
	char* datoteka2[LINE] = { 0 };
	char* datoteka3[LINE] = { 0 };
	char ime[LINE] = { 0 };
	char uneseno_ime_datoteke[LINE] = { 0 };
	int br_datoteka = 0;
	int godine = 0;
	int odabir = 0;
	int odabir_dodavanja = 0;
	int broj_pogresaka = 1;
	int broj_studenata_datoteke = 0;

	temp = (position)malloc(sizeof(osoba));
	temp_napravljene_osobe = (position)malloc(sizeof(osoba));
	hodajuca= (position)malloc(sizeof(osoba));

	menu();
	
	odabir=odluka();

	while(odabir != 420)
	{

		if ((odabir >= 0) && (odabir <= 9))
		{
			broj_pogresaka = 0;
			switch (odabir)
			{

			case 0:
				puts("Odabrali ste: Menu");
				menu();
				odabir = odluka();
				break;

			case 1:
				puts("Odabrali ste: Printanje liste ");
				printaj(&head);
				odabir = odluka();
				break;

			case 2:
				puts("Odabrali ste: Trazenje u listi");
				temp = pretraga(&head,1);
				odabir = odluka();
				break;

			case 3:
				puts("Odabrali ste: Brisanje iz liste");
				if (temp == EXIT_FAILURE)
				{
					puts("Nazalost ili element nije pronaden ili nema liste iz kojega da se element izbrise ili niste jos trazili nista");
				}
				else
				{
					brisi(&head, temp);
				}
				odabir = odluka();
				break;

			case 5:
				puts("Odabrali ste: Dodavanje elementa");
				puts("Element moze imati samo 1 ime");
				puts("Element mozete dodati:");
				puts("0 - na pocetak liste");
				puts("1 - na kraj liste");
				puts("2 - izad nekog elementa");
				puts("3 - ispred nekog elementa");
				odabir_dodavanja = odluka();

				if (odabir_dodavanja >= 0 && odabir_dodavanja <= 3)
				{
					broj_pogresaka = 0;
					switch (odabir_dodavanja)
					{

					case 0:
						puts("Odabrali ste: Dodavanje na pocetak");
						puts("Unesite ime osobe i njene godine");
						printf("Ime: ");
						scanf(" %s", ime);
						printf("Godine: ");
						scanf(" %d", &godine);

						temp_napravljene_osobe = napravi_osobu(ime, godine);

						if (temp_napravljene_osobe != EXIT_FAILURE)
						{
							temp_napravljene_osobe->next = head.next;
							head.next = temp_napravljene_osobe;
						}
						else
						{
							puts("Ne znam sto bi ti reka\nVise srece drugi put i guess?");
						}
						break;

					case 1:
						puts("Odabrali ste: Dodavanje na kraj");
						puts("Unesite ime osobe i njene godine");
						printf("Ime: ");
						scanf(" %s", ime);
						printf("Godine: ");
						scanf(" %d", &godine);
						temp_napravljene_osobe = napravi_osobu(ime, godine);
						hodajuca= head.next;

						if (temp_napravljene_osobe != EXIT_FAILURE)
						{
							while (hodajuca!=NULL)
							{
								hodajuca = hodajuca->next;
								if (hodajuca!=NULL)
								{
									hodajuca->next = temp_napravljene_osobe;
									temp_napravljene_osobe = NULL;
									break;
								}
							}
						}
						else
						{
							puts("Ne znam sto bi ti reka\nVise srece drugi put i guess?");
						}
						break;

					case 2:
						puts("Odabrali ste: Dodavanje izad nekod elementa");
						puts("Unesite ime osobe i njene godine");
						printf("Ime: ");
						scanf(" %s", ime);
						printf("Godine: ");
						scanf(" %d", &godine);
						temp_napravljene_osobe = napravi_osobu(ime, godine);

						temp=pretraga(&head,0);

						unesi_poslje(&head,temp);

						/*
						hodajuca = head.next;
						
						while(hodajuca!=temp)
						{
							hodajuca = hodajuca->next;
							if (hodajuca = temp)
							{
								temp_napravljene_osobe->next = temp->next;
								temp->next = temp_napravljene_osobe;
								break;
							}
						}*/

						break;

					case 3:
						puts("Odabrali ste: Dodavanje ispred nekod elementa");
						puts("Unesite ime osobe i njene godine");
						printf("Ime: ");
						scanf(" %s", ime);
						printf("Godine: ");
						scanf(" %d", &godine);
						temp_napravljene_osobe = napravi_osobu(ime, godine);

						temp = pretraga(&head,1);

						unesi_prije(&head, temp);
						break;
					}
				}
				else
				{
					printf("Mozda je prekomleksno zadano, probaj opet\n");
					printf("Ispucali ste %d pogresku imate pravo na jos njih %d nakon cega ce se program sam zaustavit\n", broj_pogresaka, 3 - broj_pogresaka);
					odabir_dodavanja = odluka();
				}
				odabir = odluka();
				break;

			case 4:
				puts("Odabrali ste: Brisanje svega");
				brisi_sve(&head);
				odabir = odluka();
				break;

			case 6:
				puts("Odabrali ste: Trazenje u vezanoj listi");
				pretraga(&head,0);
				odabir = odluka();
				break;
			case 7:
				puts("Odabrali ste: Stvaranje datoteke za spremanje liste");
				if (br_datoteka < 2)
				{
					if (br_datoteka == 0)
					{
						printf("Program moze imat max 3 datoteke (za sad),sada ih imate %d",br_datoteka);
						puts("Smatramo vas pametnim korisnikom i molimo da ne ponavljete imena datoteka");
						strcpy((lista_u_datoteku(&head,datoteka2)), datoteka2);
						br_datoteka++;
					}
					else
					{						
						printf("Program moze imat max 3 datoteke (za sad),sada ih imate %d", br_datoteka);
						puts("Smatramo vas pametnim korisnikom i molimo da ne ponavljete imena datoteka");
						strcpy(lista_u_datoteku(&head,datoteka3), datoteka3);
						br_datoteka++;
					}
				}
				else
				{
					printf("Ima previse datoteka napravljenih");
				}
				odabir = odluka();
				break;

			case 8:
				puts("Odabrali ste: Citanje datoteke");
				printf("Za sada ima %d datoteka\n",br_datoteka+1);
				printf("To su datoteke pod imenima: ");
				imena_datoteka(datoteka1,datoteka2,datoteka3);
				printf("\nKoju citamo");
				scanf(" %s",uneseno_ime_datoteke);

				if(strcmp(datoteka1,uneseno_ime_datoteke)==0)
				{
					citaj_listu_iz_datoteke(datoteka1);
				}
				else if (strcmp(datoteka2, uneseno_ime_datoteke) == 0)
				{
					citaj_listu_iz_datoteke(datoteka2);
				}
				else if (strcmp(datoteka3, uneseno_ime_datoteke) == 0)
				{
					citaj_listu_iz_datoteke(datoteka3);
				}
				odabir = odluka();
				break;

			case 9:
				puts("Odabrali ste: Da unesete element sortirano");
				printf("Kako se taj element zove: ");
				scanf(" %s", ime);
				printf("Koliko godina ima: ");
				scanf(" %d", &godine);

				temp_napravljene_osobe=napravi_osobu(ime, godine);

				hodajuca = head.next;

				if (hodajuca==NULL)
				{
					temp_napravljene_osobe->next = head.next;
					head.next = temp_napravljene_osobe;
				}

				while (hodajuca!=NULL)
				{
					if(strcmp(hodajuca->ime,temp_napravljene_osobe->ime)>0)
					{
						unesi_poslje(&head, temp_napravljene_osobe);
					}
					hodajuca = hodajuca->next;
				}
				odabir = odluka();
				break;
			default:
				perror("Fatalni error brb");
			}
		}

		else if (odabir==420)
		{
			printf("Dovidenja\n\n\n\n");
			break;
		}

		else 
		{
			printf("Mozda je prekomleksno zadano, probaj opet\n");
			printf("Ispucali ste %d pogresku imate pravo na jos njih %d nakon cega ce se program sam zaustavit\n", broj_pogresaka, 3 - broj_pogresaka);
			odabir = odluka();

		}
	}

	/*
	broj_studenata_datoteke = provjera_datoteke(filename);		//za sada radi 
	//printf("%d",broj_studenata_datoteke);	

	datoteka_u_listu(&head, filename);
	printaj(&head);
	puts("Brisemo tonija");
	temp = pretraga(&head, "toni");
	unesi_prije(&head, temp);
	unesi_poslje(&head, temp);
	brisi(&head, temp);
	printaj(&head);
	lista_u_datoteku(&head);
	//sort(head.next);
	brisi_sve(&head);
	printaj(&head);*/

	/*while (head.next!=NULL);
		brisi sve*/
	return 0;
}



int provjera_datoteke(char* filename)
{
	FILE* datoteka = NULL;
	char buffer[LINE] = { 0 };
	int count = 0;

	datoteka = fopen(filename, "r");

	if (!datoteka)
	{
		perror("\nNemogu otvorit datoteku!\n");
		return EXIT_FAILURE;
	}

	while (!feof(datoteka))
	{
		fgets(buffer, LINE, datoteka);
		count++;
	}

	fclose(datoteka);

	return count;
}

int datoteka_u_listu(osoba* head, char* filename)
{
	FILE* datoteka = NULL;
	char ime[LINE] = { 0 };
	int godine;
	position p = NULL;
	position temp;
	temp = (position)malloc(sizeof(osoba));

	datoteka = fopen(filename, "r");

	while (!feof(datoteka))
	{
		fscanf(datoteka, " %s %d", ime, &godine);
		p = napravi_osobu(ime, godine);
		temp->next = p;
		p->next = NULL;
		temp = temp->next;
	}

	fclose(datoteka);

	return EXIT_SUCCESS;
}

position napravi_osobu(char* name, int age)
{
	position p = NULL;

	p = (position)malloc(sizeof(osoba));

	strcpy(p->ime, name);
	p->godina = age;
	p->next = NULL;

	return p;
}

int printaj(osoba* head)
{
	position p=NULL;

	p = head->next;							//kada bi isao printat bez p iman clan manje, zasto?

	if (p==NULL)
	{
		printf("lista je prazna :");
		return EXIT_SUCCESS;
	}

	puts("");
	while (p!= NULL)
	{
		printf("%s ima %d godina\n", p->ime, p->godina);
		p = p->next;
	}
	puts("");

	return EXIT_SUCCESS;
}

position pretraga(osoba* head,int funkcija)
{
	position p = NULL;
	char name[LINE] = { 0 };
	int count = 1;
	int redni_broj = 0;
	p = (position)malloc(sizeof(osoba));
	p = head->next;
	position temp;
	temp = (position)malloc(sizeof(osoba));
	temp = &head;

	printf("\nKoju osobu trazite: ");
	scanf(" %s",name);

	int pozicija = 0;
	
	if (p == NULL)
	{
		printf("Nazalost u listi nema nista");
		puts("Prvo unesite elemente u listu");
		return EXIT_FAILURE;
	}

	else
	{
		while (p != NULL)												//npr zasto vamo nije p.next nego samo p ako je p na kraju isto sto i p.next
		{
			p = temp->next;
			if (!strcmp(p->ime, name))
			{
				pozicija++;
				printf("Trazeni clan je na %d mjestu\n", pozicija);
				count++;
				if (count>1)
				{
					printf("Trazeni clan je na takoder i na %d mjestu\n", pozicija);
					count++;
				}
			}
			pozicija++;
			temp = temp->next;
		}

		if (funkcija == 1)								//u slucaju da je funckija indexa 1 to znaci da korisnik ima vise opcija kod izbora unosa, kod same pretrage ispisuje se samo samo clanovi
		{
			if (count == 2)
			{
				return p;
			}
			else
			{
				printf("U funkciji ima vise istih imena, unesite mjesto clana: ");
				scanf(" %d", &redni_broj);

				while (p != NULL)												//npr zasto vamo nije p.next nego samo p ako je p na kraju isto sto i p.next
				{
					p = temp->next;
					if (!strcmp(p->ime, name) && pozicija == redni_broj)
					{
						return p;
					}
					pozicija++;
					temp = temp->next;
				}

			}
		}

		puts("\nTrazeni clan nije pronaden\n");
		return EXIT_FAILURE;
	}
}

int brisi(osoba* head, position trazeni)
{
	position setajuci = NULL;
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
	position p = NULL;
	position prev= NULL;

	prev = &head;
	p = prev->next;

	if(p==NULL)
	{
		return EXIT_SUCCESS;
	}

	while (p != NULL)
	{
		p = prev->next;
		if (p == trazeni)
		{
			trazeni->next=p;
			prev->next = trazeni;
			break;
		}
		prev = prev->next;
	}
	return EXIT_SUCCESS;
}


int unesi_poslje(osoba* head, position trazeni)
{
	position p = NULL;
	position temp= NULL;

	p = (position)malloc(sizeof(osoba));
	temp = (position)malloc(sizeof(osoba));
	p=head->next;
	temp = &head;

	if (p == NULL)
	{
		return EXIT_SUCCESS;
	}

	while (p != NULL)
	{
		p = temp->next;
		if (p == trazeni)
		{
			trazeni->next = p->next;
			p->next = trazeni;
			break;
		}
		temp= temp->next;
	}
	return EXIT_SUCCESS;


	/*
	while (head != NULL)					//zasto ovako zasto ne moze !head ili !head.next
	{
		p = head->next;
		if (p == trazeni)
		{
			temp->next = p->next;
			p->next = temp;
			break;
		}
		head = head->next;
	}
	return EXIT_SUCCESS;
	*/
}


char* lista_u_datoteku(osoba* head,char *ime)
{
	FILE* datoteka = NULL;
	char* ulazno[LINE] = { 0 };
	osoba* temp = head->next;

	printf("\nUnesite ime datoteke u koju zelite spremiti listu: ");
	scanf(" %s",&ime);

	datoteka = fopen(ime, "w");

	if (!datoteka)
	{
		perror("Ne mogu otvorit file za upis");
		return *ime;
	}

	while (temp != NULL)
	{
		fprintf(datoteka, " %s %d\n", temp->ime, temp->godina);
		temp = temp->next;
	}

	fclose(datoteka);

	return *ime;

	//citaj_listu_iz_datoteke(ime);

	return *ime;
}

int citaj_listu_iz_datoteke(char* filename)
{
	FILE* datoteka = NULL;
	char buffer[LINE] = { 0 };
	char ime[LINE] = { 0 };
	int godine = 0;

	datoteka = fopen(filename, "r");
	while (!feof(datoteka))
	{
		strcpy(buffer, "");
		fgets(buffer, LINE, datoteka);
		if (sscanf(buffer," %s %d", ime, &godine) == 2)
		{
			printf(" %s %d\n", ime, godine);
		}
	}

	fclose(datoteka);

	return EXIT_SUCCESS;
}

int sort(position p)								//kopirano sa prezentacija sa predavanja
{
	position j, prev_j, temp, end;
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

int brisi_sve(osoba* head)
{
	position p;
	position temp;
	p = (position)malloc(sizeof(osoba));
	temp = (position)malloc(sizeof(osoba));
	p = (position)malloc(sizeof(osoba));
	temp = &head;

	p = temp->next;
	while (p != NULL)
	{
		temp = p;
		p = p->next;
		free(temp);
	}
	temp->next = NULL;

	return EXIT_SUCCESS;
}

int menu()
{
	puts("");
	printf("0 - pogledaj opet menu\n");
	printf("1 - printanje vezane liste\n");
	printf("2 - trazi u vezanoj listi\n");
	printf("3 - brisi element vezane liste\n");
	printf("4 - brisi sve elemente liste\n");
	printf("5 - dodaj element\n");
	printf("6 - trazi u vezanoj listi\n");
	printf("7 - napravi datoteku za spremanje liste/lista\n");
	printf("8 - procitaj datoteku\n");
	printf("9 - unesi sortirano\n\n");
	printf("U slucaju da se unos ne poklapa sa zadanim mogucnostima imat ce te jos 3 pokusaja nakon toga program ce se zavrsit\n");
	printf("U slucaju da ga zelite sami zavrsit unesite broj 420\n");
	printf("Sami zavrsavate samo iz glavnog meni-a\n");

	return EXIT_SUCCESS;
}

int odluka()
{
	int odluka;
	printf("\nSto cemo radit: ");
	scanf(" %d",&odluka);
	puts("");
	return odluka;
}

int imena_datoteka(char* filename1, char* filename2, char* filename3)
{
	if (filename1!=0)
	{
		printf(" %s",filename1);
	}
	if (filename2 != 0)
	{
		printf(" %s", filename2);
	}
	if (filename3 != 0)
	{
		printf(" %s", filename3);
	}
	return EXIT_SUCCESS;
}

/*int unesit_sortirano(osoba* temp)
{
	osoba* newperson = NULL;
	newperson = (osoba*)malloc(sizeof(osoba));


	return EXIT_SUCCESS;
}*/