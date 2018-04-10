#ifndef _ASIGNMENT1_H_
#define _ASIGNMENT1_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*Size of array*/
#define NUMBER      5

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief: Enter array elements
 *
 * @param [in]: *arr: arry to enter interger.
 *
 * @return: not return 
 */
void EntercArr(int *arr);

/*!
 * @brief: Display array elements
 *
 * @param [in]: *arr: arry to enter interger.
 *
 * @return: not return 
 */
void DisplayArr(int *arr);

/*!
 * @brief: Average of array elements
 *
 * @param [in]: *arr: arry to enter interger.
 *
 * @return: [out]: return average 
 */
float Average(int *arr);

/*!
 * @brief: Average of array elements
 *
 * @param [in]: *arr: arry to enter interger.
 *
 * @return: [out]: number of element value less average 
 */
int CountLessAverage(int *arr);

/*!
 * @brief: Swap odd number to left, even number to right
 *
 * @param [in]: *arr: arry to enter interger.
 *
 * @return: not return 
 */
 void Swap(int *arr);

#endif 
