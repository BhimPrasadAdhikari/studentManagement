/**
 * @file utils.c
 * @brief Implementation of utility functions
 */

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

bool getStringInput(char* buffer, int maxLength) {
    if (!fgets(buffer, maxLength, stdin)) {
        return false;
    }
    
    // Remove trailing newline if present
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    } else if (len == maxLength - 1) {
        // Input might be longer than maxLength, clear the rest
        clearInputBuffer();
    }
    
    // Validate input (not just whitespace)
    bool valid = false;
    for (size_t i = 0; i < strlen(buffer); i++) {
        if (!isspace((unsigned char)buffer[i])) {
            valid = true;
            break;
        }
    }
    
    return valid;
}

bool getIntInput(int* value) {
    char buffer[20]; // Large enough for any integer
    
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        return false;
    }
    
    // Remove trailing newline
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    } else {
        clearInputBuffer();
    }
    
    // Check for valid input (only digits)
    for (size_t i = 0; i < strlen(buffer); i++) {
        if (i == 0 && buffer[i] == '-') {
            // Allow negative sign at start
            continue;
        }
        if (!isdigit((unsigned char)buffer[i])) {
            return false;
        }
    }
    
    char* endptr;
    *value = (int)strtol(buffer, &endptr, 10);
    
    // Check if conversion was successful
    return (*endptr == '\0');
}

void generateBackupFilename(char* buffer, const char* prefix, 
                           const char* extension, int maxLength) {
    time_t now = time(NULL);
    struct tm* timeinfo = localtime(&now);
    
    // Format: prefix_YYYYMMDD_HHMMSS.extension
    snprintf(buffer, maxLength, "%s_%04d%02d%02d_%02d%02d%02d.%s",
             prefix,
             timeinfo->tm_year + 1900,
             timeinfo->tm_mon + 1,
             timeinfo->tm_mday,
             timeinfo->tm_hour,
             timeinfo->tm_min,
             timeinfo->tm_sec,
             extension);
}
