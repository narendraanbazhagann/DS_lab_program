#include <stdio.h>
#include <string.h>
#define MAX_ITEMS 100
#define MAX_ITEM_LENGTH 50
char shoppingList[MAX_ITEMS][MAX_ITEM_LENGTH];
int itemCount = 0;
void addItem(const char* item) {
    if (itemCount < MAX_ITEMS) {
        strncpy(shoppingList[itemCount], item, MAX_ITEM_LENGTH);
        itemCount++;
    } else {
        printf("Shopping list is full!\n");
    }
}
void removeItem(const char* item) {
    int i, found = 0;
    for (i = 0; i < itemCount; i++) {
        if (strcmp(shoppingList[i], item) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        for (int j = i; j < itemCount - 1; j++) {
            strcpy(shoppingList[j], shoppingList[j + 1]);
        }
        itemCount--;
        printf("Item removed successfully!\n");
    } else {
        printf("Item not found!\n");
    }
}
void displayShoppingList() {
    if (itemCount == 0) {
        printf("No items in the shopping list.\n");
        return;
    }

    printf("Shopping List:\n");
    for (int i = 0; i < itemCount; i++) {
        printf("%d. %s\n", i + 1, shoppingList[i]);
    }
}
int main() {
    addItem("Milk");
    addItem("Eggs");
    displayShoppingList();
    
    removeItem("Milk");
    displayShoppingList();
    
    return 0;
}
