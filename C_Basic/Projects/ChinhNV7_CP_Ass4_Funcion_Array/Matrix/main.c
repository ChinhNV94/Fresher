#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main(){
    MATRIX a;
    MATRIX b;
    
    /*Enter row an column for matrix a*/
    printf("\nMatrix A ROW: ");
    scanf("%d", &a.row);
    printf("\nMatrix A COL: ");
    scanf("%d", &a.column);
    
    /*Check size of matrix a if row and column are not positive integer exit*/
    if(!CheckSizeMatrix(a.row, a.column)){
        return 0;
    }
    
    /*Check size of matrix b if row and column are not positive integer exit*/
    printf("\nMatrix B ROW: ");
    scanf("%d", &b.row);
    printf("\nMatrix B COL: ");
    scanf("%d", &b.column);
    
    /*Check size of matrix b*/
    if(!CheckSizeMatrix(b.row, b.column)){
        return 0;
    }
    
   /*Enter matrix a*/
    printf("\nMatrix A:\n");
    a = EnterMatrix(a);
    
    /*Enter matrix b*/
    printf("\nMatrix B:\n");
    b = EnterMatrix(b);
    
    /*Clear screen*/
    system("cls");
    
    /*Check can two matrices add together? and print report*/
    if(CheckAddMatrix(a, b)){
        printf("\nMatrix A, Matrix B can add together");
    }
    else{
        printf("\nMatrix A, Matrix B can't add together");
    }
    
    /*Check can matrix a multiply matrix b? and print report*/
    if(CheckMultiMatrix(a, b)){
        printf("\nMatrix A, Matrix B can multi together");
    }
    else{
        printf("\nMatrix A, Matrix B can't multi together");
    }
    
    /*Check can matrix b multiply matrix a? and print report*/
    if(CheckMultiMatrix(b, a)){
        printf("\nMatrix B, Matrix A can multi together");
    }
    else{
        printf("\nMatrix B, Matrix A can't multi together");
    }
    
    /*Display matrix a*/
    printf("\n\nMatrix A:\n");
    DisplayMatrix(a);
    
    /*Display matrix b*/
    printf("\nMatrix B:\n");
    DisplayMatrix(b);
    
    /*Display matrix a + matrix b*/
    printf("\nMatrix A + Matrix B:\n");
    if(CheckAddMatrix(a, b)){
        DisplayMatrix(AddMatrix(a, b));
    }
    else{
        printf("N/A\n");
    }
    
    /*Display matrix a * matrix b*/
    printf("\nMatrix A * Matrix B:\n");
    if(CheckMultiMatrix(a, b)){
        DisplayMatrix(MultiMatrix(a, b));
    }
    else{
        printf("N/A\n");
    }
    
    /*Display matrix b * matrix a*/
    printf("\nMatrix B * Matrix A:\n");
    if(CheckMultiMatrix(b, a)){
        DisplayMatrix(MultiMatrix(b, a));
    }
    else{
        printf("N/A\n");
    }

    return 0;
}
