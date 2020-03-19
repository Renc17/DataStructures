#ifndef COVID_19_HASHTABLE_H
#define COVID_19_HASHTABLE_H

#include "RedBlackTree.h"

typedef struct {
    char* name;
    RBT* RBTptr;
    RBT* TNILL;
}Value;

typedef struct Bucket{
    int size;
    int count;
    Value* value;
    struct Bucket *nextBacket;
}Bucket;

typedef struct HashTable{
    Bucket *buckets;
    Bucket *currentBucket;
}HashTable;


HashTable *InitHashTable(int numOfEntries);
int hashFunc(char* hashValue,int entries);
Bucket* newbucket(int size, char* hashValue, patientRecord* patient);
void insertPatientHT(HashTable *h, char* hashValue, int entries, int size, patientRecord *patient);
void printHashTable(HashTable* h, int entries);
void DestroyHashTable(HashTable* h, int entries);
Value FindPatientHTDisease(HashTable* h, int entries, char* disease);
void allDiseases(HashTable *h, int entries, char *date1, char* date2, char* country, char* virus);
void allDiseasesByCountry(HashTable *h, int entries, char *date1, char* date2, char* virus, int k);
void allCountriesByDisease(HashTable *h, int entries, char *date1, char* date2, char* country, int k);

#endif //COVID_19_HASHTABLE_H
