#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure to hold book details
struct Book {
    int book_id;
    char title[100];
    char author[100];
    int is_available; // 1 if available, 0 if borrowed
};

// Structure to hold user details
struct User {
    int user_id;
    char name[100];
    char borrowed_book[100];
};

// Function declarations
void add_book(struct Book books[], int *book_count);
void list_books(struct Book books[], int book_count);
void borrow_book(struct Book books[], struct User *user, int book_count);
void return_book(struct Book books[], struct User *user, int book_count);
int find_book_by_id(struct Book books[], int book_count, int book_id);
void menu();

int main() {
    struct Book books[100];
    struct User user = {0}; // User has no borrowed book initially
    int book_count = 0;
    int choice;

    while(1) {
        menu();
        scanf("%d", &choice);

        switch(choice) {
            case 1: add_book(books, &book_count); break;
            case 2: list_books(books, book_count); break;
            case 3: borrow_book(books, &user, book_count); break;
            case 4: return_book(books, &user, book_count); break;
            case 5: printf("Exiting...\n"); exit(0);
            default: printf("Invalid choice. Try again.\n"); break;
        }
    }

    return 0;
}

// Function to display the menu
void menu() {
    printf("\nLibrary Management System\n");
    printf("1. Add Book\n");
    printf("2. List Books\n");
    printf("3. Borrow Book\n");
    printf("4. Return Book\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

// Function to add a new book
void add_book(struct Book books[], int *book_count) {
    printf("\nEnter Book ID: ");
    scanf("%d", &books[*book_count].book_id);
    getchar(); // consume newline character
    printf("Enter Book Title: ");
    fgets(books[*book_count].title, sizeof(books[*book_count].title), stdin);
    books[*book_count].title[strcspn(books[*book_count].title, "\n")] = '\0'; // remove newline

    printf("Enter Book Author: ");
    fgets(books[*book_count].author, sizeof(books[*book_count].author), stdin);
    books[*book_count].author[strcspn(books[*book_count].author, "\n")] = '\0'; // remove newline

    books[*book_count].is_available = 1; // New books are available
    (*book_count)++;

    printf("Book added successfully.\n");
}

// Function to list all books
void list_books(struct Book books[], int book_count) {
    printf("\nListing all books:\n");
    for (int i = 0; i < book_count; i++) {
        printf("Book ID: %d\n", books[i].book_id);
        printf("Title: %s\n", books[i].title);
        printf("Author: %s\n", books[i].author);
        printf("Status: %s\n", books[i].is_available ? "Available" : "Borrowed");
        printf("\n");
    }
}

// Function to borrow a book
void borrow_book(struct Book books[], struct User *user, int book_count) {
    if (user->user_id == 0) {
        printf("\nNo user found. Please provide user details first.\n");
        return;
    }

    int book_id;
    printf("\nEnter Book ID to borrow: ");
    scanf("%d", &book_id);

    int index = find_book_by_id(books, book_count, book_id);
    if (index == -1) {
        printf("Book not found.\n");
        return;
    }

    if (books[index].is_available == 0) {
        printf("Sorry, this book is already borrowed.\n");
        return;
    }

    books[index].is_available = 0;
    printf("\nEnter your name: ");
    getchar(); // consume newline character
    fgets(user->name, sizeof(user->name), stdin);
    user->name[strcspn(user->name, "\n")] = '\0'; // remove newline
    strcpy(user->borrowed_book, books[index].title);

    printf("You have borrowed '%s'.\n", books[index].title);
}

// Function to return a borrowed book
void return_book(struct Book books[], struct User *user, int book_count) {
    if (user->user_id == 0) {
        printf("\nNo user found. Please provide user details first.\n");
        return;
    }

    if (strlen(user->borrowed_book) == 0) {
        printf("You have not borrowed any book.\n");
        return;
    }

    int book_id;
    printf("\nEnter Book ID to return: ");
    scanf("%d", &book_id);

    int index = find_book_by_id(books, book_count, book_id);
    if (index == -1) {
        printf("Book not found.\n");
        return;
    }

    if (books[index].is_available == 1) {
        printf("This book is already available in the library.\n");
        return;
    }

    books[index].is_available = 1;
    printf("You have successfully returned '%s'.\n", books[index].title);
    memset(user->borrowed_book, 0, sizeof(user->borrowed_book));
}

// Function to find a book by its ID
int find_book_by_id(struct Book books[], int book_count, int book_id) {
    for (int i = 0; i < book_count; i++) {
        if (books[i].book_id == book_id) {
            return i;
        }
    }
    return -1; // Book not found
}