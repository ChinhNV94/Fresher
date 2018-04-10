#include <stdio.h>
#include <stdlib.h>
#include "Asignment1.h"

int main(){
    int *arr;
    /*Dynamic memory for pointer arr*/
    arr = (int*)malloc(NUMBER*sizeof(int));
    
    /*Enter array*/
    printf("\nEnter Array:\n");
    EntercArr(arr);
    
    /*Print average and number of elements less average*/
    printf("\nAverage: %f", Average(arr));
    printf("\nNumer of number less average: %d", CountLessAverage(arr));
    
    /*Print array befor swap*/
    printf("\nArray befor swap:\n");
    DisplayArr(arr);
    
    /*Swap odd number to left, even number to right*/
    Swap(arr);
    
    /*Print array after swap*/
    printf("\nArray after swap:\n");
    DisplayArr(arr);
    
    /*Free memory pointer arr management*/
    free(arr);
    
    return 0;
}
