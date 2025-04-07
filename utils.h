/**
 * @file utils.h
 * @brief Header file containing utility functions
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

/**
 * @brief Clear the input buffer
 */
void clearInputBuffer();

/**
 * @brief Get a string input with validation
 * @param buffer Buffer to store the input
 * @param maxLength Maximum length of the input
 * @return true if input was successfully read, false otherwise
 */
bool getStringInput(char* buffer, int maxLength);

/**
 * @brief Get an integer input with validation
 * @param value Pointer to store the integer value
 * @return true if input was successfully read, false otherwise
 */
bool getIntInput(int* value);

/**
 * @brief Generate a unique filename using the current timestamp
 * @param buffer Buffer to store the generated filename
 * @param prefix Prefix for the filename
 * @param extension Extension for the filename
 * @param maxLength Maximum length of the buffer
 */
void generateBackupFilename(char* buffer, const char* prefix, 
                           const char* extension, int maxLength);

#endif /* UTILS_H */
