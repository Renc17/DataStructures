#include "BinaryTree.h"
#include "patientRecords.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void NewPatient(patientNode **root, patientRecord* patient){

    if(*root == NULL){
        patientNode* node = malloc(sizeof(patientNode));
        node->patient = patient;
        node->left = NULL;
        node->right = NULL;
        *root = node;
        return;
    } else if((*root)->patient->recordId > patient->recordId){
        NewPatient(&(*root)->left, patient);
    } else if((*root)->patient->recordId <= patient->recordId){
        NewPatient(&(*root)->right, patient);
    } else{
        printf("Patient %s %s is already in database\n", patient->name, patient->surname);
    }
}

void Delete_Tree(patientNode *p){
    if(p == NULL)
        return;

    Delete_Tree(p->left);
    Delete_Tree(p->right);

    delete_patient(p->patient);
    free(p);
}

void Print_Tree(patientNode *p){
    if(p == NULL)
        return;

    printf("%d %s\n", p->patient->recordId, p->patient->name);
    Print_Tree(p->left);
    Print_Tree(p->right);

}

patientNode* FindPatient(patientNode *p, int recordId) {
    if(p == NULL){
        return NULL;
    } else if(p->patient->recordId > recordId){
        return FindPatient(p->left, recordId);
    } else if(p->patient->recordId < recordId){
        return FindPatient(p->right, recordId);
    }else if(p->patient->recordId ==  recordId){
        return p;
    }
}

void countPatients(patientNode *p, char *option, int *count){
    if(p == NULL){
        return;
    }
    if(strcmp(p->patient->exitDate, "-") == 0){
        (*count)++;
    }
    countPatients(p->right, option, count);
    countPatients(p->left, option, count);
}
