#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMESIZE 20
#define SEXSIZE 5
#define NATIVESIZE 50
#define TELESIZE 12

typedef struct People
{
    char Name[NAMESIZE]; //姓名
    int Age; //年龄
    char Sex[SEXSIZE]; //性别
    char Native[NATIVESIZE]; //籍贯
    char Tele[TELESIZE]; //电话
}People;

typedef struct Contact
{
    People* peo;
    struct Contact* next;
    struct Contact* rear;
}Contact;

int Push_Contact(Contact* rear, People* peo);

int Delete_Contact(Contact* rear, int pos);

int PrintAll_Contact(Contact* rear);

int Find_Contact(Contact* rear, char x[]);

int Print_Contact(Contact* rear, int pos);

void Menu();

void AddContact(Contact* rear);

void ViewContact(Contact* head);

void DeleteContact(Contact* head);

void FindContact(Contact* head);