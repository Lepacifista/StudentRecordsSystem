#ifndef STUDENT_H
#define STUDENT_H

#define NAME_LENGTH 100
#define ID_LENGTH 20
#define NUMBER_OF_TESTS 3
#define PASS_MARK 50.0f

typedef struct {
    char student_id[ID_LENGTH];
    char name[NAME_LENGTH];
    float scores[NUMBER_OF_TESTS];
} Student;

float calculateAverage(const Student *student);
char calculateGrade(float average);

void registerStudent(void);
void displayStudents(void);
void searchStudent(void);
void displayClassAverage(void);
void exportStudentsToCSV(void);

#endif
