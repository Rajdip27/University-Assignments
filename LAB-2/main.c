#include <stdio.h>      // For standard input/output functions (printf, scanf)
#include <stdlib.h>     // For exit() function
#include <string.h>     // For string handling functions like strcspn()

#define MAX 20           // Define a constant: maximum number of students that can be stored

// STRUCT DECLARATION
// Define a 'student' structure to hold student data
struct student {
    int id;              // Unique ID for each student
    char name[50];       // Student name (string)
    float marks;         // Marks of the student (float value)
};
// GLOBAL VARIABLES

struct student stu[MAX]; // Array of 'student' structs to store up to MAX students
int count = 0;           // Keeps track of how many students are currently stored


// FUNCTION DECLARATIONS
void flush();             // Clears input buffer
void addStudent();        // Adds a new student record
void displayStudents();   // Displays all student records
void searchStudent();     // Searches a student by ID

// MAIN FUNCTION
int main() {
    int choice;  // Variable to hold user's menu choice

    // Infinite loop for continuous menu display
    while(1) {
        // Display menu options
        printf("\n1. Add Student\n2. Display Students\n3. Search Student\n4. Exit\n");
        printf("Enter your choice: ");

        // Take input from user, check if it's valid
        // If scanf fails (non-integer entered), flush buffer and retry
        if(scanf("%d", &choice) != 1){
            flush();      // Remove invalid input
            continue;     // Go back to menu
        }

        // Perform action based on user choice
        switch(choice) {
            case 1: addStudent(); break;       // Add a new student
            case 2: displayStudents(); break;  // Show all students
            case 3: searchStudent(); break;    // Search by ID
            case 4: exit(0);                   // Exit program
            default: printf("Invalid choice!\n"); // Handle wrong input
        }
    }
    return 0;
}
// FUNCTION: flush()
// PURPOSE : Clear the input buffer after invalid or leftover input

void flush() {
    // Continue reading characters until newline is found
    while(getchar() != '\n');
}
// FUNCTION: addStudent()
// PURPOSE : Add a new student record to the array
void addStudent() {

    // Check if student list is full
    if(count >= MAX) {
        printf("Student list is full!\n");
        return;
    }

    // Input student ID
    printf("Enter ID: ");
    scanf("%d", &stu[count].id);
    flush();  // Clear buffer to avoid newline issues

    // Input student name using fgets() to allow spaces
    printf("Enter Name: ");
    fgets(stu[count].name, 50, stdin);

    // Remove trailing newline character from name
    stu[count].name[strcspn(stu[count].name, "\n")] = 0;

    // Input student marks
    printf("Enter Marks: ");
    scanf("%f", &stu[count].marks);
    flush();

    // Increase student count after adding
    count++;

    printf("Student added!\n");
}
// FUNCTION: displayStudents()
// PURPOSE : Show all student records
void displayStudents() {
    // If no students exist, show message
    if(count == 0) {
        printf("No students to display.\n");
        return;
    }

    // Loop through all stored students and print their info
    for(int i = 0; i < count; i++)
        printf("ID: %d | Name: %s | Marks: %.2f\n", stu[i].id, stu[i].name, stu[i].marks);
}

// FUNCTION: searchStudent()
// PURPOSE : Find and display student record by ID
void searchStudent() {
    int id, found = 0;   // Variables for searching and tracking result

    // Ask user for ID to search
    printf("Enter ID to search: ");
    scanf("%d", &id);
    flush();

    // Loop through all students to find match
    for(int i = 0; i < count; i++) {
        if(stu[i].id == id) {
            // If found, print details
            printf("Student found: ID: %d | Name: %s | Marks: %.2f\n",
                    stu[i].id, stu[i].name, stu[i].marks);
            found = 1;  // Set found flag
            break;      // Stop loop
        }
    }

    // If not found, display message
    if(!found)
        printf("Student not found.\n");
}
