#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include "patientRecords.h"

typedef struct node{
    patientRecord *patient;
    struct node *left;
    struct node *right;
}patientNode;

void NewPatient(patientNode **root, patientRecord* patient);
void Print_Tree(patientNode *p);
patientNode* FindPatient(patientNode *p, int recordId);
void countPatients(patientNode *p, char *option, int *count);
void Delete_Tree(patientNode *p);


#endif
