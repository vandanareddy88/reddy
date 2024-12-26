
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a book
typedef struct {
    int id;
    char title[100];
    char author[50];
    int isIssued;
} Book;

// Maximum number of books in the library
#define MAX_BOOKS 1000

// Library structure
typedef struct {
    Book books[MAX_BOOKS];
    int count;
} Library;

// Function declarations
void displayMenu();
void addBook(Library *lib);
void deleteBook(Library *lib);
void searchBook(Library *lib);
void displayBooks(Library *lib);
void issueBook(Library *lib);
void returnBook(Library *lib);
void saveLibrary(Library *lib);
void loadLibrary(Library *lib);

// Main function
int main() {
    Library library = { .count = 0 };
    loadLibrary(&library);

    int choice;
    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(&library);
                break;
            case 2:
                deleteBook(&library);
                break;
            case 3:
                searchBook(&library);
                break;
            case 4:
                displayBooks(&library);
                break;
            case 5:
                issueBook(&library);
                break;
            case 6:
                returnBook(&library);
                break;
            case 7:
                saveLibrary(&library);
                printf("Library saved successfully. Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// Function to display the menu
void displayMenu() {
    printf("\n==== Library Management System ====\n");
    printf("1. Add a new book\n");
    printf("2. Delete a book\n");
    printf("3. Search for a book\n");
    printf("4. Display all books\n");
    printf("5. Issue a book\n");
    printf("6. Return a book\n");
    printf("7. Save and exit\n");
    printf("====================================\n");
}

// Function to add a book
void addBook(Library *lib) {
    if (lib->count >= MAX_BOOKS) {
        printf("Library is full. Cannot add more books.\n");
        return;
    }

    Book newBook;
    printf("Enter book ID: ");
    scanf("%d", &newBook.id);
    getchar(); // Clear the newline character
    printf("Enter book title: ");
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0'; // Remove newline
    printf("Enter author name: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0'; // Remove newline
    newBook.isIssued = 0;

    lib->books[lib->count++] = newBook;
    printf("Book added successfully!\n");
}

// Function to delete a book
void deleteBook(Library *lib) {
    int id;
    printf("Enter book ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < lib->count; i++) {
        if (lib->books[i].id == id) {
            for (int j = i; j < lib->count - 1; j++) {
                lib->books[j] = lib->books[j + 1];
            }
            lib->count--;
            printf("Book deleted successfully!\n");
            return;
        }
    }
    printf("Book not found.\n");
}

// Function to search for a book
void searchBook(Library *lib) {
    int id;
    printf("Enter book ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < lib->count; i++) {
        if (lib->books[i].id == id) {
            printf("\nBook found:\n");
            printf("ID: %d\n", lib->books[i].id);
            printf("Title: %s\n", lib->books[i].title);
            printf("Author: %s\n", lib->books[i].author);
            printf("Status: %s\n", lib->books[i].isIssued ? "Issued" : "Available");
            return;
        }
    }
    printf("Book not found.\n");
}

// Function to display all books
void displayBooks(Library *lib) {
    if (lib->count == 0) {
        printf("No books in the library.\n");
        return;
    }

    printf("\n==== List of Books ====\n");
    for (int i = 0; i < lib->count; i++) {
        printf("ID: %d, Title: %s, Author: %s, Status: %s\n",
               lib->books[i].id, lib->books[i].title,
               lib->books[i].author, lib->books[i].isIssued ? "Issued" : "Available");
    }
}

// Function to issue a book
void issueBook(Library *lib) {
    int id;
    printf("Enter book ID to issue: ");
    scanf("%d", &id);

    for (int i = 0; i < lib->count; i++) {
        if (lib->books[i].id == id) {
            if (lib->books[i].isIssued) {
                printf("Book is already issued.\n");
            } else {
                lib->books[i].isIssued = 1;
                printf("Book issued successfully!\n");
            }
            return;
        }
    }
    printf("Book not found.\n");
}

// Function to return a book
void returnBook(Library *lib) {
    int id;
    printf("Enter book ID to return: ");
    scanf("%d", &id);

    for (int i = 0; i < lib->count; i++) {
        if (lib->books[i].id == id) {
            if (lib->books[i].isIssued) {
                lib->books[i].isIssued = 0;
                printf("Book returned successfully!\n");
            } else {
                printf("Book was not issued.\n");
            }
            return;
        }
    }
    printf("Book not found.\n");
}

// Function to save the library data to a file
void saveLibrary(Library *lib) {
    FILE *file = fopen("library_data.txt", "w");
    if (!file) {
        printf("Error saving library data.\n");
        return;
    }

    fwrite(lib, sizeof(Library), 1, file);
    fclose(file);
}

// Function to load the library data from a file
void loadLibrary(Library *lib) {
    FILE *file = fopen("library_data.txt", "r");
    if (!file) {
        printf("No existing library data found. Starting fresh.\n");
        return;
    }

    fread(lib, sizeof(Library), 1, file);
    fclose(file);
}
