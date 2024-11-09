#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char name[100];
    char phoneNumber[20];
} Contact;
Contact* searchContactByName(Contact* contacts, int n, const char* name) {
    for (int i = 0; i < n; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            return &contacts[i];
        }
    }
    return NULL;
}

int main() {
    int n;
    printf("Enter the number of contacts: ");
    scanf("%d", &n);
    Contact* contacts = (Contact*)malloc(n * sizeof(Contact));
    if (contacts == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        printf("Enter details for contact %d:\n", i + 1);
        printf("Name: ");
        getchar(); 
        fgets(contacts[i].name, 100, stdin);
        contacts[i].name[strcspn(contacts[i].name, "\n")] = '\0'; 
        printf("Phone number: ");
        fgets(contacts[i].phoneNumber, 20, stdin);
        contacts[i].phoneNumber[strcspn(contacts[i].phoneNumber, "\n")] = '\0'; 
    }

    char searchName[100];
    printf("Enter name to search for: ");
    fgets(searchName, 100, stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; 
    Contact* contact = searchContactByName(contacts, n, searchName);
    if (contact != NULL) {
        printf("Contact found:\n");
        printf("Name: %s\n", contact->name);
        printf("Phone number: %s\n", contact->phoneNumber);
    } else {
        printf("Contact with name %s not found.\n", searchName);
    }
    free(contacts);

    return 0;
}
