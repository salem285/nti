#include <stdio.h>
    int class1[10] = {45, 67, 89, 32, 50, 76, 92, 41, 55, 68};
    int class2[10] = {78, 34, 88, 95, 49, 61, 23, 70, 52, 81};
    int class3[10] = {63, 50, 42, 77, 85, 90, 39, 66, 73, 58};
    int passed = 0;
    int failed = 0;
int main() {
    int highest = class1[0];
    int lowest = class1[0];
    int total_sum = 0;
    for ( int i = 0; i < 10; i++) {
        total_sum += class1[i];
        if (class1[i] >= 50) {
            passed++;
        } else {
            failed++;
        }
        if (class1[i] > highest) highest = class1[i];
        if (class1[i] < lowest)  lowest = class1[i];
    }
    for (int i = 0; i < 10; i++) {
        total_sum += class2[i];
        
        if (class2[i] >= 50) {
            passed++;
        } else {
            failed++;
        } 
        if (class2[i] > highest) highest = class2[i];
        if (class2[i] < lowest)  lowest = class2[i];
    }

    for (int i = 0; i < 10; i++) {
        total_sum += class3[i];
        
        if (class3[i] >= 50) {
            passed++;
        } else {
            failed++;
        }
        
        if (class3[i] > highest) highest = class3[i];
        if (class3[i] < lowest)  lowest = class3[i];
    }
    printf("1- Number of passed students: %d\n", passed);
    printf("2- Number of Failed students: %d\n", failed);
    printf("3- Highest grade: %d\n", highest);
    printf("4- Lowest grade: %d\n", lowest);
    printf("5- Average grade: %.2f\n", (float)total_sum / 30);
    return 0;
}