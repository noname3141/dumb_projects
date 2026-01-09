#include <stdio.h>

#define N 100

int find(int a[N], int len, int key){
    int i;
    for(i=0;i<len;i++){
        if(a[i]==key){
            return i;
        }
    }
    return -1;
}
