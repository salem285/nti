#include <stdio.h>
int main() {
    int num, num2, sum;
    while (1) {
        printf("enter first number: ");
        scanf("%d",&num);
        printf("enter second number: ");
        scanf("%d",&num2);
        sum = num+num2;
        printf("sum = %d\n", sum); 
    }
    return 0;
}