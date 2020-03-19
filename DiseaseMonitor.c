#include "DiseaseMonitor.h"
#include "BinaryTree.h"
#include "hashTable.h"
#include "RedBlackTree.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void globalDiseaseStats(HashTable *h, int entries, char *date1, char* date2, char* country, char* virus){
    allDiseases(h, entries, date1, date2, country, virus);
}
void topkDiseases(HashTable *h, int entries, char *date1, char* date2, char* country, int k){
    allCountriesByDisease(h, entries, date1, date2, country, k);
}

void topkCountries(HashTable *h, int entries, char *date1, char* date2, char* virus, int k){
    allDiseasesByCountry(h, entries, date1, date2, virus, k);
}

void insertPatientRecord(patientNode **Root, HashTable **DiseasehashTable, int DiseaseHTCapacity, int bucketsize, int recordId, char* Name, char* SurName, char* diseaseID, char *country, char *entryDate, char *exitDate){
    patientRecord* patient = initialize();

    set_id(patient, recordId);

    patient->name = malloc(sizeof(char)*strlen(Name)+1);
    set_name(patient, Name);

    patient->surname = malloc(sizeof(char)*strlen(SurName)+1);
    set_surname(patient, SurName);

    patient->disease = malloc(sizeof(char)*strlen(diseaseID)+1);
    set_disease(patient, diseaseID);

    patient->country = malloc(sizeof(char)*strlen(country)+1);
    set_country(patient, country);

    set_entryDate(patient, entryDate);

    patient->exitDate = malloc(sizeof(char)*strlen(exitDate)+1);
    set_exitDate(patient, exitDate);

    NewPatient(Root, patient);
    insertPatientHT(*DiseasehashTable, get_disease(patient), DiseaseHTCapacity, bucketsize, patient);
}

void recordPatientExit(patientNode* root, int recordId, char* exitDate) {
    patientNode *temp = root;
    temp = FindPatient(temp, recordId);
    if(temp == NULL){
        printf("ERROR : Patient with recordId %d does not exist in records\n", recordId);
        return;
    }
    if (strcmp(get_exitDate(temp->patient), "-") == 0) {
        set_exitDate(temp->patient, exitDate);
        printf("Update : Patient %s is out\n", get_name(temp->patient));
    }else{
        printf("Patient has already an exitDate\n");
    }
}

void numCurrentPatients(patientNode *root, HashTable *DiseasehashTable, int entries, char *disease){
    int count = 0;
    if(disease != NULL){
        Value valueptr = FindPatientHTDisease(DiseasehashTable, entries, disease);
        if(valueptr.name == NULL){
            printf("ERROR : %s disease does not exist in records\n", disease);
            return;
        }
        RBT *temp = valueptr.RBTptr;
        countCurrentPatientsRBT(temp, valueptr.TNILL, &count);
    }else{
        patientNode *temp = root;
        countPatients(temp, NULL, &count);
    }
    printf("Current number of patients : %d\n", count);
}

void Exit(patientNode **Root, HashTable *hashTable, int entries, HashTable *CountryhashTable, int countryEntries){
    Delete_Tree(*Root);
    DestroyHashTable(hashTable, entries);
    DestroyHashTable(CountryhashTable, countryEntries);
}