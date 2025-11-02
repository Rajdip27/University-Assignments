#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20
#define MAX_LOGS 100

// STRUCT DECLARATIONS
struct student {
    int id;
    char name[50];
    float marks;
};

struct logEntry {
    char user[30];
    char action[100];
};

// GLOBAL VARIABLES
struct student stu[MAX];
struct logEntry logs[MAX_LOGS];
int count = 0;      // Number of students
int logCount = 0;   // Number of log entries
char currentUser[30];
char currentRole[10];

// FUNCTION DECLARATIONS
void flush();
int login();
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void addLog(const char *action);
void showLogs();

// MAIN FUNCTION
int main() {
    if (!login()) {
        printf("Login failed! Exiting...\n");
        return 0;
    }

    int choice;

    while (1) {
        printf("\n==== STUDENT MANAGEMENT SYSTEM ====\n");
        printf("Logged in as: %s (%s)\n", currentUser, currentRole);
        printf("-----------------------------------\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        if (strcmp(currentRole, "admin") == 0)
            printf("5. Delete Student\n");
        if (strcmp(currentRole, "admin") == 0)
            printf("6. View Logs\n");
        printf("0. Exit\n");
        printf("-----------------------------------\n");
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
            case 5:
                if (strcmp(currentRole, "admin") == 0)
                    deleteStudent();
                else
                    printf("Access denied. Admin only.\n");
                break;
            case 6:
                if (strcmp(currentRole, "admin") == 0)
                    showLogs();
                else
                    printf("Access denied. Admin only.\n");
                break;
            case 0:
                printf("Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

// FUNCTION: flush()
void flush() {
    while (getchar() != '\n');
}

// FUNCTION: login()
// PURPOSE : Login system for admin/user
int login() {
    char username[30], password[30];

    printf("==== LOGIN ====\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    // Hardcoded credentials
    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
        strcpy(currentUser, "admin");
        strcpy(currentRole, "admin");
        printf("Welcome Admin!\n");
        addLog("Admin logged in");
        return 1;
    } else if (strcmp(username, "user") == 0 && strcmp(password, "0000") == 0) {
        strcpy(currentUser, "user");
        strcpy(currentRole, "user");
        printf("Welcome User!\n");
        addLog("User logged in");
        return 1;
    } else {
        printf("Invalid credentials!\n");
        return 0;
    }
}

// FUNCTION: addLog()
// PURPOSE : Add an entry to log
void addLog(const char *action) {
    if (logCount >= MAX_LOGS) return;
    strcpy(logs[logCount].user, currentUser);
    strcpy(logs[logCount].action, action);
    logCount++;
}

// FUNCTION: showLogs()
// PURPOSE : Admin can view all logs
void showLogs() {
    printf("\n--- ACTION LOGS ---\n");
    if (logCount == 0) {
        printf("No logs yet.\n");
        return;
    }
    for (int i = 0; i < logCount; i++) {
        printf("[%s] %s\n", logs[i].user, logs[i].action);
    }
}

// FUNCTION: addStudent()
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
    addLog("Added new student");
}

// FUNCTION: displayStudents()
void displayStudents() {
    if (count == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("\n--- Student List ---\n");
    for (int i = 0; i < count; i++)
        printf("ID: %d | Name: %s | Marks: %.2f\n", stu[i].id, stu[i].name, stu[i].marks);

    addLog("Viewed all students");
}

// FUNCTION: searchStudent()
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
    addLog("Searched for a student");
}

// FUNCTION: updateStudent()
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

            printf("Enter new marks (-1 to keep same): ");
            float newMarks;
            scanf("%f", &newMarks);
            flush();
            if (newMarks >= 0)
                stu[i].marks = newMarks;

            printf("Student updated successfully!\n");
            addLog("Updated student record");
            break;
        }
    }

    if (!found)
        printf("Student not found.\n");
}

// FUNCTION: deleteStudent()
// PURPOSE : Admin only – delete by ID
void deleteStudent() {
    int id, found = 0;
    printf("Enter ID to delete: ");
    scanf("%d", &id);
    flush();

    for (int i = 0; i < count; i++) {
        if (stu[i].id == id) {
            found = 1;
            for (int j = i; j < count - 1; j++)
                stu[j] = stu[j + 1];
            count--;
            printf("Student deleted successfully!\n");
            addLog("Deleted student record");
            break;
        }
    }

    if (!found)
        printf("Student not found.\n");
}
