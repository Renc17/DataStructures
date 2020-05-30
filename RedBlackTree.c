#include "RedBlackTree.h"
#include "patientRecords.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


RBT* init(){
    RBT* tnill = malloc(sizeof(struct RBTnode));
    tnill -> patientNode = NULL;
    tnill -> color = 0;
    tnill -> left = tnill -> right = tnill -> parent = NULL;
    return tnill;
}

void deleteTNILL(RBT* tn){
    free(tn);
}

void LeftRotate(RBT **root,RBT* x, RBT* tn){
    RBT* y = x->right;
    x->right = y->left;
    if(y->left != tn){
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent ==  tn){
        *root = y;
    }else if(x == x->parent->left){
        x->parent->left = y;
    }else{
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}


void rightRotate(RBT **root,RBT* x, RBT* tn){
    RBT* y = x->left;
    x->left = y->right;
    if(y->right != tn){
        y->right->parent = x;
    }
    y->parent = x->parent;
    if(x->parent ==  tn){
        *root = y;
    }else if(x == x->parent->right){
        x->parent->right = y;
    }else{
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void insertFixUp(RBT **root,RBT* z, RBT* tn){

    while (z != *root && z != (*root)->left && z != (*root)->right && z->parent->color == 1)
    {
        RBT* y;

        // Find uncle and store uncle in y
        if (z->parent != tn && z->parent == z->parent->parent->left)
            y = z->parent->parent->right;
        else
            y = z->parent->parent->left;

        // If uncle is RED, do following
        // (i)  Change color of parent and uncle as BLACK
        // (ii) Change color of grandparent as RED
        // (iii) Move z to grandparent
        if (y->color == 1)
        {
            y->color = 0;
            z->parent->color = 0;
            z->parent->parent->color = 1;
            z = z->parent->parent;
        }

            // Uncle is BLACK, there are four cases (LL, LR, RL and RR)
        else
        {
            // Left-Left (LL) case, do following
            // (i)  Swap color of parent and grandparent
            // (ii) Right Rotate Grandparent
            if (z->parent != tn && z->parent == z->parent->parent->left &&
                z == z->parent->left)
            {
                int ch = z->parent->color ;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                rightRotate(root,z->parent->parent,tn);
            }

            // Left-Right (LR) case, do following
            // (i)  Swap color of current node  and grandparent
            // (iii) Right Rotate Grand Parent
            if (z->parent != tn && z->parent == z->parent->parent->left &&
                z == z->parent->right)
            {
                int ch = z->color ;
                z->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                rightRotate(root,z->parent->parent, tn);
            }

            // Right-Right (RR) case, do following
            // (i)  Swap color of parent and grandparent
            // (ii) Left Rotate Grandparent
            if (z->parent != tn &&
                z->parent == z->parent->parent->right &&
                z == z->parent->right)
            {
                int ch = z->parent->color ;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                LeftRotate(root,z->parent->parent, tn);
            }

            // Right-Left (RL) case, do following
            // (i)  Swap color of current node  and grandparent
            // (ii) Right Rotate Parent
            // (iii) Left Rotate Grand Parent
            if (z->parent != tn && z->parent == z->parent->parent->right &&
                z == z->parent->left)
            {
                int ch = z->color ;
                z->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                rightRotate(root,z->parent, tn);
                LeftRotate(root,z->parent, tn);
            }
        }
    }
    (*root)->color = 0; //keep root always black
}

void insert_RBT(RBT **root, RBT** tn, patientRecord* p){
    // Allocate memory for new node
    RBT* z = malloc(sizeof(struct RBTnode));
    z->patientNode = p;
    z->entryDate = p->entryDate;
    z->color = 1;
    z->left = z->right = z->parent = *tn;

    RBT* y = *tn;
    RBT* x = *root;
    while(x != *tn){
        y = x;
        if(compareDate(&(y->entryDate), &(p->entryDate)) <= 0){
            x = x->left;
        }else{
            x = x->right;
        }
    }

    z->parent = y;
    if(y == *tn){
        *root = z;
    }
    else if(compareDate(&(y->entryDate), &(p->entryDate)) < 0) {
        y->left = z;
    }else
        y->right = z;

    z->left = *tn;
    z->right = *tn;
    z->color = 1;

    insertFixUp(root, z, *tn);
}

int compareDate(Date* date1, Date* date2){
    if(date1->year == date2->year){
        if(date1->month == date2->month){
            if(date1->day == date2->day){
                return 0;
            } else if(date1->day > date2->day){
                return 1;
            }else{
                return -1;
            }
        } else if(date1->month > date2->month){
            return 1;
        }else {
            return -1;
        }
    } else if(date1->year > date2->year){
        return 1;
    }else {
        return -1;
    }
}

void DeleteRBTTree(RBT* node ,RBT* tn){
    if (node == tn){
        return;
    }

    DeleteRBTTree(node->left, tn);
    DeleteRBTTree(node->right, tn);

    free(node);
}


void print(RBT* root, RBT* tn){
    if(root == tn){
        return;
    }
    print(root->left, tn);
    printf("%d %d %d %d %s\n",root->entryDate.day, root->entryDate.month, root->entryDate.year, root->patientNode->recordId, root->patientNode->name);
    print(root->right, tn);
}

void countCurrentPatientsRBT(RBT* root, RBT* tn, int *count){
    if(root == tn){
        return;
    }

    if((strcmp(root->patientNode->exitDate, "-") == 0)){
        (*count)++;
    }
    countCurrentPatientsRBT(root->left, tn ,count);
    countCurrentPatientsRBT(root->right, tn,  count);
}

Date convert(char *date){   //convert date from char to int and store it into a Date struct
    char* token;
    char skip[2] = "-";

    char* d = malloc(sizeof(char)*strlen(date)+1);
    strcpy(d, date);
    token = strtok(d, "\n");
    Date ed;
    token = strtok(token, skip);
    ed.day = atoi(token);
    token = strtok(NULL, skip);
    ed.month = atoi(token);
    token = strtok(NULL, skip);
    ed.year = atoi(token);

    free(d);
    return ed;
}

void countPatientsRBTByCountry(RBT* root, RBT* tn, int *count, char* date1, char* date2, char* country){
    if(root == tn){
        return;
    }

    if(date1 != NULL && date2 != NULL && country == NULL) {
        Date d1 = convert(date1);
        Date d2 = convert(date2);
        if (compareDate(&(root->entryDate), &d1) >= 0 && compareDate(&(root->entryDate), &d2) <= 0) {
            (*count)++;
           // printf("%s %s\n", root->patientNode->entryDate, root->patientNode->exitDate);
        }
    }else if(date1 == NULL && date2 == NULL){
        (*count)++;
    }else if(date1 != NULL && date2 != NULL) {
        Date d1 = convert(date1);
        Date d2 = convert(date2);
        if (compareDate(&(root->entryDate), &d1) >= 0 && (compareDate(&(root->entryDate), &d2) <= 0) &&
            (strcmp(root->patientNode->country, country) == 0)) {
            (*count)++;
        }
    }

    countPatientsRBTByCountry(root->left, tn ,count, date1, date2, country);
    countPatientsRBTByCountry(root->right, tn,  count, date1, date2, country);
}

void countPatientsRBTByDisease(RBT* root, RBT* tn, int *count, char* date1, char* date2, char* virus){
    if(root == tn){
        return;
    }

    if(date1 == NULL && date2 == NULL){
        if ((strcmp(root->patientNode->disease, virus) == 0)) {
            (*count)++;
        }
    }else if(date1 != NULL && date2 != NULL) {
        Date d1 = convert(date1);
        Date d2 = convert(date2);
        if (compareDate(&(root->entryDate), &d1) >= 0 && (compareDate(&(root->entryDate), &d2) <= 0) &&
            (strcmp(root->patientNode->disease, virus) == 0)) {
            (*count)++;
        }
    }

    countPatientsRBTByDisease(root->left, tn ,count, date1, date2, virus);
    countPatientsRBTByDisease(root->right, tn,  count, date1, date2, virus);
}

void countCountryRBT(RBT* root, RBT* tn, int *count, char* date1, char* date2, char* country){
    if(root == tn){
        return;
    }

    if(date1 == NULL && date2 == NULL){
        if ((strcmp(root->patientNode->country, country) == 0)) {
            (*count)++;
        }
    }else if(date1 != NULL && date2 != NULL) {
        Date d1 = convert(date1);
        Date d2 = convert(date2);
        if (compareDate(&(root->entryDate), &d1) >= 0 && (compareDate(&(root->entryDate), &d2) <= 0) &&
            (strcmp(root->patientNode->country, country) == 0)) {
            (*count)++;
        }
    }

    countCountryRBT(root->left, tn ,count, date1, date2, country);
    countCountryRBT(root->right, tn,  count, date1, date2, country);
}
