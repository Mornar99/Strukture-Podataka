#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 1024

typedef struct _stog* Poz;
typedef struct _stog {
	double El;
	Poz next;
}stog;

int Push(Poz P, double El);
double Pop(Poz P); //POP MORA BIT DOUBLE FUNKCIJA JER JE RETURN TIPA DOUBLE INACE NISTA NECE RADIT
int racun(Poz P,char* filename);

int main()
{
	double rezultat = 0;
	stog Head;
	Head.next = NULL;
	
	rezultat = racun(&Head, "postfix.txt");
	printf("Rezultat: %lf\n", rezultat);
	
	return 0;
}

int Push(Poz P, double x)
{
	Poz q;

	q = (Poz)malloc(sizeof(stog));
	if (!q)
	{
		printf("Neuspjelo alociranje.\n");
		return -1;
	}

	q->El = x;
	q->next = P->next;
	P->next = q;

	return 0;
}

double Pop(Poz P)
{
	Poz temp = NULL;
	double broj;
	
	temp = P->next;
	broj = temp->El;

	if (temp == NULL)
	{
		printf("Nema nijednog elementa u stogu.\n");
		return 0;
	}
	else
	{
		P->next = P->next->next;
		free(temp);
	}

	return broj;
}

int racun(Poz P, char* filename)
{
	FILE* f;
	char buffer[MAX_SIZE] = { 0 };
	char* current_buffer;
	double number = 0;
	int br = 0;
	int status = 0;
	char znak;
	double rezultat = 0;

	f = fopen(filename, "rb"); //koristi se kad nije tekst, ali u principu isto
	if (!f)
	{
		printf("File se nije otvorio.\n");
		return -1;
	}

	fgets(buffer, MAX_SIZE, f);
	fclose(f);
	current_buffer = buffer;

	while (strlen(current_buffer) > 0)
	{
		status = sscanf(current_buffer, "%lf %n", &number, &br);
		if (status == 1) //kad je status 1 onda smo skenirali broj
		{
			//printf("%lf %d status:%d\n", number,br,status);
			Push(P, number);
		}
		
		
		if (status != 1) //nije broj nego znak, sscanf vraca 0 ako nije pokupia lf
		{
			sscanf(current_buffer, " %c %n", &znak, &br);

			if (znak == '+')
				rezultat = Pop(P) + Pop(P);
			else if (znak == '*')
				rezultat = Pop(P) * Pop(P);
			else if (znak == '-')
				rezultat = Pop(P) - Pop(P);
			else if (znak == '/')
				rezultat = Pop(P) / Pop(P);
			else
			{
				printf("Krivi znak.\n");
				return 0;
			}
			Push(P, rezultat);
		}
		
		current_buffer += br;
	}

	rezultat = Pop(P);
	return rezultat;
}