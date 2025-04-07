/**
 * @file student.c
 * @brief Implementation of student linked list operations
 */

#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

Student* createStudent(const char* id, const char* name, int age, const char* course, const char* grades) {
    // Allocate memory for a new student
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (newStudent == NULL) {
        fprintf(stderr, "Memory allocation failed for new student\n");
        return NULL;
    }

    // Copy data to the new student
    strncpy(newStudent->id, id, ID_LENGTH - 1);
    newStudent->id[ID_LENGTH - 1] = '\0';  // Ensure null termination
    
    strncpy(newStudent->name, name, MAX_NAME_LENGTH - 1);
    newStudent->name[MAX_NAME_LENGTH - 1] = '\0';
    
    newStudent->age = age;
    
    strncpy(newStudent->course, course, MAX_COURSE_LENGTH - 1);
    newStudent->course[MAX_COURSE_LENGTH - 1] = '\0';
    
    strncpy(newStudent->grades, grades, MAX_GRADES_LENGTH - 1);
    newStudent->grades[MAX_GRADES_LENGTH - 1] = '\0';
    
    newStudent->next = NULL;
    
    return newStudent;
}

Student* addStudent(Student* head, Student* student) {
    // If the list is empty, make the new student the head
    if (head == NULL) {
        return student;
    }
    
    // Find the last node in the list
    Student* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    // Add the new student at the end
    current->next = student;
    
    return head;
}

Student* deleteStudent(Student* head, const char* id) {
    if (head == NULL) {
        printf("The student list is empty.\n");
        return NULL;
    }
    
    Student* current = head;
    Student* previous = NULL;
    
    // Check if the head node needs to be deleted
    if (strcmp(current->id, id) == 0) {
        Student* newHead = current->next;
        free(current);
        printf("Student with ID %s has been deleted.\n", id);
        return newHead;
    }
    
    // Search for the student to delete
    while (current != NULL && strcmp(current->id, id) != 0) {
        previous = current;
        current = current->next;
    }
    
    // If student was found
    if (current != NULL) {
        previous->next = current->next;
        free(current);
        printf("Student with ID %s has been deleted.\n", id);
    } else {
        printf("Student with ID %s not found.\n", id);
    }
    
    return head;
}

bool modifyStudent(Student* head, const char* id, const char* name, int age, const char* course, const char* grades) {
    Student* student = searchStudentById(head, id);
    
    if (student == NULL) {
        return false;
    }
    
    // Update fields only if new values are provided
    if (name != NULL) {
        strncpy(student->name, name, MAX_NAME_LENGTH - 1);
        student->name[MAX_NAME_LENGTH - 1] = '\0';
    }
    
    if (age != -1) {
        student->age = age;
    }
    
    if (course != NULL) {
        strncpy(student->course, course, MAX_COURSE_LENGTH - 1);
        student->course[MAX_COURSE_LENGTH - 1] = '\0';
    }
    
    if (grades != NULL) {
        strncpy(student->grades, grades, MAX_GRADES_LENGTH - 1);
        student->grades[MAX_GRADES_LENGTH - 1] = '\0';
    }
    
    return true;
}

Student* searchStudentById(Student* head, const char* id) {
    Student* current = head;
    
    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;  // Student not found
}

Student** searchStudentsByName(Student* head, const char* name, int* count) {
    // First, count matching students
    *count = 0;
    Student* current = head;
    
    while (current != NULL) {
        if (strstr(current->name, name) != NULL) {
            (*count)++;
        }
        current = current->next;
    }
    
    if (*count == 0) {
        return NULL;
    }
    
    // Allocate array of pointers
    Student** results = (Student**)malloc(sizeof(Student*) * (*count));
    if (results == NULL) {
        *count = 0;
        return NULL;
    }
    
    // Fill the array with matching students
    current = head;
    int index = 0;
    
    while (current != NULL && index < *count) {
        if (strstr(current->name, name) != NULL) {
            results[index++] = current;
        }
        current = current->next;
    }
    
    return results;
}

bool studentIdExists(Student* head, const char* id) {
    return searchStudentById(head, id) != NULL;
}

void displayStudent(const Student* student) {
    if (student == NULL) {
        printf("No student data to display.\n");
        return;
    }
    
    printf("╔══════════════════════════════════════════════════════╗\n");
    printf("║ ID:     %-47s ║\n", student->id);
    printf("║ Name:   %-47s ║\n", student->name);
    printf("║ Age:    %-47d ║\n", student->age);
    printf("║ Course: %-47s ║\n", student->course);
    printf("║ Grades: %-47s ║\n", student->grades);
    printf("╚══════════════════════════════════════════════════════╝\n");
}

int displayAllStudents(const Student* head) {
    if (head == NULL) {
        printf("No students in the system.\n");
        return 0;
    }
    
    const Student* current = head;
    int count = 0;
    
    printf("╔═════════╦═════════════════════════╦═════╦═════════════════════╦═════════════╗\n");
    printf("║ ID      ║ Name                    ║ Age ║ Course              ║ Grades      ║\n");
    printf("╠═════════╬═════════════════════════╬═════╬═════════════════════╬═════════════╣\n");
    
    while (current != NULL) {
        printf("║ %-7s ║ %-25s ║ %-3d ║ %-19s ║ %-11s ║\n",
               current->id, current->name, current->age, current->course, current->grades);
        current = current->next;
        count++;
    }
    
    printf("╚═════════╩═════════════════════════╩═════╩═════════════════════╩═════════════╝\n");
    return count;
}

void freeStudentList(Student* head) {
    Student* current = head;
    Student* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
