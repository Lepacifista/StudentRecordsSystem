#include <stdio.h>
#include <stdlib.h>

#include "student.h"

int main(void){
    char choice[20];
    int running = 1;

    printf("\n");
    printf("============================================\n");
    printf("       STUDENT RECORDS MANAGEMENT SYSTEM    \n");
    printf("============================================\n");

    while (running) {
        printf("\n--------------- MAIN MENU ----------------\n");
        printf("1. Register New Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Calculate Class Average\n");
        printf("5. Export Records to CSV\n");
        printf("6. Exit\n");
        printf("-------------------------------------------\n");

        printf("Enter your choice: ");

        if (fgets(choice, sizeof(choice), stdin) == NULL) {
            printf("\nInput error. Closing application.\n");
            break;
        }

        switch (atoi(choice)) {
            case 1:
                registerStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                displayClassAverage();
                break;

            case 5:
                exportStudentsToCSV();
                break;

            case 6:
                printf("\nThank you for using the system!\n");
                running = 0;
                break;

            default:
                printf("\nInvalid choice. Please select 1-6.\n");
        }
    }

    return 0;
}
