#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATIENTS 100
#define MAX_MEDICINES 10
#define MAX_MEDICINE_NAME_LENGTH 50

typedef struct {
    char name[MAX_MEDICINE_NAME_LENGTH];
    int timesPerDay;
    char intakeTimes[3][20];
    char dosage[20];
    char advice[200];
    int durationInDays;
} Medicine;

typedef struct {
    int id;
    char name[50];
    int age;
    char diagnosis[100];
    Medicine medicines[MAX_MEDICINES];
    int medicineCount;
    char history[500];
} Patient;

Patient patients[MAX_PATIENTS];
int patientCount = 0;

void addPatient() {
    if (patientCount >= MAX_PATIENTS) {
        printf("Maximum patient limit reached.\n");
        return;
    }

    Patient newPatient;
    printf("Enter patient ID: ");
    scanf("%d", &newPatient.id);
    getchar(); 
    printf("Enter patient name: ");
    fgets(newPatient.name, sizeof(newPatient.name), stdin);
    newPatient.name[strcspn(newPatient.name, "\n")] = '\0'; 
    printf("Enter patient age: ");
    scanf("%d", &newPatient.age);
    getchar(); 
    printf("Enter patient diagnosis: ");
    fgets(newPatient.diagnosis, sizeof(newPatient.diagnosis), stdin);
    newPatient.diagnosis[strcspn(newPatient.diagnosis, "\n")] = '\0'; 
    newPatient.medicineCount = 0;
    printf("Enter patient's allergy : ");
    fgets(newPatient.history, sizeof(newPatient.history), stdin);
    newPatient.history[strcspn(newPatient.history, "\n")] = '\0';
    patients[patientCount++] = newPatient;
    printf("Patient added successfully.\n");
}

void addMedicine(int patientIndex) {
    if (patients[patientIndex].medicineCount >= MAX_MEDICINES) {
        printf("Maximum medicine limit reached for this patient.\n");
        return;
    }

    Medicine newMedicine;
    printf("Enter medicine name: ");
    fgets(newMedicine.name, sizeof(newMedicine.name), stdin);
    newMedicine.name[strcspn(newMedicine.name, "\n")] = '\0';

    printf("Enter number of times per day (1-3): ");
    scanf("%d", &newMedicine.timesPerDay);
    getchar();

    for (int i = 0; i < newMedicine.timesPerDay; i++) {
        printf("Enter intake time %d (e.g., Morning, Afternoon, Night): ", i + 1);
        fgets(newMedicine.intakeTimes[i], sizeof(newMedicine.intakeTimes[i]), stdin);
        newMedicine.intakeTimes[i][strcspn(newMedicine.intakeTimes[i], "\n")] = '\0';
    }

    printf("Enter dosage (e.g., 1 pill, 10 ml): ");
    fgets(newMedicine.dosage, sizeof(newMedicine.dosage), stdin);
    newMedicine.dosage[strcspn(newMedicine.dosage, "\n")] = '\0';

    printf("Enter duration in days: ");
    scanf("%d", &newMedicine.durationInDays);
    getchar();

    printf("Enter any specific advice for this medicine: ");
    fgets(newMedicine.advice, sizeof(newMedicine.advice), stdin);
    newMedicine.advice[strcspn(newMedicine.advice, "\n")] = '\0';

    patients[patientIndex].medicines[patients[patientIndex].medicineCount++] = newMedicine;
    printf("Medicine added successfully.\n");
}


void viewPatientInfo(int patientIndex) {
    printf("ID: %d\n", patients[patientIndex].id);
    printf("Name: %s\n", patients[patientIndex].name);
    printf("Age: %d\n", patients[patientIndex].age);
    printf("Diagnosis: %s\n", patients[patientIndex].diagnosis);
    for (int j = 0; j < patients[patientIndex].medicineCount; j++) {
        printf("  Medicine Name: %s\n", patients[patientIndex].medicines[j].name);
        printf("  Times Per Day: %d\n", patients[patientIndex].medicines[j].timesPerDay);
        for (int k = 0; k < patients[patientIndex].medicines[j].timesPerDay; k++) {
            printf("    %s\n", patients[patientIndex].medicines[j].intakeTimes[k]);
        }
    }
    printf("--------------------\n");
}

void viewAllPatients() {
    if (patientCount == 0) {
        printf("No patients to display.\n");
        return;
    }

    for (int i = 0; i < patientCount; i++) {
        viewPatientInfo(i);
    }
}

