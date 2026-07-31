#include <stdio.h>

int main() {
    int values[10];
    int min, max;
    printf("Enter values:\n");
    for(int i = 0; i < 10; i++) {
    scanf("%d", &values[i]);
    }
    min = values[0];
    max = values[0];
    for(int i = 1; i < 10; i++) {
        if(values[i] < min) {
            min = values[i];
        }
        else {
            max = values[i];
        }
    }
    printf("Minimum value: %d\n", min);
    printf("Maximum value: %d\n", max);
    return 0;
}