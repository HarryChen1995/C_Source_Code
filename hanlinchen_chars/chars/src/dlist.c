/*******************************************************************************************/

/*
* File: dlist.c
* Author: hanlinchen
* NetID: hanlinchen@email.arizona.edu
* Date:2/21/2016
*
* Description: (this c file contains functions that manipulate double linked list such as delete,insert,prepend,append,and key research )
*
*/

/*******************************************************************************************/

/* Note: comments in this file thus far are insufficient for a perfect grade in comments */

/*******************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "dlist.h"

/*******************************************************************************************/

/* creates a new list and initializes the head/tail */

void DListConstruct(DList* list) { // creat the list structure 

	list->head = NULL; // initalize the head to NULL
	list->tail = NULL;// initalize the tial to NULL 
	list->size = 0; // assign zero as element size

}

/*******************************************************************************************/

/* removes all items from the list, deallocating each item */

void DListDestruct(DList* list) {
	DListNode* currNode = NULL;
	while (list->head != NULL) { // delete the node from head to tail 
		currNode = list->head;
		list->head = currNode->next;
		free(currNode);
	}
	list->size = 0;
}

/*******************************************************************************************/

/* inserts newNode after the given currNode */

void DListInsertAfter(DList* list, DListNode* currNode, DListNode* newNode) {
	newNode->next = NULL;
	newNode->prev = NULL;
	DListNode* sucNode = NULL;
	sucNode = (DListNode*)malloc(sizeof(DListNode));
	if (list->head == NULL) {
		list->head = newNode;
		list->tail = newNode;
	}
	else if (currNode == list->tail) {
		list->tail->next = newNode;
		newNode->prev = list->tail;
		list->tail = newNode;
	}
	else {
		sucNode = currNode->next;
		newNode->next = sucNode;
		newNode->prev = currNode;
		currNode->next = newNode;
		sucNode->prev = newNode;
	}
	list->size = list->size + 1;
}

/*******************************************************************************************/

/* inserts newNode before the given currNode */

void DListInsertBefore(DList* list, DListNode* currNode, DListNode* newNode) {
	newNode->next = NULL;
	newNode->prev = NULL;
	DListNode* preNode = NULL;
	if (list->head == NULL) {
		list->head = newNode;
		list->tail = newNode;
	}
	else if (currNode == list->head) {
		newNode->next = list->head;
		list->head->prev = newNode;
		list->head = newNode;
	}
	else {
		preNode = currNode->prev;
		newNode->next = currNode;
		newNode->prev = preNode;
		currNode->prev = newNode;
		preNode->next = newNode;
	}
	list->size = list->size + 1;
}

/*******************************************************************************************/

/* return the first list node to match key */

DListNode* DListSearch(DList* list, char* key) {
	DListNode* currNode = NULL;
	currNode = list->head;
	while (currNode != NULL) {
		if (currNode->str == key) {
			return currNode;
		}
		currNode = currNode->next;
	}
	return NULL;
}

/*******************************************************************************************/

/* remove the list node (if it is a member of the list) */

void DListRemove(DList* list, DListNode* currNode) {
	DListNode* sucNode = NULL;  DListNode* predNode = NULL;
	sucNode = currNode->next;
	predNode = currNode->prev;

	if (sucNode != NULL) {
		sucNode->prev = predNode;
	}

	if (predNode != NULL) {
		predNode->next = sucNode;
	}

	if (currNode == list->head) { // Removed head
		list->head = sucNode;
	}

	if (currNode == list->tail) { // Removed tail
		list->tail = predNode;
	}
	list->size = list->size - 1;
	free(currNode);
}

/*******************************************************************************************/
