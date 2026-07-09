#include <stdio.h>
int main() {
    int height;
    while (1) {
        printf("Enter height of the pyramid: ");
        scanf("%d",&height);
        for (int row = 1; row <=height;row++) {
            for (int space = 1; space <= (height - row); space++) {
                printf(" ");
            }
            for (int star = 1; star <= (2*row-1); star++) {
                printf("*");
                if (star == (2*row-1)) {
                    continue; 
                }
            }
            printf("\n");
        }
        printf("\n\n"); 
    }
    return 0; 
}