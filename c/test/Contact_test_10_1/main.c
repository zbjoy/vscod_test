#include <stdio.h>
#include <stdlib.h>

#include "Contact.h"

int main()
{
    Contact* head= (Contact*)malloc(sizeof(Contact));
    Contact* rear = (Contact*)malloc(sizeof(Contact));
    head->next = rear;
    head->rear = NULL;
    rear->rear = head;
    rear->next = NULL;

    int select = 0;
    while(1)
    {
        Menu();
        printf("Please enter your select:");
        scanf("%d", &select);
        switch(select)
        {
        case 1: //添加联系人
            AddContact(rear);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 0:
            printf("GoodBye!\n");
            system("pause");
            exit(0);
        default:
            printf("Your enter is error, please enter again!\n");
            system("pause");
            system("cls");
            break;            
        }
    }
    return 0;
}