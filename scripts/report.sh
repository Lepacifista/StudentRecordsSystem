#!/bin/bash

# Student Records Management System
# Class performance report

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CSV_FILE="$PROJECT_DIR/data/students.csv"

if [ ! -f "$CSV_FILE" ]; then
    echo "Error: Student CSV file was not found."
    exit 1
fi

echo "=========================================="
echo "       STUDENT PERFORMANCE REPORT"
echo "=========================================="

awk -F',' '
BEGIN {
    passMark = 50
    total = 0
    studentCount = 0
    belowPass = 0
    highestAverage = -1
}

NR == 1 {
    next
}

{
    # The exported CSV contains:
    # ID, Name, Test1, Test2, Test3, Average, Grade

    average = $6 + 0
    name = $2

    total += average
    studentCount++

    if (average > highestAverage) {
        highestAverage = average
        highestName = name
        highestID = $1
    }

    if (average < passMark) {
        belowPass++
    }
}

END {
    if (studentCount == 0) {
        print "No student records available."
        exit
    }

    printf "Total students: %d\n", studentCount
    printf "Class average: %.2f\n", total / studentCount
    printf "Highest-scoring student: %s (ID: %s)\n", highestName, highestID
    printf "Highest average: %.2f\n", highestAverage
    printf "Students below pass mark (%.0f): %d\n", passMark, belowPass
}
' "$CSV_FILE"

echo "=========================================="
