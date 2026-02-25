#include <stdio.h>
#include <string.h>

#define N 100;

int bin_find(int a[N], int len, int key){
    int i, j, mid = (i+j)/2;
    while(i<j){
        if(a[mid]>key){
            j = mid + 1;
        }
        else if(a[mid]<key){
            i = mid;
        }
        else{
            return mid;
        }
    }
}