void exportPatientsToCSV() {
    FILE *file = fopen("patients.csv", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "ID,Name,Age,Diagnosis,Medicines,Quantities,IntakeTimes,Advice\n");

    for (int i = 0; i < patientCount; i++) {
        fprintf(file, "%d,%s,%d,\"%s\",", 
                patients[i].id, 
                patients[i].name, 
                patients[i].age, 
                patients[i].diagnosis);

        // Write medicines
        for (int j = 0; j < patients[i].medicineCount; j++) {
            if (j > 0) fprintf(file, ";");  // Separate multiple medicines
            fprintf(file, "%s", patients[i].medicines[j].name);
        }

        fprintf(file, ",");

        // Write dosages
        for (int j = 0; j < patients[i].medicineCount; j++) {
            if (j > 0) fprintf(file, ";");  // Separate dosages
            fprintf(file, "%s", patients[i].medicines[j].dosage);
        }

        fprintf(file, ",");

        // Write intake times
        for (int j = 0; j < patients[i].medicineCount; j++) {
            if (j > 0) fprintf(file, ";");  // Separate intake times
            for (int k = 0; k < patients[i].medicines[j].timesPerDay; k++) {
                if (k > 0) fprintf(file, ";");  // Separate multiple intake times for the same medicine
                fprintf(file, "%s", patients[i].medicines[j].intakeTimes[k]);
            }
        }

        fprintf(file, ",");

        // Write advice
        for (int j = 0; j < patients[i].medicineCount; j++) {
            if (j > 0) fprintf(file, ";");  // Separate advice for different medicines
            fprintf(file, "\"%s\"", patients[i].medicines[j].advice);
        }

        fprintf(file, "\n");
    }

    fclose(file);
    printf("Patient data exported to patients.csv successfully.\n");
}

void searchPatient() {
    char searchTerm[50];
    printf("Enter search term (name, diagnosis, or medicine): ");
    fgets(searchTerm, sizeof(searchTerm), stdin);
    searchTerm[strcspn(searchTerm, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < patientCount; i++) {
        if (strstr(patients[i].name, searchTerm) || 
            strstr(patients[i].diagnosis, searchTerm)) {
            viewPatientInfo(i);
            found = 1;
        } else {
            for (int j = 0; j < patients[i].medicineCount; j++) {
                if (strstr(patients[i].medicines[j].name, searchTerm)) {
                    viewPatientInfo(i);
                    found = 1;
                    break;
                }
            }
        }
    }

    if (!found) {
        printf("No matching patient found.\n");
    }
}
void reportCommonDiagnoses() {
    char diagnosis[100];
    printf("Enter diagnosis to report: ");
    fgets(diagnosis, sizeof(diagnosis), stdin);
    diagnosis[strcspn(diagnosis, "\n")] = '\0';

    int count = 0;
    for (int i = 0; i < patientCount; i++) {
        if (strstr(patients[i].diagnosis, diagnosis)) {
            count++;
        }
    }
    printf("Number of patients with '%s': %d\n", diagnosis, count);
}


void menu() {
    int choice;
    do {
        printf("\nPatient Management System\n");
        printf("1. Add Patient (Doctor Only)\n");
        printf("2. Add Medicine to Patient (Doctor Only)\n");
        printf("3. View Patient Info\n");
        printf("4. Export Patient Data to CSV\n");
        printf("5. Search Patient\n");
        printf("6. Report Common Diagnoses\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2: 
            {
                int id;
                printf("Enter patient ID to add medicine: ");
                scanf("%d", &id);
                getchar();

                int found = 0;
                for (int i = 0; i < patientCount; i++) {
                    if (patients[i].id == id) {
                        addMedicine(i);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("Patient not found.\n");
                }
                break;
            }
            case 3: {
                int id;
                printf("Enter your patient ID to view info: ");
                scanf("%d", &id);
                getchar();

                int found = 0;
                for (int i = 0; i < patientCount; i++) {
                    if (patients[i].id == id) {
                        viewPatientInfo(i);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("Patient not found.\n");
                }
                break;
            }
            case 4:
                exportPatientsToCSV();
                break;
            case 5:
                searchPatient();
                break;
            case 6:
                reportCommonDiagnoses();
                break;
            case 7:
                printf("Exiting the system.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
}

int main() {
    menu();
    return 0;
}
