#ifndef CARDPROCESSING_H
#define CARDPROCESSING_H
#include "dlist.h"
void inputcardfromfile(DList* list,char* filename);
void processingcard(DList* list, DList* card, DList* string);
void sortcardinsert(DList* list, DListNode* curr);
#endif 