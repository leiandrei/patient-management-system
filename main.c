#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
        int age;
        char name[50];
        char gender[20];
} Demographics;

typedef struct {
        char status[50];
        char diagnosis[50];
} Medical;

typedef struct {
        int id;
        Demographics demo;
        Medical info;
} Database;

void menu();
Database *get_input(Database *records, int *n, int *j);
void search_update(Database *records, int n);
void update_status(Database *record);
void print_to_file(FILE *fptr, Database *records, int n);
void read_file(FILE *fptr, Database *records, int n);

int main() {

    FILE *fptr = fopen("patients.txt", "a+");
    
    if (!fptr) {
       printf("File Opening Failed.\n");
       return 1;
    }
    
    int num = 3, i = 0;
    
    Database *records = malloc(num * sizeof(Database));
    
    if (!records) {
       printf("Memory Allocation Failed.\n");
       return 1;
    }
    
    while(1) {
    
    int choice;
    menu();
    scanf("%d", &choice);
    getchar();
    
              switch(choice) {
              
                             case 1: records = get_input(records, &num, &i); break;
                             case 2: search_update(records, i); break;
                             case 3: read_file(fptr, records, i); break;
                             case 4: printf("\nExiting The Program.\n\n"); free(records); fclose(fptr); return 0;
                             default: printf("\nInvalid Input.\n\n"); break;
              
              }
    
    }

    return 0;
}

void menu() {
     printf("=== PATIENT MANAGEMENT SYSTEM ===\n");
     printf("[1] - ADD PATIENT\n");
     printf("[2] - SEARCH A PATIENT\n");
     printf("[3] - VIEW ALL PATIENT RECORDS\n");
     printf("[4] - EXIT THE PROGRAM\n\n");
     printf("ENTER YOUR CHOICE: ");
}

Database *get_input(Database *records, int *n, int *j) {

         if (*j >= *n) {
            *n += 5;
            Database *temp = realloc(records, (*n) * sizeof(Database));
            if (!temp) {
               printf("Memory Reallocation Failed.\n");
               free(records);
               return NULL;
            }
         }
         
         printf("\nENTER PATIENT INFORMATION\n");
         printf("Enter Patient ID: ");
         scanf("%d", &records[*j].id);
         
         printf("Enter Patient Age: ");
         scanf("%d", &records[*j].demo.age);
         
         getchar();
         
         printf("Enter Patient Name: ");
         fgets(records[*j].demo.name, sizeof(records[*j].demo.name), stdin);
         records[*j].demo.name[strcspn(records[*j].demo.name, "\n")] = 0;
         
         printf("Enter Patient Gender: ");
         fgets(records[*j].demo.gender, sizeof(records[*j].demo.gender), stdin);
         records[*j].demo.gender[strcspn(records[*j].demo.gender, "\n")] = 0;
         
         printf("Enter Patient Status: ");
         fgets(records[*j].info.status, sizeof(records[*j].info.status), stdin);
         records[*j].info.status[strcspn(records[*j].info.status, "\n")] = 0;

         printf("Enter Patient Diagnosis: ");
         fgets(records[*j].info.diagnosis, sizeof(records[*j].info.diagnosis), stdin);
         records[*j].info.diagnosis[strcspn(records[*j].info.diagnosis, "\n")] = 0;
         
         (*j)++;
         
         printf("\nPATIENT ADDED SUCCESSFULLY.\n\n");
         return records;
}

void search_update(Database *records, int n) {

     char search[50];
     int i, flag = 0;
     
     printf("\nEnter name to search for a patient: ");
     fgets(search, sizeof(search), stdin);
     search[strcspn(search, "\n")] = 0;
     
     for (i = 0; i < n; i++) {
         
         if (strstr(records[i].demo.name, search)) {
                 update_status(&records[i]);
                 flag = 1;
                 break; 
         }
     }
     
     if (!flag) {
        printf("\nPatient Not Found.\n\n");
     }
}

void update_status(Database *record) {

     char upd_status[50];

     printf("Update A Patient's Status: ");
     fgets(upd_status, sizeof(upd_status), stdin);
     upd_status[strcspn(upd_status, "\n")] = 0;
     
     strcpy(record->info.status, upd_status);
     
     printf("\nPatient Status Updated Successfully.\n\n");

}

void print_to_file(FILE *fptr, Database *records, int n) {
     
     int i;
     fprintf(fptr, "\nPatient Records:\n");
     
     for (i = 0; i < n; i++) {
     
         fprintf(fptr, "Patient #%d:\n", i + 1);
         fprintf(fptr, "Name: %s\n", records[i].demo.name);
         fprintf(fptr, "Age: %d\n", records[i].demo.age);
         fprintf(fptr, "Gender: %s\n", records[i].demo.gender);
         fprintf(fptr, "Patient ID: %d\n", records[i].id);
         fprintf(fptr, "Diagnosis: %s\n", records[i].info.diagnosis);
         fprintf(fptr, "Status: %s\n", records[i].info.status);
         fprintf(fptr, "-----------\n\n");
         
     }

     fflush(fptr);
}

void read_file(FILE *fptr, Database *records, int n) {

     fclose(fptr);
     
     fptr = fopen("patients.txt", "w");
     
     if (!fptr) {
        printf("File Opening Failed.\n");
        return; 
     }
     
     print_to_file(fptr, records, n);
     fclose(fptr);
     
     fptr = fopen("patients.txt", "r");
     if (!fptr) {
        printf("File Opening Failed.\n");
        return; 
     }
     
     char line[1000];
     
     while(fgets(line, sizeof(line), fptr)) {
         printf("%s", line);
     }
     
     printf("\n");
}
