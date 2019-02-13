#include "something.h"

int main() {
    FILE *inputfile = fopen("in.txt" , "r");
    FILE *outputfile = fopen("out.txt", "a");
    
    int size;
    fscanf(inputfile, "%d", &size);
    int *array;
    array = (int*) malloc(size * sizeof(int));
    for(int i = 0; i < size; i++) {
        fscanf(inputfile, "%d", (array + i));
    }
    int array_last_index = size - 1;
    
    quick_sort(array, 0, array_last_index);
    
    for(int i = 0; i < size; i++) {
        fprintf(outputfile, "%d ", *(array + i));
    }
    
    fclose (inputfile);
    fclose (outputfile);
    return 0;
}