#include "Contact.h"

int PushContact(Contact* rear, People* tempPeo)
{
    Contact* s = (Contact*)malloc(sizeof(Contact));
    // if(s == NULL)
    // {
    //     return 0;
    // }

    assert(s);

    s->peo = (People*)malloc(sizeof(People));
    assert(s->peo);

    s->peo = tempPeo;
    
    rear->rear->next = s;
    s->rear = rear->rear;
    rear->rear = s;
    s->next = rear;

    return 1;

}

int FindContact(Contact* head, int pos)
{

}

int FindPos_Name(Contact* head, char x[])
{

}

int ShowContact(Contact* head)
{
    head = head->next;
    if(head->next == NULL)
    {
        return 0;
    }

    while(head->next != NULL)
    {
        printf("%-10s%-10d%-20s\n",
            head->peo->Name,
            head->peo->Age,
            head->peo->Tele);

        head = head->next;
    }

    return 1;
}

int DeleteContact(Contact* head)
{

}