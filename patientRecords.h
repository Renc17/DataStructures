#ifndef COVID_19_PATIENTRECORDS_H
#define COVID_19_PATIENTRECORDS_H

#include <time.h>

typedef struct {
    int day;
    int month;
    int year;
}Date;

typedef struct patient{
    int recordId;
    char *name;
    char *surname;
    char *disease;
    char *country;
    Date entryDate;
    char *exitDate;
}patientRecord;

patientRecord* initialize();

void set_id(patientRecord* v, int id);
void set_name(patientRecord* v, char* n);
void set_surname(patientRecord* v, char* sn);
void set_disease(patientRecord* v, char* dis);
void set_country(patientRecord* v, char* co);
void set_entryDate(patientRecord* v, char* ed);
void set_exitDate(patientRecord* v, char* ed);

int get_id(patientRecord* v);
char* get_name(patientRecord* v);
char* get_surname(patientRecord* v);
char* get_country(patientRecord* v);
char* get_disease(patientRecord* v);
Date get_entryDate(patientRecord* v);
char* get_exitDate(patientRecord* v);

void delete_patient(patientRecord* v);

#endif //COVID_19_PATIENTRECORDS_H
