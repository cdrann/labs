#ifndef H_SOMETHING
#define H_SOMETHING

#include<stdio.h>
#include <stdlib.h>

void quick_sort(int *array, int left, int right) {
    if (left >= right) { 
        return;
    }

    int x = *(array + left + (right - left) / 2);  

    int i = left;
    int j = right;
    while (i <= j) {
        while (*(array + i) < x) {
            i++;
        }
        while (*(array + j) > x) {
            j--;
        }
        if (i <= j) {
            int temp = *(array + i);
            *(array + i) = *(array + j);
            *(array + j) = temp;
            i++;
            j--;
        }
    }
    if (j > left) {
        quick_sort(array, left, j);
    }
    if (i < right) {
        quick_sort(array, i, right);
    }
} 

#endif