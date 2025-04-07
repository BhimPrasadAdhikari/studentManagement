/**
 * @file student.h
 * @brief Header file containing student structure and linked list operations
 * 
 * This file defines the Student structure and declares functions for
 * managing students in a linked list. It provides the core data structure
 * and operations for the student management system.
 */

#ifndef STUDENT_H  /* Prevents multiple inclusions of this header file */
#define STUDENT_H

#include <stdio.h>   /* For input/output functions */
#include <stdlib.h>  /* For memory allocation functions like malloc() */
#include <string.h>  /* For string manipulation functions like strcpy() */
#include <stdbool.h> /* For boolean data type */

/* Maximum lengths for different student data fields */
#define MAX_NAME_LENGTH 50    /* Maximum characters for student name */
#define MAX_COURSE_LENGTH 30  /* Maximum characters for course name */
#define MAX_GRADES_LENGTH 20  /* Maximum characters for grades */
#define ID_LENGTH 10          /* Fixed length for student ID */

/**
 * @struct Student
 * @brief Structure to store student information
 * 
 * This structure represents a single student in our system.
 * It stores personal and academic information, and contains
 * a pointer to the next student in the linked list.
 */
typedef struct Student {
    char id[ID_LENGTH];         /* Unique identifier for each student */
    char name[MAX_NAME_LENGTH]; /* Full name of the student */
    int age;                    /* Age of the student */
    char course[MAX_COURSE_LENGTH]; /* The course/program the student is enrolled in */
    char grades[MAX_GRADES_LENGTH]; /* Student's academic grades */
    struct Student* next;       /* Pointer to the next student in the linked list - NULL if last student */
} Student;

/**
 * @brief Create a new student node
 * @param id Student ID
 * @param name Student name
 * @param age Student age
 * @param course Student's enrolled course
 * @param grades Student's grades
 * @return Pointer to the newly created student
 */
Student* createStudent(const char* id, const char* name, int age, const char* course, const char* grades);

/**
 * @brief Add a student to the linked list
 * @param head Pointer to the head of the linked list
 * @param student Student to be added
 * @return Updated head of the linked list
 */
Student* addStudent(Student* head, Student* student);

/**
 * @brief Delete a student from the linked list
 * @param head Pointer to the head of the linked list
 * @param id ID of the student to be deleted
 * @return Updated head of the linked list
 */
Student* deleteStudent(Student* head, const char* id);

/**
 * @brief Modify a student's information
 * @param head Pointer to the head of the linked list
 * @param id ID of the student to be modified
 * @param name New name (or NULL to keep existing)
 * @param age New age (or -1 to keep existing)
 * @param course New course (or NULL to keep existing)
 * @param grades New grades (or NULL to keep existing)
 * @return true if student was found and modified, false otherwise
 */
bool modifyStudent(Student* head, const char* id, const char* name, int age, const char* course, const char* grades);

/**
 * @brief Search for a student by ID
 * @param head Pointer to the head of the linked list
 * @param id ID of the student to be searched
 * @return Pointer to the found student or NULL if not found
 */
Student* searchStudentById(Student* head, const char* id);

/**
 * @brief Search for students by name
 * @param head Pointer to the head of the linked list
 * @param name Name to search for
 * @param count Pointer to store the count of matching students
 * @return Array of pointers to matching students (must be freed by caller)
 */
Student** searchStudentsByName(Student* head, const char* name, int* count);

/**
 * @brief Check if a student ID already exists
 * @param head Pointer to the head of the linked list
 * @param id ID to check
 * @return true if ID exists, false otherwise
 */
bool studentIdExists(Student* head, const char* id);

/**
 * @brief Display information of a single student
 * @param student Pointer to the student
 */
void displayStudent(const Student* student);

/**
 * @brief Display all students in the linked list
 * @param head Pointer to the head of the linked list
 * @return Number of students displayed
 */
int displayAllStudents(const Student* head);

/**
 * @brief Free all memory allocated for the linked list
 * @param head Pointer to the head of the linked list
 */
void freeStudentList(Student* head);

#endif /* STUDENT_H */
