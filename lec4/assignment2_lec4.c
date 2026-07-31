#include <stdio.h>
int add(int, int);
int substract(int, int);
int mul(int, int);
int dive(int, int);
int ande(int, int);
int ore(int, int);
int note(int);
int xore(int, int);
int reminder(int, int);
int increment(int);
int decremint(int);

int main() {
    int choice, num1, num2, result;
    printf("Enter number of operation: \n");
    printf(" 1-add \n 2-sub\n 3-mul\n 4-div\n 5-and\n 6-or\n 7-not\n 8-xor\n 9-reminder\n 10-increment\n 11-decrement\n");
    printf("Your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
        printf("Enter two numbers: ");
        scanf("%d %d", &num1, &num2);
        printf("Result = %d\n", add(num1, num2));
        break;
        case 2:
        printf("Enter two numbers: ");
        scanf("%d %d", &num1, &num2);
        printf("Result = %d\n", substract(num1, num2));
        break;
        case 3:
        printf("Enter two numbers: ");
        scanf("%d %d", &num1, &num2);
        printf("Result = %d\n", mul(num1, num2));
        break;
        case 4:
        printf("Enter two numbers: ");
        scanf("%d %d", &num1, &num2);
            if (num2 != 0) {
                printf("Result = %d\n", dive(num1, num2));
            } else {
                printf("Error: Division by zero!\n");
            }
            break;
        case 5:
        printf("Enter two numbers: ");
        scanf("%d %d", &num1, &num2);
        printf("Result = %d\n", ande(num1, num2));
        break;
        case 6:
        printf("Enter two numbers: ");
        scanf("%d %d", &num1, &num2);
        printf("Result = %d\n", ore(num1, num2));
        break;
        case 7:
        printf("Enter one number: ");
        scanf("%d", &num1);
        printf("Result = %d\n", note(num1));
        break;
        case 8:
        printf("Enter two numbers: ");
        scanf("%d %d", &num1, &num2);
        printf("Result = %d\n", xore(num1, num2));
        break;
        case 9:
            printf("Enter two numbers: ");
            scanf("%d %d", &num1, &num2);
            if (num2 != 0) {
                printf("Result = %d\n", reminder(num1, num2));
            } else {
                printf("Error: Division by zero!\n");
            }
            break;
        case 10:
        printf("Enter one number: ");
        scanf("%d", &num1);
        printf("Result = %d\n", increment(num1));
        break;
        case 11:
        printf("Enter one number: ");
        scanf("%d", &num1);
        printf("Result = %d\n", decremint(num1));
        break;
        default:
        printf("Invalid choice!\n");
    }
    return 0;
}
int add(int a, int b) {
    return a + b;
}
int substract(int a, int b) {
    return a - b;
}
int mul(int a, int b) {
    return a * b;
}
int dive(int a, int b) {
    return a / b;
}
int ande(int a, int b) {
    return a & b;
}
int ore(int a, int b) {
    return a | b;
}
int note(int a) {
    return ~a;
}
int xore(int a, int b) {
    return a ^ b;
}
int reminder(int a, int b) {
    return a % b;
}
int increment(int a) {
    return ++a; 
}
int decremint(int a) {
    return --a;
}