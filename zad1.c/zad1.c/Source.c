#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 128
#define MAX_LINIJA 1024
typedef struct _student {
	char ime[MAX];
	char prezime[MAX];
	int bod;
}student;

int brojRedaka(char* ime_filea)
{
	int br = 0;
	FILE* f = NULL;
	char buffer[MAX_LINIJA] = { 0 };
	
	f = fopen(ime_filea, "r");
	if (f == NULL)
	{
		printf("Greska");
		return -1;
	}

	while (!feof(f))
	{
		fgets(buffer, MAX_LINIJA, f);
		br++;
	}

	fclose(f);

	return br;
}

student* Skeniranje(char* ime_filea, int br)
{
	student* s = NULL;
	FILE* f;
	int brojac = 0;

	f = fopen(ime_filea, "r");

	s = (student*)malloc(br * sizeof(student));
	if (s == NULL)
	{
		printf("Alociranje neuspjesno");
		free(s);
		return NULL;
	}

	while (!feof(f))
	{
		fscanf(f, "%s %s %d", s[brojac].ime, s[brojac].prezime, &s[brojac].bod);
		brojac++;
	}

	fclose(f);

	return s;
}

int main()
{
	char ime_filea[MAX];
	int br,i;
	student* s;

	printf("Unesite ime datoteke: ");//vamo stavi .txt a u mapi spremi bez .txt
	scanf("%s", ime_filea);

	br = brojRedaka(ime_filea);
	//printf("%d", br);
	
	printf("Ime\tPrezime\tAps. bodovi\tRel. bodovi\n");

	s = Skeniranje(ime_filea, br);
	for (i = 0; i < br; i++)
		printf("%s\t%s\t%d\t\t%.2f\n", s[i].ime, s[i].prezime, s[i].bod, (float)s[i].bod / 80 * 100); //neka je max br bodova 80
	return 0;
}