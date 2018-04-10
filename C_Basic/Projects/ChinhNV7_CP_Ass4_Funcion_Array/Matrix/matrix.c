#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

/*!
* @brief: Enter the matrix elements
*
*@param [in]: row: row of matrix enter from keyboard
*@param [in]: col: column of matrix enter from keyboard
*
* @return:  OK: row and column are positive integer
*           NOT_OK: row and column are not positive integer
*/
char CheckSizeMatrix(int row, int col){
    if(row > 0 && col >0){
        return OK;
    }
    else{
        return NOT_OK;
    }
}

/*!
* @brief: Enter the matrix elements
*
*@param [in]: a: matrix need to enter elements
*
* @return :return a matrix
*/
MATRIX EnterMatrix(MATRIX a){
    int i;
    int j;
    for(i = 0; i < a.row; i++){
        for(j = 0; j < a.column; j++){
            scanf("%d", &a.element[i][j]);/*enter elements for matrix*/
        }
    }
    return a;
}


/*!
* @brief: Display the matrix elements
*
*@param [in]: a: matrix need to display elements
*
*/
void DisplayMatrix(MATRIX a){
    int i;
    int j;
    for(i = 0; i < a.row; i++){
        for(j = 0; j < a.column; j++){
            printf("%d ", a.element[i][j]);/*Display elements of matrix*/
        }
        printf("\n");
    }
}

/*!
* @brief: Check can two matrices add together?
*
*@param [in]: a1: matrix 1
*@param [in]: a2: matrix 2
*
* @return :return OK: can add, NOT_OK: can't add
*/
char CheckAddMatrix(MATRIX a1, MATRIX a2){
    if(a1.row == a2.row && a1.column == a2.column){
        /*if two matrices equal size, two matrices can add*/
        return OK;
    }
    else{
        /*if two matrices unequal size, two matrices can't add*/
        return NOT_OK;
    }
}

/*!
* @brief: Check can two matrices multiply together?
*
*@param [in]: a1: matrix 1
*@param [in]: a2: matrix 2
*
* @return [out]:return OK: can multiply, NOT_OK: can't multiply
*/
 char CheckMultiMatrix(MATRIX a1, MATRIX a2){
    if(a1.column == a2.row){
        /*if row of matrix 1 equal column of matrix 2 , two matrices can multiply*/
        return OK;
    }
    else{
        /*if row of matrix 1 unequal column of matrix 2 , two matrices can't multiply*/
        return NOT_OK;
    }
 }
 
/*!
* @brief: add two matrix
*
*@param [in]: a1: matrix 1
*@param [in]: a2: matrix 2
*
* @return [out]:return matrix add
*/
MATRIX AddMatrix(MATRIX a1, MATRIX a2){
    int i;
    int j;
    MATRIX a3;
    a3.row = a1.row;
    a3.column = a1.column;
    
    for(i = 0; i < a3.row; i++){
        for(j = 0; j < a3.column; j++){
            /*add element of matrix a1 and element of matrix a2 to calculate e of matrix a3*/
            a3.element[i][j] = a1.element[i][j] + a2.element[i][j];
        }
    }
    return a3;
}

/*!
* @brief: Multiply two matrices
*
*@param [in]: a1: matrix 1
*@param [in]: a2: matrix 2
*
* @return [out]:return matrix multiply
*/
MATRIX MultiMatrix(MATRIX a1, MATRIX a2){
    int i;
    int j;
    int k;
    MATRIX a3;
    a3.row = a1.row;
    a3.column = a2.column;
    
    for(i = 0; i < a3.row; i++){
        for(j = 0; j < a3.column; j++){
            a3.element[i][j] = 0;
            for(k = 0; k < a1.column; k++){
                /*Calculate elements of matrix a3*/
                a3.element[i][j] += a1.element[i][k]*a2.element[k][j];
            }
        }
    }
    return a3;
}
