#include <stdio.h>
#include <stdlib.h>

//Given the head of a singly linked list, return true if it is a palindrome or false otherwise


 //Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};
 
int isPalindrome(struct ListNode* head){
    struct ListNode* rear = NULL;
    struct ListNode* tempHead = head;
    while(tempHead != NULL)
    {
        // struct ListNode* next = tempHead->next;
        // tempHead->next = rear;
        // rear = tempHead;
        // tempHead = next;

        struct ListNode* temp = (struct ListNode*)malloc(sizeof(struct ListNode));
        temp->val = tempHead->val;
        temp->next = rear;
        rear = temp;
        tempHead = tempHead->next;
    }

    while(head != NULL)
    {
        if(rear->val != head->val)
        {
            return 0;
        }
        head = head->next;
        rear = rear->next;
    }
    return 1;
}

int main()
{
    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    head = NULL;
    int val = 0;
    while(val != -1)
    {
        struct ListNode* temp = (struct ListNode*)malloc(sizeof(struct ListNode));
        printf("Please enter your val :");
        scanf("%d", &val);
        if(val != -1)
        {
            temp->val = val;
            temp->next = head;
            head = temp;
        }
        else
        {
            free(temp);
        }
    }    

    printf("%d\n", isPalindrome(head));
    return 0;

}