#ifndef COVID_19_REDBLACKTREE_H
#define COVID_19_REDBLACKTREE_H

#include "patientRecords.h"
#include <time.h>

typedef struct RBTnode
{
    patientRecord *patientNode;
    struct tm entryDate;
    int color;
    struct RBTnode *left, *right, *parent;
}RBT;

RBT* init();
void LeftRotate(RBT **root,RBT* x, RBT* tn);
void rightRotate(RBT **root,RBT* x, RBT* tn);
void insertFixUp(RBT **root,RBT* z, RBT* tn);
void insert_RBT(RBT **root, RBT** tn, patientRecord* p);
void _deleteTree(RBT* node ,RBT* tn);
void print(RBT* root, RBT* tn);
void deleteTNILL(RBT* tn);
void countCurrentPatientsRBT(RBT* root, RBT* tn, int *count);
void countPatientsRBTByCountry(RBT* root, RBT* tn, int *count, char* date1, char* date2, char* country);
void countPatientsRBTByDisease(RBT* root, RBT* tn, int *count, char* date1, char* date2, char* virus);
void countCountryRBT(RBT* root, RBT* tn, int *count, char* date1, char* date2, char* country);

#endif //COVID_19_REDBLACKTREE_H
