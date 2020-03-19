#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashTable.h"
#include "BinaryTree.h"
#include "patientRecords.h"
#include "DiseaseMonitor.h"


void Init(char* PatientFile, patientNode **Root, HashTable **DiseasehashTable, int DiseaseHTCapacity, HashTable **CountryhashTable, int CountryHTCapacity, int bucketsize);
void Options(char *patientFile, int DiseaseHTCapacity, int CountryHTCapacity, int bucketsize);

int main(int argc, char** argv){

    char *patientRecordsFile = NULL;
    int diseaseHashtableNumOfEntries = 50;
    int countryHashtableNumOfEntries = 50;
    int bucketSize = 40;

    int i=0;
    while(argv[i] != NULL && strcmp(argv[i], "-p") != 0){
        i++;
    }
    patientRecordsFile = argv[i+1];

    i = 0;
    while(argv[i] != NULL && strcmp(argv[i], "-h1") != 0){
        i++;
    }
    diseaseHashtableNumOfEntries = atoi(argv[i+1]);

    i = 0;
    while(argv[i] != NULL && strcmp(argv[i], "-h2") != 0){
        i++;
    }
    countryHashtableNumOfEntries = atoi(argv[i+1]);

    i = 0;
    while(argv[i] != NULL && strcmp(argv[i], "-b") != 0){
        i++;
    }
    bucketSize = atoi(argv[i+1]);

    diseaseHashtableNumOfEntries = 50;
    countryHashtableNumOfEntries = 50;
    bucketSize = 40;

    Options(patientRecordsFile, diseaseHashtableNumOfEntries, countryHashtableNumOfEntries, bucketSize);
}

