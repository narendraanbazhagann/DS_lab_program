#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 100
unsigned int hash(int productID) {
    return productID % TABLE_SIZE;
}
typedef struct Product {
    int productID;
    char name[100];
    float price;
    struct Product *next;  
} Product;
Product *hashTable[TABLE_SIZE];
void initializeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
}
void insertProduct(int productID, const char *name, float price) {
    unsigned int index = hash(productID);
    Product *newProduct = (Product *)malloc(sizeof(Product));
    if (!newProduct) {
        printf("Memory allocation failed!\n");
        return;
    }
    newProduct->productID = productID;
    strcpy(newProduct->name, name);
    newProduct->price = price;
    newProduct->next = hashTable[index];
    hashTable[index] = newProduct;
}
Product* searchProduct(int productID) {
    unsigned int index = hash(productID);
    Product *current = hashTable[index];
    while (current != NULL) {
        if (current->productID == productID) {
            return current;
        }
        current = current->next;
    }
    return NULL; 
}

int main() {
    initializeTable();
    insertProduct(101, "Laptop", 999.99);
    insertProduct(102, "Smartphone", 599.99);
    insertProduct(103, "Headphones", 199.99);
    printf("Enter product ID to search for: ");
    scanf("%d", &searchID);

    Product *product = searchProduct(searchID);
    if (product != NULL) {
        printf("Product found: %s\n", product->name);
        printf("Price: %.2f\n", product->price);
    } else {
        printf("Product not found!\n");
    }

    return 0;
}
