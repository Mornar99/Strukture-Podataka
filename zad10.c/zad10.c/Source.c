#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _gradovi* Pok;
typedef struct _gradovi {
	char ime[50];
	int stanovnici;
	Pok L;
	Pok D;
}gradovi;

typedef struct _drzave* Poz;
typedef struct _drzave {
	char ime[50];
	Pok data;
	Poz next;
}drzave;

int DodajDrzavu(Poz P, char* ime, char* ime_filea_grada)
{
	Poz q;
	q = (Poz)malloc(sizeof(drzave));
	if (!q)
	{
		printf("Neuspjela alokacija!\n");
		return 0;
	}

	Pok h;
	h = (Pok)malloc(sizeof(gradovi));
	if (!h)
	{
		printf("Neuspjela alokacija!\n");
		return 0;
	}
	strcpy(h->ime, "");
	h->stanovnici = 0;
	h->L = NULL;
	h->D = NULL;

	strcpy(q->ime, ime);
	q->data = h;
	DodajGrad(q->data, ime_filea_grada);

	while (P->next != NULL && strcmp(P->next->ime, ime) < 0)//sortiranje po imenima drzava
		P = P->next;
	q->next = P->next;
	P->next = q;

	return 0;
}

Pok UnosGradaUStablo(Pok P, char* ime, int stanovnici)
{
	Pok q;

	if (P == NULL)
	{
		q = (Pok)malloc(sizeof(gradovi));
		if (!q)
		{
			printf("Neuspjela alokacija!\n");
			return 0;
		}
		strcpy(q->ime, ime);
		q->stanovnici = stanovnici;
		q->L = NULL;
		q->D = NULL;
		return q; //VAMO IDE RETURN q!!!!!!!
	}
	else if (stanovnici < P->stanovnici)
		P->L = UnosGradaUStablo(P->L, ime, stanovnici);
	else if (stanovnici > P->stanovnici)
		P->D = UnosGradaUStablo(P->D, ime, stanovnici);
	else if (stanovnici == P->stanovnici)//sort po nazivu grada
	{
		if(strcmp(ime,P->ime) < 0)
			P->L = UnosGradaUStablo(P->L, ime, stanovnici);
		else
			P->D = UnosGradaUStablo(P->D, ime, stanovnici);
	}

	return P;
}

int DodajGrad(Pok P, char* ime_filea_grada)
{
	char ime[50];
	int stanovnici;
	FILE* f;
	f = fopen(ime_filea_grada, "r");
	if (!f)
	{
		printf("Neuspjelo otvaranje filea!\n");
		return 0;
	}
	while (!feof(f))
	{
		fscanf(f, "%s %d", ime, &stanovnici);
		P = UnosGradaUStablo(P, ime, stanovnici);
	}

	fclose(f);
	return 0;
}

int IspisDrzava(Poz P)
{
	while (P != NULL)
	{
		printf("%s\n", P->ime);
		IspisGradova(P->data);//u ispisu nece bit pocetne 0 ako se stavi P->data->D

		P = P->next;
	}

	return 0;
}

int IspisGradova(Pok P)//inorder
{
	if (P != NULL)
	{
		IspisGradova(P->L);
		printf("\t-%s %d\n", P->ime, P->stanovnici);
		IspisGradova(P->D);
	}
	return 0;
}


int Trazi(Poz P, char* ime_drzave, int br_stanovnika)
{
	while (P != NULL && strcmp(P->ime, ime_drzave) != 0)
		P = P->next;

	TraziGradove(P->data, br_stanovnika);
	return 0;
}

int TraziGradove(Pok P, int br_stanovnika)
{
	if (P != NULL)
	{
		if (P->stanovnici > br_stanovnika)
			printf("%s ", P->ime);
		
		TraziGradove(P->L, br_stanovnika);
		TraziGradove(P->D, br_stanovnika);
	}
	return 0;
}

int main()
{
	drzave Head;
	Head.next = NULL;
	Head.data = NULL;
	char ime[50], ime_filea_grada[50];
	FILE* f;
	f = fopen("drzave.txt", "r");
	if (!f)
	{
		printf("Neuspjelo otvaranje filea!\n");
		return 0;
	}

	while (!feof(f))
	{
		fscanf(f, "%s %s", ime, ime_filea_grada);
		DodajDrzavu(&Head, ime, ime_filea_grada);
	}

	fclose(f);

	IspisDrzava(Head.next);

	printf("\n");
	Trazi(Head.next, "Francuska", 500000);//trazimo gradove francuske sa 
										  //sa brojem stanovnika vecim od 500000
	return 0;
}