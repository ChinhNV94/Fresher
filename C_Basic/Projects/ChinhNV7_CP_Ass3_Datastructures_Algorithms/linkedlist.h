#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_


/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef struct Fresher{
    char *name;
    char *code;
    char *account;
    float score;
}FRESHER;

typedef struct List{
    FRESHER fr;
    struct List *next;
}LIST;


/*******************************************************************************
* API
******************************************************************************/
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
FRESHER CreateFr(const char *_code, const char *_account, const char *_name, float _score);

/*!
* @brief: Display fresher with informations: code number, name, score
*
* @param [in] fr: struct Fresher
*
* @return [out] Display: code number, name, score .
*/
void DisplayFr(FRESHER fr);

/*!
* @brief: Add a fresher to first list
*
* @param [in] head: list fresher befor add
*
*/
void AddFirstL(LIST **head, FRESHER frs);

/*!
* @brief: Display list fresher with informations: code number, name, score
*
* @param [in] head: list fresher need to display
*
* @return [out] Display: code number, name, score .
*/
void DisplayList(LIST *head);

/*!
* @brief: Count length list
*
* @param [in] head: list need to count length
*
* @return [out] 0: empty list; length: not empty list.
*/
int LengthList(LIST *head);

/*!
* @brief: find fresher by account
*
* @param [in] head: list fresher
* @param [in] acc: account of fresher need to find
*
* @return [out] fresher with account = acc; NULL: if acc not in list.
*/
LIST* FindMem(LIST *head, const char *acc);

/*!
* @brief: Insert fresher to index in list
*
* @param [in] head: list fresher
* @param [in] fr: fresher need to insert
* @param [in] _index: index to insert
*
* @return [out] 1: insert successful; 0: not insert successful
*/
int InsertAtIndex(LIST **head, FRESHER fr, int _index);

/*!
* @brief: Remove fresher by account
*
* @param [in] head: list fresher
* @param [in] acc: account of fresher need to remove
*
* @return [out] 1: remove successful; 0: not remove successful
*/
int RemoveByAcc(LIST **head, const char *acc);

/*!
* @brief: Remove fresher at index _index in list
*
* @param [in] head: list fresher
* @param [in] _index: index of fresher need to remove
*
* @return [out] 1: remove successful; 0: not remove successful
*/
int RemoveAtIndex(LIST **head, int _index);

/*!
* @brief: sort list fresher follow name: a, b, c...
*
* @param [in] head: list fresher need to sort
*
* @return [out] 1: sort successful; 0: not sort successful
*/
int SortNameASC(LIST **head);

/*!
* @brief: sort list fresher follow name descending
*
* @param [in] head: list fresher need to sort
*
* @return [out] 1: sort successful; 0: not sort successful
*/
int SortNameDESC(LIST **head);

/*!
* @brief: sort list fresher follow score ascending;
*
* @param [in] head: list fresher need to sort
*
* @return [out] 1: sort successful; 0: not sort successful
*/
int SortScoreASC(LIST **head);

/*!
* @brief: sort list fresher follow score descending;
*
* @param [in] head: list fresher need to sort
*
* @return [out] 1: sort successful; 0: not sort successful
*/
int SortScoreDESC(LIST **head);
 
#endif
