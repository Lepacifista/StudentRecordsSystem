# Student Records Management System

## 1. Project Overview

The Student Records Management System is a command-line application developed using the C programming language. It helps manage student academic records by allowing users to register students, view their results, search for individual records and calculate class performance.

The system stores student information in a binary file and can export records into CSV format for further analysis.

## 2. Project Objectives

- To demonstrate file handling in C.
- To apply structures and functions in procedural programming.
- To manage student records efficiently.
- To perform calculations using student test scores.
- To demonstrate the use of Unix shell scripting and AWK.

## 3. Main Features

- Register new students.
- Store student names, identification numbers and three test scores.
- Display all registered students.
- Calculate individual averages and grades.
- Calculate the overall class average.
- Search for students using their identification numbers.
- Export student records to CSV.
- Create timestamped backups of student data.
- Generate academic performance reports using AWK.

## 4. Technologies Used

- C programming language
- GCC compiler
- Bash shell scripting
- AWK
- GNU Make
- Git and GitHub
- Visual Studio Code

## 5. Project Structure

```text
StudentRecordsSystem/
├── src/
│   ├── main.c
│   ├── student.c
│   ├── student.h
│   ├── file_manager.c
│   └── file_manager.h
├── data/
│   ├── students.dat
│   └── students.csv
├── scripts/
│   ├── backup.sh
│   └── report.sh
├── backups/
├── Makefile
├── README.md
└── .gitignore
```

## 6. Compilation and Execution

Make sure GCC, GNU Make, Bash and AWK are installed.

Compile the application:

```bash
make
```

Run the application:

```bash
make run
```

Remove generated build files:

```bash
make clean
```

## 7. Shell Scripts

### Backup Script

The backup script creates a timestamped copy of the binary student database.

Run:

```bash
./scripts/backup.sh
```

### Performance Report

The AWK-based report script analyses the exported CSV records and displays the class average, highest-scoring student and number of students below the pass mark.

Run:

```bash
./scripts/report.sh
```

## 8. Data Storage

Student records are stored in `data/students.dat` using binary file handling.

The system also exports records to `data/students.csv`, allowing the information to be opened in spreadsheet applications or analysed using AWK.

## 9. Grading System

| Average | Grade |
|---|---|
| 80–100 | A |
| 70–79 | B |
| 60–69 | C |
| 50–59 | D |
| Below 50 | F |

The minimum pass mark is 50%.

## 10. Version Control

Git is used to track project development and maintain a history of changes.

## 11. Author

Developed as an individual academic project for CCS 219: Systems and Procedural Programming.
