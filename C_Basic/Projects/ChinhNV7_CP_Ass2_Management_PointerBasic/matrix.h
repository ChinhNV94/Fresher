#ifndef _MATRIX_H_
#define _MATRIX_H_

/*******************************************************************************
* Definitions
******************************************************************************/
#define OK          1
#define NOT_OK      0

/*!
* @brief: Define data type for matrix
* row: row of matrix
* column: column of matrix
* **matrix: pointer management matrix
*/
typedef struct Matrix{
    int row;
    int column;
    int **element;
}MATRIX;

/*******************************************************************************
* API
******************************************************************************/

/*!
* @brief: dynamic for pointer management matrix
*
*@param [in]: a: matrix need to Initialize
*
* @return [out]:return a matrix
*/
MATRIX DynamicMatrix(MATRIX a);

/*!
* @brief: Enter the matrix elements
*
*@param [in]: a: matrix need to enter elements
*
* @return [out]:return a matrix
*/
MATRIX EnterMatrix(MATRIX a);

/*!
* @brief: Free pointer management matrix return memory to operating system
*
*@param [in]: a: matrix need to free pointer
*
*/
void FreeMatrix(MATRIX a);

/*!
* @brief: Display the matrix elements
*
*@param [in]: a: matrix need to display elements
*
*/
void DisplayMatrix(MATRIX a);

/*!
* @brief: Check can two matrices add together?
*
*@param [in]: a1: matrix 1
*@param [in]: a2: matrix 2
*
* @return [out]:return OK: can add, NOT_OK: can't add
*/
char CheckAddMatrix(MATRIX a1, MATRIX a2);
 
 /*!
* @brief: Check can two matrices multiply together?
*
*@param [in]: a1: matrix 1
*@param [in]: a2: matrix 2
*
* @return [out]:return OK: can multiply, NOT_OK: can't multiply
*/
char CheckMultiMatrix(MATRIX a1, MATRIX a2);
 
 /*!
* @brief: add two matrix
*
*@param [in]: a1: matrix 1
*@param [in]: a2: matrix 2
*
* @return :return matrix add
*/
MATRIX AddMatrix(MATRIX a1, MATRIX a2);

/*!
* @brief: Multiply two matrices
*
*@param [in]: a1: matrix 1
*@param [in]: a2: matrix 2
*
* @return [out]:return matrix multiply
*/
MATRIX MultiMatrix(MATRIX a1, MATRIX a2);

 #endif
