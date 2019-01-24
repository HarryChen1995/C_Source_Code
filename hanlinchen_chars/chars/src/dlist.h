/*******************************************************************************************/

/*
* File: dlist.h
* Author: Your Name
* NetID: Your NetID
* Date:
*
* Description: (enter your description of what this file does)
*
*/

/*******************************************************************************************/

/* Note: comments in this file thus far are insufficient for a perfect grade in comments */

/*******************************************************************************************/

#ifndef DLIST_H
#define DLIST_H

/*******************************************************************************************/

/* if the str does not contain a blank, then blankIndex and blankLength should be -1 */
typedef struct DListNode_struct {
	char *str;
	int blankIndex;
	int blankLength;
	struct DListNode_struct *next;
	struct DListNode_struct *prev;
} DListNode;

typedef struct DList_struct {
	int size;
	DListNode *head;
	DListNode *tail;
} DList;

/*******************************************************************************************/

/* creates a new list and initializes the head/tail */
void DListConstruct(DList* list);

/* removes all items from the list, deallocating each item */
void DListDestruct(DList* list);

/* inserts newNode after the given currNode */
void DListInsertAfter(DList* list, DListNode* currNode, DListNode* newNode);

/* inserts newNode before the given currNode */
void DListInsertBefore(DList* list, DListNode* currNode, DListNode* newNode);

/* return the first list node to match key */
DListNode* DListSearch(DList* list, char* key);

/* remove the list node (if it is a member of the list) */
void DListRemove(DList* list, DListNode* currNode);

/*******************************************************************************************/

#endif // DLIST_H