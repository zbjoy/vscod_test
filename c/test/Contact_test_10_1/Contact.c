#include "Contact.h"

int Push_Contact(Contact* rear, People* peo)
{
    Contact* s = (Contact*)malloc(sizeof(Contact));
    s->peo = (People*)malloc(sizeof(People));

    if(s == NULL)
    {
        return 0;
    }

    s->peo = peo;
    s->next = rear;
    s->rear = rear->rear;
    s->rear->next = s;
    s->next->rear = s;

    return 1;
}

int Delete_Contact(Contact* head, int pos)
{
    Contact* s = (Contact*)malloc(sizeof(Contact));

    if(s == NULL)
    {
        return 0;
    }

    int i = 0;

    while(--pos && head->next != NULL)
    {
        head = head->next;
    }

    if(head->next == NULL)
    {
        return 0;
    }

    s = head->next;
    head->next = s->next;
    s->next->rear = head;
    free(s);

    return 1;
}

int PrintAll_Contact(Contact* head)
{
    // Contact* s = (Contact*)malloc(sizeof(Contact));
    // s = head;
    //head = head->next;
    while(head->next->next != NULL)
    {
        head = head->next;
        printf("%-5s%-5d%-5s%-20s%-20s\n",
             head->peo->Name,
             head->peo->Age, 
             head->peo->Sex, 
             head->peo->Native, 
             head->peo->Tele);
    }

    return 1;
}

int FindByName_Contact(Contact* head, char x[])
{
    // Contact* s = (Contact*)malloc(sizeof(Contact));
    // s = head->next;
    int index = 0;

    while(head->next->next != NULL)
    {
        head = head->next;
        index++;
        if(!strcmp(head->peo->Name, x))
        {
            return index;
        }
    }

    return -1;
}

int Print_Contact(Contact* head, int pos)
{
    // Contact* s = (Contact*)malloc(sizeof(Contact));
    // s = head->next;

    while(head != NULL && pos--)
    {
        head = head->next;
    }

    if(pos != 0)
    {
        return 0;
    }
           
    printf("%-5s%-5d%-5s%-20s%-20s\n",
            head->peo->Name,
            head->peo->Age, 
            head->peo->Sex, 
            head->peo->Native, 
            head->peo->Tele);

    return 1;
}

void Menu()
{
    printf("-------------------------------------\n");
    printf("|                                   |\n");
    printf("|         1. Add Contact            |\n");
    printf("|                                   |\n");
    printf("|         2. Delete Contact         |\n");
    printf("|                                   |\n");
    printf("|         3. Find Contact           |\n");
    printf("|                                   |\n");
    printf("|         4. View all Contacts      |\n");
    printf("|                                   |\n");
    printf("|         0.    Exit                |\n");
    printf("|                                   |\n");
    printf("-------------------------------------\n");
}

void AddContact(Contact* rear)
{
    People tempPeo;
    printf("Please enter the name of the contact you want to add:");
    scanf("%s", tempPeo.Name);
    printf("Please enter age:");
    scanf("%d", &tempPeo.Age);
    printf("Please enter sex:");
    scanf("%s", tempPeo.Sex);
    printf("Please enter native:");
    scanf("%s", tempPeo.Native);
    printf("Please enter telephone:");
    scanf("%s", tempPeo.Tele);

    Push_Contact(rear, &tempPeo);
}

void ViewContact(Contact* head)
{
    printf("%-5s%-5s%-5s%-20s%-20s\n", "Name", "Age", "Sex", "Native", "Telephone");
    PrintAll_Contact(head);
}

void DeleteContact(Contact* head)
{
    char Name[NAMESIZE];
    printf("Please enter name whitch you want to delete:");
    scanf("%s", Name);

    int pos = FindByName_Contact(head, Name);

    Delete_Contact(head, pos);

    printf("Delete successful\n");

    system("pause");
    system("cls");

}

void FindContact(Contact* head)
{

}