/**
 * @file fileio.c
 * @brief Implementation of file I/O operations for student data
 */

#include "fileio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool saveStudentsToFile(const char* filename, const Student* head) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s for writing.\n", filename);
        return false;
    }
    
    const Student* current = head;
    
    while (current != NULL) {
        // Write student data to file in CSV format
        fprintf(file, "%s,%s,%d,%s,%s\n", 
                current->id, 
                current->name, 
                current->age, 
                current->course, 
                current->grades);
        
        current = current->next;
    }
    
    fclose(file);
    return true;
}

Student* loadStudentsFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        // File doesn't exist yet, which is okay for first run
        return NULL;
    }
    
    Student* head = NULL;
    char line[256];
    
    while (fgets(line, sizeof(line), file)) {
        char id[ID_LENGTH];
        char name[MAX_NAME_LENGTH];
        int age;
        char course[MAX_COURSE_LENGTH];
        char grades[MAX_GRADES_LENGTH];
        
        // Remove newline character if present
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        
        // Parse the CSV line
        char* token = strtok(line, ",");
        if (token == NULL) continue;
        strncpy(id, token, ID_LENGTH - 1);
        id[ID_LENGTH - 1] = '\0';
        
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strncpy(name, token, MAX_NAME_LENGTH - 1);
        name[MAX_NAME_LENGTH - 1] = '\0';
        
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        age = atoi(token);
        
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strncpy(course, token, MAX_COURSE_LENGTH - 1);
        course[MAX_COURSE_LENGTH - 1] = '\0';
        
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strncpy(grades, token, MAX_GRADES_LENGTH - 1);
        grades[MAX_GRADES_LENGTH - 1] = '\0';
        
        // Create a student and add to list
        Student* newStudent = createStudent(id, name, age, course, grades);
        if (newStudent != NULL) {
            head = addStudent(head, newStudent);
        }
    }
    
    fclose(file);
    return head;
}

bool doesFileExist(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return true;
    }
    return false;
}
