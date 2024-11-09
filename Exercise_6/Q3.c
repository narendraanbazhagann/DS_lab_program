#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int compare(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

int main() {
    int n;
    printf("Enter the number of books: ");
    scanf("%d", &n);
    char **titles = (char **)malloc(n * sizeof(char *));
    if (titles == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    printf("Enter the titles of the books:\n");
    for (int i = 0; i < n; i++) {
        titles[i] = (char *)malloc(100 * sizeof(char)); 
        if (titles[i] == NULL) {
            printf("Memory allocation failed!\n");
            return 1;
        }
        getchar(); 
        fgets(titles[i], 100, stdin);
        titles[i][strcspn(titles[i], "\n")] = '\0'; 
    }
    qsort(titles, n, sizeof(char *), compare);
    printf("Sorted book titles (alphabetically):\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", titles[i]);
    }
    for (int i = 0; i < n; i++) {
        free(titles[i]);
    }
    free(titles);

    return 0;
}
