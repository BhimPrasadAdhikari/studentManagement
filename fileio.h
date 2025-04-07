/**
 * @file fileio.h
 * @brief Header file containing functions for file I/O operations
 */

#ifndef FILEIO_H
#define FILEIO_H

#include "student.h"

/**
 * @brief Save the student linked list to a file
 * @param filename Name of the file to save to
 * @param head Pointer to the head of the linked list
 * @return true if save was successful, false otherwise
 */
bool saveStudentsToFile(const char* filename, const Student* head);

/**
 * @brief Load student data from a file into a linked list
 * @param filename Name of the file to load from
 * @return Head of the loaded linked list, or NULL if file doesn't exist
 */
Student* loadStudentsFromFile(const char* filename);

/**
 * @brief Check if the student data file exists
 * @param filename Name of the file to check
 * @return true if file exists, false otherwise
 */
bool doesFileExist(const char* filename);

#endif /* FILEIO_H */
