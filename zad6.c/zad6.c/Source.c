#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _popis* Poz2;
typedef struct _popis {
	char naziv[50];
	int kolicina;
	double cijena; //AKO JE NESTO U DOUBLE TRIBA DOLI SVAGDI PAZIT DA BUDE %lf !!!!!!
	Poz2 next;
}popis;

typedef struct _racuni* Poz;
typedef struct _racuni {
	char ime[50];
	int year;
	int mon;
	int day;
	popis Head;
	Poz next;
}racuni;

int UnosPopisa(Poz2 P, char* naziv, int kolicina, double cijena)
{
	Poz2 q;
	q = (Poz2)malloc(sizeof(popis));
	if (!q)
	{
		printf("Neuspjelo alociranje!\n");
		return -1;
	}

	strcpy(q->naziv, naziv);
	q->kolicina = kolicina;
	q->cijena = cijena;

	q->next = P->next;
	P->next = q;

	return 0;
}

int UnosRacuna(Poz P, char* ime, int year, int mon, int day, char* naziv, int kolicina, double cijena)
{
	Poz q;
	q = (Poz)malloc(sizeof(racuni));
	if (!q)
	{
		printf("Neuspjelo alociranje!\n");
		return -1;
	}

	strcpy(q->ime, ime);
	q->year = year;
	q->mon = mon;
	q->day = day;
	(q->Head).next = NULL;

	UnosPopisa(&(q->Head), naziv, kolicina, cijena);

	while (P->next != NULL && P->next->year < year)
		P = P->next;

	q->next = P->next;
	P->next = q;

	return 0;
}

int ProcitajDatoteku(char* ime_filea, Poz P)
{
	char ime[50], naziv[50];
	int year = 0, mon = 0, day = 0, kolicina = 0;
	double cijena = 0;
	popis q;

	FILE* f;
	FILE* f1;
	f = fopen(ime_filea, "r");
	if (!f)
	{
		printf("Datoteka se nije otvorila.\n");
		return -1;
	}
	while (!feof(f))
	{
		fscanf(f, "%s", ime);

		f1 = fopen(ime, "r");
		if (!f1)
		{
			printf("Datoteka(popis) se nije otvorila.\n");
			return -1;
		}

		fscanf(f1, "%d-%d-%d", &year, &mon, &day);

		while (!feof(f1))
		{
			fscanf(f1, "%s %d %lf", naziv, &kolicina, &cijena);
			UnosRacuna(P, ime, year, mon, day, naziv, kolicina, cijena); //problem: za svaki element stvara novu listu
		}

		fclose(f1);
	}

	fclose(f);
	return 0;
}

int Ispis(Poz P)
{
	while (P != NULL)
	{
		Poz2 P2 = &(P->Head);
		P2 = P2->next; //JER U ISPIS DAJEMO HEAD.NEXT!!!!!!!!
		while (P2 != NULL)
		{
			printf("%s %d %lf\n", P2->naziv, P2->kolicina, P2->cijena);
			P2 = P2->next;
		}
		P = P->next;
	}
	return 0;
}

int main()
{
	racuni Head;
	Head.next = NULL;
	ProcitajDatoteku("racuni.txt", &Head);
	Ispis(Head.next);
	return 0;
}