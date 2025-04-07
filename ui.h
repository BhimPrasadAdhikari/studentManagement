/**
 * @file ui.h
 * @brief Header file containing UI functions for the student management system
 */

#ifndef UI_H
#define UI_H

#include "student.h"

/**
 * @brief Display the main menu of the application
 */
void displayMainMenu();

/**
 * @brief Handle the add student operation
 * @param head Pointer to the head of the student linked list
 * @return Updated head of the linked list
 */
Student* handleAddStudent(Student* head);

/**
 * @brief Handle the modify student operation
 * @param head Pointer to the head of the student linked list
 */
void handleModifyStudent(Student* head);

/**
 * @brief Handle the delete student operation
 * @param head Pointer to the head of the student linked list
 * @return Updated head of the linked list
 */
Student* handleDeleteStudent(Student* head);

/**
 * @brief Handle the search student operation
 * @param head Pointer to the head of the student linked list
 */
void handleSearchStudent(Student* head);

/**
 * @brief Display the search menu
 */
void displaySearchMenu();

/**
 * @brief Clear the console screen (platform-independent)
 */
void clearScreen();

/**
 * @brief Wait for user to press enter to continue
 */
void waitForEnter();

#endif /* UI_H */
