#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashTable.h"
#include "BinaryTree.h"
#include "MaxHeap.h"

HashTable *InitHashTable(int numOfEntries){
    HashTable* hashTable = malloc(numOfEntries* sizeof(HashTable));
    for (int i = 0; i < numOfEntries; ++i) {
        hashTable[i].buckets = NULL;
        hashTable[i].currentBucket = NULL;
    }
    return hashTable;
}

int hashFunc(char* hashValue,int entries){
    int hash = 0;
    int c;
    while (c = *hashValue++){
        hash += c;
    }
    return hash%entries;
}

void insertPatientHT(HashTable *h, char* hashValue, int entries, int size, patientRecord *patient){
    int key = hashFunc(hashValue, entries);
    if(h[key].buckets == NULL){
        h[key].buckets = newbucket(size, hashValue, patient);
        h[key].currentBucket = h[key].buckets;
    }else{
        int flag = 0;
        for (int i = 0; i < (size / sizeof(Value)); ++i) {
            if(h[key].currentBucket->value[i].name != NULL) {
                if (strcmp(h[key].currentBucket->value[i].name, hashValue) == 0) {
                    insert_RBT(&h[key].currentBucket->value[i].RBTptr, &h[key].currentBucket->value[i].TNILL, patient);
                    flag = 1;
                    break;
                }
            }
        }

        if(flag == 0){
            for (int j = 0; j < (size / sizeof(Value)); ++j) {
                if (h[key].currentBucket->count != (size / sizeof(Value))) {
                    if (h[key].currentBucket->value[j].name == NULL) {
                        h[key].currentBucket->value[j].name = malloc(sizeof(char) * strlen(hashValue) + 1);
                        strcpy(h[key].currentBucket->value[j].name, hashValue);
                        h[key].currentBucket->value[j].TNILL = init();
                        h[key].currentBucket->value[j].RBTptr = h[key].currentBucket->value[j].TNILL;
                        insert_RBT(&h[key].currentBucket->value[j].RBTptr, &h[key].currentBucket->value[j].TNILL, patient);
                        h[key].currentBucket->count++;
                    }
                } else {
                    h[key].currentBucket->nextBacket = newbucket(size, hashValue, patient);
                    h[key].currentBucket = h[key].currentBucket->nextBacket;
                }
            }
        }
    }
}

Bucket *newbucket(int size, char* hashValue, patientRecord *patient){
    Bucket *bucketptr = malloc(sizeof(Bucket));
    bucketptr->nextBacket = NULL;
    bucketptr->size = size;
    bucketptr->count = 0;
    bucketptr->value = malloc(sizeof(Value)* (size/ sizeof(Value)));

    for (int i = 0; i < (size/ sizeof(Value)); ++i) {
        bucketptr->value[i].name = NULL;
    }

    bucketptr->value[0].name = malloc(sizeof(char)*strlen(hashValue)+1);
    strcpy(bucketptr->value[0].name, hashValue);
    bucketptr->value[0].TNILL = init();
    bucketptr->value[0].RBTptr = bucketptr->value[0].TNILL;

    insert_RBT(&bucketptr->value[0].RBTptr, &bucketptr->value[0].TNILL, patient);

    return bucketptr;
}

void printHashTable(HashTable* h, int entries){
    for (int i = 0; i < entries; ++i) {
        if(h[i].buckets != NULL){
            h[i].currentBucket = h[i].buckets;
            do{
                printf("Backets %d : ", i);
                for (int j = 0; j < (h[i].currentBucket->size / sizeof(Value)); ++j) {
                    if (h[i].currentBucket->value[j].name != NULL){
                        printf("%s\t", h[i].currentBucket->value[j].name);
                        printf("\nENTRY-DATE ID NAME\n");
                        print(h[i].currentBucket->value[j].RBTptr, h[i].currentBucket->value[j].TNILL);
                    }
                    printf("\n");
                }
                h[i].currentBucket = h[i].currentBucket->nextBacket;
            }while (h[i].currentBucket != NULL);
        }
    }
}

void DestroyHashTable(HashTable* h, int entries){
    for (int i = 0; i < entries; ++i) {
        if(h[i].buckets != NULL){
            h[i].currentBucket = h[i].buckets;
            do{
                for (int j = 0; j < (h[i].currentBucket->size / sizeof(Value)); ++j) {
                    if (h[i].currentBucket->value[j].name != NULL){
                        free(h[i].currentBucket->value[j].name);
                        DeleteRBTTree(h[i].currentBucket->value[j].RBTptr,h[i].currentBucket->value[j].TNILL);
                        deleteTNILL(h[i].currentBucket->value[j].TNILL);
                    }
                }
                h[i].currentBucket = h[i].currentBucket->nextBacket;
                free(h[i].buckets->value);
                free(h[i].buckets);
            }while (h[i].currentBucket != NULL);
        }
    }
    free(h);
}

