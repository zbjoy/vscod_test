#include <stdio.h>
#include <stdlib.h>


  //Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};
 
int isPalindrome(struct ListNode* head){
    if(head == NULL)
    {
        return 1;
    }

    struct ListNode* tHead = head;
    struct ListNode* tempHead = NULL;
    while(head != NULL)
    {
        struct ListNode* next = head->next;

        struct ListNode* tempNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        tempNode->val = head->val;
        tempNode->next = tempHead;
        tempHead = tempNode;

        head = next;
    }

    while(tHead != NULL && tempHead != NULL)
    {
        if(tHead->val != tempHead->val)
        {
            return 0;
        }
        tHead = tHead->next;
        tempHead = tempHead->next;
    }

    return 1;
}

int main()
{
    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* s = (struct ListNode*)malloc(sizeof(struct ListNode));
    //s->next = NULL;
    head =  NULL;
    s->val = 1;
    s->next = head;
    head = s;
    struct ListNode* s2 = (struct ListNode*)malloc(sizeof(struct ListNode));
    s2->val = 2;
    s2->next = head;
    head = s2;
    int ret = isPalindrome(head);
    printf("%d", ret); 
    return 0;
}