void Options(char *patientFile, int DiseaseHTCapacity, int CountryHTCapacity, int bucketsize) {

    patientNode* Root = NULL;
    HashTable *DiseasehashTable = NULL;
    HashTable *CountryhashTable = NULL;

    Init(patientFile, &Root, &DiseasehashTable, DiseaseHTCapacity, &CountryhashTable, CountryHTCapacity, bucketsize);

    const char skip[2] = " ";
    char *token;
    char *buffer;
    size_t bufsize = 150;
    buffer = malloc(sizeof(char) * bufsize);

    while (1) {
        printf("> ");
        getline(&buffer, &bufsize, stdin);
        strtok(buffer, "\n");
        token = strtok(buffer, skip);
        if (strcmp(token, "globalDiseaseStats") == 0) {
            token = strtok(NULL, skip);
            if (token != NULL) {
                char *date1 = malloc(sizeof(char)*strlen(token)+1);
                char *date2 = malloc(sizeof(char)*strlen(token)+1);
                strcpy(date1, token);
                token = strtok(NULL, skip);
                if (token != NULL) {
                    strcpy(date2, token);
                } else{
                    free(date1);
                    free(date2);
                    printf("Input Error : Two dates must be entered\n");
                    continue;
                }
                globalDiseaseStats(DiseasehashTable, DiseaseHTCapacity, date1, date2, NULL, NULL);
                free(date1);
                free(date2);
            }else{
                globalDiseaseStats(DiseasehashTable, DiseaseHTCapacity, NULL, NULL, NULL, NULL);
            }
            continue;
        }else if (strcmp(token, "diseaseFrequency") == 0) {
            token = strtok(NULL, skip);
            if (token == NULL) {
                printf("Input Error : Disease Name must be entered\n");
                continue;
            }
            char *virusName = malloc(strlen(token) + 1);
            strcpy(virusName, token);

            token = strtok(NULL, skip);
            if (token == NULL) {
                printf("Input Error : Entry Date must be entered\n");
                free(virusName);
                continue;
            }
            char *date1 = malloc(sizeof(char)*strlen(token)+1);
            strcpy(date1, token);

            token = strtok(NULL, skip);
            if (token == NULL) {
                printf("Input Error : Entry Date must be entered\n");
                free(virusName);
                free(date1);
                continue;
            }
            char *date2 = malloc(sizeof(char)*strlen(token)+1);
            strcpy(date2, token);

            token = strtok(NULL, skip);
            if (token != NULL) {
                char *country = malloc(sizeof(char)*strlen(token)+1);
                strcpy(country, token);
                globalDiseaseStats(DiseasehashTable, DiseaseHTCapacity, date1, date2, country, virusName);
                free(country);
                free(virusName);
                free(date1);
                free(date2);
                continue;
            }else{
                globalDiseaseStats(DiseasehashTable, DiseaseHTCapacity, date1, date2, NULL, virusName);
                free(virusName);
                free(date1);
                free(date2);
                continue;
            }
        } else if (strcmp(token, "topkDiseases") == 0) {
            token = strtok(NULL, skip);
            if (token == NULL) {
                printf("Input Error : Enter rank number\n");
                continue;
            }
            int k = atoi(token) ;

            token = strtok(NULL, skip);
            if (token == NULL) {
                printf("Input Error : Enter Country\n");
                continue;
            }
            char *country = malloc(sizeof(char)*strlen(token)+1);
            strcpy(country, token);

            token = strtok(NULL, skip);
            if (token != NULL) {
                char *date1 = malloc(sizeof(char)*strlen(token)+1);
                strcpy(date1, token);
                token = strtok(NULL, skip);
                if (token == NULL) {
                    printf("Input Error : Two dates must be entered\n");
                    free(date1);
                    free(country);
                    continue;
                }
                char *date2 = malloc(sizeof(char)*strlen(token)+1);
                strcpy(date2, token);
                topkDiseases(DiseasehashTable, DiseaseHTCapacity, date1, date2, country, k);
                free(date1);
                free(date2);
                free(country);
                continue;
            }
            topkDiseases(DiseasehashTable, DiseaseHTCapacity, NULL, NULL, country, k);
            free(country);
            continue;
        }else if (strcmp(token, "topkCountries") == 0) {
            token = strtok(NULL, skip);
            if (token == NULL) {
                printf("Input Error : Enter rank number\n");
                continue;
            }
            int k = atoi(token) ;

            token = strtok(NULL, skip);
            if (token == NULL) {
                printf("Input Error : Enter Country\n");
                continue;
            }
            char *disease = malloc(sizeof(char)*strlen(token)+1);
            strcpy(disease, token);

            token = strtok(NULL, skip);
            if (token != NULL) {
                char *date1 = malloc(sizeof(char)*strlen(token)+1);
                strcpy(date1, token);
                token = strtok(NULL, skip);
                if (token == NULL) {
                    printf("Input Error : Two dates must be entered\n");
                    free(date1);
                    free(disease);
                    continue;
                }
                char *date2 = malloc(sizeof(char)*strlen(token)+1);
                strcpy(date2, token);
                topkCountries(CountryhashTable, CountryHTCapacity,date1, date2, disease, k);

                free(date1);
                free(date2);
                free(disease);
                continue;
            }
            topkCountries(CountryhashTable, CountryHTCapacity,NULL, NULL, disease, k);
            free(disease);
            continue;
        }else if (strcmp(token, "insertPatientRecord") == 0) {
            token = strtok(NULL, skip);
            if (token == NULL) {
                printf("Input Error : RecordId must be entered\n");
                continue;
            }
            int recordId = atoi(token);

            token = strtok(NULL, skip);
            if (token == NULL) {
                printf("Input Error : patientFirstName must be entered\n");
                continue;
            }
            char *Name = malloc(sizeof(char)*strlen(token)+1);
            strcpy(Name, token);

            token = strtok(NULL, skip);
            if (token == NULL) {
                printf("Input Error : patientLastName must be entered\n");
                free(Name);
                continue;
            }
            char *SurName = malloc(sizeof(char)*strlen(token)+1);
            strcpy(SurName, token);

            token = strtok(NULL, skip);
            if (token == NULL) {
                printf("Input Error : diseaseID must be entered\n");
                free(Name);
                free(SurName);
                continue;
            }
            char *diseaseID = malloc(sizeof(char)*strlen(token)+1);
            strcpy(diseaseID, token);

            token = strtok(NULL, skip);
            if (token == NULL) {
                printf("Input Error : country must be entered\n");
                free(Name);
                free(SurName);
                free(diseaseID);
                continue;
            }
            char *country = malloc(sizeof(char)*strlen(token)+1);
            strcpy(country, token);

            token = strtok(NULL, skip);
            if (token == NULL) {
                printf("Input Error : entryDate must be entered\n");
                free(Name);
                free(SurName);
                free(diseaseID);
                free(country);
                continue;
            }
            char *entryDate = malloc(sizeof(char)*strlen(token)+1);
            strcpy(entryDate, token);

            token = strtok(NULL, skip);
            char *exitDate = malloc(sizeof(char)*strlen(token)+1);
            if (token == NULL) {
                strcpy(exitDate, "-");
            }else{
                strcpy(exitDate, token);
            }

            insertPatientRecord(&Root, &DiseasehashTable, DiseaseHTCapacity, bucketsize, recordId, Name, SurName, diseaseID, country, entryDate, exitDate);

            free(Name);
            free(SurName);
            free(diseaseID);
            free(country);
            free(entryDate);
            free(exitDate);
            continue;
        }else if (strcmp(token, "recordPatientExit") == 0) {
            token = strtok(NULL, skip);
            if (token == NULL) {
                printf("Input Error : RecordId must be entered\n");
                continue;
            }
            int recordId = atoi(token);

            token = strtok(NULL, skip);
            if (token == NULL) {
                printf("Input Error : Exit date must be entered\n");
                continue;
            }
            char *exitDate = malloc(sizeof(char)*strlen(token)+1);
            strcpy(exitDate, token);

            recordPatientExit(Root, recordId, exitDate);

            free(exitDate);
            continue;
        }else if (strcmp(token, "numCurrentPatients") == 0) {
            token = strtok(NULL, skip);

            if (token == NULL) {
                numCurrentPatients(Root, DiseasehashTable, DiseaseHTCapacity, NULL);
                continue;
            }else{
                char *disease = malloc(sizeof(char)*strlen(token)+1);
                strcpy(disease, token);

                numCurrentPatients(Root, DiseasehashTable, DiseaseHTCapacity, disease);
                free(disease);
                continue;
            }
        }else if (strcmp(token, "Exit") == 0) {
            Exit(&Root, DiseasehashTable, DiseaseHTCapacity, CountryhashTable, CountryHTCapacity);
            free(buffer);
            return;
        }
    }
}