Value FindPatientHTDisease(HashTable* h, int entries, char* disease){
    int key = hashFunc(disease, entries);
    if(h[key].buckets != NULL){
        h[key].currentBucket = h[key].buckets;
        do{
            for (int j = 0; j < (h[key].currentBucket->size / sizeof(Value)); ++j) {
                if (strcmp(h[key].currentBucket->value[j].name, disease) == 0){
                    return h[key].currentBucket->value[j];
                }
            }
            h[key].currentBucket = h[key].currentBucket->nextBacket;
        }while (h[key].currentBucket != NULL);
    }
    Value null;
    null.name = NULL;
    return null;
}

void allDiseases(HashTable *h, int entries, char *date1, char* date2, char* country, char* virus){
    if(country == NULL && virus == NULL){ // globalDisease
        for (int i = 0; i < entries; ++i) {
            if (h[i].buckets != NULL) {
                h[i].currentBucket = h[i].buckets;
                do {
                    for (int j = 0; j < (h[i].currentBucket->size / sizeof(Value)); ++j) {
                        int count = 0;
                        if (h[i].currentBucket->value[j].name != NULL) {
                            printf("Number of patiants that have %s  : ", h[i].currentBucket->value[j].name);
                            countPatientsRBTByCountry(h[i].currentBucket->value[j].RBTptr, h[i].currentBucket->value[j].TNILL, &count, date1, date2, NULL);
                            printf("%d\n", count);
                        }
                        printf("\n");
                    }
                    h[i].currentBucket = h[i].currentBucket->nextBacket;
                } while (h[i].currentBucket != NULL);
            }
        }
    }else if(country != NULL && virus != NULL) { // diseaseFrequency
        int count = 0;
        Value valueptr = FindPatientHTDisease(h, entries, virus);
        if(valueptr.name == NULL){
            printf("ERROR : Disease %s can not be found in records\n", virus);
            return;
        }
        printf("Country : %s -> Number of patiants that have %s  : ", country, valueptr.name);
        countPatientsRBTByCountry(valueptr.RBTptr, valueptr.TNILL, &count, date1, date2, country);
        printf("%d\n", count);
        return;
    }else{  // diseaseFrequency
        int count = 0;
        Value valueptr = FindPatientHTDisease(h, entries, virus);
        if(valueptr.name == NULL){
            printf("ERROR : Disease %s can not be found in records\n", virus);
            return;
        }
        printf("Number of patiants that have %s  : ", virus);
        countPatientsRBTByCountry(valueptr.RBTptr, valueptr.TNILL,&count, date1, date2, NULL);
        printf("%d\n", count);
        return;
    }
}

void allDiseasesByCountry(HashTable *h, int entries, char *date1, char* date2, char* virus, int k){
    Node *Root = NULL;
    for (int i = 0; i < entries; ++i) {
        if (h[i].buckets != NULL) {
            h[i].currentBucket = h[i].buckets;
            do {
                for (int j = 0; j < (h[i].currentBucket->size / sizeof(Value)); ++j) {
                    int count = 0;
                    if (h[i].currentBucket->value[j].name != NULL) {
                        countPatientsRBTByDisease(h[i].currentBucket->value[j].RBTptr, h[i].currentBucket->value[j].TNILL, &count, date1, date2, virus);
                        insert(&Root, count, h[i].currentBucket->value[j].name, NULL);
                    }
                }
                h[i].currentBucket = h[i].currentBucket->nextBacket;
            } while (h[i].currentBucket != NULL);
        }
    }
    printLevelOrder(Root, k);
    DeleteMaxHeap(Root);
}

void allCountriesByDisease(HashTable *h, int entries, char *date1, char* date2, char* country, int k){
    Node *Root = NULL;
    for (int i = 0; i < entries; ++i) {
        if (h[i].buckets != NULL) {
            h[i].currentBucket = h[i].buckets;
            do {
                for (int j = 0; j < (h[i].currentBucket->size / sizeof(Value)); ++j) {
                    int count = 0;
                    if (h[i].currentBucket->value[j].name != NULL) {
                        countCountryRBT(h[i].currentBucket->value[j].RBTptr, h[i].currentBucket->value[j].TNILL, &count, date1, date2, country);
                        insert(&Root, count, h[i].currentBucket->value[j].name, NULL);
                    }
                }
                h[i].currentBucket = h[i].currentBucket->nextBacket;
            } while (h[i].currentBucket != NULL);
        }
    }
    printLevelOrder(Root, k);
    DeleteMaxHeap(Root);
}
