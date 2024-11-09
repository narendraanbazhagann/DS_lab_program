#include <stdio.h>
#include <stdlib.h>
int compare(const void *a, const void *b) {
    return (*(float *)a > *(float *)b) - (*(float *)a < *(float *)b);
}
void sortPrices(float *prices, int n) {
    qsort(prices, n, sizeof(float), compare);
}
int main() {
  int n;
    printf("Enter the number of products: ");
    scanf("%d", &n);
    float *prices = (float *)malloc(n * sizeof(float));
    if (prices == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    printf("Enter the prices of the products:\n");
    for (int i = 0; i < n; i++) {
        scanf("%f", &prices[i]);
    }
    sortPrices(prices, n);
    printf("Sorted prices (ascending order):\n");
    for (int i = 0; i < n; i++) {
        printf("%.2f ", prices[i]);
    }
    printf("\n");
    free(prices);
    return 0;
}
