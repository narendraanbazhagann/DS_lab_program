#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100
unsigned int hash(const char *username) {
    unsigned int hashValue = 0;
    while (*username) {
        hashValue = (hashValue * 31) + *username++;
    }
    return hashValue % TABLE_SIZE;
}
typedef struct User {
    char username[50];
    char password[50];
    struct User *next;  
User *hashTable[TABLE_SIZE];
void initializeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
}
int usernameExists(const char *username) {
    unsigned int index = hash(username);
    User *current = hashTable[index];
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            return 1;  // Username exists
        }
        current = current->next;
    }
    return 0;  // Username does not exist
}
void insertUser(const char *username, const char *password) {
    unsigned int index = hash(username);
    User *newUser = (User *)malloc(sizeof(User));
    if (!newUser) {
        printf("Memory allocation failed!\n");
        return;
    }
    strcpy(newUser->username, username);
    strcpy(newUser->password, password);
    newUser->next = hashTable[index];
    hashTable[index] = newUser;
}
void registerUser(const char *username, const char *password) {
    if (usernameExists(username)) {
        printf("Username '%s' already exists!\n", username);
    } else {
        insertUser(username, password);
        printf("User '%s' registered successfully!\n", username);
    }
}

int main() {
    initializeTable();

    char username[50], password[50];
    int choice;

    while (1) {
        printf("\n1. Register User\n2. Exit\nChoose an option: ");
        scanf("%d", &choice);
        getchar(); 
        if (choice == 1) {
            printf("Enter username: ");
            fgets(username, sizeof(username), stdin);
            username[strcspn(username, "\n")] = 0;  

            printf("Enter password: ");
            fgets(password, sizeof(password), stdin);
            password[strcspn(password, "\n")] = 0;  

            registerUser(username, password);
        } else if (choice == 2) {
            break;
        }
    }

    return 0;
}
