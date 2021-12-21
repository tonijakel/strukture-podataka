#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>

#define LINE 1024
#define COUNT 10

struct _element;
typedef struct _element* position;

typedef struct _element
{
	int broj;
	position left;
	position right;
}element;

//odluke
int menu();
int decision();
int menu_ispisa();
int razmak();

//stvaranje
position make_element();
position insert(position current, position novi);
position dodaj_na_kraj(position head, position stvoreni);

//trazenje i brisanje
int zbrajanje(position current);
int lista_u_datoteku(position head, char* ime);
int slucbr(int min, int max);

//ispisi 
//nikoji ne radi ispravno
position inorder(position current, position head);
position print2D(position current, int space);

int main()
{
	char* filename = "ime_datoteka.txt";
	position head = NULL;
	position putujuci = NULL;
	position first = NULL;
	position root = NULL;
	position temp = NULL;
	int arr[10] = { 2,5,7,8,11,1,4,2,3,7 };
	int nasumicni[10] = { 0 };
	int min = 0;
	int max = 0;
	int i = 0;
	//temp=(position)malloc(sizeof(element));

	srand(time(NULL));

	head = (position)malloc(sizeof(element));

	for (i = 0;i < 10;i++)
	{
		temp = make_element(arr[i]);
		if (i == 0)
		{
			first = temp;
		}
		else
		{
			insert(first, temp);
		}
	}
	razmak();
	print2D(first, 0);
	zbrajanje(first);

	razmak();

	print2D(first, 0);

	puts("\n\n");

	head->broj = 0;
	head->left = NULL;
	head->right = NULL;
	puts("Inorder ispis glasi: \n");
	inorder(first, head);
	first = head->right;

	//razmak();

	//ispis
	while (first != NULL)
	{
		printf(" %d", first->broj);
		first = first->right;
	}

	razmak();
	lista_u_datoteku(head, filename);

	printf("Unesite granice nasumicnih brojeva");
	printf("\n\nDonja: ");
	scanf(" %d", &min);
	printf("\nGornja: ");
	scanf(" %d", &max);
	razmak();

	for (i = 0;i < 10;i++)
	{
		nasumicni[i] = slucbr(min, max);
		//printf("%d ",nasumicni[i]);
	}

	for (i = 0;i < 10;i++)
	{
		temp = make_element(nasumicni[i]);
		if (i == 0)
		{
			first = temp;
		}
		else
		{
			insert(first, temp);
		}
	}

	print2D(first, 0);

	razmak();

	inorder(first, head);
	zbrajanje(first);
	print2D(first, 0);

	razmak();

	return 0;
}

position make_element(int number)
{
	position new = NULL;
	new = (position)malloc(sizeof(element));
	new->broj = number;
	new->left = NULL;
	new->right = NULL;
	return new;
}

position insert(position current, position novi)
{
	if (current == NULL)
	{
		return novi;
	}
	if ((current->broj) <= (novi->broj))
	{
		current->right = insert(current->right, novi);
	}
	else if ((current->broj) > (novi->broj))
	{
		current->left = insert(current->left, novi);
	}
	return current;
}

position dodaj_na_kraj(position head, position stvoreni)
{
	position temp = NULL;
	temp = head;
	while (temp->right != NULL)
	{
		temp = temp->right;
	}
	temp->right = stvoreni;
	stvoreni->right = NULL;
	stvoreni->left = NULL;
	return EXIT_SUCCESS;
}

position inorder(position current, position head)
{
	position temp = NULL;
	if (current != NULL)
	{
		inorder(current->right, head);
		temp = make_element(current->broj);
		dodaj_na_kraj(head, temp);
		inorder(current->left, head);			//zasto ide prvo right pa left a ne obrnuto
	}
	return EXIT_SUCCESS;
}

position preorder(position current)
{
	if (current != NULL)
	{
		printf("%d ", current->broj);
		preorder(current->left);
		preorder(current->right);
	}
	return EXIT_SUCCESS;
}

position postorder(position current)
{
	if (current != NULL)
	{
		postorder(current->left);
		postorder(current->right);
		printf("%d ", current->broj);
	}
	return EXIT_SUCCESS;
}

position print2D(position current, int space)
{
	if (current == NULL)
		return EXIT_SUCCESS;
	space += COUNT;

	print2D(current->left, space);

	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf("%d\n", current->broj);

	print2D(current->right, space);

	return current;
}

int zbrajanje(position current)
{
	int L_prije = 0;
	int D_prije = 0;
	int L_sad = 0;
	int D_sad = 0;

	if (current != NULL)
	{
		if (current->left != NULL)
		{
			L_prije = current->left->broj;
		}
		if (current->right != NULL)
		{
			D_prije = current->right->broj;
		}

		zbrajanje(current->left);
		zbrajanje(current->right);

		if (current->left != NULL)
		{
			L_sad = current->left->broj;
		}

		if (current->right != NULL)
		{
			D_sad = current->right->broj;
		}

		return current->broj = L_sad + D_sad + L_prije + D_prije;
	}
	return EXIT_SUCCESS;
}

int lista_u_datoteku(position head, char* ime)
{
	FILE* datoteka = NULL;
	position temp;

	temp = head->right;
	datoteka = fopen(ime, "w");

	while (temp != NULL)
	{
		fprintf(datoteka, "%d ", temp->broj);
		temp = temp->right;
	}

	fclose(datoteka);

	return EXIT_SUCCESS;
}

int slucbr(int min, int max)
{
	int brmogucnosti = 0;
	brmogucnosti = max - min + 1;
	//printf("%d\n", brmogucnosti);
	//puts("\n");
	int novagranica = RAND_MAX - (RAND_MAX % brmogucnosti);
	//printf("%d\n", novagranica);
	//puts("\n");
	int slucbr = rand();
	while (slucbr > novagranica)
		slucbr = rand();
	return slucbr % brmogucnosti + min;
}

int razmak()
{
	puts("\n\n\n");
	puts("**********************************************************************************");
	puts("**********************************************************************************");
	puts("**********************************************************************************");
	puts("\n\n\n");
	return EXIT_SUCCESS;
}

/*
* int temp = 0;
	int temp1 = 0;
	int temp2 = 0;

	if (current != NULL)
	{
		temp = current->broj;
		zbrajanje(current->right);
		zbrajanje(current->left);

		if ((current->left == NULL) && (current->right != NULL))
		{
			temp1 = 0;
			temp2 = current->right->broj;
			printf("\nsadasnji %d, livo %d, desno %d\n", temp, temp1, temp2);
			return current->broj = temp1 + temp2;
		}

		else if ((current->left != NULL) && (current->right == NULL))
		{
			temp2 = 0;
			temp1 = current->left->broj;
			printf("\nsadasnji %d, livo %d, desno %d\n", temp, temp1, temp2);
			return current->broj = temp1 + temp2;
		}

		else if ((current->left == NULL) && (current->right == NULL))
		{
			temp1 = 0;
			temp2 = 0;
			printf("\nsadasnji %d, livo %d, desno %d\n", temp, temp1, temp2);
			return current->broj = 0;
		}
		else
		{
			temp1 = current->left->broj;
			temp2 = current->right->broj;
			printf("\nsadasnji %d, livo %d, desno %d\n", temp, temp1, temp2);
			return current->broj = temp1 + temp2;
		}
		return current->broj = temp + temp1 + temp2;
	}
	return EXIT_SUCCESS;
*/