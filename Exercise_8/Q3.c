#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100
unsigned int hash(const char *title) {
    unsigned int hashValue = 0;
    while (*title) {
        hashValue = (hashValue * 31) + *title++;
    }
    return hashValue % TABLE_SIZE;
}
typedef struct Article {
    char title[100];
    char content[500];
    struct Article *next;  
} Article;
Article *hashTable[TABLE_SIZE];
void initializeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
}
void insertArticle(const char *title, const char *content) {
    unsigned int index = hash(title);
    Article *newArticle = (Article *)malloc(sizeof(Article));
    if (!newArticle) {
        printf("Memory allocation failed!\n");
        return;
    }
    strcpy(newArticle->title, title);
    strcpy(newArticle->content, content);
    newArticle->next = hashTable[index];
    hashTable[index] = newArticle;
}
Article* searchArticle(const char *title) {
    unsigned int index = hash(title);
    Article *current = hashTable[index];
    while (current != NULL) {
        if (strcmp(current->title, title) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL; 
}

int main() {
    initializeTable();
    insertArticle("C Programming", "Content of C programming article...");
    insertArticle("Data Structures", "Content of Data structures article...");
    insertArticle("Hashing in C", "Content about hashing in C...");

    char searchTitle[100];
    printf("Enter article title to search for: ");
    fgets(searchTitle, 100, stdin);
    searchTitle[strcspn(searchTitle, "\n")] = '\0';  

    Article *article = searchArticle(searchTitle);
    if (article != NULL) {
        printf("Article found: %s\n", article->title);
        printf("Content: %s\n", article->content);
    } else {
        printf("Article not found!\n");
    }

    return 0;
}
