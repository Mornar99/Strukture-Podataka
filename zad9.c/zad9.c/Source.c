#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//binarno stablo pretrazivanja
typedef struct _cvorStabla* Stablo;
typedef struct _cvorStabla {
	int El;
	Stablo L;
	Stablo D;
}cvorStabla;

Stablo Dodaj(int x, Stablo S);
void Ispis_inorder(Stablo S);
Stablo Replace(Stablo S);
int Suma(Stablo S);
void Ispis_inorder_u_file(Stablo S, FILE* f);
							 
int main()
{
	Stablo root = NULL;
	int suma = 0;
	/* zad pod a i b
	root = Dodaj(2, root);
	root = Dodaj(5, root);
	root = Dodaj(7, root);
	root = Dodaj(8, root);
	root = Dodaj(11, root);
	root = Dodaj(1, root);
	root = Dodaj(4, root);
	root = Dodaj(2, root);
	root = Dodaj(3, root);
	root = Dodaj(7, root);
	
	Ispis_inorder(root);

	printf("\nNakon replacea:\n");
	root = Replace(root);
	Ispis_inorder(root);
	*/
	int x;
	FILE* f;
	f = fopen("random stablo.txt", "w");
	if (!f)
	{
		printf("File se nije otvorio!\n");
		return 0;
	}
	srand(time(NULL));
	for (int i = 0; i < 20; i++)
	{
		x = (rand() % (90 - 10 + 1)) + 10;
		root = Dodaj(x, root);
	}
	root = Replace(root);
	Ispis_inorder_u_file(root, f);
	return 0;
}

Stablo Dodaj(int x, Stablo S)//u ovom zad je unos naopak
{							//(livo veci, desno manji), samo obrnit < i >
	if (S == NULL)			//smiju se ponavlajt elementi, tretraju se kao veci
	{
		S = (Stablo)malloc(sizeof(cvorStabla));
		S->El = x;
		S->L = NULL;
		S->D = NULL;
	}
	else if (x > S->El || x == S->El)
		S->L = Dodaj(x, S->L);
	else if (x < S->El)
		S->D = Dodaj(x, S->D);
	return S;
}

void Ispis_inorder(Stablo S)
{
	if (S != NULL)
	{
		Ispis_inorder(S->L);
		printf("%d ", S->El);
		Ispis_inorder(S->D);
	}
}

int Suma(Stablo S)
{
	int suma = 0;
	if (S == NULL)
		return suma + 0;
	if (S->L != NULL)
		suma += S->L->El + Suma(S->L);
	if(S->D != NULL)
		suma += S->D->El + Suma(S->D);
		return suma;
}

Stablo Replace(Stablo S)
{
	if (S != NULL)
	{
		S->El = Suma(S);
		S->L = Replace(S->L);
		S->D = Replace(S->D);
	}
	return S;
}

void Ispis_inorder_u_file(Stablo S, FILE* f)
{
	if (S != NULL)
	{
		Ispis_inorder_u_file(S->L, f);
		fprintf(f, "%d ", S->El);
		Ispis_inorder_u_file(S->D, f);
	}
}