#include <stdio.h>
#include <stdlib.h>

#include "file_manager.h"

int saveStudent(const Student *student){
    FILE *file = fopen(DATA_FILE, "ab");

    if (file == NULL) {
        perror("Could not open student data file");
        return 0;
    }

    size_t written = fwrite(student, sizeof(Student), 1, file);

    fclose(file);

    return written == 1;
}

int readStudents(Student **students, int *count){
    FILE *file = fopen(DATA_FILE, "rb");

    *students = NULL;
    *count = 0;

    if (file == NULL) {
        return 1;
    }

    Student current;
    int capacity = 0;

    while (fread(&current, sizeof(Student), 1, file) == 1) {
        if (*count == capacity) {
            int newCapacity = (capacity == 0) ? 10 : capacity * 2;

            Student *expanded = realloc(*students, newCapacity * sizeof(Student));

            if (expanded == NULL) {
                free(*students);
                *students = NULL;
                *count = 0;
                fclose(file);
                return 0;
            }

            *students = expanded;
            capacity = newCapacity;
        }

        (*students)[*count] = current;
        (*count)++;
    }

    fclose(file);
    return 1;
}
