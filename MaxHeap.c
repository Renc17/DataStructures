#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "MaxHeap.h"


void swapValues(Node **p1, Node **p2, int sizep1, int sizep2){
    char *valuep1 = (char *)malloc(sizeof(char)*sizep1);
    char *valuep2 = (char *)malloc(sizeof(char)*sizep2);

    int temp = (*p1)->count;
    strcpy(valuep1, (*p1)->value);
    strcpy(valuep2, (*p2)->value);

    (*p1)->count = (*p2)->count;
    free((*p1)->value);
    (*p1)->value = malloc(sizeof(char)*sizep2);
    strcpy((*p1)->value, (*p2)->value);

    (*p2)->count = temp;
    free((*p2)->value);
    (*p2)->value = malloc(sizeof(char)*sizep1);
    strcpy((*p2)->value, valuep1);

    free(valuep1);
    free(valuep2);

}

void printGivenLevel(Node* root, int level, int k, int *num)
{
    if (root == NULL)
        return;
    if (level == 1) {
        if(*num != k) {
            printf("%d %s\n", root->count, root->value);
            (*num)++;
        } else{
            return;
        }
    }
    else if (level > 1)
    {
        printGivenLevel(root->left, level-1, k, num);
        printGivenLevel(root->right, level-1, k, num);
    }
}

void printLevelOrder(Node* root, int k)
{
    int level = height(root);
    int i, num = 0;
    for (i=1; i<=level; i++) {
        printGivenLevel(root, i, k, &num);
    }
}

int  check(Node *r)
{
    //traversing the nodes of the subtree to check any node with balance factor > 0
    if(r == NULL)
        return 0;
    int x = check(r->left);
    if(bal(r))
        return 1;
    int y = check(r->right);

    return x||y;    //If any node present with balance factor > 0
}

void FixInsert(Node *node){
    if(node->parent == NULL){
        return;
    }

    if(node->count > node->parent->count){
        swapValues(&node, &(node->parent), strlen(node->value)+1, strlen(node->parent->value)+1);
    }

    FixInsert(node->parent);
}

void insert(Node **root, int count, char* value, Node *parent)
{
    if((*root) == NULL) {
        Node *node = malloc(sizeof(Node));
        node->value = malloc(strlen(value)+1);
        strcpy(node->value, value);
        node->left = NULL;
        node->right = NULL;
        node->count = count;
        node->parent = parent;
        *root = node;
        FixInsert(*root);
        return;
    }else if(bal((*root))==0 && check((*root)->right))  //Condition to insert node in the right sub-tree
        insert(&(*root)->right, count, value, *root);
    else if(bal((*root))==0)                      //condition to insert node in the left sub-tree
        insert(&(*root)->left,count, value, *root);
    else if(bal((*root))==1 && check((*root)->left))   //condition to insert node in the left sub-tree
        insert(&(*root)->left,count, value, *root);
    else if(bal((*root))==1)
        insert(&(*root)->right,count, value, *root);      //condition to insert node in right sub-tree
}

int height(Node *r)
{
    if(r == NULL)
        return 0;
    else
    {
        int lheight = height(r->left)+1;
        int rheight = height(r->right)+1;

        return (lheight > rheight) ? lheight : rheight; //returns maximum height
    }
}

int bal(Node *r)
{
    if(r == NULL)
        return 0;
    int lheight = height(r->left)+1;
    int rheight = height(r->right)+1;

    return (lheight - rheight); //[Balance Factor = Height of Left Sub-Tree - Height of Right Sub-Tree]
}


void DeleteMaxHeap(Node *p){
    if(p == NULL)
        return;

    DeleteMaxHeap(p->left);
    DeleteMaxHeap(p->right);

    free(p->value);
    free(p);
}