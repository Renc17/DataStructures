#ifndef _DISEASEMONITOR_H
#define _DISEASEMONITOR_H

#include "BinaryTree.h"
#include "hashTable.h"

void globalDiseaseStats(HashTable *h, int entries, char *date1, char* date2, char* country, char* virus);
void topkDiseases(HashTable *h, int entries, char *date1, char* date2, char* country, int k);
void topkCountries(HashTable *h, int entries, char *date1, char* date2, char* virus, int k);
void insertPatientRecord(patientNode **Root, HashTable **DiseasehashTable, int DiseaseHTCapacity, HashTable **CountryhashTable, int CountryHTCapacity, int bucketsize, int recordId, char* Name, char* SurName, char* diseaseID, char *country, char *entryDate, char *exitDate);
void recordPatientExit(patientNode *root, int recordId, char *exitDate);
void numCurrentPatients(patientNode *root, HashTable *DiseasehashTable, int entries, char *disease);
void Exit(patientNode **Root, HashTable *hashTable, int entries, HashTable *CountryhashTable, int countryEntries);


#endif
