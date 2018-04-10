#include "Asignment1.h"
#include <stdio.h>


/*!
 * @brief: Enter array elements
 *
 * @param [in]: *arr: arry to enter interger.
 *
 * @return: not return 
 */
void EntercArr(int *arr){
    int i;
    for(i = 0; i < NUMBER; i++){
        scanf("%d", &arr[i]);
    }
}

/*!
 * @brief: Display array elements
 *
 * @param [in]: *arr: arry to enter interger.
 *
 * @return: not return 
 */
void DisplayArr(int *arr){
    int i;
    for(i = 0; i < NUMBER; i++){
        printf("%d", arr[i]);
    }
}

/*!
 * @brief: Average of array elements
 *
 * @param [in]: *arr: arry to enter interger.
 *
 * @return: [out]: return array 
 */
float Average(int *arr){
    int i;
    int sum = 0;
    float average;
    for(i = 0; i < NUMBER; i++){
        sum += arr[i];
    }
    average = (float)sum/NUMBER;
    return average;
}


/*!
 * @brief: Average of array elements
 *
 * @param [in]: *arr: arry to enter interger.
 *
 * @return: [out]: number of element value less average 
 */
int CountLessAverage(int *arr){
    int counter = 0;
    int i;
    for(i = 0; i < NUMBER; i++){
        if(arr[i] < Average(arr)){
            counter++;
        }
    }
    return counter;
}

/*!
 * @brief: Swap odd number to left, even number to right
 *
 * @param [in]: *arr: arry to enter interger.
 *
 * @return: not return 
 */
void Swap(int *arr){
    int i;
    int j;
    int temp;
    for(i = 0; i < NUMBER; i++){
        if(!(arr[i]%2)){/*check odd number*/
            for(j = NUMBER - 1; j > i; j--){
                if(arr[j]%2){/*check even number*/
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
    }
}
