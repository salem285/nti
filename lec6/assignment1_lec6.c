#include <stdio.h>
void bubbleSort(int arr[]) ;
int main() {
    int arr[7] = {64, 34, 25, 12, 22, 11, 90};
    int i;
    printf("Original Array: ");
    for (i = 0; i < 7; i++) {
        printf("%d", arr[i]);
        if (i < 6) printf(", ");
    }
    printf("\n");
    bubbleSort(arr);
    printf("Sorted Array: ");
    for (i = 0; i < 7; i++) {
        printf("%d", arr[i]);
        if (i < 6) printf(", ");
    }
    return 0;
}
void bubbleSort(int arr[]) {
    int i, j, temp;
    for (i = 0; i < 7 - 1; i++) {
        for (j = 0; j < 7 - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}