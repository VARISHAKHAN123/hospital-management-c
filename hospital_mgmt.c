#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for Patient
struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
};

// Function declarations
void addPatient();
void viewPatients();
void searchPatient();
void deletePatient();
void bookAppointment();

int main() {
    int choice;

    while (1) {
        printf("\n==== Hospital Management System ====\n");
        printf("1. Add Patient\n");
        printf("2. View Patients\n");
        printf("3. Search Patient\n");
        printf("4. Delete Patient\n");
        printf("5. Book Appointment\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: searchPatient(); break;
            case 4: deletePatient(); break;
            case 5: bookAppointment(); break;
            case 6: printf("Exiting... Thank you!\n"); exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

// Function to add a patient
void addPatient() {
    struct Patient p;
    FILE *fp = fopen("patients.txt", "a");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Patient ID: ");
    scanf("%d", &p.id);
    printf("Enter Name: ");
    scanf("%s", p.name);
    printf("Enter Age: ");
    scanf("%d", &p.age);
    printf("Enter Disease: ");
    scanf("%s", p.disease);

    fwrite(&p, sizeof(struct Patient), 1, fp);
    fclose(fp);

    printf("Patient added successfully!\n");
}

// Function to view all patients
void viewPatients() {
    struct Patient p;
    FILE *fp = fopen("patients.txt", "r");

    if (fp == NULL) {
        printf("No patient records found!\n");
        return;
    }

    printf("\n--- Patient Records ---\n");
    while (fread(&p, sizeof(struct Patient), 1, fp)) {
        printf("ID: %d, Name: %s, Age: %d, Disease: %s\n", p.id, p.name, p.age, p.disease);
    }
    fclose(fp);
}

// Function to search a patient by ID
void searchPatient() {
    struct Patient p;
    FILE *fp = fopen("patients.txt", "r");
    int id, found = 0;

    if (fp == NULL) {
        printf("No patient records found!\n");
        return;
    }

    printf("Enter Patient ID to search: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(struct Patient), 1, fp)) {
        if (p.id == id) {
            printf("Patient Found - ID: %d, Name: %s, Age: %d, Disease: %s\n", p.id, p.name, p.age, p.disease);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Patient with ID %d not found!\n", id);

    fclose(fp);
}

// Function to delete a patient record
void deletePatient() {
    struct Patient p;
    FILE *fp = fopen("patients.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    int id, found = 0;

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(struct Patient), 1, fp)) {
        if (p.id == id) {
            found = 1;
            printf("Patient with ID %d deleted successfully!\n", id);
        } else {
            fwrite(&p, sizeof(struct Patient), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (!found)
        printf("Patient with ID %d not found!\n", id);
}

// Function to book an appointment
void bookAppointment() {
    char patientName[50], doctorName[50], date[20];

    printf("Enter Patient Name: ");
    scanf("%s", patientName);
    printf("Enter Doctor Name: ");
    scanf("%s", doctorName);
    printf("Enter Appointment Date (DD/MM/YYYY): ");
    scanf("%s", date);

    FILE *fp = fopen("appointments.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fp, "Patient: %s | Doctor: %s | Date: %s\n", patientName, doctorName, date);
    fclose(fp);

    printf("Appointment booked successfully!\n");
}
