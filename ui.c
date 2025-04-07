/**
 * @file ui.c
 * @brief Implementation of UI functions for the student management system
 */

#include "ui.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void displayMainMenu() {
    printf("\n");
    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║             STUDENT MANAGEMENT SYSTEM            ║\n");
    printf("╠══════════════════════════════════════════════════╣\n");
    printf("║ 1. Add a new student                             ║\n");
    printf("║ 2. Modify student details                        ║\n");
    printf("║ 3. Delete a student                              ║\n");
    printf("║ 4. Search for a student                          ║\n");
    printf("║ 5. Display all students                          ║\n");
    printf("║ 6. Save and exit                                 ║\n");
    printf("╚══════════════════════════════════════════════════╝\n");
    printf("Enter your choice (1-6): ");
}

Student* handleAddStudent(Student* head) {
    char id[ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    int age;
    char course[MAX_COURSE_LENGTH];
    char grades[MAX_GRADES_LENGTH];
    
    clearScreen();
    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║               ADD A NEW STUDENT                  ║\n");
    printf("╚══════════════════════════════════════════════════╝\n\n");
    
    // Get student ID
    do {
        printf("Enter student ID (max %d chars): ", ID_LENGTH - 1);
        if (!getStringInput(id, ID_LENGTH)) {
            printf("Error reading input. Please try again.\n");
            continue;
        }
        
        // Check if ID already exists
        if (studentIdExists(head, id)) {
            printf("Error: A student with ID %s already exists. Please use a different ID.\n", id);
            continue;
        }
        
        break;
    } while (1);
    
    // Get student name
    do {
        printf("Enter student name (max %d chars): ", MAX_NAME_LENGTH - 1);
        if (!getStringInput(name, MAX_NAME_LENGTH)) {
            printf("Error reading input. Please try again.\n");
            continue;
        }
        break;
    } while (1);
    
    // Get student age
    do {
        printf("Enter student age (1-120): ");
        if (!getIntInput(&age) || age < 1 || age > 120) {
            printf("Please enter a valid age between 1 and 120.\n");
            continue;
        }
        break;
    } while (1);
    
    // Get student course
    do {
        printf("Enter student course (max %d chars): ", MAX_COURSE_LENGTH - 1);
        if (!getStringInput(course, MAX_COURSE_LENGTH)) {
            printf("Error reading input. Please try again.\n");
            continue;
        }
        break;
    } while (1);
    
    // Get student grades
    do {
        printf("Enter student grades (max %d chars): ", MAX_GRADES_LENGTH - 1);
        if (!getStringInput(grades, MAX_GRADES_LENGTH)) {
            printf("Error reading input. Please try again.\n");
            continue;
        }
        break;
    } while (1);
    
    // Create and add the student
    Student* newStudent = createStudent(id, name, age, course, grades);
    if (newStudent == NULL) {
        printf("Error: Failed to create student. Memory allocation failed.\n");
        return head;
    }
    
    Student* updatedHead = addStudent(head, newStudent);
    printf("\nStudent added successfully!\n");
    waitForEnter();
    
    return updatedHead;
}

void handleModifyStudent(Student* head) {
    char id[ID_LENGTH];
    int choice;
    char name[MAX_NAME_LENGTH];
    int age;
    char course[MAX_COURSE_LENGTH];
    char grades[MAX_GRADES_LENGTH];
    bool modified = false;
    
    clearScreen();
    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║             MODIFY STUDENT DETAILS               ║\n");
    printf("╚══════════════════════════════════════════════════╝\n\n");
    
    if (head == NULL) {
        printf("There are no students in the system.\n");
        waitForEnter();
        return;
    }
    
    // Display all students for reference
    printf("Current students in the system:\n");
    displayAllStudents(head);
    printf("\n");
    
    // Get student ID to modify
    printf("Enter the ID of the student to modify: ");
    if (!getStringInput(id, ID_LENGTH)) {
        printf("Error reading input.\n");
        waitForEnter();
        return;
    }
    
    // Search for the student
    Student* student = searchStudentById(head, id);
    if (student == NULL) {
        printf("No student found with ID %s.\n", id);
        waitForEnter();
        return;
    }
    
    // Display current details
    printf("\nCurrent details of student ID %s:\n", id);
    displayStudent(student);
    
    // Select what to modify
    printf("\nWhat would you like to modify?\n");
    printf("1. Name\n");
    printf("2. Age\n");
    printf("3. Course\n");
    printf("4. Grades\n");
    printf("5. Modify all fields\n");
    printf("6. Cancel\n");
    printf("Enter your choice (1-6): ");
    
    if (!getIntInput(&choice) || choice < 1 || choice > 6) {
        printf("Invalid choice. Modification canceled.\n");
        waitForEnter();
        return;
    }
    
    // Initialize with default values (no change)
    strncpy(name, student->name, MAX_NAME_LENGTH);
    age = student->age;
    strncpy(course, student->course, MAX_COURSE_LENGTH);
    strncpy(grades, student->grades, MAX_GRADES_LENGTH);
    
    // Get new values based on choice
    switch (choice) {
        case 1: // Name only
            printf("Enter new name: ");
            if (getStringInput(name, MAX_NAME_LENGTH)) {
                modified = modifyStudent(head, id, name, -1, NULL, NULL);
            }
            break;
            
        case 2: // Age only
            printf("Enter new age (1-120): ");
            if (getIntInput(&age) && age >= 1 && age <= 120) {
                modified = modifyStudent(head, id, NULL, age, NULL, NULL);
            } else {
                printf("Invalid age. Modification canceled.\n");
            }
            break;
            
        case 3: // Course only
            printf("Enter new course: ");
            if (getStringInput(course, MAX_COURSE_LENGTH)) {
                modified = modifyStudent(head, id, NULL, -1, course, NULL);
            }
            break;
            
        case 4: // Grades only
            printf("Enter new grades: ");
            if (getStringInput(grades, MAX_GRADES_LENGTH)) {
                modified = modifyStudent(head, id, NULL, -1, NULL, grades);
            }
            break;
            
        case 5: // All fields
            printf("Enter new name: ");
            if (!getStringInput(name, MAX_NAME_LENGTH)) break;
            
            printf("Enter new age (1-120): ");
            if (!getIntInput(&age) || age < 1 || age > 120) {
                printf("Invalid age. Modification canceled.\n");
                break;
            }
            
            printf("Enter new course: ");
            if (!getStringInput(course, MAX_COURSE_LENGTH)) break;
            
            printf("Enter new grades: ");
            if (!getStringInput(grades, MAX_GRADES_LENGTH)) break;
            
            modified = modifyStudent(head, id, name, age, course, grades);
            break;
            
        case 6: // Cancel
            printf("Modification canceled.\n");
            waitForEnter();
            return;
    }
    
    if (modified) {
        printf("\nStudent details updated successfully!\n");
        displayStudent(student);
    } else {
        printf("\nFailed to update student details.\n");
    }
    
    waitForEnter();
}

Student* handleDeleteStudent(Student* head) {
    char id[ID_LENGTH];
    char confirmation;
    
    clearScreen();
    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║                DELETE A STUDENT                  ║\n");
    printf("╚══════════════════════════════════════════════════╝\n\n");
    
    if (head == NULL) {
        printf("There are no students in the system.\n");
        waitForEnter();
        return NULL;
    }
    
    // Display all students for reference
    printf("Current students in the system:\n");
    displayAllStudents(head);
    printf("\n");
    
    // Get student ID to delete
    printf("Enter the ID of the student to delete: ");
    if (!getStringInput(id, ID_LENGTH)) {
        printf("Error reading input.\n");
        waitForEnter();
        return head;
    }
    
    // Search for the student
    Student* student = searchStudentById(head, id);
    if (student == NULL) {
        printf("No student found with ID %s.\n", id);
        waitForEnter();
        return head;
    }
    
    // Display student details and confirm deletion
    printf("\nStudent details:\n");
    displayStudent(student);
    
    printf("\nAre you sure you want to delete this student? (y/n): ");
    if (!scanf(" %c", &confirmation)) {
        printf("Error reading input.\n");
        waitForEnter();
        return head;
    }
    
    // Clear input buffer
    clearInputBuffer();
    
    if (tolower(confirmation) == 'y') {
        head = deleteStudent(head, id);
        printf("Student deleted successfully.\n");
    } else {
        printf("Deletion canceled.\n");
    }
    
    waitForEnter();
    return head;
}

void displaySearchMenu() {
    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║                SEARCH STUDENTS                   ║\n");
    printf("╠══════════════════════════════════════════════════╣\n");
    printf("║ 1. Search by ID                                  ║\n");
    printf("║ 2. Search by Name                                ║\n");
    printf("║ 3. Return to Main Menu                           ║\n");
    printf("╚══════════════════════════════════════════════════╝\n");
    printf("Enter your choice (1-3): ");
}

void handleSearchStudent(Student* head) {
    int choice;
    char searchId[ID_LENGTH];
    char searchName[MAX_NAME_LENGTH];
    
    clearScreen();
    displaySearchMenu();
    
    if (!getIntInput(&choice) || choice < 1 || choice > 3) {
        printf("Invalid choice. Returning to main menu.\n");
        waitForEnter();
        return;
    }
    
    switch (choice) {
        case 1: // Search by ID
            printf("Enter student ID to search: ");
            if (!getStringInput(searchId, ID_LENGTH)) {
                printf("Error reading input.\n");
                break;
            }
            
            Student* foundStudent = searchStudentById(head, searchId);
            if (foundStudent != NULL) {
                printf("\nStudent found:\n");
                displayStudent(foundStudent);
            } else {
                printf("\nNo student found with ID %s.\n", searchId);
            }
            break;
            
        case 2: // Search by Name
            printf("Enter student name to search (partial match supported): ");
            if (!getStringInput(searchName, MAX_NAME_LENGTH)) {
                printf("Error reading input.\n");
                break;
            }
            
            int count = 0;
            Student** results = searchStudentsByName(head, searchName, &count);
            
            if (count > 0) {
                printf("\nFound %d student(s) matching '%s':\n\n", count, searchName);
                for (int i = 0; i < count; i++) {
                    displayStudent(results[i]);
                    printf("\n");
                }
                free(results);
            } else {
                printf("\nNo students found with name containing '%s'.\n", searchName);
            }
            break;
            
        case 3: // Return to main menu
            return;
    }
    
    waitForEnter();
}

void clearScreen() {
    // This is a cross-platform way to clear the screen
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void waitForEnter() {
    printf("\nPress Enter to continue...");
    clearInputBuffer();
    getchar();
}
