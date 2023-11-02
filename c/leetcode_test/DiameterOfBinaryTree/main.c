#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


int get_Max(int a, int b)
{
    return a > b ? a : b;
}

int depthOfBinaryTree(struct TreeNode* root)
{
    if(root == NULL)
    {
        return 0;
    }
    else
    {
        //depthOfBinaryTree(root->left);
        //depthOfBinaryTree(root->right);
        return get_Max(depthOfBinaryTree(root->right), depthOfBinaryTree(root->left)) + 1;
    }
}

static int max = 0;
int diameterOfBinaryTree(struct TreeNode* root){
    if(root == NULL)
    {
        return max;
    }
    else
    {
        int temp1 = depthOfBinaryTree(root->left);
        int temp2 = depthOfBinaryTree(root->right);
        int sum = temp1 + temp2;
        if(max < sum)
        {
            max = sum;
        }

        diameterOfBinaryTree(root->left);
        diameterOfBinaryTree(root->right);
        return max;
    }
}

void CreateTree(struct TreeNode** root)
{
    // char temp1[10];
    // char temp2[10];
    // scanf("%s", temp1);
    // scanf("%s", temp2);
    // if(strcmp(temp1, "null"))
    // {
    //     root->left = NULL;
    // }

    // if(strcmp(temp2, "null"))
    // {
    //     root->right = NULL;
    // }
    // struct TreeNode* left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    // struct TreeNode* right = (struct TreeNode*)malloc(sizeof(struct TreeNode));

    // left->val = temp1[0] - '0';
    // right->val = temp2[0] - '0';
    // left->right = NULL;
    // left->left = NULL;
    // right->right = NULL;
    // right->left = NULL;

    // root->left = left;
    // root->right = right;

    char a;
    scanf("%c", &a);

    if(a == '#')
    {
        *root = NULL;
    }
    else
    {
        *root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        (*root)->val = a - '0';
        CreateTree(&(*root)->left);
        CreateTree(&(*root)->right);
    }

}

int main()
{
    struct TreeNode* root = NULL;
    CreateTree(&root);
    getchar();
    printf("%d", diameterOfBinaryTree(root));
    return 0;
}