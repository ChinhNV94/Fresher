#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*!
* @brief: Create fresher with informations: code number, name, score
*
* @param [in] _code: code number of fresher.
* @param [in] _account: account of fresher.
* @param [in] _name: name of fresher
* @param [in] _score: score of fresher
*
* @return [out] struct Fresher with informations [in].
*/
FRESHER CreateFr(const char *_code, const char *_account, const char *_name, float _score){
    FRESHER fr;
    /*Dynamic memory*/
    fr.code = (char*)malloc(strlen(_code)*sizeof(char));
    fr.account = (char*)malloc(strlen(_account)*sizeof(char));
    fr.name = (char*)malloc(strlen(_name)*sizeof(char));
    /*Copy string data to FRESHER*/
    strcpy(fr.code, _code);
    strcpy(fr.account, _account);
    strcpy(fr.name, _name);
    
    fr.score = _score;
    /*Return fresher*/
    return fr;
}

/*!
* @brief: Display fresher with informations: code number, name, score
*
* @param [in] fr: struct Fresher
*
* @return [out] Display: code number, name, score .
*/
void DisplayFr(FRESHER fr){
    /*Print informations of fresher: code number, name, score*/
     printf("\n%-20s%-20s%-20s%.2f", fr.code, fr.account, fr.name, fr.score);
}

/*!
* @brief: Add a fresher to first list
*
* @param [in] head: list fresher befor add
*
*/
void AddFirstL(LIST **head, FRESHER frs){
    LIST *link;
    /*Create new node of list link*/
    link = (LIST*)malloc(sizeof(LIST));
    /*Get data for node*/
    link->fr = frs;
    /*link point to list first head*/
    link->next = *head;
    /*head point to list first link*/
    *head = link;
}

/*!
* @brief: Display list fresher with informations: code number, name, score
*
* @param [in] head: list fresher need to display
*
* @return [out] Display: code number, name, score .
*/
void DisplayList(LIST *head){
    LIST *l;
    l = head;
    
    while(l != NULL){
        /*Display data of each fresher*/
        DisplayFr(l->fr);
        /*point to next node*/
        l = l->next;
    }
}

/*!
* @brief: Count length list
*
* @param [in] head: list need to count length
*
* @return [out] 0: empty list; length: not empty list.
*/
int length(LIST *head)
{
    int length = 0;
    LIST *current;
    current = head;
    
    /*Check empty list*/
    if(current == NULL){
        return 0;
    }
    
    while(current != NULL){
        /*point to node next*/
        current = current->next;
        /*Count node of list*/
        length++;
    }
    
    return length;
}

/*!
* @brief: find fresher by account
*
* @param [in] head: list fresher
* @param [in] acc: account of fresher need to find
*
* @return [out] fresher with account = acc; NULL: if acc not in list.
*/
LIST* FindMem(LIST *head, const char *acc){
    LIST *current;
    current = head;
    /*Check empty list*/
    if(head == NULL){
        return NULL;
    }
    /*Check account of fresher*/
    while(strcmp(current->fr.account, acc)){
        if(current->next == NULL){
            /*End of list return null*/
            return NULL;
        }
        else{
            /*point to node next*/
            current = current->next;
        }
    }
    return current;
}

/*!
* @brief: Insert fresher to index in list
*
* @param [in] head: list fresher
* @param [in] fr: fresher need to insert
* @param [in] _index: index to insert
*
* @return [out] 1: insert successful; 0: not insert successful
*/
int InsertAtIndex(LIST **head, FRESHER fr, int _index){
    int count;
    LIST *current;
    LIST *prev;
    LIST *temp;
    
    count = 0;
    current = *head;
    prev = NULL;
    /*Dynamic for new list*/
    temp = (LIST*)malloc(sizeof(LIST));
    
    temp->fr = fr;
    temp->next = NULL;
    
    /*Check empty list*/
    if(current == NULL){
        return 0;
    }
    
    /*point to index*/
    while(count != _index){
        if(current->next == NULL){
            return 0;
        }
        else{
            prev = current;
            /*point to next*/
            current = current->next;
            /*cuont to check index*/
            count++;
        }
    }
    
    if(current == (*head)){
        /*Add to index 0*/
        AddFirstL(head, fr);
        return 1;
    }
    else{
        /*link previous node to need to insert*/
        prev->next = temp;
        /*link node to need to insert to current*/
        temp->next = current;
        return 1;
    }
}

/*!
* @brief: Remove fresher by account
*
* @param [in] head: list fresher
* @param [in] acc: account of fresher need to remove
*
* @return [out] 1: remove successful; 0: not remove successful
*/
int RemoveByAcc(LIST **head, const char *acc){
    LIST *current;
    LIST *prev;
    
    current = *head;
    prev = NULL;
    /*Check empty list*/
    if(head == NULL){
        return 0;
    }
    
    /*Find fresher equal account*/
    while(strcmp(current->fr.account, acc)){
        if(current->next == NULL){
            return 0;
        }
        else{
            prev = current;
            current = current->next;
        }
    }
    
    /*Fresher first of list*/
    if(current == (*head)){
        /*point to next node*/
        *head = (*head)->next;
    }
    else{
        /*link previous to next node to remove current node*/
        prev->next = current->next;
    }
    /*free memory of pointer current*/
    free(current);
    return 1;
}

