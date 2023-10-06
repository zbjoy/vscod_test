#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NAMEMAX 20
#define TELEMAX 12

typedef struct People
{
    char Name[NAMEMAX];
    int Age;
    char Tele[TELEMAX];
}People;

typedef struct Contact
{
    People* peo;
    struct Contact* next;
    struct Contact* rear;
}Contact;

int PushContact(Contact* rear, People* tempPeo);

int FindContact(Contact* head, int pos);

int FindPos_Name(Contact* head, char x[]);

int ShowContact(Contact* head);

int DeleteContact(Contact* head);