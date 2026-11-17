#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "student.h"
#include "file_manager.h"

/* Reads a line of text safely from the keyboard. */
static int readLine(const char *prompt, char *buffer, size_t size){
    printf("%s", prompt);

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    size_t length = strlen(buffer);

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
    } else {
        int character;

        while ((character = getchar()) != '\n' && character != EOF) {
            /* Clear any remaining input. */
        }
    }

    return 1;
}

/* Accepts only valid scores between 0 and 100. */
static int readScore(int testNumber, float *score){
    char input[100];
    char *endPointer;
    float value;

    while (1) {
        char prompt[60];

        snprintf(prompt, sizeof(prompt), "Enter Test %d score (0-100): ", testNumber);

        if (!readLine(prompt, input, sizeof(input))) {
            return 0;
        }

        value = strtof(input, &endPointer);

        while (isspace((unsigned char)*endPointer)) {
            endPointer++;
        }

        if (input == endPointer || *endPointer != '\0' ||
            value < 0.0f || value > 100.0f) {
            printf("Invalid score. Enter a number between 0 and 100.\n");
            continue;
        }

        *score = value;
        return 1;
    }
}

/* Calculates the average of the three tests. */
float calculateAverage(const Student *student){
    float total = 0.0f;

    for (int i = 0; i < NUMBER_OF_TESTS; i++) {
        total += student->scores[i];
    }

    return total / NUMBER_OF_TESTS;
}

/* Assigns a letter grade based on the average. */
char calculateGrade(float average){
    if (average >= 80.0f) {
        return 'A';
    } else if (average >= 70.0f) {
        return 'B';
    } else if (average >= 60.0f) {
        return 'C';
    } else if (average >= PASS_MARK) {
        return 'D';
    }

    return 'F';
}

/* Registers a new student and saves the record. */
void registerStudent(void){
    Student newStudent;
    Student *existingStudents = NULL;
    int studentCount = 0;

    printf("\n========== REGISTER STUDENT ==========\n");

    if (!readLine("Enter student ID: ", newStudent.student_id, sizeof(newStudent.student_id))) {
        printf("Input could not be read.\n");
        return;
    }

    if (strlen(newStudent.student_id) == 0) {
        printf("Student ID cannot be empty.\n");
        return;
    }

    if (!readStudents(&existingStudents, &studentCount)) {
        printf("Unable to check existing student records.\n");
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(existingStudents[i].student_id, newStudent.student_id) == 0) {
            printf("A student with that ID already exists.\n");
            free(existingStudents);
            return;
        }
    }

    free(existingStudents);

    if (!readLine("Enter student's full name: ", newStudent.name, sizeof(newStudent.name))) {
        printf("Input could not be read.\n");
        return;
    }

    if (strlen(newStudent.name) == 0) {
        printf("Student name cannot be empty.\n");
        return;
    }

    for (int i = 0; i < NUMBER_OF_TESTS; i++) {
        if (!readScore(i + 1, &newStudent.scores[i])) {
            printf("Input could not be read.\n");
            return;
        }
    }

    if (saveStudent(&newStudent)) {
        printf("\nStudent registered successfully!\n");
        printf("Average: %.2f\n", calculateAverage(&newStudent));
        printf("Grade: %c\n", calculateGrade(calculateAverage(&newStudent)));
    } else {
        printf("Failed to save student record.\n");
    }
}

