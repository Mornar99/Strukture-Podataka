#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _cvorStabla* Stablo;
typedef struct _cvorStabla {
	char ime[50];
	Stablo sibling;
	Stablo child;
}cvorStabla;

typedef struct _Stog* PozStog;
typedef struct _Stog {
	Stablo data;
	PozStog next;
}Stog;

Stablo MakeDir(Stablo current, char* ime)
{
	Stablo q;
	q = (Stablo)malloc(sizeof(cvorStabla));
	if (!q)
	{
		printf("Nije se alociralo!\n");
		return -1;
	}
	strcpy(q->ime, ime);
	q->sibling = NULL;
	q->child = NULL;

	if (current == NULL)
		return q;
	else if (strcmp(current->ime, q->ime) > 0)
	{
		q->sibling = current;
		return q;
	}
	else if (strcmp(current->ime, q->ime) < 0)
		current->sibling = MakeDir(current->sibling, q->ime);
	else
	{
		printf("Vec postoji dir sa istim imenom!\n");
		free(q);
	}
	return current;
}

Stablo ChangeDir(Stablo current, char* ime, PozStog stog)
{
	Stablo P = current->child;
	if (P == NULL)
	{
		printf("Nema tog direktorija.\n");
		return current; //vrati nas odakle smo krenili ako ga nema
	}
	while (P != NULL)
	{
		if (strcmp(P->ime, ime) == 0)
		{
			printf("\n");
			//Push u stogˇˇ kako bi mogli cd.. kasnije
			PozStog q;
			q = (PozStog)malloc(sizeof(Stog));
			q->data = P;
			q->next = stog->next;
			stog->next = q;

			printf("Sad smo unutar: %s", ime);
			return P; //vraca poziciju trazenog dir
		}
		P = P->sibling;
	}
}

Stablo ChangeDirBack(Stablo current, PozStog stog)
{
	if (stog->next->next == NULL) //jer je prvi el u stogu root koji je odma tamo, tako sam stavia u mainu
	{								
		printf("Nema direktorija iznad!\n");
		return current;
	}
	else 
	{
		PozStog temp;
		temp = stog->next;
		Stablo P = temp->next->data; //VAMO MORAMO UZET ONAJ NAKON OVOG STA BRISEMO
		stog->next = stog->next->next;
		free(temp);
		printf("Sad smo unutar: %s", P->ime);
		return P;
	}
	
}

void Dir(Stablo current) //ispis
{
	printf("\n");
	if (current == NULL)
		printf("Nema nijednog direktorija!\n");
	
	while (current != NULL)
	{
		printf("\t-%s\n", current->ime);
		current = current->sibling;
	}
}

void BrisiSve(Stablo current) //neradi u svim slucajevima
{
	if (!current)
	{
		BrisiSve(current->sibling);
		BrisiSve(current->child);
		free(current);
	}
}

void obicniPush(PozStog stog, Stablo root)
{
	PozStog q;
	q = (PozStog)malloc(sizeof(Stog));
	q->data = root;
	q->next = stog->next;
	stog->next = q;
}
int main()
{
	int i;
	char ime[50];
	
	cvorStabla Root;
	Root.sibling = NULL;
	Root.child = NULL;
	strcpy(Root.ime, "C:");
	Stablo root = &Root;

	Stog stog;
	stog.data = NULL;
	stog.next = NULL;

	obicniPush(&stog, root); //da bi mogli kad smo u nekom od dice od roota vratit se iznad

	printf("MENI:\n");
	printf("md - 1\ncd - 2\ncd.. - 3\ndir - 4\nbrisi sve - 5\nizlaz - 6");
	do
	{
		printf("\nIZBOR: ");
		scanf("%d", &i);
		if (i == 1)
		{
			printf("Unesi ime direktorija za stvorit: ");
			scanf("%s", ime);
			root->child = MakeDir(root->child, ime); //VAMO IDE: root->child !!!
		}
		else if (i == 2)
		{
			printf("Unesi ime direktorija: ");
			scanf("%s", ime);
			root = ChangeDir(root, ime, &stog);
		}
		else if (i == 3)
			root = ChangeDirBack(root, &stog);
		else if (i == 4)
			Dir(root->child); //VAMO IDE: root->child !!!
		else if (i == 5)
			BrisiSve(root);
		else if(i != 6)
			printf("Krivi unos!\n");
	} while (i != 6);

	return 0;
}