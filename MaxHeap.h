#ifndef COVID_19_MAXHEAP_H
#define COVID_19_MAXHEAP_H

typedef struct hnode{
    int count;
    char *value;
    struct hnode *left;
    struct hnode *right;
    struct hnode *parent;
}Node;

void swapValues(Node **p1, Node **p2, int sizep1, int sizep2);
void printGivenLevel(Node* root, int level, int k, int *num);
void printLevelOrder(Node* root, int k);


int bal(Node *r);
int height(Node *r);
void insert(Node **root, int count, char* value, Node *parent);
void FixInsert(Node *node);
int check(Node *r);
void DeleteMaxHeap(Node *p);

#endif //COVID_19_MAXHEAP_H