void Init(char* PatientFile, patientNode **Root, HashTable **DiseasehashTable, int DiseaseHTCapacity, HashTable **CountryhashTable, int CountryHTCapacity, int bucketsize) {
    FILE *fd = fopen(PatientFile, "r");
    size_t bufsize = 200;
    char* token;
    char skip[2] = " ";
    char *buffer = malloc(sizeof(char)*bufsize);

    *DiseasehashTable = InitHashTable(DiseaseHTCapacity);
    *CountryhashTable = InitHashTable(CountryHTCapacity);

    while (getline(&buffer, &bufsize, fd) != -1) {
        patientRecord* patient = initialize();

        strtok(buffer,"\n");
        token=strtok(buffer,skip);
        set_id(patient, atoi(token));

        token=strtok(NULL,skip);
        patient->name = malloc(sizeof(char)*strlen(token)+1);
        set_name(patient, token);

        token=strtok(NULL,skip);
        patient->surname = malloc(sizeof(char)*strlen(token)+1);
        set_surname(patient, token);

        token=strtok(NULL,skip);
        patient->disease = malloc(sizeof(char)*strlen(token)+1);
        set_disease(patient, token);

        token=strtok(NULL,skip);
        patient->country = malloc(sizeof(char)*strlen(token)+1);
        set_country(patient, token);

        token=strtok(NULL,skip);
        char* date = malloc(sizeof(char)* strlen(token)+1);
        strcpy(date, token);

        token=strtok(NULL,skip);
        patient->exitDate = malloc(sizeof(char)*strlen(token)+1);
        set_exitDate(patient, token);

        set_entryDate(patient, date);
        free(date);

        NewPatient(Root, patient);
        insertPatientHT(*DiseasehashTable, get_disease(patient), DiseaseHTCapacity, bucketsize, patient);
        insertPatientHT(*CountryhashTable, get_country(patient), CountryHTCapacity, bucketsize, patient);
    }
    free(buffer);
    fclose(fd);

    printHashTable(*DiseasehashTable, DiseaseHTCapacity);
    printHashTable(*CountryhashTable, CountryHTCapacity);
    //Print_Tree(*Root);
}