/* Displays all student records. */
void displayStudents(void){
    Student *students = NULL;
    int count = 0;

    if (!readStudents(&students, &count)) {
        printf("Unable to read student records.\n");
        return;
    }

    if (count == 0) {
        printf("\nNo student records found.\n");
        free(students);
        return;
    }

    printf("\n================ STUDENT RECORDS ================\n");
    printf("%-15s %-25s %-10s %-10s %-10s %-10s %-8s %-6s\n",
           "ID", "NAME", "TEST 1", "TEST 2", "TEST 3",
           "TOTAL AVG", "GRADE", "STATUS");

    printf("--------------------------------------------------------------------------"
           "----------------\n");

    for (int i = 0; i < count; i++) {
        float average = calculateAverage(&students[i]);

        printf("%-15s %-25s %-10.2f %-10.2f %-10.2f %-10.2f %-8c %-6s\n",
               students[i].student_id,
               students[i].name,
               students[i].scores[0],
               students[i].scores[1],
               students[i].scores[2],
               average,
               calculateGrade(average),
               average >= PASS_MARK ? "PASS" : "FAIL");
    }

    printf("\nTotal registered students: %d\n", count);

    free(students);
}

/* Searches for a student using their ID. */
void searchStudent(void){
    Student *students = NULL;
    int count = 0;
    char searchID[ID_LENGTH];

    printf("\n========== SEARCH STUDENT ==========\n");

    if (!readLine("Enter student ID to search: ", searchID, sizeof(searchID))) {
        printf("Input could not be read.\n");
        return;
    }

    if (!readStudents(&students, &count)) {
        printf("Unable to read student records.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].student_id, searchID) == 0) {
            float average = calculateAverage(&students[i]);

            printf("\nStudent found!\n");
            printf("Student ID: %s\n", students[i].student_id);
            printf("Full Name: %s\n", students[i].name);
            printf("Test 1: %.2f\n", students[i].scores[0]);
            printf("Test 2: %.2f\n", students[i].scores[1]);
            printf("Test 3: %.2f\n", students[i].scores[2]);
            printf("Average: %.2f\n", average);
            printf("Grade: %c\n", calculateGrade(average));
            printf("Status: %s\n", average >= PASS_MARK ? "PASS" : "FAIL");

            free(students);
            return;
        }
    }

    printf("No student found with ID: %s\n", searchID);
    free(students);
}

/* Calculates the average performance of the entire class. */
void displayClassAverage(void){
    Student *students = NULL;
    int count = 0;
    float total = 0.0f;

    if (!readStudents(&students, &count)) {
        printf("Unable to read student records.\n");
        return;
    }

    if (count == 0) {
        printf("\nNo records available to calculate class average.\n");
        free(students);
        return;
    }

    for (int i = 0; i < count; i++) {
        total += calculateAverage(&students[i]);
    }

    printf("\n========== CLASS PERFORMANCE ==========\n");
    printf("Number of students: %d\n", count);
    printf("Class average: %.2f\n", total / count);

    free(students);
}


/* Writes a text field safely in CSV format. */
static void writeCSVField(FILE *file, const char *value)
{
    fputc('"', file);

    while (*value != '\0') {
        if (*value == '"') {
            fputc('"', file);
        }

        fputc(*value, file);
        value++;
    }

    fputc('"', file);
}

/* Exports all student records into a CSV file. */
void exportStudentsToCSV(void){
    Student *students = NULL;
    int count = 0;

    if (!readStudents(&students, &count)) {
        printf("Unable to read student records.\n");
        return;
    }

    FILE *file = fopen("data/students.csv", "w");

    if (file == NULL) {
        perror("Could not create CSV file");
        free(students);
        return;
    }

    fprintf(file, "StudentID,Name,Test1,Test2,Test3,Average,Grade\n");

    for (int i = 0; i < count; i++) {
        float average = calculateAverage(&students[i]);

        writeCSVField(file, students[i].student_id);
        fputc(',', file);

        writeCSVField(file, students[i].name);

        fprintf(file, ",%.2f,%.2f,%.2f,%.2f,%c\n",
                students[i].scores[0],
                students[i].scores[1],
                students[i].scores[2],
                average,
                calculateGrade(average));
    }

    if (fclose(file) != 0) {
        perror("Error closing CSV file");
    } else {
        printf("\nCSV export completed successfully!\n");
        printf("Records exported: %d\n", count);
        printf("File location: data/students.csv\n");
    }

    free(students);
}

