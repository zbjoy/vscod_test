#include <stdio.h>
#include <stdlib.h>
#include "ListNode.h"

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{
    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    head = NULL;
    struct ListNode* arg = (struct ListNode*)malloc(sizeof(struct ListNode));
    arg = NULL;
    int num1 = 0;
    int num2 = 0;
    int carry = 0;
    while(l1 || l2)
    {
        num1 = 0;
        num2 = 0;
        if(l1)
        {
            num1 = l1->val;
        }

        if(l2)
        {
            num2 = l2->val;
        }

        int sum = num1 + num2;

        if(carry == 1)
        {
            sum += 1;
            carry = 0;
        }
        
        if(sum >= 10)
        {
            sum %= 10;
            carry = 1;
        }

        PushList(&head, sum);

        if(l1 == NULL && l2 == NULL)
        {
            break;
        }

        if(l1 == NULL)
        {
            l1 = NULL;
        }
        else
        {
            l1 = l1->next;
        }
       
        if(l2 == NULL)
        {
            l2 = NULL;
        }
        else
        {
            l2 = l2->next;
        }
 
    }

    if(carry == 1)
    {
        PushList(&head, 1);
    }

    while(head)
    {
        PushList(&arg, head->val);
        head = head->next;
    }

 
    return arg;
}

int main()
{
    struct ListNode* s1 = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* s2 = (struct ListNode*)malloc(sizeof(struct ListNode));
    s1 = NULL;
    s2 = NULL;
    PushList(&s1, 3);
    PushList(&s1, 5);
    PushList(&s1, 5);
    PushList(&s2, 4);
    PushList(&s2, 6);
    PushList(&s2, 7);

    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    head = addTwoNumbers(s1, s2);
    return 0;
}