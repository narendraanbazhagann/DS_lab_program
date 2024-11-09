#include <stdio.h>
#include <stdlib.h>
void merge(int *ages, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *leftArr = (int *)malloc(n1 * sizeof(int));
    int *rightArr = (int *)malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++) leftArr[i] = ages[left + i];
    for (int j = 0; j < n2; j++) rightArr[j] = ages[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            ages[k] = leftArr[i];
            i++;
        } else {
            ages[k] = rightArr[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        ages[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < n2) {
        ages[k] = rightArr[j];
        j++;
        k++;
    }
    free(leftArr);
    free(rightArr);
}
void mergeSort(int *ages, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(ages, left, mid);
        mergeSort(ages, mid + 1, right);
        merge(ages, left, mid, right);
    }
}

int main() {
    int n;
    printf("Enter the number of participants: ");
    scanf("%d", &n);
    int *ages = (int *)malloc(n * sizeof(int));
    if (ages == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    printf("Enter the ages of the participants:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &ages[i]);
    }
    mergeSort(ages, 0, n - 1);
    printf("Sorted ages (youngest to oldest):\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", ages[i]);
    }
    printf("\n");

    // Free allocated memory
    free(ages);

    return 0;
}
