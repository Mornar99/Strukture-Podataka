#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _lista* Pok;
typedef struct _lista {
	char ime[50];
	int stanovnici;
	Pok next;
}lista;

typedef struct _stablo* Poz;
typedef struct _stablo {
	char ime[50];
	Pok data;
	Poz L;
	Poz D;
}stablo;

Poz DodajUStablo(Poz P, char* ime, char* ime_filea_gradova);
void DodajUListu(Pok P, char* ime_filea_gradova);
int UnosUListu(Pok P, char* ime, int stanovnici);
void IspisStabla(Poz P);
void IspisListe(Pok P);
void TraziDrzavu(Poz P, char* ime, int stanovnici);
void TraziGradove(Pok P, int stanovnici);

Poz DodajUStablo(Poz P, char* ime, char* ime_filea_gradova)
{
	if (P == NULL)
	{
		Poz q;
		q = (Poz)malloc(sizeof(stablo));
		if (!q)
		{
			printf("Greska pri alociranju!\n");
			return 0;
		}
		strcpy(q->ime, ime);

		Pok t;
		t = (Pok)malloc(sizeof(lista));
		if (!t)
		{
			printf("Greska pri alociranju!\n");
			return 0;
		}
		strcpy(t->ime, "");
		t->stanovnici = 0;
		t->next = NULL;

		q->data = t;
		DodajUListu(q->data, ime_filea_gradova);

		q->L = NULL;
		q->D = NULL;

		return q;
	}
	else if (strcmp(ime, P->ime) < 0)
		P->L = DodajUStablo(P->L, ime, ime_filea_gradova);
	else if (strcmp(ime, P->ime) > 0)
		P->D = DodajUStablo(P->D, ime, ime_filea_gradova);
	
	return P;
}

void DodajUListu(Pok P, char* ime_filea_gradova)
{
	char ime[50];
	int stanovnici;

	FILE* f;
	f = fopen(ime_filea_gradova, "r");
	if (!f)
	{
		printf("Neuspjelo otvaranje filea!\n");
		return 0;
	}
	while (!feof(f))
	{
		fscanf(f, " %s %d", ime, &stanovnici);
		UnosUListu(P, ime, stanovnici);
	}

	fclose(f);
}

int UnosUListu(Pok P, char* ime, int stanovnici)
{
	Pok q;
	q = (Pok)malloc(sizeof(lista));
	if (!q)
	{
		printf("Greska pri alociranju!\n");
		return 0;
	}

	strcpy(q->ime, ime);
	q->stanovnici = stanovnici;

	while (P->next != NULL && P->next->stanovnici < stanovnici)
	{
		if (P->next->stanovnici == stanovnici)
			while (P->next != NULL && strcmp(P->next->ime,ime) < 0)
				P = P->next;
		else
		P = P->next;
	}


	q->next = P->next;
	P->next = q;
	return 0;
}

void IspisStabla(Poz P)//inorder
{
	if (P != NULL)
	{
		IspisStabla(P->L);
		printf("%s\n", P->ime);
		IspisListe(P->data->next);
		IspisStabla(P->D);
	}
}

void IspisListe(Pok P)
{
	while (P != NULL)
	{
		printf("\t%s %d\n", P->ime, P->stanovnici);
		P = P->next;
	}
}

void TraziDrzavu(Poz P,char* ime,int stanovnici)
{
	if (P == NULL)
		printf("Nema trazene drzave.\n");
	else if (strcmp(ime, P->ime) < 0)
		TraziDrzavu(P->L, ime, stanovnici);
	else if (strcmp(ime, P->ime) > 0)
		TraziDrzavu(P->D, ime, stanovnici);
	else if (strcmp(ime, P->ime) == 0)
		TraziGradove(P->data->next, stanovnici);
}

void TraziGradove(Pok P, int stanovnici)
{
	while (P != NULL && P->stanovnici < stanovnici)
		P = P->next;
	while (P != NULL)
	{
		printf("%s %d ", P->ime, P->stanovnici);
		P = P->next;
	}
}

int main()
{
	Poz root = NULL;
	char ime[50];
	char ime_filea_gradova[50];

	FILE* f;
	f = fopen("drzave.txt", "r");
	if (!f)
	{
		printf("Neuspjelo otvaranje filea!\n");
		return 0;
	}

	while (!feof(f))
	{
		fscanf(f, " %s %s", ime, ime_filea_gradova);
		root = DodajUStablo(root, ime, ime_filea_gradova);
	}
	fclose(f);

	IspisStabla(root);

	int stanovnici = 0;
	printf("\nUnesite drzavu za pretraziti: ");
	scanf(" %s", ime);
	printf("\nUnesite broj stanovnika: ");
	scanf("%d", &stanovnici);
	TraziDrzavu(root, ime, stanovnici);

	return 0;
}