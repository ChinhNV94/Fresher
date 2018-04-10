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
    
    /*Dynamic memory for pointer management matrix a*/
    a = DynamicMatrix(a);
    
    /*Enter row an column for matrix b*/
    printf("\nMatrix B ROW: ");
    scanf("%d", &b.row);
    printf("\nMatrix B COL: ");
    scanf("%d", &b.column);
    
    /*Dynamic memory for pointer management matrix b*/
    b = DynamicMatrix(b);
    
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

    /*Free pointer management matrix a*/
    FreeMatrix(a);
    
    /*Free pointer management matrix b*/
    FreeMatrix(b);

    return 0;
}
