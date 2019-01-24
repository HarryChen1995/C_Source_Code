
#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include "cardprocessing.h"
/* this function is to read valid card from input text file and valid file contain only one blank
   which it has more than three underscore and assign those valid card into the card link list
*/
void inputcardfromfile(DList* list, char* filename) {
	FILE* input = NULL; char line[1024]; int i = 0; int blank = 0; int underscore = 0; DListNode* a = NULL;
	int index = 0;// declare the varible 
	input = fopen(filename, "r");
	while (!feof(input)) {
		if (fgets(line, 1024, input) == NULL) {
			break;
		}
		i = 0; blank = 0; 	a = NULL; 
		underscore = 0; index = 0;
		for (i = 0; i < strlen(line); i++) {// this for loop is to read number of blank in each single string 
			if ((i != (strlen(line) - 1)) && (line[i] == '_') && (line[i + 1] != '_')) {
				blank++;
			}
			else if (i == (strlen(line) - 1) && line[i] == '_') {// condtion when the i reach the end of line 
				blank++;
			}
		}
	
		if (blank == 1) {
			for (i = 0; i < strlen(line); i++) {// this for loop is to count number of the underscore in each line and assign the first index of underscore into card list
				if (line[i] == '_') {
					underscore=underscore+1;
					if ((i != strlen(line) - 1) && (line[i] == '_') && (line[i + 1] != '_')) {
						index = i - underscore + 1;
					}
					else if ((i== strlen(line) - 1) && (line[i] == '_')) {
						index = i - underscore + 1;
					}
				}
	}

			if (underscore>=3) {// assign the valid card into the list 
				a = NULL;
				a = (DListNode*)malloc(sizeof(DListNode));
				a->str = (char*)malloc((strlen(line) + 1)*sizeof(char));// allocate the char array for str variable
				strtok(line, "\n");
                strtok(line,"\r");
				strcpy(a->str, line);
				a->blankLength = underscore;
				a->blankIndex = index;
				DListInsertAfter(list, list->tail, a);
			}
		}
	}
	fclose(input);

}
/* this function is to insert the proccessed card into the processed card link list in oder of char length from 
shor to long. 
*/
void sortcardinsert(DList* list, DListNode* curr) {
	DListNode* temp = NULL; DListNode *temp2 = NULL; int flag = 0;
	if (list->size == 0) {// if the list is empty insert it  at head 
		DListInsertAfter(list, list->head, curr);
	}
	else if (list->size == 1) {// if the list contain only one node, compare it with current node 
		if (strlen(curr->str) < strlen(list->head->str)) {
			DListInsertBefore(list, list->head, curr);
		}

		else if (strlen(curr->str) >= strlen(list->head->str)) {
			DListInsertAfter(list, list->head, curr);
		}

	}
	else{// when list contain more than two node. 
		temp = list->head; flag = 0;
       while (temp != NULL) {
			if (strlen(curr->str) < strlen(temp->str)) {
				flag = 1;
				DListInsertBefore(list, temp, curr);
				break;
			}
			temp = temp->next;
		}
		if (flag == 0) {
			temp2 = list->tail;
			while (temp2 != NULL) {
				if (strlen(curr->str) >= strlen(temp2->str)) {
					DListInsertAfter(list, temp2, curr);
					break;
				}
				temp2 = temp2->prev;
			}
		}
}
	
}
/*this function is to the prcessed the valid card and string together 
  after each string has successfully processed, it should removed from the string link list.
*/
void processingcard(DList* list, DList* card, DList* string) {
	DListNode* a = NULL; DListNode* b = NULL; int i = 0; char line1[1042]; char line2[1024]; DListNode* c = NULL; DListNode* t = NULL;
	a = card->head; b = string->head; // aisgn card list and string list to traverse 
	while (a != NULL) {
		b = string->head;
		while (b != NULL) {
			if ((b->blankLength == a->blankLength)) {
				c = NULL; t = NULL;
				c = (DListNode*)malloc(sizeof(DListNode));
				strcpy(line1, a->str);
				strcpy(line2, b->str);
				for (i = 0; i < a->blankLength; i++) {// inser the mathces string into the blank 
					line1[a->blankIndex + i] = line2[i];
				}
				c->str = (char*)malloc((strlen(line1) + 1)*sizeof(char));
				strcpy(c->str, line1);
				sortcardinsert(list,c);
				t = b;
				DListRemove(string, t);// remove the string from the list if it is valid.
				break;// break the while loop and restart from the next input valid card.
			}
			else {
				b = b->next;
			}
		}
	  a = a->next;
	}
	
}


