#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


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

//stvaranje
position make_element();
position insert(position current, position novi);

//trazenje i brisanje
int trazi_element(position current, int trazeni);
position DeleteElement(position current, int element);		//ne razumijem niti radi
position FindMin(position current);

//ispisi 
//nikoji ne radi ispravno
position inorder(position current);
position preorder(position current);
position postorder(position current);
position levelorder(position current);
position print2D(position current, int space);

int main()
{
	position first = NULL;
	position root = NULL;
	position temp = NULL;
	int broj_elemenata = 0;
	int choice = 0;
	int wrong_input = 0;
	int brisanje = 0;
	int search = 0;
	int odluka_ispisa = 0;
	//temp=(position)malloc(sizeof(element));

	menu();
	do
	{
		choice = decision();
		if ((choice <= 5) && (choice >= 0))
		{
			wrong_input = 0;
			switch (choice)
			{
			case 0:
			{
				printf("Odabrali ste: Ispis meni\n\n");
				menu();
				break;
			}
			case 1:
			{
				printf("Odabrali ste: Dodavanje elementa\n");
				temp = make_element();
				if (broj_elemenata == 0)
				{
					first = root = temp;
					//first = root;
					broj_elemenata++;
				}
				else
				{
					root = insert(root, temp);
					broj_elemenata++;
				}
				break;
			}
			case 2:
			{
				printf("Odabrali ste: Brisanje elementa\n");
				printf("Koji element zelite obrisati: ");
				scanf("%d", &brisanje);
				DeleteElement(first, brisanje);
				broj_elemenata--;
				break;
			}
			case 3:
			{
				printf("Odabrali ste: Ispisivanje elemenata\n");
				menu_ispisa();
				do
				{
					odluka_ispisa = decision();
					if ((odluka_ispisa >= 0) && (odluka_ispisa <= 6))
					{
						switch (odluka_ispisa)
						{
						case 0:
						{
							puts("");
							menu_ispisa();
							break;
						}
						case 1:
						{
							inorder(root);
							puts("");
							break;
						}
						case 2:
						{
							preorder(root);
							puts("");
							break;
						}
						case 3:
						{
							postorder(root);
							puts("");
							break;
						}
						case 4:
						{
							printf("Jos u razvijanju\n");
							//lvlorder();
							break;
						}
						case 5:
						{
							print2D(first, 0);
							puts("");
							break;
						}
						case 6:
						{
							break;
						}
						default:
						{
							perror("Fatalni error brb");
							break;
						}
						}
					}
					else if ((odluka_ispisa < 0) || (odluka_ispisa > 4))
					{
						wrong_input++;
						printf("Za sada imate %d pogresaka, imate pravo napraviti jos %d\n", wrong_input, 3 - wrong_input);
					}
				} while ((wrong_input != 3) && ((odluka_ispisa > 7) || (odluka_ispisa < 0)));
				break;
			}
			case 4:
			{
				printf("Odabrali ste: Ispitati dali element postoji\n");
				printf("\nUnesite element koji trazite: ");
				scanf_s(" %d", &search);
				if (trazi_element(root, search))
					printf("\nElement postoji vec ste ga unjeli\n");
				else
					printf("\nTaj element jos nije unesen :(\n");
				break;
			}
			case 5:
			{
				printf("Odabrali ste: Kraj programa\n");
				printf("\nDovidenja\n\n\n\n\n\n\n\n");
				break;
			}
			default:
			{
				perror("Fatalni error brb");
				break;
			}
			}
		}
		else if ((choice < 0) || (choice > 5))
		{
			wrong_input++;
			printf("Za sada imate %d pogresaka, imate pravo napraviti jos %d\n", wrong_input, 3 - wrong_input);
		}

	} while ((choice != 5) && (wrong_input != 3));

	if (wrong_input == 3)
	{
		printf("\nNapravili ste 3 greske za redom program je gotov :'(\n\n\n\n\n\n");
	}
}

int menu()
{
	printf("Izaberite sto zelite raditi\n");
	printf("0-Menu\n");
	printf("1-Dodaj element\n");
	printf("2-Brisi element\n");
	printf("3-Ispisi elemente\n");
	printf("4-Ispitivanje dali element postoji\n");
	printf("5-Kraj programa\n");
	printf("Program ce se sam  zavrsiti ako 3 puta zaredom unesete krivi broj ili broj izvan granica\n");
	printf("Pogreske se resetiraju nakon svakog tocnog unosa\n");
	return EXIT_SUCCESS;
}

int menu_ispisa()
{
	printf("\nKakav ispis zelite?\n");
	printf("0-opet ispisi meni\n");
	printf("1-inoreder\n");
	printf("2-preoreder\n");
	printf("3-postoreder\n");
	printf("4-levelorder\n");
	printf("5-2D prikaz\n");
	printf("6-Kada bolje razmislim ipak ne zelim ispis\n");
	return EXIT_SUCCESS;
}

int decision()
{
	int odluka;
	printf("\nSto cemo radit: ");
	scanf(" %d", &odluka);
	puts("");
	return odluka;
}

position make_element()
{
	position new = NULL;
	new = (position)malloc(sizeof(element));
	printf("Unesite broj: ");
	scanf_s(" %d", &new->broj);
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
	if ((current->broj) > (novi->broj))
	{
		current->right = insert(current->right, novi);
	}
	else if ((current->broj) < (novi->broj))
	{
		current->left = insert(current->left, novi);
	}
	else
	{
		free(novi);
	}
	return current;
}

int trazi_element(position current, int trazeni)
{

	/*
	* pogledaj jeli postoji ista
	* pogledaj prvi jeli on
	* pogledaj desno
	* nemas vise desno
	* pogledaj livo
	* nemas vise livo
	* vrati se
	* ako nisi pronasa nista vise srece iduci put
	* ako si pronasa JEDNOG stani
	*/

	//jeli postoji ista
	if (current == NULL)
	{
		return 0;
	}

	//jeli prvi on
	if (current->broj == trazeni)
	{
		return 1;
	}

	if (trazeni > current->broj)
	{
		return trazi_element(current->left, trazeni);
	}

	else
	{
		return trazi_element(current->right, trazeni);
	}
}

position inorder(position current)
{
	if (current != NULL)
	{
		inorder(current->left);
		printf("%d ", current->broj);
		inorder(current->right);
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

/*position levelorder(position root)
{
	if (root == NULL)
	{
		return 0;
	}

	printf(" %d", inorder(root->left));
	printf(" %d", root->broj);
	printf(" %d", inorder(root->right));
	return root;
}*/

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

position DeleteElement(position current, int element)		//sa prezentacije
{
	position temp = NULL;

	if (current == NULL)
	{
		printf("Nazalost ne postoji taj element\n");
		return current;
	}
	if (element < current->broj)
	{
		current->left = DeleteElement(current->left, element);
	}
	else if (element > current->broj)
	{
		current->right = DeleteElement(current->right, element);
	}
	else if (current->left != NULL && current->right != NULL)
	{
		temp = FindMin(current->right);
		current->broj = temp->broj;
		current->right = DeleteElement(current->right, current->broj);
	}
	else {
		temp = current;
		if (current->left == NULL)
		{
			current = current->right;
		}
		else
		{
			current = current->left;
		}
		free(temp);
	}
	return current;
}

position FindMin(position current)		//sa prezentacije takoder
{
	if (current == NULL)
	{
		return NULL;
	}
	else if (current->left == NULL)
	{
		return current;
	}
	else
	{
		return FindMin(current->left);
	}
}