/*!
* @brief: Remove fresher at index _index in list
*
* @param [in] head: list fresher
* @param [in] _index: index of fresher need to remove
*
* @return [out] 1: remove successful; 0: not remove successful
*/
int RemoveAtIndex(LIST **head, int _index){
    int count;
    LIST *current;
    LIST *prev;
    
    count = 0;
    current = *head;
    prev = NULL;
    /*Check empty list*/
    if(current == NULL){
        return 0;
    }
    /*point to index*/
    while(count != _index){
        if(current->next == NULL){
            /*End of node return 0*/
            return 0;
        }
        else{
            /*point to next node*/
            prev = current;
            current = current->next;
            /*count to check index*/
            count++;
        }
    }
    
    /*Fresher first of list*/
    if(current == (*head)){
        /*point to next node*/
        *head = (*head)->next;
    }
    else{
        /*link previous to next node to remove current node*/
        prev->next = current->next;
    }
    /*free memory of pointer current*/
    free(current);
    return 1;
}

/*!
* @brief: sort list fresher follow name: a, b, c...
*
* @param [in] head: list fresher need to sort
*
* @return [out] 1: sort successful; 0: not sort successful
*/
int SortNameASC(LIST **head){
    int i;
    int j;
    int k;
    int size;
    FRESHER tempFr;
    LIST *p_current;
    LIST *p_next;
    
    size = length(*head);
    /*Check not empty list*/
    if(size){
        k = size;
        /*Bubble sort*/
        for(i = 0 ; i < size - 1 ; i++, k-- ){
            p_current = *head ;
            p_next = (*head)->next ;
            
            for (j = 1 ; j < k ; j++ ){   
                /*check name of current fresher lager name of next fresher*/
                if(strcmp(p_current->fr.name, p_current->next->fr.name) > 0){
                    /*swap node*/
                    tempFr = p_current->fr;
                    p_current->fr = p_next->fr;
                    p_next->fr = tempFr;
                }
                /*point to next node*/
                p_current = p_current->next;
                p_next = p_next->next;
            }
        }  
        return 1;
    }
    else{
        return 0;
    }
}

/*!
* @brief: sort list fresher follow name descending
*
* @param [in] head: list fresher need to sort
*
* @return [out] 1: sort successful; 0: not sort successful
*/
int SortNameDESC(LIST **head){
    int i;
    int j;
    int k;
    int size;
    FRESHER tempFr;
    LIST *p_current;
    LIST *p_next;
    
    size = length(*head);
    /*Check not empty list*/
    if(size){
        k = size;
    
        for(i = 0 ; i < size - 1 ; i++, k-- ){
            p_current = *head ;
            p_next = (*head)->next ;
            
            for (j = 1 ; j < k ; j++ ){   
                /*check name of current fresher less name of next fresher*/
                if(strcmp(p_current->fr.name, p_current->next->fr.name) < 0){
                    /*swap node*/
                    tempFr = p_current->fr;
                    p_current->fr = p_next->fr;
                    p_next->fr = tempFr;
                }
                /*point to next node*/
                p_current = p_current->next;
                p_next = p_next->next;
            }
        }  
        return 1;
    }
    else{
        return 0;
    }
}

/*!
* @brief: sort list fresher follow score ascending;
*
* @param [in] head: list fresher need to sort
*
* @return [out] 1: sort successful; 0: not sort successful
*/
int SortScoreASC(LIST **head){
    int i;
    int j;
    int k;
    int size;
    FRESHER tempFr;
    LIST *p_current;
    LIST *p_next;
    
    size = length(*head);
    /*Check not empty list*/
    if(size){
        k = size;
    
        for(i = 0 ; i < size - 1 ; i++, k-- ){
            p_current = *head ;
            p_next = (*head)->next ;
            
            for (j = 1 ; j < k ; j++ ){   
                /*check score of current fresher lager score of next fresher*/
                if(p_current->fr.score > p_current->next->fr.score){
                    /*swap node*/
                    tempFr = p_current->fr;
                    p_current->fr = p_next->fr;
                    p_next->fr = tempFr;
                }
                /*point to next node*/
                p_current = p_current->next;
                p_next = p_next->next;
            }
        }
        return 1;
    }
    return 0;
}

/*!
* @brief: sort list fresher follow score descending;
*
* @param [in] head: list fresher need to sort
*
* @return [out] 1: sort successful; 0: not sort successful
*/
int SortScoreDESC(LIST **head){
    int i;
    int j;
    int k;
    int size;
    FRESHER tempFr;
    LIST *p_current;
    LIST *p_next;
    
    size = length(*head);
    /*Check not empty list*/
    if(size){
        k = size;
    
        for(i = 0 ; i < size - 1 ; i++, k-- ){
            p_current = *head ;
            p_next = (*head)->next ;
            
            for (j = 1 ; j < k ; j++ ){   
                /*check score of current fresher less score of next fresher*/
                if(p_current->fr.score < p_current->next->fr.score){
                    /*swap node*/
                    tempFr = p_current->fr;
                    p_current->fr = p_next->fr;
                    p_next->fr = tempFr;
                }
                /*point to next node*/
                p_current = p_current->next;
                p_next = p_next->next;
            }
        }
        return 1;
    }
    return 0;
}


