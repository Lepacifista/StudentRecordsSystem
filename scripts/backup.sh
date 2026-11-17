#!/bin/bash

# Student Records Management System
# Automatic backup utility

# Locate the main project directory
PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

# Define source and backup locations
DATA_FILE="$PROJECT_DIR/data/students.dat"
BACKUP_DIR="$PROJECT_DIR/backups"

# Generate a timestamp
CURRENT_TIME=$(date +"%Y-%m-%d_%H-%M-%S")

# Check whether student data exists
if [ ! -f "$DATA_FILE" ]; then
    echo "Error: Student data file was not found."
    echo "Register some students before creating a backup."
    exit 1
fi

# Create backup directory if necessary
mkdir -p "$BACKUP_DIR"

# Construct backup filename
BACKUP_FILE="$BACKUP_DIR/students_backup_$CURRENT_TIME.dat"

# Copy student records
if cp "$DATA_FILE" "$BACKUP_FILE"; then
    echo "======================================"
    echo "     STUDENT DATA BACKUP SUCCESSFUL"
    echo "======================================"
    echo "Backup created: $BACKUP_FILE"
    echo "Backup date: $CURRENT_TIME"
else
    echo "Error: Backup operation failed."
    exit 1
fi
