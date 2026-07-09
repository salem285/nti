#include <stdio.h>
int main() {
    int x = 10;
    int y = 20;
    int z = 30;
    int *p = &x;
    int *q = &y;
    int *r = &z;
    printf("x: %d, y: %d, z: %d, p: %p, q: %p,\n", x, y, z, p, q);
    printf("r: %p, *p: %d, *q: %d, *r: %d\n", r, *p, *q, *r);

    printf("Swapping pointers.\n");

    int *temp = p; 
    p = q;         
    q = r;         
    r = temp;      
    printf("x: %d, y: %d, z: %d, p: %p, q: %p,\n", x, y, z, p, q);
    printf("r: %p, *p: %d, *q: %d, *r: %d\n", r, *p, *q, *r);
    // انا دورت علي %p علي النت 
    //عشان كنت عاوز اطبعها زي مموجوده في الصوره وكدا 
    return 0;
}