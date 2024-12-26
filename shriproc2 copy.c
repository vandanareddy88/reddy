#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 20

struct Student {
    int id;
    char name[50];
    float marks;
};

struct Student students[MAX_STUDENTS];
int studentCount = 0;

void addStudent() {
    if (studentCount < MAX_STUDENTS) {
        printf("\nEnter student ID: ");
        scanf("%d", &students[studentCount].id);
        printf("Enter student name: ");
        getchar();  // to consume the newline character
        fgets(students[studentCount].name, sizeof(students[studentCount].name), stdin);
        students[studentCount].name[strcspn(students[studentCount].name, "\n")] = '\0'; // Remove newline
        printf("Enter student marks: ");
        scanf("%f", &students[studentCount].marks);
        studentCount++;
        printf("\nStudent added successfully!\n");
    } else {
        printf("\nStudent record limit reached.\n");
    }
}

void displayStudents() {
    if (studentCount == 0) {
        printf("\nNo students to display.\n");
    } else {
        printf("\nStudent Records:\n");
        printf("ID\tName\tMarks\n");
        for (int i = 0; i < studentCount; i++) {
            printf("%d\t%s\t%.2f\n", students[i].id, students[i].name, students[i].marks);
        }
    }
}

void modifyStudent() {
    int id, found = 0;
    printf("\nEnter student ID to modify: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("\nStudent found. Modify details:\n");
            printf("Enter new name: ");
            getchar();  // to consume the newline character
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0'; // Remove newline
            printf("Enter new marks: ");
            scanf("%f", &students[i].marks);
            printf("\nStudent details updated.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nStudent with ID %d not found.\n", id);
    }
}

void deleteStudent() {
    int id, found = 0;
    printf("\nEnter student ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            printf("\nStudent with ID %d deleted.\n", id);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nStudent with ID %d not found.\n", id);
    }
}

void searchStudent() {
    int id, found = 0;
    printf("\nEnter student ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("\nStudent found: ID=%d, Name=%s, Marks=%.2f\n", students[i].id, students[i].name, students[i].marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nStudent with ID %d not found.\n", id);
    }
}

void sortStudents() {
    struct Student temp;
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = i + 1; j < studentCount; j++) {
            if (students[i].marks < students[j].marks) {
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    printf("\nStudents sorted by marks (descending):\n");
    displayStudents();
}

void menu() {
    int choice;
    do {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Modify Student\n");
        printf("4. Delete Student\n");
        printf("5. Search Student\n");
        printf("6. Sort Students by Marks\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                modifyStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                searchStudent();
                break;
            case 6:
                sortStudents();
                break;
            case 7:
                printf("\nExiting...\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    } while (choice != 7);
}

int main() {
    menu();
    return 0;
}
