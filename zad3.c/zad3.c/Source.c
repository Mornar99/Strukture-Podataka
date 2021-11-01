#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 20
#define MAX_LINE 1024

//struct _Person;
typedef struct _Person* Poz;
typedef struct _Person {
    char name[N];
    char surname[N];
    int birth;
    Poz next;
}Person;

Poz CreatePerson(char* name, char* surname, int birth);
int UnosP(Poz P, char* name, char* surname, int birth);
int Ispis(Poz P);
int UnosK(Poz P, char* name, char* surname, int birth);
Poz Search(Poz P, char* surname);
Poz TraziPret(Poz P, char* surname); //neka brise po prezimenu
int Delete(Poz P, char* surname);
int UnosIza(char* x, char *name, char *surname, int birth, Poz P);
int UnosIspred(char* x, char* name, char* surname, int birth, Poz P);
int Ispis_uFile(Poz P, char* ime_filea);
int Unos_izFile(Poz P, char* ime_filea);
int SortListe(Poz P);

Poz CreatePerson(char* name, char* surname, int birth)
{
    Poz a = NULL;
    a = (Poz)malloc(sizeof(Person));
    if (!a)
    {
        perror("Greska kod alociranja\n");
        return -1;
    }

    strcpy(a->name, name);
    strcpy(a->surname, surname);
    a->birth = birth;
    a->next = NULL;

    return a;
}

int UnosP(Poz P, char* name, char* surname, int birth)
{
    Poz a = NULL;
    a = (Poz)malloc(sizeof(Person));
    if (!a)
    {
        perror("Greska kod alociranja\n");
        return -1;
    }

    a = CreatePerson(name, surname, birth);
    if (!a)
        return -1;

    a->next = P->next;
    P->next = a;

    return 0;
}

int Ispis(Poz P)
{
    Poz temp = P;

    while (temp != NULL)
    {
        printf("Name: %s, surname: %s, birth: %d\n", temp->name, temp->surname, temp->birth);
        temp = temp->next;
    }

    return 0;
}

int UnosK(Poz P, char* name, char* surname, int birth)
{
    while (P->next != NULL)
        P = P->next;

    UnosP(P, name, surname, birth);

    return 0;
}

Poz Search(Poz P, char* surname)
{
    while (P != NULL && strcmp(P->surname, surname) != 0)
        P = P->next;

    return P;
}

Poz TraziPret(Poz P, char* surname)
{
    while (P->next != NULL && strcmp(P->next->surname, surname) != 0)
        P = P->next;

    if (P->next == NULL)
        return NULL;
    else
        return P;
}

int Delete(Poz P, char* surname)
{
    Poz temp = NULL;
    P = TraziPret(P, surname);

    if (P == NULL)
        printf("Greska, nema elementa\n");
    else
    {
        temp = P->next;
        P->next = P->next->next;
        free(temp);
    }

    return 0;
}

int UnosIza(char* x, char* name, char* surname, int birth, Poz P)
{
    P = Search(P->next, x);

    if (P != NULL)
        UnosP(P,name,surname,birth);
    else
        printf("Greska,element ne postoji.\n");

    return 0;
}

int UnosIspred(char* x, char* name, char* surname, int birth, Poz P)
{
    P = TraziPret(P,x);

    if (P != NULL)
        UnosP(P, name, surname, birth);
    else
        printf("Greska,element ne postoji.\n");

    return 0;
}

int Ispis_uFile(Poz P, char* ime_filea)
{
    FILE* file = NULL;
    file = fopen(ime_filea, "w");
    if (!file)
    {
        printf("Datoteka se nije otvorila.\n");
        return -1;
    }

    while (P != NULL)
    {
        fprintf(file,"Name: %s, surname: %s, birth: %d\n", P->name, P->surname, P->birth);
        P = P->next;
    }

    fclose(file);

    return 0;
}

int Unos_izFile(Poz P, char* ime_filea)
{
    int br = 0,i;
    FILE* file = NULL;
    char buffer[MAX_LINE] = { 0 };
    char temp[60] = { 0 }, name[60] = { 0 }, surname[60] = { 0 };
    int birth = 0;

    file = fopen(ime_filea, "r");
    if (!file)
    {
        printf("Datoteka se nije otvorila.\n");
        return -1;
    }
    
    while (!feof(file))
    {
        fgets(buffer, MAX_LINE, file);
        br++;
    }
    rewind(file); //STAVIT REWIND NAKON BROJANJA REDAKA!!!!!

    for (i = 0; i < br; i++)
    {
        fscanf(file, "%s %s %s %s %s %d", temp, name, temp, surname, temp, &birth);
      
        UnosK(P, name, surname, birth);
    }
    /* KRACE:
    while (!feof(file))
    {
        fscanf(file, "%s %s %s %s %s %d", temp, name, temp, surname, temp, &birth);

        UnosK(P, name, surname, birth);
    }
    */
    fclose(file);

    return 0;
}

int SortListe(Poz P)
{
    Poz x = NULL, prevX = NULL, temp = NULL, end = NULL;

    while (P->next != end)
    {
        prevX = P;
        x = P->next;
        while (x->next != end)
        {
            if (strcmp(x->surname, x->next->surname) > 0)
            {
                temp = x->next;
                prevX->next = temp;
                x->next = temp->next;
                temp->next = x;

                x = temp;
            }
            prevX = x;
            x = x->next;
        }
        end = x;
    }
    return 0;
}

int main()
{
    Poz P = NULL;
    Person Head = { .next = NULL, .name = {0}, .surname = {0}, .birth = 0 };

    
    UnosP(&Head, "Ivo", "Ivic", 10);
    UnosP(&Head, "Pero", "Peric", 17);
    UnosK(&Head, "Ante", "Antic", 75);

    P = Search(Head.next, "Ivic");
    UnosP(P, "Bela", "Belic", 29);  //unosi iza searcha

    Delete(&Head, "Ivic");

    UnosIza("Belic", "Tonci", "Toncic", 64, &Head); //unosi iza danog prezimena(belic)

    UnosIspred("Belic", "Stipe", "Stipic", 46, &Head);

    SortListe(&Head);

    Ispis(Head.next);

    //Ispis_uFile(Head.next, "osobe.txt");
    /*
    Unos_izFile(&Head, "osobe.txt");
    Ispis(Head.next);*/

    return 0;
}
