#include "ListNode.h"

int PushList(struct ListNode** head, int val)
{   
    // if(!(*head)->val)
    // {
    //     (*head)->next = NULL;
    // }
    struct ListNode* s = (struct ListNode*)malloc(sizeof(struct ListNode));
    s->val = val;
    s->next = *head;
    *head = s;
}