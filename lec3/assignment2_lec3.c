#include <stdio.h>
int main() {
    char saved_user,input_user;
    int saved_pass1;
    int input_pass1;
    int authenticated = 0;
    printf("enter your User  : ");
    scanf(" %c", &saved_user);
    printf("enter your Password : ");
    scanf("%d ", &saved_pass1 );
    while (!authenticated) {
        printf("Enter your User ID: ");
        scanf(" %c", &input_user);
        printf("Enter your Password: ");
        scanf("%d", &input_pass1 );
        if (input_user == saved_user && input_pass1 == saved_pass1) {
            printf("Login Successful! Welcome back.\n");
            authenticated = 1;
        } else {
            printf("\nIncorrect Credentials. Please try again.\n");
        }
    }

    return 0;
}