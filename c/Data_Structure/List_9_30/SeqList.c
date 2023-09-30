#include "SeqList.h"

int Push_SeqList(SeqList* head, char x[])
{
    SeqList* s = (SeqList*)malloc(sizeof(SeqList));
    strcpy(s->Name, x);
    s->next = head->next;
    head->next = s;

    return 1;
}

int Delete_SeqList(SeqList* head, int pos)
{
    while(head != NULL && pos-- != 1)
    {
        head = head->next;
    }


    if(head != NULL && pos == 0)
    {
        SeqList* temp = head->next;
        head->next = head->next->next;
        free(temp);
    }
}

int printAll_SeqList(SeqList* head)
{
    while(head != NULL)
    {
        head = head->next;
        if(head != NULL)
        {
            printf("%s\n", head->Name);
        }
    }

    return 1;
}
int print_SeqList(SeqList* head, int pos)
{
    while(head != NULL && pos--)
    {
        head = head->next;
    }

    pos += 1;
    if(head != NULL && pos == 0)
    {
        printf("%s\n", head->Name);
        return 1;
    }
    else
    {
        return 0;
    }

}