#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

// STRUCT DECLARATION
struct student {
    int id;
    char name[50];
    float marks;
};

// GLOBAL VARIABLES
struct student stu[MAX];
int count = 0;

// FUNCTION DECLARATIONS
void flush();
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

// MAIN FUNCTION
int main() {
    int choice;

    while (1) {
        printf("\n==== STUDENT MANAGEMENT SYSTEM ====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            flush();
            printf("Invalid input! Try again.\n");
            continue;
        }

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

// FUNCTION: flush()
// PURPOSE : Clear input buffer
void flush() {
    while (getchar() != '\n');
}

// FUNCTION: addStudent()
// PURPOSE : Add new student
void addStudent() {
    if (count >= MAX) {
        printf("Student list is full!\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%d", &stu[count].id);
    flush();

    printf("Enter Name: ");
    fgets(stu[count].name, 50, stdin);
    stu[count].name[strcspn(stu[count].name, "\n")] = 0;

    printf("Enter Marks: ");
    scanf("%f", &stu[count].marks);
    flush();

    count++;
    printf("Student added successfully!\n");
}

// FUNCTION: displayStudents()
// PURPOSE : Display all students
void displayStudents() {
    if (count == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("\n--- Student List ---\n");
    for (int i = 0; i < count; i++)
        printf("ID: %d | Name: %s | Marks: %.2f\n", stu[i].id, stu[i].name, stu[i].marks);
}

// FUNCTION: searchStudent()
// PURPOSE : Search by ID
void searchStudent() {
    int id, found = 0;
    printf("Enter ID to search: ");
    scanf("%d", &id);
    flush();

    for (int i = 0; i < count; i++) {
        if (stu[i].id == id) {
            printf("Student found: ID: %d | Name: %s | Marks: %.2f\n",
                   stu[i].id, stu[i].name, stu[i].marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found.\n");
}

// FUNCTION: updateStudent()
// PURPOSE : Update name or marks of a student by ID
void updateStudent() {
    int id, found = 0;
    printf("Enter ID to update: ");
    scanf("%d", &id);
    flush();

    for (int i = 0; i < count; i++) {
        if (stu[i].id == id) {
            found = 1;
            printf("Current Name: %s | Marks: %.2f\n", stu[i].name, stu[i].marks);

            printf("Enter new name (leave blank to keep same): ");
            char newName[50];
            fgets(newName, 50, stdin);
            newName[strcspn(newName, "\n")] = 0;
            if (strlen(newName) > 0)
                strcpy(stu[i].name, newName);

            printf("Enter new marks (or -1 to keep same): ");
            float newMarks;
            scanf("%f", &newMarks);
            flush();
            if (newMarks >= 0)
                stu[i].marks = newMarks;

            printf("Student updated successfully!\n");
            break;
        }
    }

    if (!found)
        printf("Student not found.\n");
}

// FUNCTION: deleteStudent()
// PURPOSE : Delete a student by ID
void deleteStudent() {
    int id, found = 0;
    printf("Enter ID to delete: ");
    scanf("%d", &id);
    flush();

    for (int i = 0; i < count; i++) {
        if (stu[i].id == id) {
            found = 1;
            // Shift all students after this one to left
            for (int j = i; j < count - 1; j++) {
                stu[j] = stu[j + 1];
            }
            count--;
            printf("Student deleted successfully!\n");
            break;
        }
    }

    if (!found)
        printf("Student not found.\n");
}
