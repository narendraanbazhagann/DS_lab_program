#include <stdio.h>
#include <string.h>
#define MAX_CONTACTS 100
#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 15
typedef struct {
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
} Contact;
Contact contactList[MAX_CONTACTS];
int contactCount = 0;
void addContact(const char* name, const char* phone) {
    if (contactCount < MAX_CONTACTS) {
        strncpy(contactList[contactCount].name, name, MAX_NAME_LENGTH);
        strncpy(contactList[contactCount].phone, phone, MAX_PHONE_LENGTH);
        contactCount++;
    } else {
        printf("Contact list is full!\n");
    }
}
void deleteContact(const char* name) {
    int i, found = 0;
    for (i = 0; i < contactCount; i++) {
        if (strcmp(contactList[i].name, name) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        for (int j = i; j < contactCount - 1; j++) {
            contactList[j] = contactList[j + 1];
        }
        contactCount--;
        printf("Contact deleted successfully!\n");
    } else {
        printf("Contact not found!\n");
    }
}
void displayContacts() {
    if (contactCount == 0) {
        printf("No contacts to display.\n");
        return;
    }

    for (int i = 0; i < contactCount; i++) {
        printf("Name: %s, Phone: %s\n", contactList[i].name, contactList[i].phone);
    }
}
int main() {
    addContact("Darshana", "1234567890");
    addContact("Shivani", "0987654321");
    displayContacts();
    
    deleteContact("Darshana");
    displayContacts();
    
    return 0;
}
