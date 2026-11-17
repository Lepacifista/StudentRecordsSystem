#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "student.h"

#define DATA_FILE "data/students.dat"

int saveStudent(const Student *student);
int readStudents(Student **students, int *count);

#endif
