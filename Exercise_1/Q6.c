#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Book {
    char bookTitle[100];
    struct Book* prev;
    struct Book* next;
} Book;
Book* head = NULL;
Book* tail = NULL;
void addBook(const char* bookTitle) {
    Book* newBook = (Book*)malloc(sizeof(Book));
    strcpy(newBook->bookTitle, bookTitle);
    newBook->next = NULL;
    newBook->prev = tail;

    if (tail != NULL) {
        tail->next = newBook;
    } else {
        head = newBook;
    }

    tail = newBook;
}

void removeBook(const char* bookTitle) {
    Book* temp = head;
    
    while (temp != NULL && strcmp(temp->bookTitle, bookTitle) != 0) {
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Book not found.\n");
        return;
    }

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    } else {
        tail = temp->prev;
    }

    free(temp);
    printf("Book removed.\n");
}
void displayBooks() {
    if (head == NULL) {
        printf("No books in the library.\n");
        return;
    }

    Book* temp = head;
    printf("Books in the library (Forward):\n");
    while (temp != NULL) {
        printf("%s\n", temp->bookTitle);
        temp = temp->next;
    }
}
void displayBooksReverse() {
    if (tail == NULL) {
        printf("No books in the library.\n");
        return;
    }

    Book* temp = tail;
    printf("Books in the library (Reverse):\n");
    while (temp != NULL) {
        printf("%s\n", temp->bookTitle);
        temp = temp->prev;
    }
}
int main() {
    addBook("The Catcher in the Rye");
    addBook("To Kill a Mockingbird");
    displayBooks();
    displayBooksReverse();
    
    removeBook("To Kill a Mockingbird");
    displayBooks();
    
    return 0;
}
