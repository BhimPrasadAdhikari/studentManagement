/**
 * @file main.c
 * @brief Main application for Student Management System
 * 
 * This program implements a student management system using linked lists.
 * It provides CRUD operations for student records and persists data to files.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "student.h"
#include "fileio.h"
#include "ui.h"
#include "utils.h"

#define DATA_FILE "students.dat"
#define BACKUP_PREFIX "students_backup"
#define BACKUP_EXT "dat"

/**
 * Main function that drives the student management system
 */
int main() {
    // Load existing student data from file
    Student* studentList = loadStudentsFromFile(DATA_FILE);
    
    int choice;
    bool exitProgram = false;
    
    // Main program loop
    while (!exitProgram) {
        clearScreen();
        displayMainMenu();
        
        if (!getIntInput(&choice)) {
            printf("Invalid input. Please enter a number between 1 and 6.\n");
            waitForEnter();
            continue;
        }
        
        switch (choice) {
            case 1: // Add a new student
                studentList = handleAddStudent(studentList);
                break;
                
            case 2: // Modify student details
                handleModifyStudent(studentList);
                break;
                
            case 3: // Delete a student
                studentList = handleDeleteStudent(studentList);
                break;
                
            case 4: // Search for a student
                handleSearchStudent(studentList);
                break;
                
            case 5: // Display all students
                clearScreen();
                printf("╔══════════════════════════════════════════════════╗\n");
                printf("║               ALL STUDENTS LIST                  ║\n");
                printf("╚══════════════════════════════════════════════════╝\n\n");
                
                int count = displayAllStudents(studentList);
                printf("\nTotal number of students: %d\n", count);
                waitForEnter();
                break;
                
            case 6: // Save and exit
                // Create a backup of the existing file if it exists
                if (doesFileExist(DATA_FILE)) {
                    char backupFilename[100];
                    generateBackupFilename(backupFilename, BACKUP_PREFIX, BACKUP_EXT, sizeof(backupFilename));
                    
                    // Rename the existing file to the backup name
                    if (rename(DATA_FILE, backupFilename) == 0) {
                        printf("Created backup: %s\n", backupFilename);
                    } else {
                        fprintf(stderr, "Failed to create backup file.\n");
                    }
                }
                
                // Save current data
                if (saveStudentsToFile(DATA_FILE, studentList)) {
                    printf("Student data saved successfully to %s.\n", DATA_FILE);
                } else {
                    fprintf(stderr, "Failed to save student data.\n");
                }
                
                exitProgram = true;
                break;
                
            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n");
                waitForEnter();
        }
    }
    
    // Free memory
    freeStudentList(studentList);
    
    printf("\nThank you for using the Student Management System!\n");
    
    return 0;
}
