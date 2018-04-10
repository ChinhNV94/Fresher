#include <stdio.h>
#include <math.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define OK      1
#define NOT_OK  0


/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
* @brief: Calculate Acreage of rectangle
*
*@param [in]: perimeter: perimeter of rectangle
*@param [in]: diagonal: diagonal line of rectangle
*
* @return :return   Acreage: if Acreage > 0 
*                   NOT_OK: if Acreage < 0
*/

float CalculateAcreage(float perimeter, float diagonal){
    /*  perimeter = 2(a + b) => perimeter^2 = 4(a^2 + b^2 + 2ab)
        diagonal^2 = a^2 + b^2
        => Acreage = ab = (perimeter^2/4 - diagonal^2)/2
    */
    float Acreage;
    Acreage = (pow(perimeter, 2)/4 - pow(diagonal, 2))/2;
    if(Acreage > 0){
        return Acreage;
    }
    else{
        return NOT_OK;
    }
}

/*!
* @brief: Check perimeter and diagonal line of rectangle
*
*@param [in]: perimeter: perimeter of rectangle
*@param [in]: diagonal: diagonal line of rectangle
*
* @return :return   OK: if perimeter > 0 && diagonal > 0 
*                   NOT_OK: if perimeter < 0 || diagonal < 0
*/

int Check(float perimeter, float diagonal){
    if(perimeter > 0 && diagonal > 0){
        return OK;
    }
    else{
        return NOT_OK;
    }
}

int main(void){
    float perimeter;
    float diagonal;
    float Acreage;
    
    /*Enter perimeter and diagonal line of rectangle*/
    scanf("%f", &perimeter);
    scanf("%f", &diagonal);
    
    /*Check perimeter and diagonal line of rectangle*/
    if(!Check(perimeter, diagonal)){
        /*if perimeter < 0 || diagonal < 0 print and exit*/
        printf("The value inputs are not valid, please re-enter new inputs");
        return 0;
    }
    
    /*Calculate Acreage of rectangle*/
    Acreage = CalculateAcreage(perimeter, diagonal);
    
    if(Acreage){
        /*if if Acreage > 0*/
        printf("S = %f",Acreage);
    }
    else{
        /*if if Acreage < 0*/
        printf("The value inputs are not valid, please re-enter new inputs");
    }
    
    return 0;
}
