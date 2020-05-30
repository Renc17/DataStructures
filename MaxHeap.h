#ifndef _MAXHEAP_H
#define _MAXHEAP_H

typedef struct hnode{
    int count;
    char *value;
    struct hnode *left;
    struct hnode *right;
    struct hnode *parent;
}Node;

typedef struct {
    int size;
    int current;
    Node **k;
}topk;


void swapValues(Node **p1, Node **p2, int sizep1, int sizep2);
void GivenLevel(Node* root, int level, int k, topk *array);
void printLevelOrder(Node* root, int k);
void ArrayEntry(topk *array, Node *value);
void FixArray(topk *array, int i);
void FixArrayLeftover(topk *array, Node *value);


int bal(Node *r);
int height(Node *r);
void insert(Node **root, int count, char* value, Node *parent);
void FixInsert(Node *node);
int check(Node *r);
void DeleteMaxHeap(Node *p);

#endif
