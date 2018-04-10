#ifndef _MATRIX_H_
#define _MATRIX_H_

/*******************************************************************************
* Definitions
******************************************************************************/
#define OK          1
#define NOT_OK      0

/*Max size for row and column of matrix*/
#define MAX         10 

/*!
* @brief: Define data type for matrix
* row: row of matrix
* column: column of matrix
* **matrix: pointer management matrix
*/
typedef struct Matrix{
    int row;
    int column;
    int element[MAX][MAX];
}MATRIX;

/*******************************************************************************
* API
******************************************************************************/

/*!
* @brief: Enter the matrix elements
*
*@param [in]: row: row of matrix enter from keyboard
*@param [in]: col: column of matrix enter from keyboard
*
* @return:  OK: row and column are positive integer
*           NOT_OK: row and column are not positive integer
*/
char CheckSizeMatrix(int row, int col);

/*!
* @brief: Enter the matrix elements
*
*@param [in]: a: matrix need to enter elements
*
* @return :return a matrix
*/
MATRIX EnterMatrix(MATRIX a);

/*!
* @brief: Free pointer management matrix return memory to operating system
*
*@param [in]: a: matrix need to free pointer
*
*/

void DisplayMatrix(MATRIX a);

/*!
* @brief: Check can two matrices add together?
*
*@param [in]: a1: matrix 1
*@param [in]: a2: matrix 2
*
* @return :return   OK: can add, 
*                   NOT_OK: can't add
*/
char CheckAddMatrix(MATRIX a1, MATRIX a2);
 
 /*!
* @brief: Check can two matrices multiply together?
*
*@param [in]: a1: matrix 1
*@param [in]: a2: matrix 2
*
* @return :return   OK: can multiply
*                   NOT_OK: can't multiply
*/
char CheckMultiMatrix(MATRIX a1, MATRIX a2);
 
 /*!
* @brief: add two matrix
*
*@param [in]: a1: matrix 1
*@param [in]: a2: matrix 2
*
* @return :return matrix added
*/
MATRIX AddMatrix(MATRIX a1, MATRIX a2);

/*!
* @brief: Multiply two matrices
*
*@param [in]: a1: matrix 1
*@param [in]: a2: matrix 2
*
* @return :return matrix multiplied
*/
MATRIX MultiMatrix(MATRIX a1, MATRIX a2);

 #endif
