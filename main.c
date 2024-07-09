#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_MEDICINES 10
#define MAX_MEDICINE_NAME_LENGTH 50

typedef struct {
    char name[MAX_MEDICINE_NAME_LENGTH];
    int timesPerDay;
    char intakeTimes[3][20]; // Can be "Morning", "Afternoon", "Night"
} Medicine;

typedef struct {
    int id;
    char name[50];
    int age;
    char diagnosis[100];
    Medicine medicines[MAX_MEDICINES];
    int medicineCount;
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
    getchar(); // To consume the newline character left by scanf
    printf("Enter patient name: ");
    fgets(newPatient.name, sizeof(newPatient.name), stdin);
    newPatient.name[strcspn(newPatient.name, "\n")] = '\0'; // Remove the newline character
    printf("Enter patient age: ");
    scanf("%d", &newPatient.age);
    getchar(); // To consume the newline character left by scanf
    printf("Enter patient diagnosis: ");
    fgets(newPatient.diagnosis, sizeof(newPatient.diagnosis), stdin);
    newPatient.diagnosis[strcspn(newPatient.diagnosis, "\n")] = '\0'; // Remove the newline character

    newPatient.medicineCount = 0;

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
    newMedicine.name[strcspn(newMedicine.name, "\n")] = '\0'; // Remove the newline character

    printf("Enter number of times per day (1-3): ");
    scanf("%d", &newMedicine.timesPerDay);
    getchar(); // To consume the newline character left by scanf

    for (int i = 0; i < newMedicine.timesPerDay; i++) {
        printf("Enter intake time %d (e.g., Morning, Afternoon, Night): ", i + 1);
        fgets(newMedicine.intakeTimes[i], sizeof(newMedicine.intakeTimes[i]), stdin);
        newMedicine.intakeTimes[i][strcspn(newMedicine.intakeTimes[i], "\n")] = '\0'; // Remove the newline character
    }

    patients[patientIndex].medicines[patients[patientIndex].medicineCount++] = newMedicine;
    printf("Medicine added successfully.\n");
}

void viewPatientInfo(int patientIndex) {
    printf("ID: %d\n", patients[patientIndex].id);
    printf("Name: %s\n", patients[patientIndex].name);
    printf("Age: %d\n", patients[patientIndex].age);
    printf("Diagnosis: %s\n", patients[patientIndex].diagnosis);
    printf("Medicines:\n");
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

void menu() {
    int choice;
    do {
        printf("\nPatient Management System\n");
        printf("1. Add Patient (Doctor Only)\n");
        printf("2. Add Medicine to Patient (Doctor Only)\n");
        printf("3. View Patient Info\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To consume the newline character left by scanf


        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2: {
                int id;
                printf("Enter patient ID to add medicine: ");
                scanf("%d", &id);
                getchar(); // To consume the newline character left by scanf

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
                getchar(); // To consume the newline character left by scanf

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
                printf("Exiting the system.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}

int main() {
    menu();
    return 0;
}
