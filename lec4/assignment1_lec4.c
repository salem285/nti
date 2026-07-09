// Online C compiler to run C program online
#include <stdio.h>
int max(int x,int y,int z,int w);
int min(int x,int y,int z,int w);
int main() {
    int x,y,z,w;
    printf("enter num 1 :");
    scanf("%d",&x);
    printf("enter num 2 : ");
    scanf("%d",&y);
    printf("enter num 3 : ");
    scanf("%d",&z);
    printf("enter num 4 : ");
    scanf("%d",&w);
    int var = max(x,y,z,w);
    printf("the max is : %d\n",var);
    int va2r = min(x,y,z,w);
    printf("the min is : %d\n",va2r);
    return 0;
}
int max(int x,int y,int z,int w){
    int max;
    if(x>y && x>z && x>w){
        max=x;
    }else if(y>x && y>z && y>w){
        max=y;
    }else if(z>x && z>y && z>w){
        max=z;
    }else if(w>x && w>z && w>y){
        max=w;
    }
    return max;
}
int min(int x,int y,int z,int w){
        int min;
    if(x<y && x<z && x<w){
        min=x;
    }else if(y<x && y<z && y<w){
        min=y;
    }else if(z<x && z<y && z<w){
        min=z;
    }else if(w<x && w<z && w<y){
        min=w;
    }
    return min;
}
