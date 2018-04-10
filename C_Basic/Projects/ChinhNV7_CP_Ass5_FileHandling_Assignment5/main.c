#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "fsrec.h"


int main(){
    FILE *pFile;
    
    parse_data_struct_t Output;
    
    uint8_t buffer[156];
    uint8_t i;
    uint8_t datalen;
    uint8_t count;
    uint8_t checksum;
    uint16_t status;
    /*open file to read*/
    pFile = fopen("filehandling.srec", "r");
    if(pFile == NULL){
        perror("Error opening file");
    }
    else{
        while(fgets(buffer, 156, pFile) != NULL){
            printf("Line:");
            /*print srec line*/
            puts(buffer);
            /*Calulate checksum*/
            checksum = checkSum(buffer);
            /*check checksum*/
            if(checksum == 255)
            {
                /*parse data*/
                status = parseData(buffer, &Output);
                if(status != e_parseStatus_error)
                {
                    /*print address*/
                    printf("Address: %x\n", Output.address);
                    printf("Data:        ");
                    datalen = Output.dataLength;
                    /*print data*/
                    for(i = 0; i < datalen; i++)
                    {
                        printf("%02x ", Output.data[i]);
                    }
                    printf("\nData length: %d", datalen);
                    
                    /*print status*/
                    switch(status)
                    {
                        case e_parseStatus_start:
                            printf("\nStatus: START");
                            break;
                        case e_parseStatus_inprogress:
                            printf("\nStatus: INPROGRESS");
                            break;
                        case e_parseStatus_done:
                            printf("\nStatus: DONE");
                            break;
                        default:
                            break;
                    }
                    printf("\n\n\n");
                }
                else{
                    printf("Converted data error!\n");
                }
            }
            else
            {
                printf("Check sum error!\n");
            }
        }
        fclose(pFile);
    }
	
    return 0;
}
