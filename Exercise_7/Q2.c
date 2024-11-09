#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char username[50];
    char name[100];
    int age;
    char email[100];
} User;
User* searchUserByUsername(User* users, int n, const char* username) {
    for (int i = 0; i < n; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return &users[i]; // Return pointer to the user record
        }
    }
    return NULL; // If username not found
}

int main() {
    int n;
    printf("Enter the number of users: ");
    scanf("%d", &n);
    User* users = (User*)malloc(n * sizeof(User));
    if (users == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        printf("Enter details for user %d:\n", i + 1);
        printf("Username: ");
        getchar(); // Clear the newline character
        fgets(users[i].username, 50, stdin);
        users[i].username[strcspn(users[i].username, "\n")] = '\0';
        printf("Name: ");
        fgets(users[i].name, 100, stdin);
        users[i].name[strcspn(users[i].name, "\n")] = '\0'; 
        printf("Age: ");
        scanf("%d", &users[i].age);
        getchar(); 
        printf("Email: ");
        fgets(users[i].email, 100, stdin);
        users[i].email[strcspn(users[i].email, "\n")] = '\0'; 
    }

    char searchUsername[50];
    printf("Enter username to search for: ");
    getchar(); // Clear the newline character
    fgets(searchUsername, 50, stdin);
    searchUsername[strcspn(searchUsername, "\n")] = '\0'; 
    User* user = searchUserByUsername(users, n, searchUsername);
    if (user != NULL) {
        printf("User found:\n");
        printf("Username: %s\n", user->username);
        printf("Name: %s\n", user->name);
        printf("Age: %d\n", user->age);
        printf("Email: %s\n", user->email);
    } else {
        printf("User with username %s not found.\n", searchUsername);
    }
    free(users);

    return 0;
}
