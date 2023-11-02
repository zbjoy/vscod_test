#include <stdio.h>
#include <stdlib.h>

//Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
 

int isSame(struct TreeNode* tempLeft, struct TreeNode* tempRight, int* ret)
{
    if((tempLeft != NULL) && (tempRight != NULL))
    {
        if(tempLeft->val != tempRight->val)
        {
            *ret = 0;
        }
        isSame(tempLeft->left, tempRight->right, ret);
        isSame(tempLeft->right, tempRight->left, ret);
        return *ret;
    }
    else if((tempLeft == NULL) && (tempRight == NULL)) 
    {
        return *ret;
    }
    else if(((tempLeft == NULL) && (tempRight != NULL)) || ((tempRight == NULL) && (tempRight != NULL)))
    {
        *ret = 0;
        return *ret;
    }
    return *ret;
}


int isSymmetric(struct TreeNode* root){
    if(root == NULL)
    {
        return 1;
    }
    // else if(root->left == NULL && root->right == NULL)
    // {
    //     return 1;
    // }
    int ret = 1;
    isSame(root->left, root->right, &ret);

    return ret;
}

void CreateTree(struct TreeNode** root)
{
    char temp;
    scanf("%c", &temp);

    if(temp == '#')
    {
        *root = NULL;
    }
    else
    {
        *root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        (*root)->val = temp - '0';
        CreateTree(&(*root)->left);
        CreateTree(&(*root)->right);

    }
}

int main()
{
    struct TreeNode* root = NULL;
    CreateTree(&root);
    getchar();
    printf("%d", isSymmetric(root));
    return 0;
}