#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"


int main(){
    
    LIST *head;
    
    FRESHER fr[5];
    char *code = "Code number";
    char *account = "Account";
    char *name = "Name";
    char *score = "Score";
    
    /*Create data for fresher*/
    fr[0] = CreateFr("11111", "Chinhnv7", "Chinh", 7.5);
    fr[1] = CreateFr("22222", "Tiepnv", "Tiep", 8.5);
    fr[2] = CreateFr("33333", "Huynv", "Huy", 9.5);
    fr[3] = CreateFr("44444", "Hungnv", "Hung", 7.0);
    fr[4] = CreateFr("55555", "Tanvn", "Tan", 8.0);
    
    head = NULL;
    
    /*Add fresher to first list*/
    AddFirstL(&head, fr[0]);
    AddFirstL(&head, fr[1]);
    AddFirstL(&head, fr[2]);
    AddFirstL(&head, fr[3]);
    AddFirstL(&head, fr[4]);

    /*Print list*/
    printf("\nList:");
    printf("\n%-20s%-20s%-20s%-20s", code, account, name, score);
    DisplayList(head);
    
    /*Sort list follow name ascending*/
    SortNameASC(&head);
    /*Print list*/
    printf("\n\nList sort name ASC:");
    printf("\n%-20s%-20s%-20s%-20s", code, account, name, score);
    DisplayList(head);
    
    /*Sort list follow name ascending*/
    SortNameDESC(&head);
    /*Print list*/
    printf("\n\nList sort name DESC:");
    printf("\n%-20s%-20s%-20s%-20s", code, account, name, score);
    DisplayList(head);
    
    /*Sort list score ascending*/
    SortScoreASC(&head);
    /*Print list*/
    printf("\n\nList sort score ASC:");
    printf("\n%-20s%-20s%-20s%-20s", code, account, name, score);
    DisplayList(head);
    
    /*Sort list score ascending*/
    SortScoreDESC(&head);
    /*Print list*/
    printf("\n\nList sort score DESC:");
    printf("\n%-20s%-20s%-20s%-20s", code, account, name, score);
    DisplayList(head);
    
    /*Remove fresher with account "ChinhNV7"*/
    RemoveByAcc(&head, "Chinhnv7");
    /*Print list*/
    printf("\n\nList after remove: Chinhnv7");
    printf("\n%-20s%-20s%-20s%-20s", code, account, name, score);
    DisplayList(head);
    
    /*Remove fresher at index 1*/
    RemoveAtIndex(&head, 1);
    /*Print list*/
    printf("\n\nList after remove at index 1:");
    printf("\n%-20s%-20s%-20s%-20s", code, account, name, score);
    DisplayList(head);
    
    /*Insert fresher to list at index 0*/
    InsertAtIndex(&head, fr[0], 0);
    /*Print list*/
    printf("\n\nfr[0]:");
    DisplayFr(fr[0]);
    printf("\n\nList after insert fr[0] at index 0:");
    printf("\n%-20s%-20s%-20s%-20s", code, account, name, score);
    DisplayList(head);
    
    return 0;
}
